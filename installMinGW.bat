@rem This batch will download and install MinGW by mingw-get

%DEVLW%\lbDMF\Develop\Tools\MinGW\bin\mingw-get install mingw
%DEVLW%\lbDMF\Develop\Tools\MinGW\bin\mingw-get install g++

REM Develop\Tools\MinGW\bin\mingw-get upgrade "gcc=%1"
REM Develop\Tools\MinGW\bin\mingw-get upgrade "g++=%1"

REM Develop\Tools\MinGW\bin\mingw-get upgrade "mingw32-w32api=%2"

@rem Required to compile ACE
REM Develop\Tools\MinGW\bin\mingw-get install msys
