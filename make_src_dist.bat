set DEVROOT=dist\Develop\Projects\CPP

del /Q /S dist

if not EXIST "dist" mkdir dist
if not EXIST "dist\Develop" mkdir dist\Develop
if not EXIST "dist\Develop\Projects" mkdir dist\Develop\Projects
if not EXIST "dist\Develop\Projects\dll" mkdir dist\Develop\Projects\dll
if not EXIST "dist\Develop\Projects\dll\libs" mkdir dist\Develop\Projects\dll\libs
if not EXIST "dist\Develop\Projects\Plugins" mkdir dist\Develop\Projects\Plugins
if not EXIST "dist\Develop\Projects\Plugins\libs" mkdir dist\Develop\Projects\Plugins\libs
if not EXIST "dist\Develop\Projects\bin" mkdir dist\Develop\Projects\bin
if not EXIST "dist\Develop\Projects\lib" mkdir dist\Develop\Projects\lib
if not EXIST "dist\Develop\Projects\dll\include" mkdir dist\Develop\Projects\dll\include
if not EXIST "dist\Develop\Projects\lib\include" mkdir dist\Develop\Projects\lib\include

call make_dist_base.bat AppDevelopmentDemo
call make_dist_base.bat AppDevelopmentDemo\App
call make_dist_base.bat AppDevelopmentDemo\DynamicApp
call make_dist_base.bat AppDevelopmentDemo\DynamicApp\App
call make_dist_base.bat AppDevelopmentDemo\DynamicApp\Doc
call make_dist_base.bat AppDevelopmentDemo\DynamicApp\UMLSamples
call make_dist_base.bat BaseDevelopment\lbHook 
call make_dist_base.bat BaseDevelopment\lbclasses 
call make_dist_base.bat BaseDevelopment\lbcs
call make_dist_base.bat BaseDevelopment\lbDB 
call make_dist_base.bat BaseDevelopment\lbPluginManager
call make_dist_base.bat BaseDevelopment\lbMetaApplication 
call make_dist_base.bat BaseDevelopment\lbWorkflowEngine
call make_dist_base.bat BaseDevelopment\lbModule 
call make_dist_base.bat BaseDevelopment\lbtransfer
call make_dist_base.bat BaseDevelopment\lbXMLConfig\lbDOMConfig 
call make_dist_base.bat Plugins
call make_dist_base.bat vendor\mkmk
call make_dist_base.bat vendor\sqlite
call make_dist_base.bat vendor\databaselayer
call make_dist_base.bat vendor\dosdir
call make_dist_base.bat vendor\propgrid
call make_dist_base.bat vendor\wxShapeFramework
call make_dist_base.bat vendor\wxaui-0.9.1
call make_dist_base.bat vendor\libxml2-2.8.0
call make_dist_base.bat vendor\libxslt-1.1.21
call make_dist_base.bat include 
call make_dist_base.bat interfaces 
call make_dist_base.bat make
call make_dist_base.bat test
call make_dist_base.bat Compilers
call make_dist_base.bat Database
call make_dist_base.bat Samples
call make_dist_base.bat Modules
call make_dist_base.bat RegressionTests

copy makewat.env %DEVROOT%
copy makefile.wat %DEVROOT%
copy README %DEVROOT%
copy COPYING %DEVROOT%
copy doxygen.conf %DEVROOT%
copy BaseDevelopment\makefile %DEVROOT%\BaseDevelopment
copy BaseDevelopment\make.bat %DEVROOT%\BaseDevelopment
copy q:\develop\Projects\CPP\watcomenv.bat %DEVROOT%
copy q:\develop\Projects\CPP\watcomenv.bat.lnk dist
copy q:\develop\ide.bat %DEVROOT%
del *.idb
del %DEVROOT%\vendor\libxml2-2.6.29\bakefile\watcom\*.obj
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.tiff
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.rtf
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.odt

@rem Ensure the source installation will fully recreate required makefiles
touch %DEVROOT%\BaseDevelopment\Makefile

@REM Make any available XMISettings.xsl configuration files writeable, or simply all.
attrib /S -R %DEVROOT%\AppDevelopmentDemo\DynamicApp\XSLT_Templates\*.*

"Q:\develop\Tools\Inno Setup 3\iscc" q:\develop\Projects\CPP\dist.iss
"Q:\develop\Tools\Inno Setup 3\iscc" q:\develop\Projects\CPP\bindist.iss
"Q:\develop\Tools\Inno Setup 3\iscc" q:\develop\Projects\CPP\docdist.iss
"Q:\develop\Tools\Inno Setup 3\iscc" q:\develop\Projects\CPP\bin-buildtools-dist.iss
"Q:\develop\Tools\Inno Setup 3\iscc" q:\develop\Projects\CPP\templatedist.iss
