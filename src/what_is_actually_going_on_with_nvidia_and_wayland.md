# What is *acutally* going on with nvidia and wayland?

## January 16th, 2020

<small>
**General Disclaimer**: I haven't perused the source code of mesa
or other libraries, most of my info is based off of xdc
talks, random phoronix articles (thanks Michael Larabel) and, worst of all, Wikipedia.
If you find an error here and want to correct
me feel free to send an email to christopher.r.odom@gmail.com
or even open a PR on this website.
</small>

Wayland and Nvidia don't play nicely with each other.
This is yet another iteration of Nvidia not really playing
too nicely with the free software side of Linux development.
The core of this issue is that Nvidia is either not willing
or not able to provide support for a Mesa API that Wayland
depends on.

All GPUs support a wide variety of open and closed
APIs that enable software to easily
use a wide variety of GPUs without having to consider
vendor, generation, chipset, etc. The benefits of this are
numerous, however the problem is that the industry hasn't
converged on a single open standard that all vendors are
willing or able to use, and probably never will.
The wide variety of problems that GPUs can solve
lends itself to different API design patterns, and as a result
the closest thing we have to a coherent standard are the
myriad of APIs that the Khronos group has developed.

The core of this API problem is that the
Wayland group uses something called Generic Buffer Management
(GBM), which sits in Mesa and isn't officially supported by
Nvidia.

### Mesa, GBM, and Nvidia

The story of Mesa is pretty simple. Mesa is an open source implementation
of a whole bunch of open source APIs, ie OpenGL, Vulkan, VDPAU, etc.
However Nvidia isn't a contributor to the Mesa project, and instead
ships most of their apis with their driver. Moreover Nvidia requires
signed firmware which Mesa would need in order to execute their APIs,
and Nvidia is slow to provide anything but the bare minimum to the community.
Because of this the only way to interact with any modern Nvidia GPU effectively
is to use the proprietary Nvidia driver and accept whatever APIs
Nvidia decides to officially support. However this is a problem
because Nvidia doesn't with to replicate the Generic Buffer Management
API that exists inside of Mesa and instead wants for Wayland to use
EGL streams to setup their internal buffers.

### EGL

EGL is an API developed by the Khronos group that serves as the
interface between a window system and other rendering APIs.
It essentially provides a transport layer between
different types of 2d and 3d application consumers
and producers. [This actually allows for Wayland to do direct
rendering](./src/The_Linux_Graphics_Stack_and_glamor.svg)

However the thing is that Wayland also uses the GBM
for client intercommunication, which is unsupported by the official
proprietary Nvidia driver. Nvidia has submitted a couple of egl implementations
of the Wayland Compositor code which both Gnome and KDE have attempted
to integrate into their respective compositors, but it's still
rather cumbersome. (At the very least it doesn't work on my machine :( )
And that's not to mention smaller repos like swaywm and the bare
weston compositor decided to not support Nvidia GPUs at all.

All of this lends itself towards a general problem of GPU
libraries, in that it's extremely fragmented due in part to
the variance in the underlying hardware, but also due in part
for the wide variety of problems that people try to solve with
GPUs. If you want to make games you use OpenGL or Vulkan.
(or directX, but only on Windows) whereas if you want to make a windowing
system, you are more concerned with managing buffers
in a more ipc context and should use EGL or GBM.
Whereas if your goal is to train an AI, OpenCL or Cuda is more your
speed.

So the summary of this Wayland/Nvidia dispute is simply that
Nvidia refuses to support mesa or mesa specific APIs, whereas
Wayland requires these APIs. And while you *could*
just reimplement the client connection code in Wayland
to use EGL streams instead of GBM buffers, then you have to
maintain two different implementations of the same thing,
which is something that Wayland wants to avoid.
