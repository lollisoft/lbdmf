@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo all: lbDOMConfig.dll >> makefile

mkmk dll lbDOMConfig %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile

