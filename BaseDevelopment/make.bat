cd lbHook
call makefile.bat
make
cd ..

cd lbDB
call makefile.bat
make
cd ..

cd lbModule
call makefile.bat
make
cd ..

cd lbMetaApplication
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
