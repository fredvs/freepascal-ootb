#!/bin/sh 

TARGET_VER=3.2.2 

 TARGET=i386-linux 
 COMPILER=/home/fred/fpc_ootb/fpc-ootb-322-i386-linux_glibc20/fpc-ootb-32

make clean
make all FPC=$COMPILER OPT="-Fl/usr/lib/gcc/x86_64-linux-gnu/11/32 -Fu/usr/lib/gcc/x86_64-linux-gnu/11/32" 
make FPC=$COMPILER install INSTALL_PREFIX=/home/fred/fpc-ootb-work32/usr
