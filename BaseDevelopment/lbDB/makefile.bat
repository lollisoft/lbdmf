@echo off
@rem This script creates a makefile based on templates

rem Linking fails, if the backup file of the source is readonly
attrib -r *.bak
rem copy ..\lbHook\lbHook.cpp .
type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbDB.dll >> makefile

mkmk dll lbDB %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile
