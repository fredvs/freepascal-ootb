
This is a fork from Free Pascal:

https://svn.freepascal.org/svn/fpc/branches/fixes_3_2

This fpc version is based on fpc 3.2.0 R1.

With the possibility for Unix users to link libraries with so numbers, like libX11.so.6.
This without the need to install dev package.

Also you may place the fpc.cfg file in the same directory as the compiler, it will be loaded.

Added a new macro: $FPCTARGET means root directory of the compiler.

In your fpc.cfg file is allowed -Fu$FPCTARGET/thedirectory.

Example:

-Fu$FPCTARGET/units/$fpctarget
-Fu$FPCTARGET/units/$fpctarget/*
-Fu$FPCTARGET/units/$fpctarget/rtl
