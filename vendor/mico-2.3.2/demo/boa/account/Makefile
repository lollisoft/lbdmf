#    DMF Distributed Multiplatform Framework (the initial goal of this library)
#    This file is part of lbDMF.
#    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#
#    The author of this work will be reached by e-Mail or paper mail.
#    e-Mail: lothar.behrens@lollisoft.de
#    p-Mail: Lothar Behrens
#            Odenwaldstr. 14
#
#            63150 Heusenstamm (germany)
# Standard template

ifeq ($(OSTYPE), Windows_NT)
ifeq ($(CRUISECONTROL), yes)
RELPATH_MAKE=\Projects\$(REPO_NAME)
RELPATH=//Projects//$(REPO_NAME)
else
RELPATH_MAKE=\Projects\$(REPO_NAME)
RELPATH=//Projects//$(REPO_NAME)
endif

include $(DEVROOT_MAKE)$(RELPATH_MAKE)/make/STD_MAKE

# Rule to overcome the possible override of path with recursive make

DEVROOT_MINGW=$(DEVLW)/$(BASE_MAKE)

endif

ifeq ($(OSTYPE), linux-debian-ppc)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
include $(DEVROOT)$(RELPATH)/make/STD_MAKE
endif

ifeq ($(OSTYPE), solaris)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
include $(DEVROOT)$(RELPATH)/make/STD_MAKE
endif

ifeq ($(OSTYPE), linux)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
include $(DEVROOT)$(RELPATH)/make/STD_MAKE
endif

ifeq ($(OSTYPE), osx)
ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/$(REPO_NAME)
else
RELPATH=/Projects/$(REPO_NAME)
endif
include $(DEVROOT)$(RELPATH)/make/STD_MAKE
endif

ifndef prefix
prefix=$(HOME)
endif

exec_prefix=$(prefix)
bindir=$(exec_prefix)/bin
sbindir=$(exec_prefix)/sbin
libdir=$(exec_prefix)/lib
plugindir=$(exec_prefix)/plugins

INSTALL=install
INSTALL_PROGRAM=$(INSTALL)
ifeq ($(OSTYPE), linux)
STRIP=strip -s
endif
ifeq ($(OSTYPE), linux-debian-ppc)
STRIP=strip -s
endif
ifeq ($(OSTYPE), solaris)
STRIP=strip 
endif
# Define your module based settings

ifeq ($(OSTYPE), Windows_NT)


MOD_INCL_MINGW=$(STD_INCL_MINGW) -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/Interfaces -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/ProxyPlugins
# Additions regarding MICO
MOD_INCL_MINGW+= -DALLOW_SUBTYPING -DBUILD_MICO_DLL -D_WINDOWS -Wno-narrowing -fpermissive -I../../../include -I../../../include/windows
MOD_INCL_MINGW_CPP=$(STD_INCL_MINGW_CPP) -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/Interfaces -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/ProxyPlugins
# Additions regarding MICO
MOD_INCL_MINGW_CPP+= -DALLOW_SUBTYPING -DBUILD_MICO_DLL -D_WINDOWS -Wno-narrowing -fpermissive -I../../../include -I../../../include/windows

MOD_INCL=$(STD_INCL) -I=$(DEVROOT)$(RELPATH)\\AppDevelopment\\Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I=$(DEVROOT_MAKE)$(RELPATH_MAKE)/AppDevelopment/Interfaces
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)/projects/dll/libs/lbhook.lib,../../../../tools/watcom/lib386/nt/odbc32.lib

MINGWLIBS += -L$(DEVROOT_MINGW)$(SLASH)projects$(SLASH)dll$(SLASH)libs
MINGWLIBS += -lorb

# use global setup
#COMPILER=MICROSOFT
ifeq ($(COMPILER), MICROSOFT)
MOD_INCL = $(STD_INCL_MICROSOFT)
MOD_INCL += $(foreach s, $(INCLS), /I "$s")
LIBS = $(BASE_LIBS), Q:/develop/Tools/msc/VC98/Lib/odbc32.lib
CC=Cl
C_DLLOPS= $(C_DLLOPS_MICROSOFT$(MODE))
C_EXEOPS= $(C_EXEOPS_MICROSOFT$(MODE))
C_LIBOPS= $(C_LIBOPS_MICROSOFT$(MODE))
LINK=  $(LINK_MICROSOFT)
L_DLLOPS= $(L_DLLOPS_MICROSOFT)
LNKDLLOPS = $(L_DLLOPS_MICROSOFT)
endif

#OBJDEP=../lbHook/lbHook.o
# ../lbHook/conio.o
endif

ifeq ($(OSTYPE), linux)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
OBJDEP=
VENDORLIBS=-L$(prefix)/lib -llbHook /usr/lib/libodbc.so
endif    

ifeq ($(LB_USE_FRAMEWORKS), yes)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)$(RELPATH)/AppDevelopment/Interfaces -I $(DEVROOT)$(RELPATH)/BaseDevelopment/lbcs
MOD_INCL_CPP=$(STD_INCL_CPP) -I $(DEVROOT)$(RELPATH)/AppDevelopment/Interfaces -I $(DEVROOT)$(RELPATH)/BaseDevelopment/lbcs
OBJDEP=
LIBS = -F$(prefix)/Library/Frameworks -framework lbHook
#VENDORLIBS=/usr/lib/libiodbc.dylib
endif    

endif

ifeq ($(LB_USE_FRAMEWORKS), no)

ifeq ($(OSTYPE), osx)
MOD_INCL=$(STD_INCL) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I $(DEVROOT)/Projects/CPP/AppDevelopment/Interfaces
OBJDEP=
VENDORLIBS=$(HOME)/lib/lbhook.so /usr/lib/libiodbc.dylib
endif    

endif
Path=/cygdrive/c/Program Files/GNU/WinCvs 1.2:/cygdrive/q/Q/develop/Tools/curl:/cygdrive/q/Q/develop/Tools/7Zip/7-Zip:/cygdrive/q/develop/Tools/MSC/VC98/Bin:/cygdrive/q/develop/Tools/MSC/VC98/Lib:/cygdrive/q/develop/bin:/cygdrive/c/Windows/system32:/cygdrive/q:/cygdrive/q/develop/Tools/WATCOM/BINNT:/cygdrive/q/develop/Tools/WATCOM/BINW:/cygdrive/q/develop/bin:/dll:/usr/bin:/lbdmf/bin:/cygdrive/q/develop/tools/bin:/cygdrive/q/develop/tools/cygwin/bin:/cygdrive/q/develop/Tools/Perl/bin:/cygdrive/g/gs/gs8.15/bin:/cygdrive/q/develop/Tools/TP:/cygdrive/q/develop/Tools/TP/TPU:/cygdrive/g/FPC/2.0.4/bin/i386-win32:/cygdrive/c/Programme/Graphviz2.26.3/bin:/cygdrive/q/lbDMF/Develop/Tools/doxygen/bin:/cygdrive/q/lbDMF/Develop/Tools/Graphviz2.26.3/bin:/cygdrive/q/develop/Tools/mingw/bin:/cygdrive/q/develop/Tools/mingw64/bin:/cygdrive/q/develop/Tools/mingw32/bin:/cygdrive/e/Program Files/Powersoft/Power21/System:/cygdrive/q/develop/Tools/Bakefile:/cygdrive/q/develop/bin:/cygdrive/q/develop/Tools/Perl/bin:/cygdrive/q/develop/Tools/doxygen/bin:/cygdrive/q/develop/Projects/lbdmf/vendor/ACE_wrappers/lib:/cygdrive/q/develop/Tools/GCC_XML/bin:/cygdrive/c/Programme/Beaver Debugger:/cygdrive/q/develop/Tools/MinGW/msys/1.0/bin
OBJ =o
all: accountTest.exe
accountTest.exe.lnk: makefile $(OBJS)
		echo NAME accountTest.exe > $@
		echo FIL main.$(OBJ) >> $@
main.$(OBJ): makefile main.cc
		@echo Build main.cc
		$(CPPMINGW) -c $(CPP_MINGW_EXEOPS) $(MOD_INCL_MINGW_CPP) -omain.$(OBJ) main.cc

OBJS = main.$(OBJ)
OBJLIST = main.$(OBJ)
PROGRAM=accountTest

accountTest.exe: $(OBJS)
		@g++ -Wl,--enable-auto-import -o $(PROGRAM).exe $(OBJS) $(MINGWLIBS)
		@$(CP) $(PROGRAM).exe $(EXEDIR) > null
clean:
		-@rm *.exp *.err *.ilk *.lib *.lk1 *.mk1 *.map *.mk *.mk1 *.sym *.obj *.o *.idb *.pch *.pdb
		-@rm -f *.bak
		-@rm *.dll
distclean:
		-@rm *.o
		-@rm makefile
		-@rm *.log
		-@rm *.so.*
