Title:  Writing a Scheduler Plugin: Step 8
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 8: Admitting real-time tasks
=================================

In the final step before the plugin can be used to schedule real-time tasks, we are going to change to `demo_admit_task()` callback to allow tasks, provided that they are located on the right core.

To this end, `change demo_admit_task()` to look as follows:

```C
static long demo_admit_task(struct task_struct *tsk)
{
        if (task_cpu(tsk) == get_partition(tsk)) {
                TRACE_TASK(tsk, "accepted by demo plugin.\n");
                return 0;
        }
        return -EINVAL;
}
```

Since `DEMO` implements a partitioned scheduler, we require that real-time tasks have migrated to the appropriated core before they become real-time tasks. This constraint simplifies the implementation of the plugin greatly and is not difficult to support in userspace (`liblitmus` contains a helper function `be_migrate_to_domain()` that can take care of this requirement).

Note that `task_cpu(tsk)` is Linux's notion of where the task currently is, whereas `get_partition(tsk)` is LITMUSRT's notion of where the task is logically assigned to.

The plugin is now fully functional by itself. However, `liblitmus` contains code to make migrating tasks to the right processors (or clusters of processors) easier, and this support code requires additional information from the plugin. In the next step, the plugin is changed to export the required information.

<div class="nav">
[Previous: Step 7 - Preemption](plugin_step_7.html) -
[Next: Step 9 - `/proc` interface](plugin_step_9.html)
</div>
