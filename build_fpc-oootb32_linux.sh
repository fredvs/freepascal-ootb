#!/bin/sh 

TARGET=i386-linux

COMPILER=fpc

INSTALLDIR=/tmp/fpc-ootb/usr

make clean
rm -f -r /tmp/fpc-ootb
mkdir /tmp/fpc-ootb
mkdir /tmp/fpc-ootb/usr

make all FPC=$COMPILER OPT="-Fl/usr/lib/gcc/x86_64-linux-gnu/13/32 -Fu/usr/lib/gcc/x86_64-linux-gnu/13/32" 
make FPC=$COMPILER OPT="-Fl/usr/lib/gcc/x86_64-linux-gnu/13/32 -Fu/usr/lib/gcc/x86_64-linux-gnu/13/32"  install INSTALL_PREFIX=$INSTALLDIR

rm -f -r ./fpc-ootb-32
mkdir ./fpc-ootb-32
mkdir ./fpc-ootb-32/lib
mkdir ./fpc-ootb-32/license
mkdir ./fpc-ootb-32/tools
mkdir ./fpc-ootb-32/units
mkdir ./fpc-ootb-32/units/i386-linux

cp ./ootb/fp.cfg ./fpc-ootb-32/
cp ./ootb/fp.ini ./fpc-ootb-32/
cp ./ootb/fpc.cfg ./fpc-ootb-32/
cp ./ootb/readme.txt ./fpc-ootb-32/

cp -rf ./license ./fpc-ootb-32

cp /tmp/fpc-ootb/usr/lib/fpc/3.2.4/ppc386 ./fpc-ootb-32/fpc-ootb-32
cp /tmp/fpc-ootb/usr/bin/fp ./fpc-ootb-32/fpide-ootb-32
cp /tmp/fpc-ootb/usr/lib/libpas2jslib.so ./fpc-ootb-32/lib/
cp -rf /tmp/fpc-ootb/usr/lib/fpc/3.2.4/units/i386-linux ./fpc-ootb-32/units
cp /tmp/fpc-ootb/usr/bin/fpcres ./fpc-ootb-32/tools/
cp /tmp/fpc-ootb/usr/bin/h2pas ./fpc-ootb-32/tools/
cp /tmp/fpc-ootb/usr/bin/fpcjres ./fpc-ootb-32/tools/
cp /tmp/fpc-ootb/usr/bin/pas2js ./fpc-ootb-32/tools/

tar -zcvf fpc-ootb-324-i386-linux_glibc20.tar.gz ./fpc-ootb-32
rm -f -r /tmp/fpc-ootb
#rm -f -r ./fpc-ootb-32