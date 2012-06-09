@rem This batch will build the wxWidgets library after the installation.

echo dummy > readme.txt

call watcomenv.bat exit

set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin

set Path=%SystemRoot%\system32

set Path=%Path%;%MINGWBIN%

set Path=%Path%;Q:\develop\Tools\Bakefile\src

echo del readme.txt > doBuildWx.bat

echo set DRIVE=%DEVLW% >> doBuildWx.bat
echo set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx >> doBuildWx.bat
echo %DRIVE% >> doBuildWx.bat
echo cd %WXDIR%\build\msw >> doBuildWx.bat
echo copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx >> doBuildWx.bat
echo mingw32-make -f makefile.gcc clean >> doBuildWx.bat
echo mingw32-make -f makefile.gcc all >> doBuildWx.bat



call watcomenv.bat doBuildWx.bat
