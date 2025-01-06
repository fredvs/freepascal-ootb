
This is a fork from Free Pascal:

https://svn.freepascal.org/svn/fpc/branches/fixes_3_2

This fpc version is based on fpc 3.2.0. official release.

With the possibility for Unix users to link libraries with so numbers, like libX11.so.6.
This without the need to install dev package.

Also you may place the fpc.cfg file in the same directory as the compiler, it will be loaded.

Added a new macro: $FPCBINDIR means root directory of the compiler.
[EDIT] That macro was added in commit 44697 12/04/20 of fpc 3.3.1 trunk.

In your fpc.cfg file is allowed -Fu$FPCBINDIR/thedirectory.

Example:

-Fu$FPCBINDIR/units/$fpctarget
-Fu$FPCBINDIR/units/$fpctarget/*
-Fu$FPCBINDIR/units/$fpctarget/rtl
