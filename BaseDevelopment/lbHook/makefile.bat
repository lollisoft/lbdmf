@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo all: lbhook.lib >> makefile

mkmk lib lbhook ..\dosdir *.cpp >> makefile
