#!/bin/sh 

TARGET_VER=3.2.0 

TARGET=x86_64-freebsd
COMPILER=/usr/local/lib/fpc/3.0.4/ppcx64

gmake clean
gmake all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
gmake FPC=$COMPILER install INSTALL_PREFIX=/usr/local/
