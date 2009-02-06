@rem This batch will build the wxWidgets library after the installation.

echo dummy > readme.txt

call watcomenv.bat exit

echo del readme.txt > doBuildWx.bat

echo set DRIVE=%DEVLW% >> doBuildWx.bat
echo set WXDIR=%DRIVE%\lbDMF\Develop\wxwin\wx >> doBuildWx.bat
echo %DRIVE% >> doBuildWx.bat
echo cd %WXDIR%\build\msw >> doBuildWx.bat
echo copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx >> doBuildWx.bat
echo wmake -f makefile.wat clean >> doBuildWx.bat
echo wmake -f makefile.wat all >> doBuildWx.bat



call watcomenv.bat doBuildWx.bat
