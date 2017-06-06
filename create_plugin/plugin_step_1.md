Title:  Writing a Scheduler Plugin: Step 1
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Step 1: Adding an empty source file to the LITMUS^RT kernel
===========================================================

The first step in creating a new plugin will be to create a place for the plugin's code in the LITMUS^RT kernel. These following steps assume that the root kernel source directory is named `litmus-rt`.

```bash
# Navigate to the "litmus" subdirectory of the LITMUS^RT kernel source tree.
cd litmus-rt/litmus

# Create an empty file to contain the new plugin
touch sched_demo.c
```

After adding the new source file, add `sched_demo.o` to the `obj-y` list in the `litmus` directory's `Makefile`. If you want, re-build the LITMUS^RT kernel to make sure you didn't make any mistakes.

<div class="nav">
[Next: Step 2 - Stub functions](plugin_step_2.html)
</div>
