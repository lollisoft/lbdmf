rem Basic development settings

set DEVLW=Q:
set MSVCDir=Q:\Develop\Tools\MSC\VC98
set DEVROOT=%DEVLW%\develop


@rem Alias to the linux environment
set OSTYPE=%OS%


rem Basic Runtime settings
set RUNROOT=%DEVLW%\develop\projects

rem Some bin dirs for development

rem set CVSBIN=%DEVROOT%\Tools\cvs
set WATBIN=%DEVROOT%\Tools\WATCOM\BINNT;%DEVROOT%\Tools\WATCOM\BINW
set DEVBIN=%DEVROOT%\bin

rem Some dll and bin search Paths
set DLLROOT=%RUNROOT%\dll
set BINROOT=%RUNROOT%\bin;%RUNROOT%\CPP\bin

set Path=C:\;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%

set MSC=%MSVCDir%\Bin;%MSVCDir%\Lib

set Path=%Path%;%MSC%;%DEVROOT%\bin;F:\develop\NT\DevTools\bin

rem MSC Library path
set LIB=%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%LIB%

rem Watcom stuff

SET INCLUDE=Q:\Develop\wxwin232\wx\src\msw;%MSVCDir%\Include;%DEVROOT%\Tools\WATCOM\H;D:\Develop\Tools\WATCOM\H\NT
rem SET INCLUDE=
SET WATCOM=%DEVROOT%\Tools\WATCOM
SET EDPath=%DEVROOT%\Tools\WATCOM\EDDAT

rem WXWIN stuff

set WXWIN=%DEVROOT%\wxwin\wx

@rem XML Module Configuration

set LBHOSTCFGFILE=Q:\Develop\Projects\CPP\AppDevelopment\Console\XML\lbXMLConfig.xml

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
set LBMODULEFUNCTOR=_getlb_ModuleInstance

start %1
exit
