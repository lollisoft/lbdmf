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

if NOT "%COMPUTERNAME%"=="ANAKIN" goto DISTMODE:

set DEVLW=q:
set BASE=develop
set BASE_MAKE=develop
goto BEGINENVIRONMENT:

:DISTMODE

set DEVLW=d:
set BASE=lbDMF\develop
set BASE_MAKE=lbDMF/develop

:BEGINENVIRONMENT


@rem ----------------------------------------------------------------
@rem *                          End config                          *
@rem ----------------------------------------------------------------


set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

set PLUGIN_DIR=%DEVROOT%/Projects/plugins


set MSVCDir=%DEVROOT%/Tools/MSC/VC98

@rem Alias to the linux environment
set OSTYPE=%OS%

rem Basic Runtime settings
set RUNROOT=%DEVROOT%/projects

rem Some bin dirs for development

rem set CVSBIN=%DEVROOT%/Tools/cvs
set WATBIN=%DEVROOT%/Tools/WATCOM/BINNT;%DEVROOT%/Tools/WATCOM/BINW
set DEVBIN=%DEVROOT%/bin

rem Some dll and bin search Paths
set DLLROOT=%RUNROOT%/dll
set BINROOT=%RUNROOT%/bin;%RUNROOT%/CPP/bin

set Path=%DEVLW%/%BASE%/bin;%SystemRoot%/system32;%DEVLW%/;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%
set Path=%Path%;q:/develop/tools/cygwin/bin;Q:/develop/Tools/Perl/bin

set MSC=%MSVCDir%/Bin;%MSVCDir%/Lib

set Path=%MSC%;%Path%;%DEVROOT%/bin
rem ??? F:/develop/NT/DevTools/bin

rem MSC Library path
set LIB=%MSVCDir%/LIB;%MSVCDir%/MFC/LIB;%LIB%

rem Watcom stuff

SET INCLUDE=%DEVROOT%/wxwin/wx/src/msw;%MSVCDir%/Include;%DEVROOT%/Tools/WATCOM/

rem ???;D:/Develop/Tools/WATCOM/H/NT
rem SET INCLUDE=
SET WATCOM=%DEVROOT%/Tools/WATCOM
SET EDPath=%DEVROOT%/Tools/WATCOM/EDDAT

rem WXWIN stuff

set WXWIN=%DEVROOT%/wxwin/wx

@rem XML Module Configuration

set LBHOSTCFGFILE=%DEVROOT%/Projects/CPP/Test/Console/XML/lbXMLConfig.xml

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

set BISON_SIMPLE=%DEVLW%/cygwin/usr/share/bison.simple
set path=%path%;%DEVLW%/develop/Tools/Perl/bin/

cd %DEVROOT%\Projects\dll
if not exist "libs" mkdir libs
cd %DEVROOT%\Projects\cpp\basedevelopment

start %1
exit
