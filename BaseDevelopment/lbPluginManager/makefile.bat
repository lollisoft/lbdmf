@echo off
@rem This script creates a makefile based on templates

rem Linking fails, if the backup file of the source is readonly
attrib -r *.bak
type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbPluginManager.dll >> makefile

mkmk dll lbPluginManager %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile
