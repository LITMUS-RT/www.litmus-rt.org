Title:  Writing a Scheduler Plugin: Step 6
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 6: Task state changes
==========================

Changes to Task state, and in particular self-suspensions (such as waiting for I/O), are one of the "real-world" aspects that make scheduling difficult in practice.

The scheduling function implemented in the previous step handles tasks that suspend because a task must be scheduled before it can self-suspend. In addition, a plugin also needs to handle "new" tasks (i.e., tasks that transition to real-time mode) and exiting tasks (i.e., tasks that leave real-time mode or quit unexpectedly). Finally, any plugin must handle resuming tasks (i.e., tasks that become available for execution again after a self-suspension ends).

{{TOC}}

## New and exiting tasks

A task is considered "new" when it becomes a real-time task. New tasks may be either already running or suspended. If a real-time task initializes itself, it should already be running when our plugin is notified. On the other hand, real-time tasks initialized by a separate initialization task are likely to be "new" while still in a suspended state.

In either case, the scheduler state pertaining to this task must be properly initialized:

 - The release time of the current job and its deadline must be set.
 - A running task must further be recorded in the `->scheduled` field of the local `struct demo_cpu_state` instance.
 - A task that is not running but part of the runqueue must be added to the ready queue.

All of this logic is contained in this `demo_task_new` function, that should be added to `sched_demo.c`:

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

        raw_spin_unlock_irqrestore(&state->local_queues.ready_lock, flags);
}
```

Als add the `demo_task_exit` function to maintain scheduler state when a task exits. Much of the boilerplate code here is identical to that in `demo_task_new`:

```C
static void demo_task_exit(struct task_struct *tsk)
{
        unsigned long flags;
        struct demo_cpu_state *state = cpu_state_for(get_partition(tsk));
        raw_spin_lock_irqsave(&state->local_queues.ready_lock, flags);

        /* For simplicity, we assume here that the task is no longer queued anywhere else. This
         * is the case when tasks exit by themselves; additional queue management is
         * is required if tasks are forced out of real-time mode by other tasks. */

        if (state->scheduled == tsk) {
                state->scheduled = NULL;
        }

        raw_spin_unlock_irqrestore(&state->local_queues.ready_lock, flags);
}
```

Note that for the purpose of keeping the tutorial simple, the above implementation of `demo_task_exit()` does not handle the case where one task revokes the real-time status of a different task that is still queued on the ready queue. A robust implementation could handle this by checking whether the exiting task is still part of some queue. This tutorial is just for learning and testing purposes, though, so we will simply avoid creating such a situation in our testing.

## Resuming tasks

Tasks that resume must be re-added to the ready or release queue, depending on when they resume. Additionally, sporadic tasks that were suspended for a "long" time are considered to experience a sporadic job release and must be given a new budget and deadline. This logic is contained in the `demo_task_resume` function, which should be added to `sched_demo.c`:

```C
/* Called when the state of tsk changes back to TASK_RUNNING.
 * We need to requeue the task.
 *
 * NOTE: If a sporadic task is suspended for a long time,
 * this might actually be an event-driven release of a new job.
 */
static void demo_task_resume(struct task_struct  *tsk)
{
        unsigned long flags;
        struct demo_cpu_state *state = cpu_state_for(get_partition(tsk));
        lt_t now;
        TRACE_TASK(tsk, "woke up at %llu\n", litmus_clock());
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
        }

        raw_spin_unlock_irqrestore(&state->local_queues.ready_lock, flags);
}
```

There are two important things to note. First, on the line assigning `*state = cpu_state_for(...)`, note that the CPU processing the wakeup is not necessarily the CPU that the task is assigned to. This is because tasks are often resumed by interrupts, which (in general) may be handled on any CPU.

Second, note that it may be the case that tsk is still scheduled, which we check using `if (state->scheduled != tsk)`. This can happen if the wakeup happens shortly after the task initiated its self-suspension, which allows the wakeup on a remote CPU to race with the suspension and to be handled before the local CPU managed to process the self-suspension. (Note that the ready queue lock serializes remote wakeups and local scheduling decisions.)

## Plugin definition

Finally, update the `struct sched_plugin` instance to include our plugin's new callback functions:

```C
static struct sched_plugin demo_plugin = {
        .plugin_name            = "DEMO",
        .schedule               = demo_schedule,
        .task_wake_up           = demo_task_resume,
        .admit_task             = demo_admit_task,
        .task_new               = demo_task_new,
        .task_exit              = demo_task_exit,
        .activate_plugin        = demo_activate_plugin,
};
```

## Testing the changes

Now, you can make sure the plugin still compiles and runs. It still won't admit tasks, though. In the next step, we'll enable preemptive scheduling.

<div class="nav">
[Previous: Step 5 - Scheduling logic](plugin_step_5.html) -
[Next: Step 7 - Preemption](plugin_step_7.html)
</div>
