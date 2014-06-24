NVPerfKit值得深入

> 原文链接 http://hakzsam.wordpress.com/2014/06/20/a-deeper-look-into-nvperfkit/

NVIDIA NVPerfKit可以帮助开发者发现OpenGL和Direct3D应用程序中的性能瓶颈。你可以
监视硬件性能计数器，记录GPU硬件相关的活动次数。开发者使用性能计数器（NVIDIA称之
为“图形计数器”）发现应用程序的瓶颈，比如“gpu有多忙？”或者“当前帧已经绘制了多少
个三角形？”但是，NVPerfKit只有Windows版。

今年Samuel的Google夏季编程项目要揭开NVIDIA的图形计数器的面纱，帮助Linux/Nouveau
开发者改进OpenGL应用程序。到暑期结束，该项目旨在提供NVIDIA显卡（只支持GeForce 
8、9和2XX先）Linux版的NVPerfKit。把硬件事件映射到用户态，我们必须在Linux内核和
mesa直接写接口。基本思路就是告诉内核去监视信号X，读用户态（例如mesa）返回的结果。
但是，在写该接口之前，我们需要学习一下Windows版NVPerfKit。

首先，让我（再）解释什么是硬件性能计数器。一个硬件性能计数器是一组特殊的寄存器，
用来统计硬件相关的活动次数。有两种计数器，PCOUNTER全局计数器和（本地）MP计数器。
PCOUNTER包含了绝大多数的性能计数器。PCOUNTER在nv50/Tesla被划分为8个域（集）。每
个域有不同的时钟、255+输入信号可以多路输出复用。PCOUNTER使用全局计数器，而MP
计数器是单应用的、上下文切换的。实际上，这两种计数器不是独立的，可能共享某些
组态，比如，信号多路输出复用。Tesla/nv50有可能同时监视4个宏信号/域。1个宏信号
是4个信号的聚合，组合成了1个函数。我们只关注全局计数器。那么NVPerfKit是如何监视
这些全局性能计数器的呢？

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
