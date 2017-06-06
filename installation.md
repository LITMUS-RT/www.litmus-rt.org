Title:  LITMUS-RT Installation Instructions
CSS:    inc/format.css


{{inc/header.markdown}}

Installing LITMUS^RT
====================

Working with LITMUS^RT generally requires compiling the entire LITMUS^RT kernel from source, and then installing liblitmus and Feather-Trace. The following instructions include cover all of the necessary compilation and installation steps.

{{TOC}}


These instructions were tested on 32- and 64-bit versions of Ubuntu 14.04 and 16.04 (running in VirtualBox VMs), but should be largely identical for other platforms. When in doubt, contact the LITMUS^RT mailing list.

## Prerequisites

Some Linux systems, including Ubuntu 14.04, do not have `git` or the `ncurses` and `openssl` libraries installed by default. These are needed for compiling LITMUS^RT, and can be installed on Debian-based systems (including Ubuntu) using this command:

```bash
sudo apt install libncurses-dev git libssl-dev
```

Create a directory to contain all of the litmus-related code. This directory is identified using the `$DIR` environment variable for the remainder of this tutorial:

```bash
mkdir litmus
cd litmus
export DIR=`pwd`
```


## Configuring and compiling the LITMUS^RT kernel

First, obtain a copy of the LITMUS^RT kernel code:

```bash
cd $DIR
git clone https://github.com/LITMUS-RT/litmus-rt.git
cd litmus-rt
```

Next, we need to configure the compile-time kernel options.

## Obtaining a default kernel configuration

If it's available, the kernel configuration used by the currently running kernel is usually a good starting point when configuring a new kernel. On Ubuntu systems, the kernel configuration files for the pre-installed kernels are located in the `/boot` directory, and can be copied by running the following command (in the `$DIR/litmus-rt` directory):

```bash
cp /boot/config-`uname -r` .config
```

Alternatively, on other systems, the existing kernel configuration options may be contained in `/proc/config.gz`:

```bash
zcat /proc/config.gz > .config
```

Finally, if neither of the two options worked and you can't locate an existing configuration file for your system, you can run the following command to generate a default configuration:

```bash
make defconfig
```

After a suitable initial configuration has been obtained with one of the above steps (or after simply creating a new configuration from scratch), some further adjustments are needed for LITMUS^RT to work correctly.

## Adjusting configuration options for LITMUS^RT

These instructions use the menu configuration tool to locate and adjust the options needed for LITMUS^RT. Access this tool by running the following command:

```bash
cd $DIR/litmus-rt
make menuconfig
```

You'll need to find and adjust several configuration options. I'll include the locations of the settings in the menu-based configuration for my Ubuntu systems, but these locations may change depending on which base version of the Linux kernel you're using:

 - Add a recognizable local version, such as `-litmus`.

    - This can be entered under `General setup`->`Local version - append to kernel release`.

 - Enable in-kernel preemptions.

    - This can be set under `Processor type and features`->`Preemption model`. Choose `Preemptible Kernel (Low-Latency Desktop)`.

 - Disable group scheduling.

    - First, disable the `Automatic process group scheduling` option under `General setup`.
    - Second, under `General setup`->`Control group support`->`CPU controller`, disable `Group scheduling for SCHED_OTHER`

 - Disable frequency scaling and power management options that affect timer frequency.

    - Under `General setup`->`Timers subsystem`->`Timer tick handling`, set the option to `constant rate, no dynticks`.
    - Under `Power management and ACPI options`, make sure that `Suspend to RAM and standby`, `Hibernation` and `Opportunistic sleep` are disabled.
    - Under `Power management and ACPI options`->`CPU Frequency scaling`, disable `CPU Frequency scaling`.

<!--
 - On my system, the AS102 driver would encounter a compilation error when building the LITMUS^RT kernel, so I disabled it. This isn't necessary unless you encounter compilation errors in `as102`-related files.

    - Under `Device Drivers`->`Multimedia Support`->`Media USB Adapters`, disable `Abilis AS102 DVB Receiver`.

-->

 - When planning to do development, enable tracing in LITMUS^RT.

    - Under `LITMUS^RT`->`Tracing`, enable `TRACE() debugging`
    - Note that this is a **high-overhead** debug tracing interface that must not be enabled for any benchmarks or production use of the system.


## Compiling the LITMUS^RT kernel

After finishing making configuration changes, save the updated configuration (keep the `.config` name). Afterwards, run the following commands to build the LITMUS^RT kernel:

```bash
make bzImage
make modules
```

This will take some time. To speed things up a little, you may want to enable a parallel build by giving the `-j` option to `make` (with a limit of twice the number of cores or so). 


## Installing the LITMUS^RT kernel

After compiling the LITMUS^RT kernel, install it using the following commands:

```bash
cd $DIR/litmus-rt
sudo make modules_install
sudo make install
```
(These instructions will usually differ somewhat on non-x86 platforms and when cross-compiling.)

Finally, configure the boot loader (e.g., grub in Ubuntu and most modern distros on x86) to show the boot menu, to allow the LITMUS^RT kernel to be selected during boot rather than the default Linux kernel.

```bash
# Comment out the line containing GRUB_HIDDEN_TIMEOUT, then save the changes.
sudo nano /etc/default/grub

# Re-generate grub's internal configuration settings.
sudo update-grub
```

You should now be able to reboot your system and select the Litmus kernel from the boot menu.


## Building liblitmus

After the kernel has been built, proceed next to building liblitmus, which is the userspace portion of LITMUS^RT. This includes both libraries for writing real-time tasks and utilities such as `setsched` for managing the system's schedulers.

To download and build liblitmus:

```bash
# You can place liblitmus elsewhere, but it's more convenient to put it
# somewhere relative to the LITMUS^RT kernel source code, which is required when
# compiling liblitmus.
cd $DIR

# Obtain a copy of the liblitmus source code
git clone https://github.com/LITMUS-RT/liblitmus.git
cd liblitmus

# Usually, no configuration file is needed for liblitmus. However, if you didn't
# place liblitmus in the same location as the LITMUS^RT kernel source code's
# directory, then you'll need to provide a .config file to refer to the correct
# location of the LITMUS^RT kernel source code. Download the following template to
# get started.
wget -O .config http://www.litmus-rt.org/releases/2016.1/liblitmus-config

# Finally, compile liblitmus
make
```


## Building the Feather-Trace Tools

The Feather-Trace tools are needed to trace and visualize scheduling events, and to measure overheads when using LITMUS^RT. Feather-Trace tools are built in a manner identical to liblitmus, with the sole difference that the (in the common case purely optional) `.config` file refers to the location of liblitmus rather than the LITMUS^RT kernel source.

To download and build Feather-Trace:

```bash
cd $DIR
git clone https://github.com/LITMUS-RT/feather-trace-tools.git
cd feather-trace-tools
wget -O .config http://www.litmus-rt.org/releases/2016.1/ft_tools-config
make
```

## Next Steps

At this point, reboot the system into LITMUS^RT and try running a few examples. Check out the [tutorial](tutorial/index.html) for some initial steps, or the [plugin creation tutorial](create_plugin/create_plugin.html) to start writing a LITMUS^RT scheduler plugin.

