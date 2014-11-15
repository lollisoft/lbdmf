@REM Expecting cwd in the CPP root folder of the project when this script is called.

set PACKAGINGROOT=%CD%
set BINARIESROOT=%CD%\..
set TOOLSFOLDER=C:\Q\develop\Tools
set DEVROOT=dist\dist_iss_src\Develop\Projects\CPP

del /Q /S dist

if not EXIST "dist" mkdir dist
if not EXIST "dist\dist_iss" mkdir dist\dist_iss
if not EXIST "dist\dist_iss_src" mkdir dist\dist_iss_src

if not EXIST "dist\dist_iss_src\Develop" mkdir dist\dist_iss_src\Develop
if not EXIST "dist\dist_iss_src\Develop\Projects" mkdir dist\dist_iss_src\Develop\Projects
if not EXIST "dist\dist_iss_src\Develop\Projects\dll" mkdir dist\dist_iss_src\Develop\Projects\dll
if not EXIST "dist\dist_iss_src\Develop\Projects\dll\libs" mkdir dist\dist_iss_src\Develop\Projects\dll\libs
if not EXIST "dist\dist_iss_src\Develop\Projects\Plugins" mkdir dist\dist_iss_src\Develop\Projects\Plugins
if not EXIST "dist\dist_iss_src\Develop\Projects\Plugins\libs" mkdir dist\dist_iss_src\Develop\Projects\Plugins\libs
if not EXIST "dist\dist_iss_src\Develop\Projects\bin" mkdir dist\dist_iss_src\Develop\Projects\bin
if not EXIST "dist\dist_iss_src\Develop\Projects\lib" mkdir dist\dist_iss_src\Develop\Projects\lib
if not EXIST "dist\dist_iss_src\Develop\Projects\dll\include" mkdir dist\dist_iss_src\Develop\Projects\dll\include
if not EXIST "dist\dist_iss_src\Develop\Projects\lib\include" mkdir dist\dist_iss_src\Develop\Projects\lib\include

@REM Prepare files for relative packaging mechanism
if not EXIST "dist\dist_iss_MinGW_Get" mkdir dist\dist_iss_MinGW_Get
if not EXIST "dist\dist_iss_psqlodbc" mkdir dist\dist_iss_psqlodbc
if not EXIST "dist\dist_iss_BinBuildTools" mkdir dist\dist_iss_BinBuildTools
if not EXIST "dist\dist_iss_wxLua_dist" mkdir dist\dist_iss_wxLua_dist

if not EXIST "dist\bindist_iss" mkdir dist\bindist_iss
if not EXIST "dist\bindist_iss\bin" mkdir dist\bindist_iss\bin
if not EXIST "dist\bindist_iss\dll" mkdir dist\bindist_iss\dll
if not EXIST "dist\bindist_iss\plugins" mkdir dist\bindist_iss\plugins

if not EXIST "dist\bindist_iss_MinGW_Libraries" mkdir dist\bindist_iss_MinGW_Libraries
if not EXIST "dist\bindist_iss_Watcom_Libraries" mkdir dist\bindist_iss_Watcom_Libraries

copy %TOOLSFOLDER%\mingw\bin\mingwm10.dll dist\bindist_iss_MinGW_Libraries
copy %TOOLSFOLDER%\mingw\bin\libgcc_s_dw2-1.dll dist\bindist_iss_MinGW_Libraries
copy "%TOOLSFOLDER%\mingw\bin\libstdc++-6.dll" dist\bindist_iss_MinGW_Libraries

copy %TOOLSFOLDER%\watcom\binnt\mt7r17.dll dist\bindist_iss_Watcom_Libraries
copy %TOOLSFOLDER%\watcom\binnt\clbr17.dll dist\bindist_iss_Watcom_Libraries
copy %TOOLSFOLDER%\watcom\binnt\plbr17.dll dist\bindist_iss_Watcom_Libraries

copy %TOOLSFOLDER%\WGet\bin\*.* dist\dist_iss
xcopy /S /E %TOOLSFOLDER%\MinGW_Get\*.* dist\dist_iss_MinGW_Get
@REM DEPENDENCY
copy C:\Q\develop\Projects\bin\xsltproc.exe dist\bindist_iss\bin
copy C:\Q\develop\Projects\dll\psqlodbc.dll dist\dist_iss_psqlodbc
copy C:\Q\develop\Tools\BinBuildTools\test.exe dist\dist_iss_BinBuildTools

copy C:\Q\develop\wxwin\wx\lib\gcc_dll\*.dll dist\bindist_iss\dll

@REM Copy binary files
copy %BINARIESROOT%\bin dist\bindist_iss\bin
copy %BINARIESROOT%\dll dist\bindist_iss\dll
copy %BINARIESROOT%\plugins dist\bindist_iss\plugins
copy %TOOLSFOLDER%\wxLua-dist\*.* dist\dist_iss_wxLua_dist 
echo CVS\ > XCopyIgnores.txt

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
copy %PACKAGINGROOT%\watcomenv.bat %DEVROOT%
copy %PACKAGINGROOT%\watcomenv.bat.lnk dist

@REM Does not exist in jenkins build
@REM copy %PACKAGINGROOT%\..\ide.bat %DEVROOT%

del *.idb
del %DEVROOT%\vendor\libxml2-2.6.29\bakefile\watcom\*.obj
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.tiff
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.rtf
del %DEVROOT%\AppDevelopmentDemo\DynamicApp\Doc\*.odt

@rem Ensure the source installation will fully recreate required makefiles
touch %DEVROOT%\BaseDevelopment\Makefile

@REM Make any available XMISettings.xsl configuration files writeable, or simply all.
attrib /S -R %DEVROOT%\AppDevelopmentDemo\DynamicApp\XSLT_Templates\*.*

@REM Dependency to tools

"%TOOLSFOLDER%\Inno Setup\iscc" %PACKAGINGROOT%\dist.iss
"%TOOLSFOLDER%\Inno Setup\iscc" %PACKAGINGROOT%\bindist.iss
"%TOOLSFOLDER%\Inno Setup\iscc" %PACKAGINGROOT%\docdist.iss
"%TOOLSFOLDER%\Inno Setup\iscc" %PACKAGINGROOT%\bin-buildtools-dist.iss
"%TOOLSFOLDER%\Inno Setup\iscc" %PACKAGINGROOT%\templatedist.iss
