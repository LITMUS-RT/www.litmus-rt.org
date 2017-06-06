Title:  LITMUS-RT Tutorial
CSS:    ../inc/format.css


{{../inc/header2.markdown}}

# Getting Started with LITMUS^RT

LITMUS^RT is a real-time extension of the Linux kernel with a focus on multiprocessor real-time scheduling and synchronization that has been continuously maintained and updated since 2006. In the past decade, LITMUS^RT has been employed by several groups in North and South America, Europe, and Asia, and to date has played a part in over 50 conference and workshop papers, as well as eight MSc and PhD theses ([list of publications](https://wiki.litmus-rt.org/litmus/Publications)).

<!--
**Quick links**:

- High-level overview: [Getting started with LITMUS^RT (PDF)](litmus-overview.pdf)
- Hands-on tutorial: [LITMUS^RT: A Hands-On Primer (PDF)](tutorial-slides.pdf)
- Manual: [A guide to LITMUS^RT](manual.html)
-->

## Tutorial Overview

This tutorial is aimed at researchers and practitioners interested in using LITMUS^RT as a development and evaluation platform. It aims to get participants up-to-speed on how to use a LITMUS^RT-equipped Linux system as the foundation for the development and assessment of real-time workloads.

This tutorial is aimed at learning how to *use* LITMUS^RT. The following topics are covered:

1. activating a scheduling plugin,
2. launching LITMUS^RT real-time tasks,
3. creating and using polling reservations,
4. table-driven scheduling (aka time partitioning),
5. how to develop custom real-time tasks that link against `liblitmus`, LITMUS^RT's user-space library,
5. how to use of LITMUS^RT's built-in tracing capabilities to record and evaluate scheduling traces (e.g., to observe actual execution costs, deadline miss ratios, tardiness, preemption and migration counts, etc.), and
6. how to measure system overheads (e.g., scheduling and context switch overheads, release latency, etc.).

Kernel development is beyond the scope of this tutorial. If you want to develop a new plugin for LITMUS^RT, see the [plugin creation tutorial](../create_plugin/create_plugin.html) instead.

## Prerequisites

- Basic familiarity with the Linux shell.

- A working knowledge of software development with C in a Linux environment (and related command-line tools such as `make`).

- A basic understanding of real-time scheduling.

- A computer (running either Windows, Mac, or Linux) with at least 10GiB of free disk space and sufficient RAM to comfortably run a large VM.

## Tutorial Materials


### High-Level Overview

A slide deck giving a high-level overview of LITMUS^RT is provided here:

- [Getting started with LITMUS^RT (PDF)](litmus-overview.pdf)

### Hands-On Tutorial

The slides for the guided hands-on session are available here:

- [LITMUS^RT: A Hands-On Primer (PDF)](tutorial-slides.pdf)

### Manual: A Tour of LITMUS^RT

The material covered in the tutorial (how to select scheduling polices, how to launch tasks, how to create new tasks, how to trace, etc.) is also made available as a manual for later reference.

- [A Tour of LITMUS^RT](manual.html)

Reading the manual prior to following the hands-on tutorial is not required, but recommended.


## VM Setup Instructions

We have built a pre-packaged VirtualBox image running a LITMUS^RT-based Xubuntu distribution. The image (3.0 GiB) comes pre-installed with all required libraries and tools.

- [http://www.litmus-rt.org/tutorial/litmus-2016.1.qcow.tar.gz](http://www.litmus-rt.org/tutorial/litmus-2016.1.qcow.tar.gz)

To get started, download the archive, unpack the image, and launch it with the virtualization tool of your choice (e.g., [Virtual Box](https://www.virtualbox.org)). Make sure that you give the VM **at least 2 GiB of memory**.

See the [detailed setup instructions](vm-setup.html) for a step-by-step walk-through using Virtual Box.

**WARNING**: the VM image is intended for demonstration and learning purposes only. Under common hypervisors, *all timings are unreliable*. In particular, *LITMUS^RT does not provide any real-time guarantees when run under regular hypervisors* as **real-time tasks will be subject to extreme timer latency within a VM**.

That said, a VM is perfectly adequate for getting to know LITMUS^RT.

## Login information

Once the VM is running, you may log in with the following credentials:

1. regular user account:
    - User name: `litmus`
    - Password: `litmus`

2. super user account:
    - User name: `root`
    - Password: `litmus`

All LITMUS^RT-related files (including source code) are installed under the **/opt** directory.





{{../inc/footer.markdown}}
