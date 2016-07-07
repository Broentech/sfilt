cd ..
SET LIB=%cd%\install\lib;%QTDIR%\lib;%LIB%
SET INCLUDE=%cd%\install\include;%QTDIR%\include;%QTDIR%\include\QtCore;%INCLUDE%
SET STARTDIR=%cd%
set MVDIR=%STARTDIR%\build\
SET INSTDIR=%STARTDIR%\install
SET BDIR=%STARTDIR%\scripts
SET OPENCV_DIR=%OPENCV_DIR%
set logfile=%STARTDIR%\log.txt

if not defined VCDIR set VCDIR=C:\Program Files (x86)\Microsoft Visual Studio 12.0
call "%VCDIR%\VC\vcvarsall.bat" x64