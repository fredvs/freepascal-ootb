#!/bin/sh 

TARGET=x86_64-openbsd

COMPILER=fpc

INSTALLDIR=/tmp/fpc-ootb/usr

gmake clean
rm -f -r /tmp/fpc-ootb
mkdir /tmp/fpc-ootb
mkdir /tmp/fpc-ootb/usr


gmake all FPC=$COMPILER OPT="-Fl/usr/local/lib" 
gmake FPC=$COMPILER install INSTALL_PREFIX=$INSTALLDIR

rm -f -r ./fpc-ootb-64
mkdir ./fpc-ootb-64
mkdir ./fpc-ootb-64/lib
mkdir ./fpc-ootb-64/license
mkdir ./fpc-ootb-64/tools
mkdir ./fpc-ootb-64/units
mkdir ./fpc-ootb-64/units/x86_64-openbsd

cp ./ootb/fp.cfg ./fpc-ootb-64/
cp ./ootb/fp.ini ./fpc-ootb-64/
cp ./ootb/fpc.cfg ./fpc-ootb-64/
cp ./ootb/readme.txt ./fpc-ootb-64/

cp -rf ./license ./fpc-ootb-64

cp /tmp/fpc-ootb/usr/lib/fpc/3.2.4/ppcx64 ./fpc-ootb-64/fpc-ootb-64
cp /tmp/fpc-ootb/usr/bin/fp ./fpc-ootb-64/fpide-ootb-64
cp /tmp/fpc-ootb/usr/lib/libpas2jslib.so ./fpc-ootb-64/lib/
cp -rf /tmp/fpc-ootb/usr/lib/fpc/3.2.4/units/x86_64-openbsd ./fpc-ootb-64/units
cp /tmp/fpc-ootb/usr/bin/fpcres ./fpc-ootb-64/tools/
cp /tmp/fpc-ootb/usr/bin/h2pas ./fpc-ootb-64/tools/
cp /tmp/fpc-ootb/usr/bin/fpcjres ./fpc-ootb-64/tools/
cp /tmp/fpc-ootb/usr/bin/pas2js ./fpc-ootb-64/tools/

tar -zcvf fpc-ootb-324-x86_64-openbsd.tar.gz ./fpc-ootb-64
rm -f -r /tmp/fpc-ootb
#rm -f -r ./fpc-ootb-64

