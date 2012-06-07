rem set TARGET_APPLICATION=Application

set LOGGING=no

if NOT "%COMPUTERNAME%"=="ANAKIN" goto DISTMODE:

set DEVLW=q:
set BASE=develop
set BASE_MAKE=develop
goto BEGINENVIRONMENT:

:DISTMODE

set DEVLW=c:
set BASE=develop
set BASE_MAKE=develop

:BEGINENVIRONMENT


@rem ----------------------------------------------------------------
@rem *                          End config                          *
@rem ----------------------------------------------------------------

set DEVROOT=.\%BASE%
set DEVROOT_MAKE=./%BASE_MAKE%

set PLUGIN_DIR=%DEVROOT%\Projects\plugins


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

set Path=%DEVLW%/%BASE%/bin;%SystemRoot%/system32;C:/;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%
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

set BISON_SIMPLE=c:/cygwin/usr/share/bison.simple
set path=%path%;Q:/develop/Tools/Perl/bin/


start wxwrapper.exe
exit
