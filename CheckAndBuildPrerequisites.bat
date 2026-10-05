IF NOT EXIST %DEVLW%\%BASE%\wxwin\wx\build\msw GOTO BUILDWX:

@echo Call final Development Console
call watcomenv.bat "" NODISTPRESET
exit

:BUILDWX

IF NOT EXIST %RUNROOT%\bin goto MISSING_SRCINSTALLER_COPIED:
call buildwxWidgets_MinGW64_debug.bat NODISTPRESET

exit

REM This installs the bin and Tools folder based on the previous installation of 

:MISSING_SRCINSTALLER_COPIED
@cls
@echo Need to copy stuff from source installation. Checking source location...
pause

if NOT EXIST C:\lbDMF goto DOWNLOAD_SOURCEINSTALLER:
goto SKIP:

:DOWNLOAD_SOURCEINSTALLER
@cls
@echo Please download and run source code installer manually first into it's standard folder on C:\lbDMF.
pause

exit

:SKIP

mkdir %RUNROOT%\bin
mkdir %RUNROOT%\dll
mkdir %DEVLW%\%BASE%\Tools

xcopy C:\lbDMF\Develop\Projects\bin %RUNROOT%\bin
xcopy /S /E C:\lbDMF\Develop\Tools %DEVLW%\%BASE%\Tools
xcopy /S /E %DEVLW%\%BASE%\Projects\lbdmf\vendor\BinBuildTools\bison-2.4.2-deploymentfiles\Tools %DEVLW%\%BASE%\Tools

copy %DEVLW%\%BASE%\Projects\lbdmf\vendor\BinBuildTools\m4.exe %RUNROOT%\bin
copy %DEVLW%\%BASE%\Projects\lbdmf\vendor\BinBuildTools\cygsigsegv-2.dll %RUNROOT%\bin

call buildwxWidgets_MinGW64_debug.bat NODIST
