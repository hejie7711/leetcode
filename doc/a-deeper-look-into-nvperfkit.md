NVPerfKit值得深入

> 原文链接 http://hakzsam.wordpress.com/2014/06/20/a-deeper-look-into-nvperfkit/

NVIDIA NVPerfKit is a suite of performance tools to help developpers in identifying the performance bottleneck of OpenGL and Direct3D applications. It allows you to monitor hardware performance counters which are used to store the counts of hardware-related activities from the GPU itself. These performance counters (called “graphics counters” by NVIDIA) are usually used by developers to identify bottlenecks in their applications, like “how the gpu is busy?” or “how many triangles have been drawn in the current frame?” and so on. But, NVPerfKit is only available on Windows.

This year, my Google Summer of Code project is to expose NVIDIA’s graphics counter to help Linux/Nouveau developpers in improving their OpenGL applications. At the end of this summer, this project aims to offer a Linux version of NVPerfkit for NVIDIA’s graphics cards (only GeForce 8, 9 and 2XX in a first time) .  To expose these hardware events to the userspace, we have to write an interface between the Linux kernel and mesa. Basically, the idea is to tell to the kernel to monitor signal X and read back results from the userspace (i.e. mesa). However, before writing that interface we have to study the behaviours of NVPerfKit on Windows.

In a first time, let me explain (again) what is really a hardware performance counter. A hardware performance counter is a set of special registers used to count hardware-relatd activities. There are two type of counters, global counters from PCOUNTER and (local) MP counters. PCOUNTER is the card unit which contains most of the performance counters. PCOUNTER is divided in 8 domains (or sets) on nv50/Tesla. Each domain has a different source clock and has 255+ input signals that can themselves be the output of one multiplexer. PCOUNTER uses global counters whereas MP counters are per-app and context switched. Actually, these two types of counters are not really independent and may share some configuration parts, for example, the output of a signal multiplexer. On Tesla/nv50, it is possible to monitor 4 macro signals concurrently per domain. A macro signal is the aggregation of 4 signals which have been combined with a function. In this post, we are only focusing on global counters. Now, the question is how NVPerfKit monitors these global performance counters ?

Case #1 : How NVPerfKit handles multiple apps being monitored concurrently ?

NVIDIA does not handle this case at all, and the behaviour is thus undefined when more than one application is monitoring performance counters at the same time. Then, because of the issue of shared configuration of global counters (PCOUNTER) and local counters (MP counters), I think it’s a bad idea to allow monitoring multiple applications concurrently. To solve this problem, I suggest, at first, to use a global lock for allowing only one application at a time and for simplifying the implementation.

Case #2 : How NVPerfKit handles only one counter per domain ?

This is the simplest case, and there are no particular requirements.

Case #3 : How NVPerfKit handles multiple counters per domain ?

NVPerfKit uses a round robin mode, then it still monitors only one counter per domain and it switches the current counter after each frame.

Case #4 : How NVPerfKit handles multiple counters on different domains ?

No problem here, NVPerfKit is able to monitor multiple counters on different domains (each domain having up to one event to monitor).

To sum up, NVPerfKit always uses a round robin mode when it has to monitor more than one hw event on the same domain.

Concerning the sampling part, NVIDIA say (NVPerfKit User Guide – page 11 – Appendix B. Counters reference):

All of the software/driver counters represent a per frame accounting. These counters are accumulated and updated in the driver per frame, so even if you sample at a sub-frame rate frequency, the software counters will hold the same data (from the previous frame) until the end of the current frame.

This article should have been published the last month, but during this time I worked on the prototype’s definition and its implementation. Currently, I have a first prototype which works quite well, I’ll submit it the next week.

See you the next week!
