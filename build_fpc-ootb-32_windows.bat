
TARGET=i386-win32

COMPILER=fpc.exe

INSTALLDIR=C:\fpc-ootb-tmp

make clean
rm -f -r C:\fpc-ootb-tmp
mkdir C:\fpc-ootb-tmp

make all FPC=$COMPILER TARGET=i386-win32  
make FPC=$COMPILER install INSTALL_PREFIX=$INSTALLDIR

rm -f -r C:\fpc-ootb-32
mkdir C:\fpc-ootb-32
mkdir C:\fpc-ootb-32\lib
mkdir C:\fpc-ootb-32\license
mkdir C:\fpc-ootb-32\tools
mkdir C:\fpc-ootb-32\units
mkdir C:\fpc-ootb-32\units\i386-win32

cp C:\ootb\fp.cfg C:\fpc-ootb-32\
cp C:\ootb\fp.ini C:\fpc-ootb-32\
cp C:\ootb\fpc.cfg C:\fpc-ootb-32\
cp C:\ootb\readme.txt C:\fpc-ootb-32\

cp -rf C:\license C:\fpc-ootb-32

cp C:\fpc-ootb-tmp\usr\lib\fpc\3.2.4\ppcx64 C:\fpc-ootb-32\fpc-ootb-32
cp C:\fpc-ootb-tmp\usr\bin\fp C:\fpc-ootb-32\fpide-ootb-64
cp C:\fpc-ootb-tmp\usr\lib\libpas2jslib.so C:\fpc-ootb-32\lib\
cp -rf C:\fpc-ootb-tmp\usr\lib\fpc\3.2.4\units\i386-win32 C:\fpc-ootb-32\units
cp C:\fpc-ootb-tmp\usr\bin\fpcres C:\fpc-ootb-32\tools\
cp C:\fpc-ootb-tmp\usr\bin\h2pas C:\fpc-ootb-32\tools\
cp C:\fpc-ootb-tmp\usr\bin\fpcjres C:\fpc-ootb-32\tools\
cp C:\fpc-ootb-tmp\usr\bin\pas2js C:\fpc-ootb-32\tools\

#tar -zcvf fpc-ootb-324_i386-win32.tar.gz C:\fpc-ootb-32
rm -f -r C:\fpc-ootb-tmp
#rm -f -r C:\fpc-ootb-32

