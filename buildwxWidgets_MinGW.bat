@rem This batch will build the wxWidgets library after the installation.

echo dummy > readme.txt

call watcomenv.bat exit

set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin

set Path=%SystemRoot%\system32

set Path=%Path%;%MINGWBIN%

rem set Path=%Path%;Q:\develop\Tools\Bakefile\src

echo del readme.txt > doBuildWx.bat

echo set DRIVE=%DEVLW% >> doBuildWx.bat
echo set WXDIR=%DEVLW%\lbDMF\Develop\wxwin\wx >> doBuildWx.bat
echo %DEVLW% >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\Tools\MinGW\bin\gcc.exe ( >> doBuildWx.bat
echo call installMinGW.bat >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\Develop\Projects\bin\bison.exe ( >> doBuildWx.bat
echo wget http://sourceforge.net/projects/lbdmf/files/lbdmf/lbDMF-1.0.4-stable-rc3/lbDMF-BinbuildTools-1.0.4-stable-rc3.exe/download >> doBuildWx.bat
echo lbDMF-BinbuildTools-1.0.4-stable-rc3.exe /VERYSILENT /SP- /DIR=%DEVLW%\lbDMF >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %WXDIR%\build\msw ( >> doBuildWx.bat
echo wget http://sourceforge.net/projects/wxwindows/files/2.8.12/wxMSW-2.8.12-Setup.exe/download >> doBuildWx.bat
echo wxMSW-2.8.12-Setup.exe /VERYSILENT /SP- /DIR=%WXDIR% >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo cd %WXDIR%\build\msw >> doBuildWx.bat
echo copy /Y %WXDIR%\include\wx\msw\setup.h %WXDIR%\include\wx >> doBuildWx.bat
echo copy /Y %DEVLW%\lbDMF\wxWidgets-config.gcc %WXDIR%\build\msw\config.gcc >> doBuildWx.bat
rem echo mingw32-make -f makefile.gcc clean >> doBuildWx.bat
echo set Path=%SystemRoot%\system32 >> doBuildWx.bat
echo set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin >> doBuildWx.bat
echo set Path=%Path%;%MINGWBIN% >> doBuildWx.bat
echo mingw32-make -f makefile.gcc all >> doBuildWx.bat
echo copy %WXDIR%\lib\gcc_dll\*.dll %DEVLW%\%BASE%\Projects\dll >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\XSLT ( >> doBuildWx.bat
echo xcopy %DEVLW%\lbDMF\Develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\XSLT_Templates %DEVLW%\lbDMF >> doBuildWx.bat
echo move %DEVLW%\lbDMF\XSLT_Templates %DEVLW%\lbDMF\XSLT >> doBuildWx.bat
echo ) >> doBuildWx.bat
echo IF NOT EXIST %DEVLW%\lbDMF\UMLSamples ( >> doBuildWx.bat
echo xcopy %DEVLW%\lbDMF\Develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\UMLSamples %DEVLW%\lbDMF >> doBuildWx.bat
echo ) >> doBuildWx.bat

@rem After installing msys, bunzip2 is available and watcomenv.bat sets up PATH

echo IF EXIST %DEVLW%\lbDMF\GetACE.txt ( call %DEVLW%\lbDMF\InstallACE.bat ) >> doBuildWx.bat
echo IF EXIST %DEVLW%\lbDMF\GetDoUMLBin.txt ( call %DEVLW%\lbDMF\InstallDoUMLBin.bat ) >> doBuildWx.bat
echo IF EXIST %DEVLW%\lbDMF\GetDoUMLSrc.txt ( call %DEVLW%\lbDMF\InstallDoUMLSrc.bat ) >> doBuildWx.bat

call watcomenv.bat doBuildWx.bat
