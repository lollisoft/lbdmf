@echo off
@rem This script creates a makefile based on templates

type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo all: premake mkmk.exe >> makefile
echo premake: >> makefile
@rem echo 		@echo No premake >> makefile
echo clean: >> makefile
echo 		@del *.obj >> makefile
echo 		@del *.exe >> makefile

mkmk exe mkmk ../dosdir *.cpp >> makefile
