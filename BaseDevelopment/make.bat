cd lbHook
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbDB
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbPluginManager
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbModule
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbMetaApplication
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbclasses
attrib -r *.bak
call makefile.bat
make --win32
cd ..

cd lbXMLConfig\lbDOMConfig
attrib -r *.bak
call makefile.bat
make --win32
cd ..\..

cd ..\Plugins\DatabaseForm
attrib -r *.bak
call makefile.bat
make --win32
cd ..\..\BaseDevelopment

cd ..\test\Console\XML
attrib -r *.bak
call makefile.bat
make --win32
cd ..\..\..\BaseDevelopment

cd ..\test\GUI\wxWrapper
attrib -r *.bak
call makefile.bat
make --win32
cd ..\..\..\BaseDevelopment

cd ..\appdevelopmentdemo
call make.bat
cd ..\BaseDevelopment

rem call makeapps.bat

doxygen ..\doxygen.conf
