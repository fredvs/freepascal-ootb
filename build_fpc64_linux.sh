#!/bin/sh 

TARGET_VER=3.2.2 

TARGET=x86_64-linux 
COMPILER=/home/fred/fpc_ootb/fpc-ootb-322-x86_64-linux_glibc225/fpc-ootb-64

make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/home/fred/fpc-ootb-work/usr