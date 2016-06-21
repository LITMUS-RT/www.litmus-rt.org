Title:  LITMUS-RT: Linux Testbed for Multiprocessor Scheduling in Real-Time Systems
CSS:    inc/format.css


{{inc/header.markdown}}

## About

The LITMUS^RT patch is **a real-time extension of the Linux kernel** with a focus on multiprocessor real-time scheduling and synchronization. The Linux kernel is modified to support the sporadic task model and modular scheduler plugins. Clustered, partitioned, and global scheduling are included, and semi-partitioned scheduling is supported as well.

LITMUS^RT has been continuously maintained since 2006 and is still being actively developed (as of 2016).

## Current Version

The current version of LITMUS^RT is **2015.1** and is based on Linux 4.1.3.
It was released on 8/9/2015 and includes plugins for the following
scheduling policies:

- Partitioned EDF with synchronization support (PSN-EDF),
- Global EDF with synchronization support (GSN-EDF),
- Clustered EDF (C-EDF),
- Partitioned Fixed-Priority (P-FP), and
- PD^2, with either staggered or aligned quanta (PFAIR).
    
Please refer to the <a href="http://wiki.litmus-rt.org/litmus/Releases">download</a> and <a href="http://wiki.litmus-rt.org/litmus/InstallationInstructions">installation</a> wiki pages for details.



## Goals

The primary purpose of the LITMUS^RT project is to **provide  a useful experimental platform for applied real-time systems research**. To that end, LITMUS^RT provides abstractions and interfaces within the kernel that simplify the prototyping of multiprocessor real-time scheduling and synchronization algorithms (compared to modifying a "vanilla" Linux kernel).

As a secondary goal, LITMUS^RT serves as a **proof of concept**, showing how algorithms such as Pfair schedulers and predictable multiprocessor locking protocols can be implemented on current hardware. Finally, we hope that parts of LITMUS^RT and the "lessons learned" may find value as blueprints/sources of inspiration for other  implementation efforts (both commercial and open source).



## Non-Goals

LITMUS^RT is a research prototype that is reasonably stable and tested---it works---but there are currently no plans to turn it into a production-quality system suitable for safety- or mission-critical applications.

Furthermore, LITMUS^RT's API is not "stable," that is, interfaces and implementations may change without warning between releases. POSIX-compliance is not a goal; the LITMUS^RT-API offers alternate system call interfaces.

While we aim to follow Linux-coding standards, LITMUS^RT is not targeted at being merged into mainline Linux. Rather, we hope that some of the ideas protoyped in LITMUS^RT may eventually find adoption in Linux or other kernels.


## Credit

The maintainer and main developer behind LITMUS^RT is <a href="http://www.mpi-sws.org/~bbb">Bj&ouml;rn Brandenburg</a> of the **Max Planck Institute for Software Systems (MPI-SWS)**.

LITMUS^RT was originally launched at the **University of North Carolina at Chapel Hill** under the direction of <a href="http://www.cs.unc.edu/~anderson/">James H. Anderson</a> and has benefited from [contributions by a number of researchers](credits.html) over the years.


When referencing LITMUS^RT, please cite two publications:

1. The **original** LITMUS^RT paper: J. Calandrino, H. Leontyev, A. Block, U. Devi, and J. Anderson, "LITMUS^RT: A Testbed for Empirically Comparing Real-Time Multiprocessor Schedulers ", Proceedings of the 27th IEEE Real-Time Systems Symposium, pp. 111-123, December 2006.
2. The **description of the current version**: B. Brandenburg, "Scheduling and Locking in Multiprocessor Real-Time Operating Systems", PhD thesis, UNC Chapel Hill, 2011.

While [1] is the first publication on LITMUS^RT, the first public release of LITMUS^RT was actually based on a reimplementation in 2007. All versions since 2007 are best described by the detailed description in [2].

To get in contact with the LITMUS^RT community, please use the <a href="https://wiki.litmus-rt.org/litmus/Mailinglist">mailing list</a>.


{{inc/footer.markdown}}

