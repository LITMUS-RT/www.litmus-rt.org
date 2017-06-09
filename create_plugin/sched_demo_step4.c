#include <linux/module.h>
#include <linux/percpu.h>
#include <linux/sched.h>
#include <litmus/litmus.h>
#include <litmus/edf_common.h>
#include <litmus/debug_trace.h>
#include <litmus/preempt.h>
#include <litmus/rt_domain.h>
#include <litmus/sched_plugin.h>

struct demo_cpu_state {
        rt_domain_t local_queues;
        int cpu;
        struct task_struct* scheduled;
};

static DEFINE_PER_CPU(struct demo_cpu_state, demo_cpu_state);

#define cpu_state_for(cpu_id)   (&per_cpu(demo_cpu_state, cpu_id))
#define local_cpu_state()       (this_cpu_ptr(&demo_cpu_state))

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
        TRACE_TASK(tsk, "The task was rejected by the demo plugin.\n");
        /* Reject every task. */
        return -EINVAL;
}

static struct sched_plugin demo_plugin = {
        .plugin_name            = "DEMO",
        .schedule               = demo_schedule,
        .admit_task             = demo_admit_task,
        .activate_plugin        = demo_activate_plugin,
};

static int __init init_demo(void)
{
        return register_sched_plugin(&demo_plugin);
}

module_init(init_demo);

