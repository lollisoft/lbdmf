@echo off
@rem This script creates a makefile based on templates

type makefile.template > makefile
type makefile.module >> makefile
echo all: mkmk.exe >> makefile

mkmk exe mkmk ../dosdir *.cpp >> makefile
