cd lbHook
rem call ../make.sh

cd ..

cd lbModule
call makefile.bat
make
cd ..

cd lbclasses
call makefile.bat
make
cd ..

cd lbXMLConfig\lbDOMConfig
call makefile.bat
make
cd ..\..

cd ..\AppDevelopment\Console\XML
call makefile.bat
make
cd ..\..\..\BaseDevelopment
