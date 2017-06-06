Title:  Writing a Scheduler Plugin: Step 4
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 4: Defining per-CPU scheduling state for P-EDF
===================================================

Steps 1 through 3 set up skeleton code for a scheduler plugin, and demonstrated how to log debug messages. In step 4, we'll finally start adding code to support a Partitioned-EDF scheduler, starting with per-CPU state.

{{TOC}}

## Including some headers

To begin, add the following lines to the beginning of `litmus/sched_demo.c`:

```C
#include <linux/percpu.h>
#include <linux/sched.h>
#include <litmus/litmus.h>
#include <litmus/rt_domain.h>
#include <litmus/edf_common.h>
```

These includes bring in several definitions we'll need:

 - `linux/percpu.h`: Needed for making CPU-local allocations.
 - `linux/sched.h`: Needed for the definition of `struct task_struct`.
 - `litmus/litmus.h`: Contains many necessary definitions for working with LITMUS^RT.
 - `litmus/rt_domain.h`: Contains definitions relating to "real-time domains", and includes ready-made definitions for release and ready queues.
 - `litmus/edf_common.h`: Contains common definitions related to EDF priority and EDF-related helper functions.

## Per-processor state

To implement the P-EDF scheduler, we need a ready queue and a release queue on each processor. We will use the `rt_domain_t` abstraction, from `litmus/rt_domain.h` to handle this. We also need to know which task is currently scheduled. For convenience, we'll keep track of each CPU's ID in its local state (this will make preemptions easier in a later step). This leads to the following definition of struct `demo_cpu_state`, which will encompass all CPU-local state of the DEMO scheduler. Add the following definitions near the top (after the `#include`s) of `sched_demo.c`:

```C
struct demo_cpu_state {
        rt_domain_t     local_queues;
        int             cpu;

        struct task_struct* scheduled;
};

static DEFINE_PER_CPU(struct demo_cpu_state, demo_cpu_state);

#define cpu_state_for(cpu_id)   (&per_cpu(demo_cpu_state, cpu_id))
#define local_cpu_state()       (this_cpu_ptr(&demo_cpu_state))
```

Note that we use Linux's per-processor allocation macro, `DEFINE_PER_CPU()`, to statically allocate the state required for the plugin. To make the later code more readable, we also define two accessor macros to wrap Linux's per-cpu data structure API: `cpu_state_for()` and `local_cpu_state()`.

## Initializing the new per-CPU state

To make sure that the per-processor state is properly initialized, we are next going to add the plugin activation callback. The `activate_plugin()` callback of a plugin is invoked when the plugin is selected by the user (with `setsched` in `liblitmus`) and is a good place to implement plugin initialization tasks.

In the DEMO plugin, we are simply going to initialize the ready queue and the release queue using `edf_domain_init()` and initialize the two fields `cpu` and `scheduled`. Add the following function to `sched_demo.c`, before the `struct sched_plugin` declaration:

```C
static long demo_activate_plugin(void)
{
        int cpu;
        struct demo_cpu_state *state;

        // Use our macros to access the per-CPU state for all CPUs
        for_each_online_cpu(cpu) {
                TRACE("Initializing CPU%d...\n", cpu);

                state = cpu_state_for(cpu);

                state->cpu = cpu;
                state->scheduled = NULL;
                edf_domain_init(&state->local_queues, NULL, NULL);
        }

        return 0;
}
```

Afterwards, adjust the `struct sched_plugin` declaration to include our `demo_activate_plugin` callback:

```C
static struct sched_plugin demo_plugin = {
        .plugin_name            = "DEMO",
        .schedule               = demo_schedule,
        .admit_task             = demo_admit_task,
        .activate_plugin        = demo_activate_plugin,
};
```

## Testing the changes

Finally, rebuild the LITMUS^RT kernel and reboot. Like in step 3, we'll test our changes by checking the LITMUS^RT kernel's log:

```bash
sudo cat /dev/litmus/log > debug.txt &
sudo liblitmus/setsched DEMO
cat debug.txt
```

This should generate output that includes the following lines (depending on the number of CPUs in your system):

```
1 P2 [demo_activate_plugin@litmus/sched_demo.c:48]: Initializing CPU0...
2 P2 [demo_activate_plugin@litmus/sched_demo.c:48]: Initializing CPU1...
3 P2 [demo_activate_plugin@litmus/sched_demo.c:48]: Initializing CPU2...
4 P2 [demo_activate_plugin@litmus/sched_demo.c:48]: Initializing CPU3...
```

<div class="nav">
[Previous: Step 3 - `TRACE`](plugin_step_3.html) -
[Next: Step 5 - Scheduling logic](plugin_step_5.html)
</div>
