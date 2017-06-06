Title:  Writing a Scheduler Plugin: Step 2
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 2: Adding stub functions for a LITMUS^RT plugin
====================================================

The first step just added an empty file to the LITMUS^RT kernel. In this step, we'll actually include some placeholder code for the new module.

{{TOC}}

## Basic scheduler plugin code

Modify `sched_demo.c` to contain the following code, which contains a minimal skeleton of a LITMUS^RT scheduler plugin. For now, the plugin does not do anything, apart from registering itself as an available scheduler:

```C
#include <linux/module.h>
#include <litmus/preempt.h>
#include <litmus/sched_plugin.h>

static struct task_struct* demo_schedule(struct task_struct * prev)
{
        /* This mandatory. It triggers a transition in the LITMUS^RT remote
         * preemption state machine. Call this AFTER the plugin has made a local
         * scheduling decision.
         */
        sched_state_task_picked();

        /* We don't schedule anything for now. NULL means "schedule background work". */
        return NULL;
}

static long demo_admit_task(struct task_struct *tsk)
{
        /* Reject every task. */
        return -EINVAL;
}

static struct sched_plugin demo_plugin = {
        .plugin_name            = "DEMO",
        .schedule               = demo_schedule,
        .admit_task             = demo_admit_task,
};

static int __init init_demo(void)
{
        return register_sched_plugin(&demo_plugin);
}

module_init(init_demo);
```

## Explanation of the plugin code

This stub scheduler implementation is best explained from the bottom to the top line of `sched_demo.c`:

 - All scheduler plugins in LITMUS^RT are actually Linux kernel modules, which require an initialization function. The `module_init(...)` macro is used to tell the compiler and linker which function to call during initialization. This plugin's initialization function is `init_demo`, so the last line in the plugin's definition is `module_init(init_demo);`.

 - Next from the bottom is the definition for the `init_demo` function, which, as mentioned, must contain any code to initialize the plugin. In our case, all it does is call the LITMUS^RT function, `register_sched_plugin(...)`, to add our scheduling plugin to the list of available schedulers. The `register_sched_plugin` function requires a pointer to a `sched_plugin` struct. Both our initialization function and `register_sched_plugin` will return 0 on success.

 - Above the definition for the `init_demo` function comes a statically-defined `sched_plugin` struct, which provides the LITMUS^RT kernel with a list of callback functions along with the scheduler name. In this case, we're setting the scheduler's name to "DEMO", and providing callback functions to be executed during the `schedule` and `admit_task` events. The full list of function callbacks that can be provided in the `sched_plugin` struct can be seen in the definition of `sched_plugin` in `include/litmus/sched_plugin.h`, in the kernel source tree. Any functions we don't provide will simply fall back to a default no-op.

 - Continuing up from the bottom, next comes the `demo_admit_task` function, which is our callback for LITMUS^RT's `admit_task` event. This function will be called whenever a real-time task attempts to be admitted to the system under this scheduler. For now, we simply reject all tasks by returning an invalid argument error.

 - Finally, the first function in `sched_demo.c` is the `demo_schedule` function, which is our callback for LITMUS^RT's `schedule` event. This function should provide a pointer to the `task_struct` for the task that should begin executing. If the plugin doesn't wish to schedule a real-time task, it can return `NULL` to allow the default Linux scheduler to schedule non-real-time processes. However, it must always call LITMUS^RT's `sched_state_task_picked` function to inform the kernel that a scheduling decision has been made.

## Testing the plugin

After you have finished adding the code to `sched_demo.c`, re-compile and re-install the kernel. When you reboot, run the following commands as root:

```bash
# Navigate to the directory where you built liblitmus
cd liblitmus

# Change the current system scheduler to our DEMO plugin
./setsched DEMO

# This should now print 'DEMO'
./showsched

# Creating a real-time task should fail due to an invalid argument error
./rt-spin 10 100 10
```

<div class="nav">
[Previous: Step 1 - Adding files](plugin_step_1.html) -
[Next: Step 3 - `TRACE`](plugin_step_3.html)
</div>
