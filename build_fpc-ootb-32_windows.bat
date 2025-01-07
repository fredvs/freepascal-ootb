make clean

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)

mkdir C:\fpc-ootb-tmp

make all FPC=fpc.exe TARGET=i386-win32  
make FPC=fpc.exe install INSTALL_PREFIX=C:\fpc-ootb-tmp

if EXIST C:\fpc-ootb-32 (
del /f/s/q C:\fpc-ootb-32 > nul
rmdir /s/q C:\fpc-ootb-32
)

mkdir C:\fpc-ootb-32
mkdir C:\fpc-ootb-32\lib
mkdir C:\fpc-ootb-32\license
mkdir C:\fpc-ootb-32\tools
mkdir C:\fpc-ootb-32\units
mkdir C:\fpc-ootb-32\units\i386-win32

xcopy /E /R /Y /Q ootb\fp.cfg C:\fpc-ootb-32\
xcopy /E /R /Y /Q ootb\fp.ini C:\fpc-ootb-32\
xcopy /E /R /Y /Q ootb\fpc.cfg C:\fpc-ootb-32\
xcopy /E /R /Y /Q ootb\readme.txt C:\fpc-ootb-32\

xcopy /E /R /Y /Q /S license C:\fpc-ootb-32\license\

xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\ppc386.exe C:\fpc-ootb-32\
ren C:\fpc-ootb-32\ppc386.exe fpc-ootb-32.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\fp.exe C:\fpc-ootb-32\
ren C:\fpc-ootb-32\fp.exe fpide-ootb-32.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\pas2jslib.dll C:\fpc-ootb-32\lib\
xcopy /E /R /Y /Q /S C:\fpc-ootb-tmp\units\i386-win32 C:\fpc-ootb-32\units
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\fpcres.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\h2pas.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\fpcjres.exe C:\fpc-ootb-32\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\i386-win32\pas2js.exe C:\fpc-ootb-32\tools\

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)
