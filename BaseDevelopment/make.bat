cd lbHook
call makefile.bat
make --win32
cd ..

cd lbDB
call makefile.bat
make --win32
cd ..

cd lbModule
call makefile.bat
make --win32
cd ..

cd lbMetaApplication
call makefile.bat
make --win32
cd ..

cd lbclasses
call makefile.bat
make --win32
cd ..

cd lbXMLConfig\lbDOMConfig
call makefile.bat
make --win32
cd ..\..

cd ..\test\Console\XML
call makefile.bat
make --win32
cd ..\..\..\BaseDevelopment

cd ..\test\GUI\wxWrapper
call makefile.bat
make --win32
cd ..\..\..\BaseDevelopment

