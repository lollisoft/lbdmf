@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbDOMConfig.dll >> makefile
copy ..\..\lbHook\lbHook.cpp .
mkmk dll lbDOMConfig %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile

