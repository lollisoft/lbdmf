@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo all: lbMetaApp.dll >> makefile

mkmk dll lbMetaApp %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile

