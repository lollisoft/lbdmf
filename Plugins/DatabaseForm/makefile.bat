@echo off
@rem This script creates a makefile based on templates

rem Linking fails, if the backup file of the source is readonly
if exist "*.bak" attrib -r *.bak
type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbDatabaseForm.dll >> makefile

mkmk plugin lbDatabaseForm %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile
