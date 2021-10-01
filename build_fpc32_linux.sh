#!/bin/sh 

TARGET_VER=3.2.2 

 TARGET=i386-linux 
 COMPILER=/home/fred/fpc-ootb_bin/fpc-ootb-320-i386-linux/fpc-ootb-32

make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/usr/
