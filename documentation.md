Title:  LITMUS-RT: Documentation
CSS:    inc/format.css

{{inc/header.markdown}}

LITMUS^RT Documentation
=======================

This page contains links to LITMUS^RT documentation, inluding basic installation and usage instructions, and in-depth tutorials such as creating a new scheduler plugin.

#### Getting Started

- The [installation instructions](installation.html) cover how to compile and install the LITMUS^RT kernel on a standard Linux system.

 - The [LITMUS^RT tutorial](tutorial/index.html) provides basic instructions for getting started with using LITMUS^RT, including working with different scheduling plugins and configuring and launching real-time tasks.

#### User Documentation

 - The [LITMUS^RT manual](tutorial/manual.html) provides additional details about how LITMUS^RT and its schedulers work. This page provides more detail about the topics covered in the [basic tutorial](tutorial/index.html).

- The [schedule tracing and visualization tutorial](https://github.com/LITMUS-RT/feather-trace-tools/blob/master/doc/howto-trace-and-analyze-a-schedule.md) explains how to capture, evaluate, and visualize *schedule traces* using LITMUS^RT's `sched_trace` facility.

- The [overhead tracing and analysis tutorial](https://github.com/LITMUS-RT/feather-trace-tools/blob/master/doc/howto-trace-and-process-overheads.md) documents how to measure and post-process *kernel overheads* using the Feather-Trace toolkit, which is part of LITMUS^RT.

- The [reservations tutorial](https://github.com/LITMUS-RT/liblitmus/blob/master/doc/howto-use-resctl.md) explains how to set up *reservation-based scheduling* and provision real-time tasks in *reservations* using LITMUS^RT's reservation framework. 

- The [table-driven scheduling tutorial](https://github.com/LITMUS-RT/liblitmus/blob/master/doc/table-driven-scheduling.md) documents how to set up *table-driven scheduling* (also know as *time partitioning* or *time-triggered scheduling*) in LITMUS^RT's reservation framework. 

#### Developer Documentation

 - The instructions for [writing a new LITMUS^RT scheduler plugin](create_plugin/create_plugin.html) provide a step-by-step guide for implementing a *partitioned EDF* (P-EDF) scheduler as a LITMUS^RT plugin. We recommend using these instructions as a starting point when implementing a new scheduler plugin.

- Instructions for [linking against `liblitmus`](https://wiki.litmus-rt.org/litmus/LinkAgainstLiblitmusTutorial).

- Chapter 3 of [Björn Brandenburg's PhD thesis](http://www.cs.unc.edu/~bbb/diss/brandenburg-diss.pdf) explains the design and implementation of LITMUS^RT, and how to account for kernel overheads as encountered in LITMUS^RT and as [measured by Feather-Trace](https://github.com/LITMUS-RT/feather-trace-tools/blob/master/doc/howto-trace-and-process-overheads.md).

 - The old [LITMUS^RT Wiki](http://wiki.litmus-rt.org/) is largely unmaintained and outdated, but contains a few additional tutorials that may be useful when using LITMUS^RT.

{{inc/footer.markdown}}
