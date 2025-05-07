![alt text](https://github.com/fredvs/attach/assets/3421249/62c44816-12e3-46b8-91b5-bc75bf32623a) 


# fpc-ootb.

This is a fork from Free Pascal. https://www.freepascal.org/

Free Pascal OOTB works out of the box.

The last commits on branch main are based on fpc 3.2.4 release_3_2_4-branch.
https://gitlab.com/freepascal.org/fpc/source/-/tree/release_3_2_4-branch
 
Commits before 3.2.4 on branch main are based on fpc 3.2.2 official release source.
https://gitlab.com/freepascal.org/fpc/source/-/tree/release_3_2_2/

The branch fixes_3.0 is based on fpc 3.0.5.
https://svn.freepascal.org/svn/fpc/branches/fixes_3_0/

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

*-Fu/$FPCBINDIR/units/$fpctarget*

*-Fu/$FPCBINDIR/units/$fpctarget/**

*-Fu/$FPCBINDIR/units/$fpctarget/rtl*

NEW: Release OOTB-glibc255 for Linux 64 bit cpu x86_64: with signed symbol
GLIBC_2.2.5. for all glibc methods and link with \'libdl.so.2\'. This is
to have binaries that run on system with older or newer version of glibc
than the one on the system-compilation.

NEW: Release OOTB-glibc20 for Linux 32 bit cpu i386: with signed symbol
GLIBC_2.0. for all glibc methods and link with \'libdl.so.2\'. This is
to have binaries that run on system with older or newer version of glibc
than the one on the system-compilation. Also fixed libc_csu_init and
l_ibc_csu_fini\_ error at linking on last Linux distros.

NEW: Release OOTB-glibc24 for Linux 32 bit cpu arm: with signed symbol
GLIBC_2.4. for all glibc methods and link with \'libdl.so.2\'. This is
to have binaries that run on system with older or newer version of glibc
than the one on the system-compilation. 

There is binary release for Windows 64/32 bit, Linux 64/32 bit and
Rasbian ARM32/aarch64 Rpi, FreeBSD 64 bit and OpenBSD 64/32 bit.
https://github.com/fredvs/freepascal-ootb/releases

*(Image on top is the Pascal's Mystic Hexagram)*

Have lot of fun!
