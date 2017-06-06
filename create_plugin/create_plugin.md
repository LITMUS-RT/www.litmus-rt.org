Title:  Writing a LITMUS^RT Scheulder Plugin
CSS:    ../inc/format.css

{{../inc/header2.markdown}}

Writing a LITMUS^RT Scheduler Plugin
====================================

In LITMUS, new scheduling policies are implemented as *scheduler plugins*, which are run in kernelspace. This set of instructions describes how to write a scheduler plugin in LITMUS^RT by re-creating the Partitioned-EDF (P-EDF) scheduler.

## Prerequisites

In order to create new scheduler plugins, you must be capable of building the LITMUS^RT kernel from source. If you haven't already, follow the [instructions for building and installing LITMUS^RT](../installation.html).

## Steps

The instructions for implementing a new LITMUS^RT scheduler plugin have been separated into 9 steps:

 1. [Adding an empty source file to the LITMUS^RT kernel](plugin_step_1.html)
 2. [Adding stub functions for a LITMUS^RT plugin](plugin_step_2.html)
 3. [Creating debug messages using TRACE](plugin_step_3.html)
 4. [Defining per-CPU scheduling state for P-EDF](plugin_step_4.html)
 5. [Adding P-EDF scheduling logic](plugin_step_5.html)
 6. [Task state changes](plugin_step_6.html)
 7. [Adding preemption checks](plugin_step_7.html)
 8. [Admitting real-time tasks](plugin_step_8.html)
 9. [Exporting plugin topology in `/proc`](plugin_step_9.html)

