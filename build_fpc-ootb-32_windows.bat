
TARGET=i386-win32

COMPILER=fpc.exe

INSTALLDIR=C:\fpc-ootb-tmp

make clean

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)

mkdir C:\fpc-ootb-tmp

make all FPC=$COMPILER TARGET=i386-win32  
make FPC=$COMPILER install INSTALL_PREFIX=$INSTALLDIR

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)

mkdir C:\fpc-ootb-32
mkdir C:\fpc-ootb-32\lib
mkdir C:\fpc-ootb-32\license
mkdir C:\fpc-ootb-32\tools
mkdir C:\fpc-ootb-32\units
mkdir C:\fpc-ootb-32\units\i386-win32

xcopy /E /R /Y /Q installbin\*.* C:\codetyphon\


xcopy /E /R /Y /Q C:\ootb\fp.cfg C:\fpc-ootb-32\
xcopy /E /R /Y /Q C:\ootb\fp.ini C:\fpc-ootb-32\
xcopy /E /R /Y /Q C:\ootb\fpc.cfg C:\fpc-ootb-32\
xcopy /E /R /Y /Q C:\ootb\readme.txt C:\fpc-ootb-32\

xcopy /E /R /Y /Q -rf C:\license C:\fpc-ootb-32

xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\lib\fpc\3.2.4\ppc386.exe C:\fpc-ootb-32\fpc-ootb-32.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\bin\fp.exe C:\fpc-ootb-32\fpide-ootb-64.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\lib\libpas2jslib.dll C:\fpc-ootb-32\lib\
xcopy /E /R /Y /Q -rf C:\fpc-ootb-tmp\usr\lib\fpc\3.2.4\units\i386-win32 C:\fpc-ootb-32\units
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\bin\fpcres.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\bin\h2pas.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\bin\fpcjres.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\usr\bin\pas2js.exe C:\fpc-ootb-32\tools\


