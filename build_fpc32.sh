#!/bin/sh 

TARGET_VER=3.2.0 

 TARGET=i386-linux 
 COMPILER=/usr/lib/fpc/3.0.4/ppc386

make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/usr/
