@echo off
@rem This script creates a makefile based on templates
@echo Build makefile
type %DEVROOT%\Projects\cpp\make\makefile.template > makefile
type makefile.module >> makefile
echo all: premake lbClasses.dll >> makefile
echo premake: >> makefile
set echodef=@copy lbKey.h $(DEVROOT)\projects\dll\include > null
echo		%echodef% >> makefile
echo clean: >> makefile
echo 		@del *.obj >> makefile
echo 		@del *.dll >> makefile

mkmk dll lbClasses %DEVROOT%\include,%DEVROOT%\interfaces *.cpp >> makefile

