Title:  Writing a Scheduler Plugin: Step 7
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 7: Adding preemption checks
================================

The scheduling logic so far selects the next job to be scheduled using EDF priorities whenever the scheduler is invoked. However, the scheduler still does not implement _preemptive_ EDF scheduling because it is not automatically invoked when a new job is released. In this step, we are going to rectify this by adding a preemption check callback to the real-time domain `local_queues` embedded in `struct demo_cpu_state`.

{{TOC}}

## Preemption check callback

The preemption check callback is invoked by the `rt_domain_t` code whenever a job is transferred from the release queue to the ready queue (i.e., when a future release is processed). Since the callback is invoked from within the `rt_domain_t` code, the calling thread already holds the ready queue lock.

The necessary logic is contained in the following callback function, which should be added somehwere before the `demo_activate_plugin` function to `sched_demo.c`:

```C
static int demo_check_for_preemption_on_release(rt_domain_t *local_queues)
{
        struct demo_cpu_state *state = container_of(local_queues, struct demo_cpu_state,
                                                    local_queues);

        /* Because this is a callback from rt_domain_t we already hold
         * the necessary lock for the ready queue. */

        if (edf_preemption_needed(local_queues, state->scheduled)) {
                preempt_if_preemptable(state->scheduled, state->cpu);
                return 1;
        }
        return 0;
}
```

The preemption check first extracts the containing `struct demo_cpu_state` from the `rt_domain_t` pointer using Linux's standard macro `container_of()`. It then checks whether the ready queue contains a job that has higher priority (an earlier deadline) than the currently scheduled job (if any). If this is the case, then an invocation of the scheduler is triggered with the `preempt_if_preemptable()` function. This LITMUS^RT helper function is a wrapper around Linux's preemption mechanism and transparently works for both remote cores and the local core.

Note that `state->scheduled` may be `NULL`; this case is transparently handled by `preempt_if_preemptable()`. (The `...if_preemptable()` suffix of the function refers to non-preemptive section support and is of no relevance to this tutorial.)

## Updating the plugin initialization function

The preemption check callback must be passed to the `edf_domain_init()` function during plugin initialization. Modify `demo_activate_plugin` to reflect this:

```C
static long demo_activate_plugin(void)
{
        int cpu;
        struct demo_cpu_state *state;

        for_each_online_cpu(cpu) {
                TRACE("Initializing CPU%d...\n", cpu);
                state = cpu_state_for(cpu);
                state->cpu = cpu;
                state->scheduled = NULL;
                edf_domain_init(&state->local_queues,
                                demo_check_for_preemption_on_release,
                                NULL);
        }
        return 0;
}
```

## Ready queue updates

Additional preemption checks are required whenever the ready queue may be changed due to resuming or new tasks. For instance, when a higher-priority task resumes, `demo_schedule()` should be invoked immediately if the currently scheduled task has lower priority (or if currently no real-time task is scheduled).

To ensure the scheduler is invoked when required, we add am explicit preemption check to `demo_task_resume()`. Modify the function to contain the following code:

```C
static void demo_task_resume(struct task_struct  *tsk)
{
        unsigned long flags;
        struct demo_cpu_state *state = cpu_state_for(get_partition(tsk));
        lt_t now;
        TRACE_TASK(tsk, "wake_up at %llu\n", litmus_clock());
        raw_spin_lock_irqsave(&state->local_queues.ready_lock, flags);

        now = litmus_clock();

        if (is_sporadic(tsk) && is_tardy(tsk, now)) {
                /* This sporadic task was gone for a "long" time and woke up past
                 * its deadline. Give it a new budget by triggering a job
                 * release. */
                release_at(tsk, now);
        }

        /* This check is required to avoid races with tasks that resume before
         * the scheduler "noticed" that it resumed. That is, the wake up may
         * race with the call to schedule(). */
        if (state->scheduled != tsk) {
                demo_requeue(tsk, state);
                if (edf_preemption_needed(&state->local_queues, state->scheduled)) {
                        preempt_if_preemptable(state->scheduled, state->cpu);
                }
        }

        raw_spin_unlock_irqrestore(&state->local_queues.ready_lock, flags);
}
```

The only difference here is the additional check in the `if (state->scheduled != tsk)` block, where we check for preemption again.

We need to make very similar changes to the `demo_task_new` function:

```C
static void demo_task_new(struct task_struct *tsk, int on_runqueue,
                          int is_running)
{
        /* We'll use this to store IRQ flags. */
        unsigned long flags;
        struct demo_cpu_state *state = cpu_state_for(get_partition(tsk));
        lt_t now;

        TRACE_TASK(tsk, "is a new RT task %llu (on runqueue:%d, running:%d)\n",
                   litmus_clock(), on_runqueue, is_running);

        /* Acquire the lock protecting the state and disable interrupts. */
        raw_spin_lock_irqsave(&state->local_queues.ready_lock, flags);

        now = litmus_clock();

        /* Release the first job now. */
        release_at(tsk, now);

        if (is_running) {
                /* If tsk is running, then no other task can be running
                 * on the local CPU. */
                BUG_ON(state->scheduled != NULL);
                state->scheduled = tsk;
        } else if (on_runqueue) {
                demo_requeue(tsk, state);
        }

        if (edf_preemption_needed(&state->local_queues, state->scheduled))
                preempt_if_preemptable(state->scheduled, state->cpu);

        raw_spin_unlock_irqrestore(&state->local_queues.ready_lock, flags);
}
```

Once again, the only change is the addition of the `if (edf_preemption_needed ...` statement.

## Testing

Once again, make sure that the plugin compiles and runs. In the next step, we'll finally let it accept real-time tasks.

<div class="nav">
[Previous: Step 6 - Task state changes](plugin_step_6.html) -
[Next: Step 8 - Admitting tasks](plugin_step_8.html)
</div>
