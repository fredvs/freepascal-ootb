![alt text](https://github.com/fredvs/attach/assets/3421249/04c74be5-c40f-4f6f-9908-e57e7f6e3d21)

# fpc-ootb.

This is a fork from Free Pascal. https://www.freepascal.org/

Free Pascal OOTB works out of the box.

The branch main is based on fpc 3.2.2 official release source.
https://gitlab.com/freepascal.org/fpc/source/-/tree/release_3\_2_2/

The branch fixes_3.0 is based on fpc 3.0.5.
https://svn.freepascal.org/svn/fpc/branches/fixes_3\_0

With the possibility for Unix users to link libraries with so numbers,
like libX11.so.6 or libdl.so.2.
This without the need to install dev package.

For FreeBSD OS, the linker ld.bsd will be used, without any tweak of
your system.

Also, for all OS, you may place the fpc.cfg file in the same directory
as the compiler, it will be loaded.

Added a new macro: \$FPCBINDIR means root directory of the compiler.
\[EDIT\] That macro was added in commit 44697 12/04/20 of fpc trunk.

In your fpc.cfg file is allowed -Fu\$FPCBINDIR/thedirectory.

Example:

-Fu\$FPCBINDIR/units/\$fpctarget -Fu\$FPCBINDIR/units/\$fpctarget/\*
-Fu\$FPCBINDIR/units/\$fpctarget/rtl

NEW: Release OOTB-glibc255 for Linux 64 bit: with signed symbol
GLIBC_2.2.5. for all glibc methods and link with \'libdl.so.2\'. This is
to have binaries that run on system with older or newer version of glibc
than the one on the system-compilation.

NEW: Release OOTB-glibc20 for Linux 32 bit: with signed symbol
GLIBC_2.0. for all glibc methods and link with \'libdl.so.2\'. This is
to have binaries that run on system with older or newer version of glibc
than the one on the system-compilation. Also fixed libc_csu_init and
l_ibc_csu_fini\_ error at linking on last Linux distros.

There is binary release for Windows 64/32 bit, Linux 64/32 bit and
Rasbian ARM32/aarch64 Rpi: \[EDIT\] Added release for FreeBSD 64 bit.
https://github.com/fredvs/freepascal-ootb/releases

Have lot of fun!
