set DEVROOT=dist\Develop\Projects\CPP

del /Y /S dist

if not EXIST "dist" mkdir dist
if not EXIST "dist\Develop" mkdir dist\Develop
if not EXIST "dist\Develop\Projects" mkdir dist\Develop\Projects
if not EXIST "dist\Develop\Projects\dll" mkdir dist\Develop\Projects\dll
if not EXIST "dist\Develop\Projects\lib" mkdir dist\Develop\Projects\lib
if not EXIST "dist\Develop\Projects\dll\include" mkdir dist\Develop\Projects\dll\include
if not EXIST "dist\Develop\Projects\lib\include" mkdir dist\Develop\Projects\lib\include

call make_dist_base.bat BaseDevelopment\lbHook 
call make_dist_base.bat BaseDevelopment\lbclasses 
call make_dist_base.bat BaseDevelopment\lbDB 
call make_dist_base.bat BaseDevelopment\lbMetaApplication 
call make_dist_base.bat BaseDevelopment\lbModule 
call make_dist_base.bat BaseDevelopment\lbXMLConfig\lbDOMConfig 
call make_dist_base.bat vendor\mkmk 
call make_dist_base.bat vendor\dosdir 
call make_dist_base.bat include 
call make_dist_base.bat interfaces 
call make_dist_base.bat make
call make_dist_base.bat test\GUI\wxwrapper
call make_dist_base.bat test\console\xml

copy README %DEVROOT%
copy COPYING %DEVROOT%
copy BaseDevelopment\makefile %DEVROOT%\BaseDevelopment
copy BaseDevelopment\make.bat %DEVROOT%\BaseDevelopment
copy q:\develop\Projects\CPP\watcomenv.bat %DEVROOT%
copy q:\develop\Projects\CPP\watcomenv.bat.lnk dist
copy q:\develop\ide.bat %DEVROOT%
del *.idb

rem xcopy /I /E /Y dist q:\dist