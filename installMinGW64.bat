@REM This batch will download and install MinGW by utilizing a prepackaged
@REM 32 bit tool chain. (First try supplied Windows 10 cUrl)

if NOT EXIST 7z2301-x64.exe (
%Systemroot%\System32\curl -k -L -o 7z2301-x64.exe https://www.7-zip.org/a/7z2301-x64.exe
)

if NOT EXIST 7z2301-x64.exe (
curl -k -L -o 7z2301-x64.exe https://www.7-zip.org/a/7z2301-x64.exe
)

if NOT EXIST MinGW64.7z (
%Systemroot%\System32\curl -k -L -o MinGW64.7z https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win64/Personal%%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z
)
if NOT EXIST MinGW64.7z (
curl -k -L -o MinGW64.7z https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win64/Personal%%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z
)

7z2301-x64.exe /S /D="C:\lbDMF\Develop\Projects\bin"
C:\lbDMF\Develop\Projects\bin\7z x MinGW64.7z -oC:\lbDMF\Develop\Tools
@REM %DEVLW%\lbDMF\Develop\Tools\MinGW\bin\mingw-get install mingw
@REM %DEVLW%\lbDMF\Develop\Tools\MinGW\bin\mingw-get install g++

REM Develop\Tools\MinGW\bin\mingw-get upgrade "gcc=%1"
REM Develop\Tools\MinGW\bin\mingw-get upgrade "g++=%1"

REM Develop\Tools\MinGW\bin\mingw-get upgrade "mingw32-w32api=%2"

@rem Required to compile ACE
REM Develop\Tools\MinGW\bin\mingw-get install msys
