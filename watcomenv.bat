if EXIST readme.txt goto WEITER:
set DEVLW=%%DEVLW%%
set DEVROOT=%%DEVROOT%%
echo ---------------------------------------------------------------- >> readme.txt
echo *                  Basic development settings                  * >> readme.txt
echo ---------------------------------------------------------------- >> readme.txt
echo * Please set the following two environment variables to your   * >> readme.txt
echo * actual unzipped source distribution.                         * >> readme.txt
echo * As example: If you have unzipped the distribution to C:\,    * >> readme.txt
echo * thn DEVLW is C: an DEVROOT will be %DEVLW%\dist\develop      * >> readme.txt
echo *                                                              * >> readme.txt
echo * The file to be edited is then located at                     * >> readme.txt
echo * %DEVLW%\dist\develop\projects\cpp\watcomenv.bat              * >> readme.txt
echo *                                                              * >> readme.txt 
echo * BEFORE you try to compile:                                   * >> readme.txt 
echo *                                                              * >> readme.txt 
echo * Install Open Watcom 1.0 or newer to %DEVROOT%\Tools\Watcom   * >> readme.txt 
echo *                                                              * >> readme.txt 
echo * Install MSVC into %DEVROOT%\Tools\msc                        * >> readme.txt 
echo * DO NOT INSTALL it TO THE DEFAULT LOCATION LIKE:              * >> readme.txt 
echo *                                                              * >> readme.txt 
echo * C:\Programme\Microsoft Visual Studio                         * >> readme.txt 
echo * or                                                           * >> readme.txt 
echo * C:\Program files\Microsoft Visual Studio                     * >> readme.txt 
echo ---------------------------------------------------------------- >> readme.txt 
start notepad readme.txt
exit

:WEITER

set TARGET_APPLICATION=Q:\develop\Projects\CPP\AppDevelopment\Trainres\App\trainres

set DEVLW=q:
set BASE=develop
set BASE_MAKE=develop

@rem ----------------------------------------------------------------
@rem *                          End config                          *
@rem ----------------------------------------------------------------

set DEVROOT=%DEVLW%\%BASE%
set DEVROOT_MAKE=%DEVLW%/%BASE_MAKE%

set MSVCDir=%DEVROOT%\Tools\MSC\VC98

@rem Alias to the linux environment
set OSTYPE=%OS%

rem Basic Runtime settings
set RUNROOT=%DEVROOT%\projects

rem Some bin dirs for development

rem set CVSBIN=%DEVROOT%\Tools\cvs
set WATBIN=%DEVROOT%\Tools\WATCOM\BINNT;%DEVROOT%\Tools\WATCOM\BINW
set DEVBIN=%DEVROOT%\bin

rem Some dll and bin search Paths
set DLLROOT=%RUNROOT%\dll
set BINROOT=%RUNROOT%\bin;%RUNROOT%\CPP\bin

set Path=%SystemRoot%\system32;C:\cygwin\bin;C:\;%WATBIN%;%DEVBIN%;%DLLROOT%;%BINROOT%

set MSC=%MSVCDir%\Bin;%MSVCDir%\Lib

set Path=%MSC%;%Path%;%DEVROOT%\bin
rem ??? F:\develop\NT\DevTools\bin

rem MSC Library path
set LIB=%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%LIB%

rem Watcom stuff

SET INCLUDE=%DEVROOT%\wxwin\wx\src\msw;%MSVCDir%\Include;%DEVROOT%\Tools\WATCOM\

rem ???;D:\Develop\Tools\WATCOM\H\NT
rem SET INCLUDE=
SET WATCOM=%DEVROOT%\Tools\WATCOM
SET EDPath=%DEVROOT%\Tools\WATCOM\EDDAT

rem WXWIN stuff

set WXWIN=%DEVROOT%\wxwin\wx

@rem XML Module Configuration

set LBHOSTCFGFILE=%DEVROOT%\Projects\CPP\Test\Console\XML\lbXMLConfig.xml

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
