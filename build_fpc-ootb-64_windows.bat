make clean

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)

mkdir C:\fpc-ootb-tmp

make all FPC=C:\Users\fiens\fpc-ootb-322-x86_64-win64\fpc-ootb-64.exe TARGET=x86_64-win64  
make FPC=C:\Users\fiens\fpc-ootb-322-x86_64-win64\fpc-ootb-64.exe install INSTALL_PREFIX=C:\fpc-ootb-tmp

if EXIST C:\fpc-ootb-64 (
del /f/s/q C:\fpc-ootb-64 > nul
rmdir /s/q C:\fpc-ootb-64
)

mkdir C:\fpc-ootb-64
mkdir C:\fpc-ootb-64\lib
mkdir C:\fpc-ootb-64\license
mkdir C:\fpc-ootb-64\tools
mkdir C:\fpc-ootb-64\units
mkdir C:\fpc-ootb-64\units\x86_64-win64

xcopy /E /R /Y /Q ootb\fp.cfg C:\fpc-ootb-64\
xcopy /E /R /Y /Q ootb\fp.ini C:\fpc-ootb-64\
xcopy /E /R /Y /Q ootb\fpc.cfg C:\fpc-ootb-64\
xcopy /E /R /Y /Q ootb\readme.txt C:\fpc-ootb-64\

xcopy /E /R /Y /Q /S license C:\fpc-ootb-64\license\

xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\ppcx64.exe C:\fpc-ootb-64\
ren C:\fpc-ootb-64\ppcx64.exe fpc-ootb-64.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\fp.exe C:\fpc-ootb-64\
ren C:\fpc-ootb-64\fp.exe fpide-ootb-64.exe
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\pas2jslib.dll C:\fpc-ootb-64\lib\
xcopy /E /R /Y /Q /S C:\fpc-ootb-tmp\units\x86_64-win64 C:\fpc-ootb-64\units\x86_64-win64\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\fpcres.exe C:\fpc-ootb-64\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\h2pas.exe C:\fpc-ootb-64\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\fpcjres.exe C:\fpc-ootb-64\tools\
xcopy /E /R /Y /Q C:\fpc-ootb-tmp\bin\x86_64-win64\pas2js.exe C:\fpc-ootb-64\tools\

if EXIST C:\fpc-ootb-tmp (
del /f/s/q C:\fpc-ootb-tmp > nul
rmdir /s/q C:\fpc-ootb-tmp
)
