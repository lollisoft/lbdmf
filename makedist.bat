set DEVROOT=dist\Develop\Projects\CPP

if not EXIST "dist" mkdir dist
if not EXIST "dist\Develop" mkdir dist\Develop
if not EXIST "dist\Develop\Projects" mkdir dist\Develop\Projects
if not EXIST "dist\Develop\Projects\dll" mkdir dist\Develop\Projects\dll
if not EXIST "dist\Develop\Projects\lib" mkdir dist\Develop\Projects\lib
if not EXIST "dist\Develop\Projects\dll\include" mkdir dist\Develop\Projects\dll\include
if not EXIST "dist\Develop\Projects\lib\include" mkdir dist\Develop\Projects\lib\include

@REM ...sAppDevelopment\92\console\92\xml:0:
xcopy AppDevelopment\console\xml %DEVROOT%\AppDevelopment\console\xml
cd %DEVROOT%\AppDevelopment\console\xml
del *.exe
del *.obj
del *.bak
del .#*
del *.ilk
del *.pch
del *.pdb
del *.lib
del *.dll
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..\..
@REM ...e
@REM ...sBaseDevelopment\92\lbHook:0:
xcopy BaseDevelopment\lbHook %DEVROOT%\BaseDevelopment\lbHook
cd %DEVROOT%\BaseDevelopment\lbHook
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...sBaseDevelopment\92\lbclasses:0:
xcopy BaseDevelopment\lbclasses %DEVROOT%\BaseDevelopment\lbclasses
cd %DEVROOT%\BaseDevelopment\lbclasses
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...sBaseDevelopment\92\lbMetaApplication:0:
xcopy BaseDevelopment\lbMetaApplication %DEVROOT%\BaseDevelopment\lbMetaApplication
cd %DEVROOT%\BaseDevelopment\lbMetaApplication
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...sBase\92\evelopment\92\lbModule:0:
xcopy BaseDevelopment\lbModule %DEVROOT%\BaseDevelopment\lbModule
cd %DEVROOT%\BaseDevelopment\lbModule
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...sBaseDevelopment\92\lbXMLConfig\92\lbDOMConfig:0:
xcopy BaseDevelopment\lbXMLConfig\lbDOMConfig %DEVROOT%\BaseDevelopment\lbXMLConfig\lbDOMConfig
cd %DEVROOT%\BaseDevelopment\lbXMLConfig\lbDOMConfig
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..\..
@REM ...e
@REM ...svendor\92\mkmk:0:
xcopy vendor\mkmk %DEVROOT%\vendor\mkmk
cd %DEVROOT%\vendor\mkmk
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...svendor\92\dosdir:0:
xcopy vendor\dosdir %DEVROOT%\vendor\dosdir
cd %DEVROOT%\vendor\dosdir
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..\..
@REM ...e
@REM ...sinclude:0:
xcopy include %DEVROOT%\include
cd %DEVROOT%\include
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..
@REM ...e
@REM ...sinterfaces:0:
xcopy interfaces %DEVROOT%\interfaces
cd %DEVROOT%\interfaces
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..
@REM ...e
@REM ...smake:0:
xcopy make %DEVROOT%\make
cd %DEVROOT%\make
del *.exe
del *.obj
del *.bak
del *.dll
del *.ilk
del *.pch
del *.pdb
del *.lib
del .#*
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.idb

del null
cd ..\..\..\..\..
@REM ...e
xcopy ..\bin %DEVROOT%\..\bin
cd %DEVROOT%\..\bin
cd ..\..\..\..


xcopy ..\lib %DEVROOT%\..\lib
cd %DEVROOT%\..\lib
ren xerc*.lib xerc*.lib.copy
del *.dll.
ren xerc*.lib.copy xerc*.lib
cd ..\..\..\..


xcopy ..\dll %DEVROOT%\..\dll
cd %DEVROOT%\..\dll
ren xerc*.dll xerc*.dll.copy
ren msp*.dll msp*.dll.copy
del *.dll.
ren xerc*.dll.copy xerc*.dll
ren msp*.dll.copy msp*.dll

cd ..\..\..\..


xcopy ..\dll\libs %DEVROOT%\..\dll\libs
cd %DEVROOT%\..\dll\libs
ren xerc*.lib xerc*.lib.copy
del *.lib.
ren xerc*.lib.copy xerc*.lib
cd ..\..\..\..\..
xcopy /E ..\..\xml\xml4csrc3_3_1\src dist\Develop\xml\xml4csrc3_3_1\src 
pause
copy README %DEVROOT%
copy COPYING %DEVROOT%
copy BaseDevelopment\makefile %DEVROOT%\BaseDevelopment
copy BaseDevelopment\make.bat %DEVROOT%\BaseDevelopment
copy q:\develop\Projects\CPP\watcomenv.bat %DEVROOT%
copy q:\develop\ide.bat %DEVROOT%
del *.idb

