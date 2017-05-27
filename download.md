Title:  Download LITMUS-RT
CSS:    inc/format.css


{{inc/header.markdown}}

# Getting the Latest LITMUS^RT Release

The source code of the LITMUS^RT project is hosted on [GitHub](https://github.com/LITMUS-RT).

The three main repositories provide

- the [LITMUS^RT kernel](https://github.com/LITMUS-RT/litmus-rt),
- the [liblitmus user-space library](https://github.com/LITMUS-RT/liblitmus), and
- the [Feather-Trace tracing tools](https://github.com/LITMUS-RT/feather-trace-tools). 


## Contents and Main Branches

The [LITMUS^RT kernel repository](https://github.com/LITMUS-RT/litmus-rt) contains the LITMUS^RT patches on top of the Linux kernel. The current main branch is `linux-4.9-litmus` and, as the name suggests, is based on Linux 4.9. 

The [liblitmus repository](https://github.com/LITMUS-RT/liblitmus) contains both  a user-space library for static linking and essential standalone tools needed to configure a LITMUS^RT system. The `master` branch is the main branch representing the latest version. 

The [tracing tools repository](https://github.com/LITMUS-RT/feather-trace-tools) contains helper tools and scripts for both overhead and schedule tracing in LITMUS^RT. The main branch is the `master` branch.

To obtain the latest LITMUS^RT version, simply clone each of the three repositories.

	git clone https://github.com/LITMUS-RT/litmus-rt.git
	
	git clone https://github.com/LITMUS-RT/liblitmus.git
	
	git clone https://github.com/LITMUS-RT/feather-trace-tools.git

Please refer to the [installation instructions](installation.html) for additional details.


## Obtaining a Specific Release

First, whenever possible, **please use the latest version**, as represented by the tips of the  `linux-4.9-litmus` branch in the kernel repository and the `master` branches in the other repositories. 

The main branches are slow-moving and we do our best to keep them stable. There is hence usually no good reason to  pick an older release  and to forgo the latest improvements and fixes in the main branches.

That said, to obtain a specific release, simply checkout the release with the corresponding tag. For example, to check out the 2017.1 release, run the following command in each of the cloned repositories.

	git checkout 2017.1

Alternatively, one may download an archive corresponding for any release from GitHub:

- [LITMUS^RT kernel releases](https://github.com/LITMUS-RT/litmus-rt/releases)
- [liblitmus releases](https://github.com/LITMUS-RT/liblitmus/releases)
- [Feather-Trace tools releases](https://github.com/LITMUS-RT/feather-trace-tools/releases)



## Release History

### LITMUS^RT 2017.1

Based on Linux 4.9.30. Released in May 2017.

#### Major changes (sine LITMUS^RT 2016.1):

- Rebased to Linux version 4.9. Major changes in "scheduling in progress" tracking and the `hrtimer` API, among many others.

- Extend plugin API to allow plugins to optionally change task parameters at runtime via the `task_change_params()` plugin callback (opt-in, none of the stock plugins support this at the moment).

- Improved handling of wake-ups and job releases triggered by `clock_nanosleep()`.

- Fix Feather-Trace compilation on ARM (Namhoon Kim, Andrea Bastoni).

- Better tracking of job completions of sporadic tasks.

- Basic support for random inter-arrival delays in `rtspin`.

- Support `clock_nanosleep()` in `rtspin` (via `-T` option).

- Improved argument handling in user-space tools.

- Support for compiling liblitmus on ARM64.

- Various new time-related helper functions in `liblitmus` such as `ns2ms()`, `litmus_clock()`, `sleep_until_mono()`, `lt_sleep_until()` etc.

---

<!-- Taken from the old MoinMoin wiki. --> 


<span class="anchor" id="line-14"></span><span class="anchor" id="line-15"></span><p class="line862">Older releases consisted of our Linux kernel modifications in the form of a patch against mainline Linux and <tt class="backtick">liblitmus</tt>, the user-space API for real-time tasks, as well as <tt class="backtick">ft_tools</tt>, a collection of tools used for tracing with Feather-Trace (which is part of the LITMUS<sup>RT</sup> patch).  The following downloads are only of historic interest.<span class="anchor" id="line-16"></span><span class="anchor" id="line-17"></span>
<span class="anchor" id="line-18"></span><p class="line867">
<h3 id="LITMUS-RT_Version_2016.1">LITMUS^RT Version 2016.1</h3>
<span class="anchor" id="line-19"></span><span class="anchor" id="line-20"></span><p class="line874">Based on Linux 4.1.3. Released in June 2016. <span class="anchor" id="line-21"></span><span class="anchor" id="line-22"></span><p class="line867">
<h4 id="Files:">Files:</h4>
<span class="anchor" id="line-23"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2016.1/litmus-rt-2016.1.patch">litmus-rt-2016.1.patch</a> <span class="anchor" id="line-24"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2016.1/liblitmus-2016.1.tgz">liblitmus-2016.1.tgz</a> <span class="anchor" id="line-25"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2016.1/ft_tools-2016.1.tgz">ft_tools-2016.1.tgz</a> <span class="anchor" id="line-26"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2016.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-27"></span><span class="anchor" id="line-28"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2015.1.29:">Major changes (since LITMUS^RT 2015.1):</h4>
<span class="anchor" id="line-29"></span><ul><li><p class="line862">new syscall <tt class="backtick">get_current_budget</tt> <span class="anchor" id="line-30"></span></li><li>export more job stats in control page, including current deadline <span class="anchor" id="line-31"></span></li><li><p class="line862">Pratyush Patel contributed much improved <tt class="backtick">hrtimer_start_on()</tt> support <span class="anchor" id="line-32"></span></li><li><p class="line862">LITMUS^RT services are now invoked via <tt class="backtick">ioctl()</tt> calls <span class="anchor" id="line-33"></span></li><li>new scheduler plugin: P-RES (partitioned reservations) <span class="anchor" id="line-34"></span></li><li><p class="line862">new user-space interfaces and tool (<tt class="backtick">resctrl</tt>) to set up reservations <span class="anchor" id="line-35"></span></li><li>add a number of callbacks to LITMUS^RT plugins <span class="anchor" id="line-36"></span></li><li><p class="line862">improved help messages of utilities in <tt class="backtick">liblitmus</tt> <span class="anchor" id="line-37"></span></li><li>vastly improved tooling and documentation as part of feather-trace-tools (ft_tools) <span class="anchor" id="line-38"></span><span class="anchor" id="line-39"></span><span class="anchor" id="line-40"></span><span class="anchor" id="line-41"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2015.1">LITMUS^RT Version 2015.1</h3>
<span class="anchor" id="line-42"></span><span class="anchor" id="line-43"></span><p class="line874">Based on Linux 4.1.3. Released in August 2015. <span class="anchor" id="line-44"></span><span class="anchor" id="line-45"></span><p class="line867">
<h4 id="Files:-1">Files:</h4>
<span class="anchor" id="line-46"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2015.1/litmus-rt-2015.1.patch">litmus-rt-2015.1.patch</a> <span class="anchor" id="line-47"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2015.1/liblitmus-2015.1.tgz">liblitmus-2015.1.tgz</a> <span class="anchor" id="line-48"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2015.1/ft_tools-2015.1.tgz">ft_tools-2015.1.tgz</a> <span class="anchor" id="line-49"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2015.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-50"></span><span class="anchor" id="line-51"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2014.2.29:">Major changes (since LITMUS^RT 2014.2):</h4>
<span class="anchor" id="line-52"></span><ul><li>now based on Linux 4.1.3 <span class="anchor" id="line-53"></span></li><li>stability fixes in P-FP, PFAIR, GSN-EDF, and C-EDF <span class="anchor" id="line-54"></span></li><li><p class="line862">Geoffrey Tran (USC/ISI) added support for running LITMUS<sup>RT</sup> under Xen/x86 <span class="anchor" id="line-55"></span></li><li><p class="line862">a new wrapper script <tt class="backtick">ft-trace-overheads</tt> to simplify overhead tracing <span class="anchor" id="line-56"></span><span class="anchor" id="line-57"></span><span class="anchor" id="line-58"></span><span class="anchor" id="line-59"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2014.2">LITMUS^RT Version 2014.2</h3>
<span class="anchor" id="line-60"></span><span class="anchor" id="line-61"></span><p class="line874">Based on Linux 3.10.41. Released in June 2014. <span class="anchor" id="line-62"></span><span class="anchor" id="line-63"></span><p class="line867">
<h4 id="Files:-2">Files:</h4>
<span class="anchor" id="line-64"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.2/litmus-rt-2014.2.patch">litmus-rt-2014.2.patch</a> <span class="anchor" id="line-65"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.2/liblitmus-2014.2.tgz">liblitmus-2014.2.tgz</a> <span class="anchor" id="line-66"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.2/ft_tools-2014.2.tgz">ft_tools-2014.2.tgz</a> <span class="anchor" id="line-67"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.2/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-68"></span><span class="anchor" id="line-69"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2014.1.29:">Major changes (since LITMUS^RT 2014.1):</h4>
<span class="anchor" id="line-70"></span><ul><li>now based on Linux 3.10.41 <span class="anchor" id="line-71"></span></li><li><p class="line862">remove integration with Linux's system tick: LITMUS<sup>RT</sup> now works with &quot;tickless&quot; kernels (i.e., <tt class="backtick">NO_HZ</tt> is supported) <span class="anchor" id="line-72"></span></li><li><p class="line862">The <tt class="backtick">PFAIR</tt> plugin now uses plugin-local hrtimers to trigger quantum boundaries. <span class="anchor" id="line-73"></span></li><li><p class="line862">added <tt class="backtick">QUANTUM_BOUNDARY</tt> Feather-Trace event (for <tt class="backtick">PFAIR</tt>) <span class="anchor" id="line-74"></span></li><li><p class="line862">performance and bug fixes in the <tt class="backtick">P-FP</tt> plugin's PCP, MPCP, and FMLP<sup>+</sup> implementations <span class="anchor" id="line-75"></span></li><li><p class="line862">bugfix in <tt class="backtick">TS_SYSCALL_IN_END</tt> <span class="anchor" id="line-76"></span></li><li><p class="line862">Migration support in <tt class="backtick">liblitmus</tt> now works for &gt;=32 CPUs <span class="anchor" id="line-77"></span><span class="anchor" id="line-78"></span><span class="anchor" id="line-79"></span><span class="anchor" id="line-80"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2014.1">LITMUS^RT Version 2014.1</h3>
<span class="anchor" id="line-81"></span><span class="anchor" id="line-82"></span><p class="line874">Based on Linux 3.10.5. Released in April 2014. <span class="anchor" id="line-83"></span><span class="anchor" id="line-84"></span><p class="line867">
<h4 id="Files:-3">Files:</h4>
<span class="anchor" id="line-85"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.1/litmus-rt-2014.1.patch">litmus-rt-2014.1.patch</a> <span class="anchor" id="line-86"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.1/liblitmus-2014.1.tgz">liblitmus-2014.1.tgz</a> <span class="anchor" id="line-87"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.1/ft_tools-2014.1.tgz">ft_tools-2014.1.tgz</a> <span class="anchor" id="line-88"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2014.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-89"></span><span class="anchor" id="line-90"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2013.1.29:">Major changes (since LITMUS^RT 2013.1):</h4>
<span class="anchor" id="line-91"></span><ul><li><p class="line862">Added <tt class="backtick">CONFIG_PREFER_LOCAL_LINKING</tt> option to avoid superfluous migrations under G-EDF and C-EDF <span class="anchor" id="line-92"></span></li><li><p class="line862">New, much improved interface for reporting CPU domain topology to userspace (see <tt class="backtick">/proc/litmus/cpus</tt> and <tt class="backtick">/proc/litmus/domains</tt>) <span class="anchor" id="line-93"></span></li><li>liblitmus: added Doxygen documentation <span class="anchor" id="line-94"></span></li><li>liblitmus: play nicely with C++ namespaces <span class="anchor" id="line-95"></span></li><li><p class="line862">Feather-Trace: support TSC offset calibration (<tt class="backtick">-c</tt> option in <tt class="backtick">ftcat</tt>, for systems with non-aligned TSCs) <span class="anchor" id="line-96"></span></li><li>Feather-Trace: Restructured to use per-CPU recording buffers to reduce tracing overheads <span class="anchor" id="line-97"></span></li><li>P-FP: Fix interaction of PCP and DPCP semaphores <span class="anchor" id="line-98"></span></li><li><p class="line862">P-FP: add implementation of <em>Distributed FIFO Locking Protocol</em> (DFLP) <span class="anchor" id="line-99"></span></li><li>PSN-EDF: support arbitrary deadlines in SRP implementation <span class="anchor" id="line-100"></span></li><li>Tasks are forced to cease being real-time tasks before exiting <span class="anchor" id="line-101"></span></li><li><p class="line862">Export LITMUS<sup>RT</sup> time stamps in <tt class="backtick">ftrace</tt> records <span class="anchor" id="line-102"></span></li><li><p class="line862">Bug fix: Avoid rare crashes caused by interaction with <tt class="backtick">stop_machine</tt> scheduling class <span class="anchor" id="line-103"></span></li><li>Bug fix: Fix cache inconsistencies of the control page on ARM <span class="anchor" id="line-104"></span></li><li>Misc. build, bug and performance fixes  <span class="anchor" id="line-105"></span><span class="anchor" id="line-106"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2013.1">LITMUS^RT Version 2013.1</h3>
<span class="anchor" id="line-107"></span><span class="anchor" id="line-108"></span><p class="line874">Based on Linux 3.10.5. Released in August 2013. <span class="anchor" id="line-109"></span><span class="anchor" id="line-110"></span><p class="line867">
<h4 id="Files:-4">Files:</h4>
<span class="anchor" id="line-111"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2013.1/litmus-rt-2013.1.patch">litmus-rt-2013.1.patch</a> <span class="anchor" id="line-112"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2013.1/liblitmus-2013.1.tgz">liblitmus-2013.1.tgz</a> <span class="anchor" id="line-113"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2013.1/ft_tools-2013.1.tgz">ft_tools-2013.1.tgz</a> <span class="anchor" id="line-114"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2013.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-115"></span><span class="anchor" id="line-116"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2012.3.29:">Major changes (since LITMUS^RT 2012.3):</h4>
<span class="anchor" id="line-117"></span><ul><li>Restructured kernel source tree as a proper patch set. <span class="anchor" id="line-118"></span></li><li>Rebased to current stable Linux version (3.10.5). <span class="anchor" id="line-119"></span></li><li>Fixed admission of suspended tasks. <span class="anchor" id="line-120"></span></li><li>Fixed several build failures in corner-case configurations. <span class="anchor" id="line-121"></span></li><li>Disabled timer coalescing for LITMUS^RT tasks in Linux timer API. <span class="anchor" id="line-122"></span></li><li>Increased maximum Feather-Trace buffer size (using vmalloc()). <span class="anchor" id="line-123"></span></li><li>Various code cleanups and reliability fixes. <span class="anchor" id="line-124"></span></li><li>Support early job releasing in EDF-based plugins. <span class="anchor" id="line-125"></span></li><li>Differentiate between SPORADIC and PERIODIC tasks. <span class="anchor" id="line-126"></span></li><li>Fixed race conditions in synchronous task set release support. <span class="anchor" id="line-127"></span></li><li>Reimplemented plugin switching code. <span class="anchor" id="line-128"></span></li><li>Added checks to prevent nesting of LITMUS^RT locks. <span class="anchor" id="line-129"></span></li><li>Added a virtual device for mmap()'ing uncached memory regions. <span class="anchor" id="line-130"></span><span class="anchor" id="line-131"></span><span class="anchor" id="line-132"></span><span class="anchor" id="line-133"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2012.3">LITMUS^RT Version 2012.3</h3>
<span class="anchor" id="line-134"></span><span class="anchor" id="line-135"></span><p class="line874">Based on Linux 3.0. Released in December 2012. <span class="anchor" id="line-136"></span><span class="anchor" id="line-137"></span><p class="line867">
<h4 id="Files:-5">Files:</h4>
<span class="anchor" id="line-138"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.3/litmus-rt-2012.3.patch">litmus-rt-2012.3.patch</a> <span class="anchor" id="line-139"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.3/liblitmus-2012.3.tgz">liblitmus-2012.3.tgz</a> <span class="anchor" id="line-140"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.3/ft_tools-2012.3.tgz">ft_tools-2012.3.tgz</a> <span class="anchor" id="line-141"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.3/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-142"></span><span class="anchor" id="line-143"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2012.2.29:">Major changes (since LITMUS^RT 2012.2):</h4>
<span class="anchor" id="line-144"></span><span class="anchor" id="line-145"></span><ul><li>configurable EDF tie-breaks (choose from one of four methods: lateness, normalized tardiness, uniform hashing, PID). <span class="anchor" id="line-146"></span></li><li>many Feather-Trace improvements, including support for userspace-reported system call overhead tracing (via control page) <span class="anchor" id="line-147"></span></li><li>IRQ counts are now exported to the control page <span class="anchor" id="line-148"></span></li><li>latency reduction when carrying out synchronous task set releases <span class="anchor" id="line-149"></span></li><li>fix of preemption logic in P-FP and PSN-EDF plugins <span class="anchor" id="line-150"></span></li><li>various improvements in the P-FP plugin <span class="anchor" id="line-151"></span></li><li>misc. bug and compile fixes (esp. on ARM) <span class="anchor" id="line-152"></span></li><li>liblitmus: new convenience functions lt_sleep() and get_nr_ts_release_waiters() <span class="anchor" id="line-153"></span></li><li>liblitmus: improved test suite <span class="anchor" id="line-154"></span></li><li>feather-trace-tools: ftsort gained the -v (verbose) and -s (simulate) flags, which are useful for outlier debugging <span class="anchor" id="line-155"></span></li><li><p class="line862">feather-trace-tools: improved outlier detection; <strong>statistical outlier filtering is no longer required</strong> (for details, see B. Brandenburg, “Improved Analysis and Evaluation of Real-Time Semaphore Protocols for P-FP Scheduling”, RTAS 2013, <a class="https" href="https://www.mpi-sws.org/~bbb/papers/index.html">available here</a>) <span class="anchor" id="line-156"></span><span class="anchor" id="line-157"></span><span class="anchor" id="line-158"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2012.2">LITMUS^RT Version 2012.2</h3>
<span class="anchor" id="line-159"></span><span class="anchor" id="line-160"></span><p class="line874">Based on Linux 3.0. Released in August 2012. <span class="anchor" id="line-161"></span><span class="anchor" id="line-162"></span><p class="line867">
<h4 id="Files:-6">Files:</h4>
<span class="anchor" id="line-163"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.2/litmus-rt-2012.2.patch">litmus-rt-2012.2.patch</a> <span class="anchor" id="line-164"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.2/liblitmus-2012.2.tgz">liblitmus-2012.2.tgz</a> <span class="anchor" id="line-165"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.2/ft_tools-2012.2.tgz">ft_tools-2012.2.tgz</a> <span class="anchor" id="line-166"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.2/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-167"></span><span class="anchor" id="line-168"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2012.1.29:">Major changes (since LITMUS^RT 2012.1):</h4>
<span class="anchor" id="line-169"></span><ul><li>Added P-FP (partitioned fixed-priority) plugin with support for the PCP, DPCP, and MPCP. <span class="anchor" id="line-170"></span></li><li>Added support for arbitrary deadlines. <span class="anchor" id="line-171"></span></li><li><p class="line862">Integration of LITMUS^RT <tt class="backtick">sched_trace_XXX</tt> events with Linux <tt class="backtick">tracepoint</tt> infrastructure (i.e., <a class="http" href="http://rostedt.homelinux.com/kernelshark/">kernelshark</a> support). <span class="anchor" id="line-172"></span></li><li>Improved Feather-Trace triggers (reduced register pressure) <span class="anchor" id="line-173"></span></li><li>Avoidance of &quot;minor&quot; page faults in control page <span class="anchor" id="line-174"></span></li><li>Fixed kernel crash related to precise budget enforcement <span class="anchor" id="line-175"></span></li><li>Improved liblitmus test suite <span class="anchor" id="line-176"></span><span class="anchor" id="line-177"></span><span class="anchor" id="line-178"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2012.1">LITMUS^RT Version 2012.1</h3>
<span class="anchor" id="line-179"></span><span class="anchor" id="line-180"></span><p class="line874">Based on Linux 3.0. Released in January 2012. <span class="anchor" id="line-181"></span><span class="anchor" id="line-182"></span><p class="line867">
<h4 id="Files:-7">Files:</h4>
<span class="anchor" id="line-183"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.1/litmus-rt-2012.1.patch">litmus-rt-2012.1.patch</a> <span class="anchor" id="line-184"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.1/liblitmus-2012.1.tgz">liblitmus-2012.1.tgz</a> <span class="anchor" id="line-185"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.1/ft_tools-2012.1.tgz">ft_tools-2012.1.tgz</a> <span class="anchor" id="line-186"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2012.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-187"></span><span class="anchor" id="line-188"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2011.1.29:">Major changes (since LITMUS^RT 2011.1):</h4>
<span class="anchor" id="line-189"></span><ul><li><p class="line862">Rebased LITMUS<sup>RT</sup> from Linux 2.6.36 to Linux 3.0. <span class="anchor" id="line-190"></span></li><li>Added cache-affinity aware migrations to GSN-EDF and C-EDF. <span class="anchor" id="line-191"></span></li><li>PFAIR and C-EDF now support the release-master feature. <span class="anchor" id="line-192"></span></li><li>Feather-Trace can now measure interrupt interference. <span class="anchor" id="line-193"></span></li><li>PFAIR now supports sporadic task releases. <span class="anchor" id="line-194"></span></li><li>PFAIR now implements early-releasing of subtasks (i.e., work-conserving scheduling). <span class="anchor" id="line-195"></span><span class="anchor" id="line-196"></span></li></ul><p class="line867">
<h3 id="LITMUS-RT_Version_2011.1">LITMUS^RT Version 2011.1</h3>
<span class="anchor" id="line-197"></span><span class="anchor" id="line-198"></span><p class="line874">Based on Linux 2.6.36. Released in January 2011. <span class="anchor" id="line-199"></span><span class="anchor" id="line-200"></span><p class="line867">
<h4 id="Files:-8">Files:</h4>
<span class="anchor" id="line-201"></span><ul><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2011.1/litmus-rt-2011.1.patch">litmus-rt-2011.1.patch</a> <span class="anchor" id="line-202"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2011.1/liblitmus-2011.1.tgz">liblitmus-2011.1.tgz</a> <span class="anchor" id="line-203"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2011.1/ft_tools-2011.1.tgz">ft_tools-2011.1.tgz</a> <span class="anchor" id="line-204"></span></li><li><p class="line891"><a class="http" href="http://www.litmus-rt.org/releases/2011.1/SHA256SUMS">SHA256 check sums</a> <span class="anchor" id="line-205"></span><span class="anchor" id="line-206"></span></li></ul><p class="line867">
<h4 id="Major_changes_.28since_LITMUS-RT_2010.2.29:">Major changes (since LITMUS^RT 2010.2):</h4>
<span class="anchor" id="line-207"></span><ul><li><p class="line862">Rebased LITMUS<sup>RT</sup> from Linux 2.6.34 to Linux 2.6.36. <span class="anchor" id="line-208"></span><span class="anchor" id="line-209"></span></li><li class="gap">Added support for the ARM architecture (tested on a PB11MPCore baseboard with a four-core ARM11 MPCore CPU). <span class="anchor" id="line-210"></span><span class="anchor" id="line-211"></span></li><li class="gap"><p class="line862">Feather-Trace devices are now allocated dynamically and are properly registered with <tt class="backtick">sysfs</tt>. This avoids bugs due to major device number collisions and removes the need for manual device node creation (on a system with standard udev rules). <span class="anchor" id="line-212"></span><span class="anchor" id="line-213"></span></li><li class="gap">Improved debug tracing output and made trace buffer size configurable. <span class="anchor" id="line-214"></span><span class="anchor" id="line-215"></span></li><li class="gap"><p class="line862">Various bug fixes concerning C-EDF cluster size changes. The cluster size can now be configured with the file <tt class="backtick">/proc/litmus/plugins/C-EDF/cluster</tt>. <span class="anchor" id="line-216"></span><span class="anchor" id="line-217"></span></li><li class="gap">Various KConfig cleanups and improvements. <span class="anchor" id="line-218"></span><span class="anchor" id="line-219"></span></li><li class="gap"><p class="line862">Dropped <tt class="backtick">SCons</tt> as the build system for <tt class="backtick">liblitmus</tt> and reverted to makefiles. <span class="anchor" id="line-220"></span><span class="anchor" id="line-221"></span></li><li class="gap"><p class="line862">Added <tt class="backtick">scope</tt> and <tt class="backtick">TAG</tt> file generation to <tt class="backtick">liblitmus</tt>. <span class="anchor" id="line-222"></span><span class="anchor" id="line-223"></span></li><li class="gap"><p class="line891"><tt class="backtick">st_trace</tt> can now be controlled with signals (part of <tt class="backtick">ft_tools</tt>). <span class="anchor" id="line-224"></span><span class="anchor" id="line-225"></span></li></ul><p class="line862">Older releases of LITMUS<sup>RT</sup> are available at UNC's old LITMUS<sup>RT</sup> webpage: <span class="anchor" id="line-226"></span><ul><li><p class="line891"><a class="http" href="http://www.cs.unc.edu/~anderson/litmus-rt/litmus2010.html">2010 series</a> <span class="anchor" id="line-227"></span></li><li><p class="line891"><a class="http" href="http://www.cs.unc.edu/~anderson/litmus-rt/litmus2008.html">2008 series</a> <span class="anchor" id="line-228"></span></li><li><p class="line891"><a class="http" href="http://www.cs.unc.edu/~anderson/litmus-rt/litmus2007.html">2007 series</a> 
<span class="anchor" id="line-229"></span></li></ul>
<span class="anchor" id="bottom"></span></div>


