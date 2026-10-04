echo Check if wxWidgets needs to be unpacked and built
pause %WXDIR%\build\msw

IF NOT EXIST %WXDIR%\build\msw GOTO BUILDWX:

echo exit
pause
exit


:BUILDWX

IF NOT EXIST %RUNROOT%\bin goto MISSING_SRCINSTALLER:

echo Start buildng wxWidgets
pause Building ...

call buildwxWidgets_MinGW64_debug.bat NODISTPRESET

exit

:MISSING_SRCINSTALLER
echo Missing source installation. Please download and install source code installer. I try that for you...

mkdir %RUNROOT%\bin
xcopy C:\lbDMF\Develop\Projects\bin %RUNROOT%\bin

pause
