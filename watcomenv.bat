if EXIST readme.txt goto WEITER:
set DEVLW=%%DEVLW%%
set DEVROOT=%%DEVROOT%%
echo ------------------------------------------------------------------------ >> readme.txt
echo *                  Basic development settings                          * >> readme.txt
echo ------------------------------------------------------------------------ >> readme.txt
echo * You have started lbDMF Develop the first time. Please read           * >> readme.txt
echo * lbDMF Help at your desktop for further instructions.                 * >> readme.txt
echo *                                                                      * >> readme.txt
echo * If you don't find the help icon, download the latest                 * >> readme.txt
echo * documentation install package from my sourceforge project site.      * >> readme.txt 
echo ------------------------------------------------------------------------ >> readme.txt 
start notepad readme.txt
exit

:WEITER

rem set TARGET_APPLICATION=Application

set LOGGING=no
set CONSOLE_DETACH=yes

rem set lbDMFPasswd=
rem set lbDMFUser=

if "%COMPUTERNAME%"=="ANAKIN" goto NODIST:
if "%COMPUTERNAME%"=="T43" goto NODIST:

goto DISTMODE:

:NODIST

set DEVLW=q:
set BASE=develop
set BASE_MAKE=develop

set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

goto BEGINENVIRONMENT:

:DISTMODE

if "%2"=="CC" goto CCBUILD:

set DEVLW=C:
set BASE=lbDMF\develop
set BASE_MAKE=lbDMF/develop


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

goto BEGINENVIRONMENT:

:CCBUILD

set DEVLW=E:
set BASE=Programme\CruiseControl\projects\lbDMF\develop
set BASE_MAKE=Programme/CruiseControl/projects/lbDMF/develop


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

:BEGINENVIRONMENT


@rem ----------------------------------------------------------------
@rem *                          End config                          *
@rem ----------------------------------------------------------------

rem WXWIN stuff

set WXWIN=%DEVLW%\%BASE%\wxwin\wx
set WXDIR=%WXWIN%

set PLUGIN_DIR=%DEVLW%\%BASE%\Projects\plugins


set MSVCDir=%DEVLW%\%BASE%\Tools\MSC\VC98

@rem Alias to the linux environment
set OSTYPE=%OS%

rem Basic Runtime settings
set RUNROOT=%DEVLW%\%BASE%\projects

rem Some bin dirs for development

rem set CVSBIN=%DEVROOT%\Tools\cvs
set WATBIN=%DEVLW%\%BASE%\Tools\WATCOM\BINNT;%DEVROOT%\Tools\WATCOM\BINW
set DEVBIN=%DEVLW%\%BASE%\bin

set MINGWBIN=%DEVLW%\%BASE%\Tools\mingw\bin

rem Some dll and bin search Paths
set DLLROOT=%RUNROOT%\dll
set BINROOT=%RUNROOT%\bin;%RUNROOT%\CPP\bin

set Path=%DEVLW%\%BASE%\bin;%SystemRoot%\system32;%DEVLW%\;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%
set Path=%Path%;q:\develop\tools\cygwin\bin;Q:\develop\Tools\Perl\bin;G:\gs\gs8.15\bin
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

set LBHOSTCFGFILE=%DEVLW%\%BASE%\Projects\CPP\Test\Console\XML\lbXMLConfig.xml

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
set path=%path%;%DEVLW%\develop\Tools\Perl\bin\

REM ------------------------------------------------------------
REM This stuff is related to integrate the ACE libraries from
REM http://www.cs.wustl.edu/~schmidt/ACE.html
REM ------------------------------------------------------------

set ACE_ROOT=%DEVROOT_MAKE%/Projects/CPP/vendor/ACE_wrappers
set MPC_ROOT=%ACE_ROOT%/MPC

set PATH=%PATH%;%DEVROOT%\Projects\CPP\vendor\ACE_wrappers\lib

REM -------------------
REM GCC-XML Location
REM -------------------

set PATH=%PATH%;%DEVLW%\develop\Tools\GCC_XML\bin

REM -------------------
REM Beaver Debugger
REM -------------------

set PATH=%PATH%;"C:\Programme\Beaver Debugger\"

REM -------------------
REM Prepend my cvs path
REM -------------------

set path=C:\Program Files\GNU\WinCvs 1.2;%PATH%

if "%2"=="CC" goto CCBUILD_END:

rem set CONSOLE_DETACH=no
rem wdw ..\..\bin\%1
start %1

:CCBUILD_END