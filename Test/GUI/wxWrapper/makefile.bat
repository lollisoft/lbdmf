@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: wxwrapper.exe >> makefile

mkmk exe wxwrapper .,..\..\..\..\..\wxwin\wx *.cpp >> makefile
