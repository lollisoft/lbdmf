# **************************************************************
# * $Locker:  $
# * $Revision: 1.1 $
# * $Name:  $
# * $Id: lbDOMConfig.mak,v 1.1 2001/04/05 18:54:14 lothar Exp $
# *
# * $Log: lbDOMConfig.mak,v $
# * Revision 1.1  2001/04/05 18:54:14  lothar
# * Initial (should work with foreign source dirs)
# *
# **************************************************************

# Microsoft Developer Studio Generated NMAKE File, Based on lbDOMConfig.dsp
!IF "$(CFG)" == ""
CFG=lbDOMConfig - Win32 Debug
!MESSAGE No configuration specified. Defaulting to lbDOMConfig - Win32 Debug.
!ENDIF 

#...sHandle errors:0:
!IF "$(CFG)" != "lbDOMConfig - Win32 Release" && "$(CFG)" != "lbDOMConfig - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lbDOMConfig.mak" CFG="lbDOMConfig - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lbDOMConfig - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lbDOMConfig - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 
#...e

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

#...sRelease build:0:
!IF  "$(CFG)" == "lbDOMConfig - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
LB_DEFINES=/D WINDOWS /D LB_RUNTIME_LINK
LB_INCLUDE=/I q:\develop\projects\cpp\include /I Q:\Develop\Projects\CPP\BaseDevelopment\lbclasses
#HOOKDIR=..\..\lbHook
HOOKDIR=.

# End Custom Macros

ALL : "$(OUTDIR)\lbDOMConfig.dll"


CLEAN :
-@erase "$(INTDIR)\lbDOMConfig.obj"
-@erase "$(INTDIR)\vc60.idb"
-@erase "$(OUTDIR)\lbDOMConfig.dll"
-@erase "$(OUTDIR)\lbDOMConfig.exp"
-@erase "$(OUTDIR)\lbDOMConfig.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo $(LB_DEFINES) $(LB_INCLUDE) /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LBDOMCONFIG_EXPORTS" /Fp"$(INTDIR)\lbDOMConfig.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.cpp{$(HOOKDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lbDOMConfig.bsc" 
BSC32_SBRS= \

LINK32=link.exe
#LINK32_FLAGS=..\..\..\..\dll\libs\lbhook.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\lbDOMConfig.pdb" /machine:I386 /out:"$(OUTDIR)\lbDOMConfig.dll" /implib:"$(OUTDIR)\lbDOMConfig.lib" 
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\lbDOMConfig.pdb" /machine:I386 /out:"$(OUTDIR)\lbDOMConfig.dll" /implib:"$(OUTDIR)\lbDOMConfig.lib" 
LINK32_OBJS= \
"$(INTDIR)\lbDOMConfig.obj" \
"$(INTDIR)\lbHook.obj"

"$(OUTDIR)\lbDOMConfig.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<
#...e
!ELSEIF  "$(CFG)" == "lbDOMConfig - Win32 Debug"
#...sDebug build:0:

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
HOOKDIR=.
LB_DEFINES=/D WINDOWS /D LB_RUNTIME_LINK
LB_INCLUDE=/I q:\develop\projects\cpp\include /I Q:\Develop\Projects\CPP\BaseDevelopment\lbclasses
# End Custom Macros

ALL : "$(OUTDIR)\lbDOMConfig.dll"


CLEAN :
	-@erase "$(INTDIR)\lbDOMConfig.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\lbDOMConfig.dll"
	-@erase "$(OUTDIR)\lbDOMConfig.exp"
	-@erase "$(OUTDIR)\lbDOMConfig.ilk"
	-@erase "$(OUTDIR)\lbDOMConfig.lib"
	-@erase "$(OUTDIR)\lbDOMConfig.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo $(LB_DEFINES) $(LB_INCLUDE) /MTd /W3 /Gm /GX /ZI /Od /I "E:\develop\projects\lothar\XML\xml4c3_1_0-win32\include" /I "Q:\Develop\Projects\CPP\include" /I "Q:\Develop\Projects\CPP\interfaces" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LBDOMCONFIG_EXPORTS" /Fp"$(INTDIR)\lbDOMConfig.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

!MESSAGE Includes:
!MESSAGE $(LB_INCLUDE)
!MESSAGE _____________

.cpp{$(HOOKDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) /I "/TEST" $< 
<<

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lbDOMConfig.bsc" 
BSC32_SBRS= \

LINK32=link.exe
#LINK32_FLAGS=..\..\..\..\dll\libs\lbhook.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib E:\develop\projects\lothar\XML\xml4c3_1_0-win32\lib\xerces-c_1.lib E:\develop\projects\lothar\XML\xml4c3_1_0-win32\lib\icuuc.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\lbDOMConfig.pdb" /debug /machine:I386 /out:"$(OUTDIR)\lbDOMConfig.dll" /implib:"$(OUTDIR)\lbDOMConfig.lib" /pdbtype:sept 
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib E:\develop\projects\lothar\XML\xml4c3_1_0-win32\lib\xerces-c_1.lib E:\develop\projects\lothar\XML\xml4c3_1_0-win32\lib\icuuc.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\lbDOMConfig.pdb" /debug /machine:I386 /out:"$(OUTDIR)\lbDOMConfig.dll" /implib:"$(OUTDIR)\lbDOMConfig.lib" /pdbtype:sept 
LINK32_OBJS= \
"$(INTDIR)\lbDOMConfig.obj" \
"$(INTDIR)\lbHook.obj"

"$(OUTDIR)\lbDOMConfig.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<
#...e

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\lbDOMConfig.dll"
   copy debug\*.dll q:\develop\xml
   copy debug\*.dll q:\develop\projects\dll
   copy lbDOMConfig.h q:\develop\projects\cpp\include
   echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("lbDOMConfig.dep")
!INCLUDE "lbDOMConfig.dep"
!ELSE 
!MESSAGE Warning: cannot find "lbDOMConfig.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "lbDOMConfig - Win32 Release" || "$(CFG)" == "lbDOMConfig - Win32 Debug"
SOURCE=.\lbDOMConfig.cpp .\lbHook.cpp

!MESSAGE Compiling source
"$(INTDIR)\lbDOMConfig.obj" : $(SOURCE) "$(INTDIR)"
!MESSAGE Compiled


!ENDIF 

