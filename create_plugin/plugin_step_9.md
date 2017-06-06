Title:  Writing a Scheduler Plugin: Step 8
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

<!-- Using "`proc`" (with backticks) here will break the table of contents in mmd version 5 -->
Step 9: Exporting plugin topology in /proc
==========================================

The userspace library `liblitmus` offers several functions that allow tasks to migrate to the appropriate CPUs under partitioned and clustered schedulers. This code needs to know which CPUs a particular plugin considers to form a "partition" or a "cluster". To enable `liblitmus` to work as intended, a plugin must hence export the required topology hints via the `/proc/` filesystem, for which LITMUS^RT provides a wrapper API.

{{TOC}}

## Using the LITMUS^RT API to provide domain information

To access the LITMUS^RT topology hints API, the plugin needs to include `litmus/litmus_proc.h`. Add the following to the list of includes in `sched_demo.c`:

```C
#include <litmus/litmus_proc.h>
```

Secondly, allocate a struct of type `struct domain_proc_info`, which will hold the required topology information. Add the following line near the beginning of `sched_demo.c`:

```C
static struct domain_proc_info demo_domain_proc_info;
```

To communicate with the `/proc` wrapper, the plugin must define another callback function, which provides a pointer to a `struct proc_domain_info` instance:

```C
static long demo_get_domain_proc_info(struct domain_proc_info **ret)
{
        *ret = &demo_domain_proc_info;
        return 0;
}
```

We'll later update the plugin's `struct sched_plugin` instance to include the `demo_get_domain_proc_info` callback, but first we will add code to initialize `demo_domain_proc_info`.

## Initializing the domain info structure

When the plugin is activated, the current topology must be stored in `demo_domain_proc_info`. In short, in a simple partitioned plugin such as the `DEMO` plugin, each processor forms its own "scheduling domain". The initialization code shown here iterates over all online CPUs and creates an entry for the corresponding "scheduling domain". Add this function to `sched_demo.c`, somewhere before the `demo_activate_plugin` function:

```C
static void demo_setup_domain_proc(void)
{
        int i, cpu;
        int num_rt_cpus = num_online_cpus();

        struct cd_mapping *cpu_map, *domain_map;

        memset(&demo_domain_proc_info, 0, sizeof(demo_domain_proc_info));
        init_domain_proc_info(&demo_domain_proc_info, num_rt_cpus, num_rt_cpus);
        demo_domain_proc_info.num_cpus = num_rt_cpus;
        demo_domain_proc_info.num_domains = num_rt_cpus;

        i = 0;
        for_each_online_cpu(cpu) {
                cpu_map = &demo_domain_proc_info.cpu_to_domains[i];
                domain_map = &demo_domain_proc_info.domain_to_cpus[i];

                cpu_map->id = cpu;
                domain_map->id = i;
                cpumask_set_cpu(i, cpu_map->mask);
                cpumask_set_cpu(cpu, domain_map->mask);
                ++i;
        }
}
```

We'll next add a call to the `demo_setup_domain_proc` helper function in the `demo_activate_plugin` function. Modify `demo_activate_plugin` to contain the call to `demo_setup_domain_proc`:

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
                edf_domain_init(&state->local_queues, demo_check_for_preemption_on_release, NULL);
        }

        demo_setup_domain_proc();
        return 0;
}
```

## Adding a cleanup function

LITMUS^RT supports another callback function that is invoked whenever a plugin is unloaded. We'll use this callback to tell LITMUS^RT to clean up any state used for this plugin's `/proc` interface. Add the following function to `sched_demo.c`:

```C
static long demo_deactivate_plugin(void)
{
        destroy_domain_proc_info(&demo_domain_proc_info);
        return 0;
}
```

## Registering the new callback functions

Finally, we'll need to add the `demo_deactivate_plugin` and `demo_setup_domain_proc` functions to the `demo_plugin` struct:

```C
static struct sched_plugin demo_plugin = {
        .plugin_name            = "DEMO",
        .schedule               = demo_schedule,
        .task_wake_up           = demo_task_resume,
        .admit_task             = demo_admit_task,
        .task_new               = demo_task_new,
        .task_exit              = demo_task_exit,
        .get_domain_proc_info   = demo_get_domain_proc_info,
        .activate_plugin        = demo_activate_plugin,
        .deactivate_plugin      = demo_deactivate_plugin,
};
```

## Testing

With these changes in place, our P-EDF scheduler should be complete and ready for use by `liblitmus`. To test the changes:

 1. Re-compile the LITMUS^RT kernel and reboot.
 2. Activate the `DEMO` plugin using `setsched`.
 3. Launch some real-time tasks (as a test, you can use `rtspin` or `rt_launch` from `liblitmus`).

```bash
cd liblitmus

# Activate the demo plugin
sudo ./setsched DEMO

# Run a real-time task. This rtspin instance should run on CPU 1, have a WCET of 10 ms,
# a period of 100ms, and run for 5 seconds.
sudo ./rtspin -p 1 10 100 5
```

The `rtspin` instance in the above sample should terminate after 5 seconds and produce no output. The exact behavior of the plugin can be observed using the `sched_trace` infrastructure described in the tracing tutorial.

<div class="nav">
[Previous: Step 8 - Admitting tasks](plugin_step_8.html)
</div>
