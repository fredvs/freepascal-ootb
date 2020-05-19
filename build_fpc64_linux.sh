#!/bin/sh 

TARGET_VER=3.0.5 

TARGET=x86_64-linux 
COMPILER=/usr/lib/fpc/3.0.4/ppcx64

make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/usr/
