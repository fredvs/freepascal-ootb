
This is a fork from Free Pascal:

Free Pascal OOTB works out of the box.

The branch master branch is based on fpc 3.2.0 R1.
https://svn.freepascal.org/svn/fpc/branches/fixes_3_2

The fpc_3.0.5 branch is based on fpc 3.0.5
https://svn.freepascal.org/svn/fpc/branches/fixes_3_0

With the possibility for Unix users to link libraries with so numbers, like libX11.so.6.
This without the need to install dev package.

Also you may place the fpc.cfg file in the same directory as the compiler, it will be loaded.

Added a new macro: $FPCBINDIR means root directory of the compiler.
[EDIT] That macro was added in commit 44697 12/04/20 of fpc trunk.

In your fpc.cfg file is allowed -Fu$FPCBINDIR/thedirectory.

Example:

-Fu$FPCBINDIR/units/$fpctarget
-Fu$FPCBINDIR/units/$fpctarget/*
-Fu$FPCBINDIR/units/$fpctarget/rtl

There is binary release for Windows 64/32 bit, Linux 64/32 bit and Rasbian ARM Rpi:
[EDIT] Added release for FreeBSD 64 bit.
https://github.com/fredvs/freepascal-ootb/releases

Have lot of fun!

