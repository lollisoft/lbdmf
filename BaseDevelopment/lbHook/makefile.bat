@echo off
@rem This script creates a makefile based on templates

@echo makefile.bat called '%DEVROOT%'

type %DEVROOT%/Projects/cpp/make/makefile.template > makefile
type makefile.module >> makefile
echo Path=$(PATH) >> makefile
echo all: lbhook.dll >> makefile

copy %DEVROOT%/Projects/cpp/basedevelopment/lbclasses/lbkey.h %DEVROOT%/Projects/cpp/include

mkmk dll lbhook ../dosdir *.cpp >> makefile
