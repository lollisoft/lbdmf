@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbDB.dll >> makefile

mkmk dll lbDB %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile
