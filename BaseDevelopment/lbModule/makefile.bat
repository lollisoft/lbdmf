@echo off
@rem This script creates a makefile based on templates

if exist "*.bak" attrib -r *.bak
if exist "*.bak" del *.bak
type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbModule.dll >> makefile

mkmk dll lbModule %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile
