Title:  Writing a Scheduler Plugin: Step 5
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 5: Adding P-EDF scheduling logic
=====================================

Step 4 covered adding necessary state variables to our plugin, so we're now ready to define how the DEMO plugin selects the task that should be scheduled next. Since we're implementing a P-EDF scheduler, we will use the `edf_preemption_needed()` function from `litmus/edf_common.h` to determine when the previous task should be preempted.

{{TOC}}

## More headers related to job parameters and budgets

Add the following two includes to the list at the start of `sched_demo.c`:

```C
#include <litmus/jobs.h>
#include <litmus/budget.h>
```

We will need these headers when managing job- and budget- related information in the scheduler.

## Adding helper functions

Before diving into the scheduling function, we are going to define two helper functions that will aid in preventing the `schedule()` implementation from becoming too convoluted.

The first helper, `demo_job_completion()`, is called to process a job when it the job completes. In this simple example, it simply delegates all of the work to the common helper, `prepare_for_next_period()`, declared in `litmus/jobs.h`. In more complicated scheduling policies, additional housekeeping code to be run on job completions may be put here.

```C
/* This helper is called when task `prev` exhausted its budget or when
 * it signaled a job completion. */
static void demo_job_completion(struct task_struct *prev, int budget_exhausted)
{
        /* Call common helper code to compute the next release time, deadline,
         * etc. */
        prepare_for_next_period(prev);
}
```

Next, we add the `demo_requeue()` helper function. It is used to place a task on the appropriate queue. If the task has a pending job, it is placed in the (core-local) ready queue. Otherwise, if the next job's earliest release time is in the future, the task will be placed in the (also core-local) release queue.

```C
/* Add the task `tsk` to the appropriate queue. Assumes the caller holds the ready lock.
 */
static void demo_requeue(struct task_struct *tsk, struct demo_cpu_state *cpu_state)
{
        if (is_released(tsk, litmus_clock())) {
                /* Uses __add_ready() instead of add_ready() because we already
                 * hold the ready lock. */
                __add_ready(&cpu_state->local_queues, tsk);
        } else {
                /* Uses add_release() because we DON'T have the release lock. */
                add_release(&cpu_state->local_queues, tsk);
        }
}
```

Note that `demo_requeue()` uses `__add_ready()`, but not `__add_release()`. This is because `demo_requeue()` will be called only from contexts where the calling thread already holds the lock for the ready queue.

## Adding scheduling logic

Finally, we can define the P-EDF scheduling logic. Conceptually, it follows these three steps:

 1. Checks what state the previously scheduled real-time task is in (if any)
 2. Checks whether a higher-priority job is waiting in the ready queue (i.e., if a preemption is required)
 3. Returns the next task to be scheduled (which may be NULL if there is no real-time workload pending)

The scheduler is serialized (with respect to each core) using the ready queue lock `local_state->local_queues.ready_lock`. Reusing the ready queue lock to serialize scheduling decisions is a common idiom in LITMUS^RT. Alternatively, we could also define an additional spinlock inside `struct demo_cpu_state`.

Modify the `demo_schedule` function to contain the following content:

```C
static struct task_struct* demo_schedule(struct task_struct * prev)
{
        struct demo_cpu_state *local_state = local_cpu_state();

        /* next == NULL means "schedule background work". */
        struct task_struct *next = NULL;

        /* prev's task state */
        int exists, out_of_time, job_completed, self_suspends, preempt, resched;

        raw_spin_lock(&local_state->local_queues.ready_lock);

        BUG_ON(local_state->scheduled && local_state->scheduled != prev);
        BUG_ON(local_state->scheduled && !is_realtime(prev));

        exists = local_state->scheduled != NULL;
        self_suspends = exists && !is_current_running();
        out_of_time = exists && budget_enforced(prev) && budget_exhausted(prev);
        job_completed = exists && is_completed(prev);

        /* preempt is true if task `prev` has lower priority than something on
         * the ready queue. */
        preempt = edf_preemption_needed(&local_state->local_queues, prev);

        /* check all conditions that make us reschedule */
        resched = preempt;

        /* if `prev` suspends, it CANNOT be scheduled anymore => reschedule */
        if (self_suspends) {
                resched = 1;
        }

        /* also check for (in-)voluntary job completions */
        if (out_of_time || job_completed) {
                demo_job_completion(prev, out_of_time);
                resched = 1;
        }

        if (resched) {
                /* First check if the previous task goes back onto the ready
                 * queue, which it does if it did not self_suspend.
                 */
                if (exists && !self_suspends) {
                        demo_requeue(prev, local_state);
                }
                next = __take_ready(&local_state->local_queues);
        } else {
                /* No preemption is required. */
                next = local_state->scheduled;
        }

        local_state->scheduled = next;
        if (exists && prev != next) {
                TRACE_TASK(prev, "descheduled.\n");
        }
        if (next) {
                TRACE_TASK(next, "scheduled.\n");
        }

        /* This mandatory. It triggers a transition in the LITMUS^RT remote
         * preemption state machine. Call this AFTER the plugin has made a local
         * scheduling decision.
         */
        sched_state_task_picked();

        raw_spin_unlock(&local_state->local_queues.ready_lock);
        return next;
}
```

The scheduler is serialized by obtaining the obtaining the ready queue lock: `raw_spin_lock(&local_state->local_queues.ready_lock)`. Note that interrupts are already disabled when a scheduler plugin's `schedule` callback is invoked, so we do not have to worry about local interrupts within `demo_schedule()`.

The `BUG_ON` lines assert that the following invariant holds: when a real-time task is scheduled on the local core, then it is pointed to by `local_state->scheduled`, and if no real-time task is scheduled, then `local_state->scheduled` is `NULL`. Note that `prev` may refer to a non-real-time task.

The next lines establish the state of `prev`:

 - `exists` is true if the previous task is a real-time task.
 - `self_suspends` is true if `prev` cannot be scheduled any longer.
 - `out_of_time` is true if the current job overran its budget.
 - `job_completed` is true if the current job signaled completion via syscall.

The call to `edf_preemption_needed` checks whether higher-priority work is pending (i.e., jobs with earlier deadlines) on the local ready queue.

The next few lines determine whether a preemption / scheduling decision is required. No change in scheduling is required if the previous task does not self-suspend or complete and if no higher-priority work is pending. Note that this involves calling the `demo_job_completion()` helper function, which is simply a wrapper around `prepare_for_next_period`, as described above.

The final lines carry out the actual scheduling decision. If `prev` needs to be preempted (in the `if (resched)` block), then the previous task is requeued (if required) using `demo_requeue` and a new task is taken from the ready queue. Otherwise, `next` is simply the locally scheduled task, `local_state->scheduled`, which may be `NULL`. The "local state invariant" is maintained by the `local_state->scheduled = next` assignment.

## Testing

With these changes in place, the kernel should compile and boot without problems. However, scheduling is still not possible because all tasks are still being rejected. Before tasks can be accepted, however, we need to add support for task state changes (i.e., self-suspensions).

<div class="nav">
[Previous: Step 4 - Per-CPU state](plugin_step_4.html) -
[Next: Step 6 - Task state changes](plugin_step_6.html)
</div>
