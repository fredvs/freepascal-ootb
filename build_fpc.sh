#!/bin/sh 

TARGET_VER=3.2.0 

TARGET=x86_64-linux 
# TARGET=i386-linux 
 COMPILER=/usr/lib/fpc/3.0.4/ppcx64
# COMPILER=/usr/lib/fpc/3.0.4/ppc386


make clean
make all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
make FPC=$COMPILER install INSTALL_PREFIX=/usr/
