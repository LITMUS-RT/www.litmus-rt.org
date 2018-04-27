Title:  Writing a Scheduler Plugin: Step 3
CSS:    ../inc/format.css
HTML header:    <script type="text/javascript" src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script> <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.10.0/styles/tomorrow-night.min.css"><script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/9.10.0/highlight.min.js"></script>

{{../inc/header2.markdown}}

Step 3: Creating debug messages using TRACE
-------------------------------------------

We know that the code from step 2 is working due to the `EINVAL` error, but but debugging a new plugin will likely require recording more detailed logging. Step 3 includes how this can be accomplished in LITMUS^RT plugins.

{{TOC}}

### Why not use printk in a LITMUS^RT plugin?

In most modules for the standard Linux kernel, `printk` is generally the go-to choice for writing debug messages to the kernel log. `printk`, however, requires some kernel locks and therefore can cause deadlock if we use it within a LITMUS^RT plugin when making scheduling decisions. LITMUS^RT provides the `TRACE` macro instead, which functions identically to `printk` from the programmer's perspective but doesn't require locking.

### Modifying our basic code to include a TRACE statement

First, add the new header file, needed for the `TRACE` macro, to the list of includes at the start of `sched_demo.c`:

```C
#include <litmus/debug_trace.h>
```

Second, modify the `demo_admit_task` from step 2 to contain a `TRACE` statement:

```C
static long demo_admit_task(struct task_struct *tsk)
{
        TRACE_TASK(tsk, "The task was rejected by the demo plugin.\n");
        /* Reject every task. */
        return -EINVAL;
}
```

In this example, we used `TRACE_TASK`, which takes a `task_struct` pointer in addition to the message to print. It will include information about the task in the log, along with the message.

### Viewing LITMUS^RT trace output

For the `TRACE` macro to work, make sure that you have enabled `TRACE() debugging` when configuring your kernel build (it's under `LITMUS^RT`->`Tracing` in the configuration menu).

After rebuilding the kernel and rebooting, try submitting another real-time task to the DEMO plugin, and viewing the LITMUS^RT log. _As root_, run these commands:

```bash
# Start using the DEMO scheduler plugin.
setsched DEMO

# In the background, start copying the LITMUS^RT log output to a separate file.
tail -f /dev/litmus/log > debug.txt &

# Try starting a real-time task again.
liblitmus/rtspin 10 100 10

# View the log
cat debug.txt
```

The log should contain lines similar to the following:

```
17 P0 [alloc_ctrl_page@litmus/ctrldev.c:28]: (rtspin/2076:0) alloc_ctrl_page ctrl_page = ffff9709a4933000
18 P0 [map_ctrl_page@litmus/ctrldev.c:42]: (rtspin/2076:0) litmus/ctrl: mapping ffff9709a4933000 (pfn:64933) to 0x7f65190b2000 (prot:8000000000000027)
19 P0 [litmus_ctrl_mmap@litmus/ctrldev.c:117]: (rtspin/2076:0) litmus_ctrl_mmap flags=0x10160073 prot=0x8000000000000027
20 P0 [vprintk_emit@kernel/printk/printk.c:1854]: Setting up rt task parameters for process 2076.
21 P0 [map_ctrl_page@litmus/ctrldev.c:42]: (rtspin/2076:0) litmus/ctrl: mapping ffff9709a4933000 (pfn:64933) to 0x7f65190b1000 (prot:8000000000000027)
22 P0 [litmus_ctrl_mmap@litmus/ctrldev.c:117]: (rtspin/2076:0) litmus_ctrl_mmap flags=0x10162073 prot=0x8000000000000027
23 P0 [demo_admit_task@litmus/sched_demo.c:19]: (rtspin/2076:0) The task was rejected by the DEMO plugin.
24 P0 [litmus_ctrl_vm_close@litmus/ctrldev.c:56]: (rtspin/2076:0) litmus_ctrl_vm_close flags=0x18160073 prot=0x25
25 P0 [litmus_ctrl_vm_close@litmus/ctrldev.c:61]: (rtspin/2076:0) litmus/ctrl: 00007f65190b1000:00007f65190b2000 vma:ffff9709a49f1c00 vma->vm_private_data:          (null) closed.
26 P0 [litmus_ctrl_vm_close@litmus/ctrldev.c:56]: (rtspin/2076:0) litmus_ctrl_vm_close flags=0x18160073 prot=0x25
27 P0 [litmus_ctrl_vm_close@litmus/ctrldev.c:61]: (rtspin/2076:0) litmus/ctrl: 00007f65190b2000:00007f65190b3000 vma:ffff9709a49f1540 vma->vm_private_data:          (null) closed.
28 P1 [exit_litmus@litmus/litmus.c:599]: (rtspin/2076:0) freeing ctrl_page ffff9709a4933000
```

Notice the line containing `The task was rejected by the DEMO plugin.` corresponding to our `TRACE_TASK` invocation.

Depending on your kernel build configuration, you may also see a lot of "noise" in the log similar to:

```
SCHED_STATE [P0] 0x1 (TASK_SCHEDULED) -> 0x4 (WILL_SCHEDULE)
```

Messages like this are the result of the configuration option `CONFIG_PREEMPT_STATE_TRACE`, which can be disabled in the kernel configuration. To do so, disable the option at `LITMUS^RT`->`Tracing`->`Trace preemption state machine transitions`.

### Source code

The full code for this step of the tutorial is available [here](./sched_demo_step3.c).

<div class="nav">

[Previous: Step 2 - Stub functions](plugin_step_2.html) -
[Next: Step 4 - Per-CPU state](plugin_step_4.html)

</div>

<script>hljs.initHighlightingOnLoad();</script>
