#!/bin/sh 

TARGET_VER=3.2.2 

TARGET=x86_64-linux 
COMPILER=/home/fred/fpc-ootb_bin/fpc-ootb-320-x86_64-linux/fpc-ootb-64

make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/usr/
