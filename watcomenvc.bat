if EXIST readme.txt goto WEITER:
set DEVLW=%%DEVLW%%
set DEVROOT=%%DEVROOT%%
echo --------------------------------------------------------------------------------- >> readme.txt
echo *                        Basic development settings                             * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt
echo * Buildsystem may use mkmk ported to MinGW. A precompiled Open Watcom 1.7 port  * >> readme.txt
echo * may be used until the MinGW version works well.                               * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt
echo * Mkmk is the main tool, that creates the required makefiles. A prebuild        * >> readme.txt
echo * version got built by Open Watcom 1.7 prior to porting to MinGW started for it * >> readme.txt
echo * to replace it later. Using the MinGW version requires include building it.    * >> readme.txt
echo * To do so. search for #   ../vendor/mkmk \ and include it as described.        * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt
echo * You have started lbDMF Develop the first time. Wait until wxWidgets           * >> readme.txt
echo * got built if you opted for a build. If that is finished, reopen               * >> readme.txt
echo * lbDMF Develop and type make. Depending on the version you opted, mkmk needs   * >> readme.txt
echo * to be included into the build process as described above.                     * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * If you don't have opted for building wxWigets, the library and MinGW must     * >> readme.txt
echo * be installed manually. Folders for that look respectively like this:          * >> readme.txt
echo * C:\lbDMF\Develop\wxwin\wx (wx is the base folder for wxWidgets)               * >> readme.txt
echo * C:\lbDMF\Develop\Tools\MinGW (MinGW is the base MinGW Get) 				     * >> readme.txt
echo * C:\lbDMF\Develop\Tools\mingw32 (MinGW is the base for the compiler stuff)     * >> readme.txt
echo *                                                                               * >> readme.txt
echo * Also install the lbDMF Build tools at the same place as the source code.      * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * If installation and building is finished, type wxWrapper and enjoy running    * >> readme.txt
echo * the lbDMF Manager prototype (default login: user, password: TestUser)         * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * Important note: If you have chosen to install in another location,            * >> readme.txt
echo * update the watcomenv.bat file environment variables DEVLW, BASE, BASE_MAKE    * >> readme.txt
echo * and DEVROOT_MAKE_BASE respectively                                            * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * Download the latest documentation and follow the modeling quickstart.         * >> readme.txt 
echo --------------------------------------------------------------------------------- >> readme.txt
echo * KNOWN ISSUES: The prototype doesn't cope with empty tables when using         * >> readme.txt
echo * Sqlite. To overcome this, use a Sqlite database browser to setup sample data. * >> readme.txt
echo * Using a properly set up ODBC database (tested is PostgreSQL), no problems are * >> readme.txt
echo * known.                                                                        * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
start notepad readme.txt
exit

:WEITER

@rem Most important setup is the root folder where the version system is checking out To
SET REPO_NAME=lbdmf

rem set TARGET_APPLICATION=Application

set LOGGING=no
set CONSOLE_DETACH=yes

rem set lbDMFPasswd=
rem set lbDMFUser=

goto DISTMODE:

:NODIST

set DEVLW=q:
set BASE=develop
set BASE_MAKE=develop

set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%
set DEVROOT_MAKE_BASE=/cygdrive/q/%BASE_MAKE%

set WXWIN=%DEVLW%/%BASE%/wxwin/wx
set wxBase=%WXWIN%/lib

goto BEGINENVIRONMENT:

:DISTMODE

if "%2"=="CC" goto CCBUILD:

set DEVLW=C:
set BASE=lbDMF\develop
set BASE_MAKE=lbDMF/develop


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%
set DEVROOT_MAKE_BASE=/cygdrive/c/%BASE_MAKE%

REM set WXWIN=%DEVLW%\%BASE%\wxwin\wx
REM To get distribution build correctly (wx is built separately at setup)
set WXWIN=%DEVLW%/%BASE_MAKE%/wxwin/wx
set wxBase=%WXWIN%/lib

goto BEGINENVIRONMENT:

:CCBUILD

set DEVLW=E:
set BASE=Programme\CruiseControl\projects\lbDMF\develop
set BASE_MAKE=Programme/CruiseControl/projects/lbDMF/develop


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

set WXWIN=%DEVLW%\%BASE%\wxwin\wx

goto BEGINENVIRONMENT:

:JENKINSBUILD

set DEVLW=%CD:~0,2%
set BASE=%WORKSPACE:~3%
set BASE_MAKE=%BASE:\=/%

set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%
set DEVROOT_MAKE_BASE=%DEVLW%/%BASE_MAKE%

@REM Try to fix path for Jenkins environment
set PATH=%PATH%;%DEVLW%\Q\develop\Tools\MkMk
set PATH=%PATH%;%DEVLW%\Q\develop\Tools\bin

REM Current location for the dependent wx library (subst Q: C:\Q - thus C:\Q ...)
set WXWIN=C:\Q\develop\wxwin\wx
set wxBase_Win=%WXWIN%\lib
set wxBase=%wxBase_Win:\=/%

goto BEGINENVIRONMENT:

:APPVEYORBUILD

set DEVLW=%CD:~0,2%
set BASE=%WORKSPACE:~3%
set BASE_MAKE=%BASE:\=/%

echo %DEVLW%
echo %BASE%
echo %BASE_MAKE%


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%
set DEVROOT_MAKE_BASE=%DEVLW%/%BASE_MAKE%

@REM Try to fix path for Jenkins environment
set PATH=%PATH%;%DEVLW%\Q\develop\Tools\MkMk
set PATH=%PATH%;%DEVLW%\Q\develop\Tools\bin

@REM Add MinGW PATH of Appveyor Buildhost
@REM Assume most recent worker image is used
set PATH=%PATH%;%DEVLW%\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\bin


REM Current location for the dependent wx library (subst Q: C:\Q - thus C:\Q ...)
set WXWIN=C:\Q\develop\wxwin\wx
set wxBase_Win=%WXWIN%\lib
set wxBase=%wxBase_Win:\=/%

@rem ----------------------------------------------------------------
@rem *                          End config                          *
@rem ----------------------------------------------------------------

:BEGINENVIRONMENT

rem WXWIN stuff

set WXDIR=%WXWIN%

set PLUGIN_DIR=%DEVLW%\%BASE%\Projects\plugins


set MSVCDir=%DEVLW%\%BASE%\Tools\MSC\VC98

@rem Alias to the linux environment
set OSTYPE=%OS%
set OSNAME=%OS%

rem Basic Runtime settings
set RUNROOT=%DEVLW%\%BASE%\projects

rem Some bin dirs for development

rem set CVSBIN=%DEVROOT%\Tools\cvs
set WATBIN=%DEVLW%\%BASE%\Tools\WATCOM\BINNT;%DEVROOT%\Tools\WATCOM\BINW
set DEVBIN=%DEVLW%\%BASE%\bin

set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin;%DEVLW%\%BASE%\Tools\mingw32\bin;

rem Some dll and bin search Paths
set DLLROOT=%RUNROOT%\dll
set BINROOT=%RUNROOT%\bin;%RUNROOT%\%REPO_NAME%\bin

set Path=%DEVLW%\%BASE%\bin;%SystemRoot%\system32;%DEVLW%\;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%
set Path=%Path%;q:\develop\tools\bin;q:\develop\tools\cygwin\bin;Q:\develop\Tools\Perl\bin;G:\gs\gs8.15\bin
set Path=%Path%;Q:\develop\Tools\TP;Q:\develop\Tools\TP\TPU
set Path=%path%;G:\FPC\2.0.4\bin\i386-win32;C:\Programme\Graphviz2.26.3\bin

set Path=%Path%;%MINGWBIN%

rem Enable my Power++ IDE
set Path=%Path%;"E:\Program Files\Powersoft\Power21\System"

rem Bakefile binary
set Path=%Path%;Q:\develop\Tools\Bakefile

set MSC=%MSVCDir%\Bin;%MSVCDir%\Lib

set Path=%MSC%;%Path%;%DEVLW%\%BASE%\bin
rem ??? F:\develop\NT\DevTools\bin

rem MSC Library path
rem set LIB=%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%LIB%

rem Watcom stuff

rem SET INCLUDE=%DEVLW%\%BASE%\wxwin\wx\src\msw;%DEVLW%\%BASE%\Tools\WATCOM\;%DEVLW%\%BASE%\Tools\WATCOM\h;%DEVLW%\%BASE%\Tools\WATCOM\h\nt
rem SET INCLUDE=%INCLUDE%;"C:\Program Files\Microsoft Visual Studio\VC98\MFC\Include";%MSVCDir%\Include

rem Enable building libxml2
SET INCLUDE=
SET LIB=

rem ???;D:\Develop\Tools\WATCOM\H\NT
SET WATCOM=%DEVLW%\%BASE%\Tools\WATCOM
SET EDPath=%DEVLW%\%BASE%\Tools\WATCOM\EDDAT

@rem XML Module Configuration

set LBHOSTCFGFILE=%DEVLW%\%BASE%\Projects\%REPO_NAME%\Test\Console\XML\lbXMLConfig.xml

REM __stdcall convention
set LBXMLFUNCTOR=_getlbDOMConfigInstance@16

REM __cdecl convention
REM set LBXMLFUNCTOR=getlbDOMConfigInstance


set LBXMLLIB=lbDOMConfig

@rem lbModule configuration

set MODULELIB=lbModule

REM __stdcall convention
REM set LBMODULEFUNCTOR=_getlb_ModuleInstance@4

REM __cdecl convention
set LBMODULEFUNCTOR=getlb_ModuleInstance


REM ------------------------------------------------------------
REM This stuff is added due to integrate Doxygen into my console
REM ------------------------------------------------------------

set BISON_SIMPLE=%DEVROOT_MAKE%/projects/bin/bison.simple
set path=%path%;%DEVLW%\develop\Tools\Perl\bin\;%DEVLW%\develop\Tools\doxygen\bin

REM ------------------------------------------------------------
REM This stuff is related to integrate the ACE libraries from
REM http://www.cs.wustl.edu/~schmidt/ACE.html
REM ------------------------------------------------------------

set ACE_ROOT=%DEVROOT_MAKE%/Projects/%REPO_NAME%/vendor/ACE_wrappers
set MPC_ROOT=%ACE_ROOT%/MPC

set PATH=%PATH%;%DEVROOT%\Projects\%REPO_NAME%\vendor\ACE_wrappers\lib

REM -------------------
REM GCC-XML Location
REM -------------------

set PATH=%PATH%;%DEVLW%\develop\Tools\GCC_XML\bin

REM -------------------
REM Beaver Debugger
REM -------------------

set PATH=%PATH%;"C:\Programme\Beaver Debugger\"

REM -------------------
REM MSYS Path
REM -------------------

set PATH=%PATH%;"%DEVROOT%\Tools\MinGW\msys\1.0\bin"

REM -------------------
REM Prepend my cvs path
REM -------------------

set path=C:\Program Files\GNU\WinCvs 1.2;%DEVLW%\Q\develop\Tools\curl;%DEVLW%\Q\develop\Tools\7Zip\7-Zip;%PATH%

if "%2"=="JENKINS" goto CCBUILD_END:
if "%2"=="CC" goto CCBUILD_END:

SET CABUNDLEFILE=%DEVLW%\develop\Tools\curl\ca-bundle.crt

set BISON_PKGDATADIR=/cygdrive/q/develop/Tools/cygwin/usr/share/bison

rem set CONSOLE_DETACH=no
rem wdw ..\..\bin\%1
start /D %DEVROOT%\Projects\%REPO_NAME%\BaseDevelopment %1
goto EXIT:

:CCBUILD_END

SET CABUNDLEFILE=%DEVLW%\Q\develop\Tools\curl\ca-bundle.crt

REM Tools used but are prerequisites and may be located anywhere.
SET PATH=c:\q\develop\tools\tar;c:\q\develop\tools\bison;%DEVLW%\Q\develop\Tools\mingw\bin;%DEVLW%\Q\develop\Tools\MkMk;%DEVLW%\Q\develop\Tools\BinBuildTools;%DEVLW%\Q\develop\Tools\bin;%DEVLW%\Q\develop\Projects\bin;%DEVLW%\Q\develop\Tools\curl;%PATH%

cd %DEVROOT%\Projects\%REPO_NAME%\BaseDevelopment

REM SET OSNAME=Windows_NT
SET CRUISECONTROL=yes

@rem Get an explicite version that always ensures to build the code
set MINGW_STICKON_VERSION=4.7.*
set MINGW_STICKON_WIN32_VERSION=4.0.3-*

IF NOT EXIST %DEVLW%\q\develop\Tools\MinGW\bin\gcc.exe (
cd %DEVLW%\q 
call %DEVROOT%\Projects\CPP\installMinGW.bat %MINGW_STICKON_VERSION% %MINGW_STICKON_WIN32_VERSION%
cd %DEVROOT%\Projects\CPP\BaseDevelopment
)

IF NOT EXIST %DEVROOT%\wxwin (
cd %DEVLW%\q 
cd %DEVROOT%
set PATH=%PATH%;C:\Q\develop\Tools\7Zip\7-Zip
7z x %DEVROOT%\Projects\lbdmf\vendor\wxMSW-2.8.12.zip -aoa
rename wxMSW-2.8.12 wxwin
rem call %DEVROOT%\Projects\lbdmf\buildwxWidgets_MinGW_CC.bat
cd %DEVROOT%\Projects\lbdmf\BaseDevelopment
)

mingw32-make


@REM Bailout with goto instead of exit. This is because source code installer (breaking post installation process).
:EXIT

