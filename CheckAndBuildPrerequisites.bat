IF NOT EXIST %DEVLW%\%BASE%\wxwin\wx\build\msw GOTO BUILDWX:

echo Call final Development Console
call watcomenv.bat "" NODISTPRESET
exit

:BUILDWX

IF NOT EXIST %RUNROOT%\bin goto MISSING_SRCINSTALLER:

call buildwxWidgets_MinGW64_debug.bat NODISTPRESET

exit

REM This installs the bin and Tools folder based on the previous installation of 

:MISSING_SRCINSTALLER
echo Missing source installation. Please download and install source code installer. I try that for you...

mkdir %RUNROOT%\bin
mkdir %RUNROOT%\dll
mkdir %DEVLW%\%BASE%\Tools

xcopy C:\lbDMF\Develop\Projects\bin %RUNROOT%\bin
xcopy /S /E C:\lbDMF\Develop\Tools %DEVLW%\%BASE%\Tools
xcopy /S /E %DEVLW%\%BASE%\Projects\lbdmf\vendor\BinBuildTools\bison-2.4.2-deploymentfiles\Tools %DEVLW%\%BASE%\Tools

call buildwxWidgets_MinGW64_debug.bat NODIST
