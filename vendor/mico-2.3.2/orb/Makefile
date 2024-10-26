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


MOD_INCL_MINGW=$(STD_INCL_MINGW) -DALLOW_SUBTYPING -DBUILD_MICO_DLL -D_WINDOWS -Wno-narrowing -fpermissive -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/Interfaces -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/ProxyPlugins -I../include -I../include/windows
MOD_INCL_MINGW_CPP=$(STD_INCL_MINGW_CPP) -DALLOW_SUBTYPING -DBUILD_MICO_DLL -D_WINDOWS -Wno-narrowing -fpermissive -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/Interfaces -I$(DEVROOT_MAKE_APPLICATIONS)$(RELPATH_MAKE)/AppDevelopment/ProxyPlugins -I../include -I../include/windows

MOD_INCL=$(STD_INCL) -I=$(DEVROOT)$(RELPATH)\\AppDevelopment\\Interfaces
MOD_INCL_CPP=$(STD_INCL_CPP) -I=$(DEVROOT_MAKE)$(RELPATH_MAKE)/AppDevelopment/Interfaces
LIBS = $(BASE_LIBS) $(DEVROOT_MAKE)/projects/dll/libs/lbhook.lib,../../../../tools/watcom/lib386/nt/odbc32.lib

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
Path=/cygdrive/c/Program Files/GNU/WinCvs 1.2:/cygdrive/c/Q/develop/Tools/curl:/cygdrive/c/Q/develop/Tools/7Zip/7-Zip:/cygdrive/c/lbDMF/develop/Tools/MSC/VC98/Bin:/cygdrive/c/lbDMF/develop/Tools/MSC/VC98/Lib:/cygdrive/c/lbDMF/develop/bin:/cygdrive/c/Windows/system32:/cygdrive/c:/cygdrive/c/lbDMF/develop/Tools/WATCOM/BINNT:/cygdrive/c/lbDMF/develop/Tools/WATCOM/BINW:/cygdrive/c/lbDMF/develop/bin:/dll:/usr/bin:/lbdmf/bin:/cygdrive/q/develop/tools/bin:/cygdrive/q/develop/tools/cygwin/bin:/cygdrive/q/develop/Tools/Perl/bin:/cygdrive/g/gs/gs8.15/bin:/cygdrive/q/develop/Tools/TP:/cygdrive/q/develop/Tools/TP/TPU:/cygdrive/g/FPC/2.0.4/bin/i386-win32:/cygdrive/c/Programme/Graphviz2.26.3/bin:/cygdrive/c/lbDMF/Develop/Tools/doxygen/bin:/cygdrive/c/lbDMF/Develop/Tools/Graphviz2.26.3/bin:/cygdrive/c/lbDMF/develop/Tools/mingw/bin:/cygdrive/c/lbDMF/develop/Tools/mingw32/bin:/cygdrive/e/Program Files/Powersoft/Power21/System:/cygdrive/q/develop/Tools/Bakefile:/cygdrive/c/lbDMF/develop/bin:/cygdrive/c/develop/Tools/Perl/bin:/cygdrive/c/develop/Tools/doxygen/bin:/cygdrive/c/lbDMF/develop/Projects/lbdmf/vendor/ACE_wrappers/lib:/cygdrive/c/develop/Tools/GCC_XML/bin:/cygdrive/c/Programme/Beaver Debugger:/cygdrive/c/lbDMF/develop/Tools/MinGW/msys/1.0/bin
OBJ =o
all: orb.dll
orb.dll.lnk: makefile $(OBJS)
		echo NAME orb.dll > $@
		echo FIL address.$(OBJ) >> $@
		echo FIL any.$(OBJ) >> $@
		echo FIL basic_seq.$(OBJ) >> $@
		echo FIL boa.$(OBJ) >> $@
		echo FIL buffer.$(OBJ) >> $@
		echo FIL codec.$(OBJ) >> $@
		echo FIL codeset.$(OBJ) >> $@
		echo FIL context.$(OBJ) >> $@
		echo FIL current.$(OBJ) >> $@
		echo FIL dii.$(OBJ) >> $@
		echo FIL dispatch.$(OBJ) >> $@
		echo FIL dsi.$(OBJ) >> $@
		echo FIL dynany.$(OBJ) >> $@
		echo FIL dynany_impl.$(OBJ) >> $@
		echo FIL except.$(OBJ) >> $@
		echo FIL except2.$(OBJ) >> $@
		echo FIL fixed.$(OBJ) >> $@
		echo FIL intercept.$(OBJ) >> $@
		echo FIL iop.$(OBJ) >> $@
		echo FIL ioptypes.$(OBJ) >> $@
		echo FIL ior.$(OBJ) >> $@
		echo FIL memcheck.$(OBJ) >> $@
		echo FIL memtrace.$(OBJ) >> $@
		echo FIL object.$(OBJ) >> $@
		echo FIL orb.$(OBJ) >> $@
		echo FIL orb_all.$(OBJ) >> $@
		echo FIL orb_excepts.$(OBJ) >> $@
		echo FIL os-unix.$(OBJ) >> $@
		echo FIL os-windows.$(OBJ) >> $@
		echo FIL poa.$(OBJ) >> $@
		echo FIL poa_base.$(OBJ) >> $@
		echo FIL poa_impl.$(OBJ) >> $@
		echo FIL policy.$(OBJ) >> $@
		echo FIL policy2.$(OBJ) >> $@
		echo FIL policy_impl.$(OBJ) >> $@
		echo FIL queue.$(OBJ) >> $@
		echo FIL service_info.$(OBJ) >> $@
		echo FIL ssl.$(OBJ) >> $@
		echo FIL ssliop.$(OBJ) >> $@
		echo FIL static.$(OBJ) >> $@
		echo FIL string.$(OBJ) >> $@
		echo FIL tckind.$(OBJ) >> $@
		echo FIL transport.$(OBJ) >> $@
		echo FIL typecode.$(OBJ) >> $@
		echo FIL uni_base64.$(OBJ) >> $@
		echo FIL uni_fromuni.$(OBJ) >> $@
		echo FIL uni_touni.$(OBJ) >> $@
		echo FIL uni_unicode.$(OBJ) >> $@
		echo FIL util.$(OBJ) >> $@
		echo FIL value.$(OBJ) >> $@
		echo FIL valuetype.$(OBJ) >> $@
		echo FIL valuetype_impl.$(OBJ) >> $@
		echo FIL win32def.$(OBJ) >> $@
		echo FIL win32dll.$(OBJ) >> $@
address.$(OBJ): makefile address.cc
		@echo Build address.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oaddress.$(OBJ) address.cc
any.$(OBJ): makefile any.cc
		@echo Build any.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oany.$(OBJ) any.cc
basic_seq.$(OBJ): makefile basic_seq.cc
		@echo Build basic_seq.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -obasic_seq.$(OBJ) basic_seq.cc
boa.$(OBJ): makefile boa.cc
		@echo Build boa.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oboa.$(OBJ) boa.cc
buffer.$(OBJ): makefile buffer.cc
		@echo Build buffer.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -obuffer.$(OBJ) buffer.cc
codec.$(OBJ): makefile codec.cc
		@echo Build codec.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ocodec.$(OBJ) codec.cc
codeset.$(OBJ): makefile codeset.cc uni_conversion.h uni_types.h \
		 uni_strtypes.h uni_errors.h
		@echo Build codeset.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ocodeset.$(OBJ) codeset.cc
context.$(OBJ): makefile context.cc
		@echo Build context.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ocontext.$(OBJ) context.cc
current.$(OBJ): makefile current.cc
		@echo Build current.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ocurrent.$(OBJ) current.cc
dii.$(OBJ): makefile dii.cc
		@echo Build dii.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -odii.$(OBJ) dii.cc
dispatch.$(OBJ): makefile dispatch.cc
		@echo Build dispatch.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -odispatch.$(OBJ) dispatch.cc
dsi.$(OBJ): makefile dsi.cc
		@echo Build dsi.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -odsi.$(OBJ) dsi.cc
dynany.$(OBJ): makefile dynany.cc
		@echo Build dynany.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -odynany.$(OBJ) dynany.cc
dynany_impl.$(OBJ): makefile dynany_impl.cc
		@echo Build dynany_impl.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -odynany_impl.$(OBJ) dynany_impl.cc
except.$(OBJ): makefile except.cc
		@echo Build except.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oexcept.$(OBJ) except.cc
except2.$(OBJ): makefile except2.cc
		@echo Build except2.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oexcept2.$(OBJ) except2.cc
fixed.$(OBJ): makefile fixed.cc
		@echo Build fixed.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ofixed.$(OBJ) fixed.cc
intercept.$(OBJ): makefile intercept.cc
		@echo Build intercept.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ointercept.$(OBJ) intercept.cc
iop.$(OBJ): makefile iop.cc
		@echo Build iop.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oiop.$(OBJ) iop.cc
ioptypes.$(OBJ): makefile ioptypes.cc
		@echo Build ioptypes.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oioptypes.$(OBJ) ioptypes.cc
ior.$(OBJ): makefile ior.cc
		@echo Build ior.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oior.$(OBJ) ior.cc
memcheck.$(OBJ): makefile memcheck.cc
		@echo Build memcheck.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -omemcheck.$(OBJ) memcheck.cc
memtrace.$(OBJ): makefile memtrace.cc
		@echo Build memtrace.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -omemtrace.$(OBJ) memtrace.cc
object.$(OBJ): makefile object.cc
		@echo Build object.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oobject.$(OBJ) object.cc
orb.$(OBJ): makefile orb.cc
		@echo Build orb.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oorb.$(OBJ) orb.cc
orb_all.$(OBJ): makefile orb_all.cc address.cc any.cc basic_seq.cc boa.cc \
		 buffer.cc codec.cc context.cc dii.cc dsi.cc iop.cc ior.cc object.cc \
		 value.cc valuetype_impl.cc orb.cc string.cc except.cc transport.cc \
		 dispatch.cc typecode.cc util.cc fixed.cc codeset.cc uni_conversion.h \
		 uni_types.h uni_strtypes.h uni_errors.h queue.cc static.cc intercept.cc \
		 os-unix.cc ssl.cc current.cc valuetype.cc policy2.cc dynany_impl.cc \
		 policy_impl.cc service_info.cc ioptypes.cc tckind.cc orb_excepts.cc \
		 policy.cc poa.cc poa_base.cc poa_impl.cc dynany.cc ssliop.cc
		@echo Build orb_all.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oorb_all.$(OBJ) orb_all.cc
orb_excepts.$(OBJ): makefile orb_excepts.cc
		@echo Build orb_excepts.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oorb_excepts.$(OBJ) orb_excepts.cc
os-unix.$(OBJ): makefile os-unix.cc
		@echo Build os-unix.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oos-unix.$(OBJ) os-unix.cc
os-windows.$(OBJ): makefile os-windows.cc
		@echo Build os-windows.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oos-windows.$(OBJ) os-windows.cc
poa.$(OBJ): makefile poa.cc
		@echo Build poa.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opoa.$(OBJ) poa.cc
poa_base.$(OBJ): makefile poa_base.cc
		@echo Build poa_base.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opoa_base.$(OBJ) poa_base.cc
poa_impl.$(OBJ): makefile poa_impl.cc
		@echo Build poa_impl.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opoa_impl.$(OBJ) poa_impl.cc
policy.$(OBJ): makefile policy.cc
		@echo Build policy.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opolicy.$(OBJ) policy.cc
policy2.$(OBJ): makefile policy2.cc
		@echo Build policy2.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opolicy2.$(OBJ) policy2.cc
policy_impl.$(OBJ): makefile policy_impl.cc
		@echo Build policy_impl.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -opolicy_impl.$(OBJ) policy_impl.cc
queue.$(OBJ): makefile queue.cc
		@echo Build queue.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oqueue.$(OBJ) queue.cc
service_info.$(OBJ): makefile service_info.cc
		@echo Build service_info.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -oservice_info.$(OBJ) service_info.cc
ssl.$(OBJ): makefile ssl.cc
		@echo Build ssl.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ossl.$(OBJ) ssl.cc
ssliop.$(OBJ): makefile ssliop.cc
		@echo Build ssliop.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ossliop.$(OBJ) ssliop.cc
static.$(OBJ): makefile static.cc
		@echo Build static.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ostatic.$(OBJ) static.cc
string.$(OBJ): makefile string.cc
		@echo Build string.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ostring.$(OBJ) string.cc
tckind.$(OBJ): makefile tckind.cc
		@echo Build tckind.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -otckind.$(OBJ) tckind.cc
transport.$(OBJ): makefile transport.cc
		@echo Build transport.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -otransport.$(OBJ) transport.cc
typecode.$(OBJ): makefile typecode.cc
		@echo Build typecode.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -otypecode.$(OBJ) typecode.cc
uni_base64.$(OBJ): makefile uni_base64.cc uni_base64.h uni_types.h \
		 uni_errors.h uni_support.h
		@echo Build uni_base64.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ouni_base64.$(OBJ) uni_base64.cc
uni_fromuni.$(OBJ): makefile uni_fromuni.cc uni_unicode.h uni_types.h \
		 uni_base64.h uni_strtypes.h uni_errors.h uni_conversion.h
		@echo Build uni_fromuni.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ouni_fromuni.$(OBJ) uni_fromuni.cc
uni_touni.$(OBJ): makefile uni_touni.cc uni_unicode.h uni_types.h \
		 uni_base64.h uni_strtypes.h uni_errors.h uni_conversion.h
		@echo Build uni_touni.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ouni_touni.$(OBJ) uni_touni.cc
uni_unicode.$(OBJ): makefile uni_unicode.cc uni_unicode.h uni_types.h \
		 uni_base64.h uni_errors.h uni_support.h
		@echo Build uni_unicode.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ouni_unicode.$(OBJ) uni_unicode.cc
util.$(OBJ): makefile util.cc
		@echo Build util.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -outil.$(OBJ) util.cc
value.$(OBJ): makefile value.cc
		@echo Build value.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ovalue.$(OBJ) value.cc
valuetype.$(OBJ): makefile valuetype.cc
		@echo Build valuetype.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ovaluetype.$(OBJ) valuetype.cc
valuetype_impl.$(OBJ): makefile valuetype_impl.cc
		@echo Build valuetype_impl.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -ovaluetype_impl.$(OBJ) valuetype_impl.cc
win32def.$(OBJ): makefile win32def.cc
		@echo Build win32def.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -owin32def.$(OBJ) win32def.cc
win32dll.$(OBJ): makefile win32dll.cc
		@echo Build win32dll.cc
		$(CPPMINGW)  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -owin32dll.$(OBJ) win32dll.cc
OBJS = address.$(OBJ) any.$(OBJ) basic_seq.$(OBJ) boa.$(OBJ) buffer.$(OBJ) \
		 codec.$(OBJ) codeset.$(OBJ) context.$(OBJ) current.$(OBJ) dii.$(OBJ) \
		 dispatch.$(OBJ) dsi.$(OBJ) dynany.$(OBJ) dynany_impl.$(OBJ) \
		 except.$(OBJ) except2.$(OBJ) fixed.$(OBJ) intercept.$(OBJ) iop.$(OBJ) \
		 ioptypes.$(OBJ) ior.$(OBJ) memcheck.$(OBJ) memtrace.$(OBJ) \
		 object.$(OBJ) orb.$(OBJ) orb_all.$(OBJ) orb_excepts.$(OBJ) \
		 os-unix.$(OBJ) os-windows.$(OBJ) poa.$(OBJ) poa_base.$(OBJ) \
		 poa_impl.$(OBJ) policy.$(OBJ) policy2.$(OBJ) policy_impl.$(OBJ) \
		 queue.$(OBJ) service_info.$(OBJ) ssl.$(OBJ) ssliop.$(OBJ) static.$(OBJ) \
		 string.$(OBJ) tckind.$(OBJ) transport.$(OBJ) typecode.$(OBJ) \
		 uni_base64.$(OBJ) uni_fromuni.$(OBJ) uni_touni.$(OBJ) \
		 uni_unicode.$(OBJ) util.$(OBJ) value.$(OBJ) valuetype.$(OBJ) \
		 valuetype_impl.$(OBJ) win32def.$(OBJ) win32dll.$(OBJ)
OBJLIST = address.$(OBJ), any.$(OBJ), basic_seq.$(OBJ), boa.$(OBJ), buffer.$(OBJ), \
		 codec.$(OBJ), codeset.$(OBJ), context.$(OBJ), current.$(OBJ), \
		 dii.$(OBJ), dispatch.$(OBJ), dsi.$(OBJ), dynany.$(OBJ), \
		 dynany_impl.$(OBJ), except.$(OBJ), except2.$(OBJ), fixed.$(OBJ), \
		 intercept.$(OBJ), iop.$(OBJ), ioptypes.$(OBJ), ior.$(OBJ), \
		 memcheck.$(OBJ), memtrace.$(OBJ), object.$(OBJ), orb.$(OBJ), \
		 orb_all.$(OBJ), orb_excepts.$(OBJ), os-unix.$(OBJ), os-windows.$(OBJ), \
		 poa.$(OBJ), poa_base.$(OBJ), poa_impl.$(OBJ), policy.$(OBJ), \
		 policy2.$(OBJ), policy_impl.$(OBJ), queue.$(OBJ), service_info.$(OBJ), \
		 ssl.$(OBJ), ssliop.$(OBJ), static.$(OBJ), string.$(OBJ), tckind.$(OBJ), \
		 transport.$(OBJ), typecode.$(OBJ), uni_base64.$(OBJ), \
		 uni_fromuni.$(OBJ), uni_touni.$(OBJ), uni_unicode.$(OBJ), util.$(OBJ), \
		 value.$(OBJ), valuetype.$(OBJ), valuetype_impl.$(OBJ), win32def.$(OBJ), \
		 win32dll.$(OBJ)
FILE = FIL
FILE += $(OBJLIST)
LNK=orb.lnk
ifeq ($(COMPILER), WATCOM)
LINKFLAGS=@orb.dll.lnk
endif
ifeq ($(COMPILER), MICROSOFT)
LINKFLAGS=$(OBJS) $(VENDORLIBS) $(LIBS)
endif
PROGRAM=orb
ifeq ($(COMPILER), WATCOM)

orb.dll: $(OBJS) orb.dll.lnk
		@echo Link orb.dll
		@cmd /C if NOT "$(LIBS)" == "" echo LIBR $(LIBS) >> $@.lnk
		@$(CPPMINGW) -fPIC -shared -Wl,--enable-auto-import -Wl,--subsystem,windows -mthreads -mwindows -Wl,--out-implib=$(PROGRAM).a -o $(PROGRAM).dll $(OBJS) $(MINGWLIBS)
		@$(CP) $(PROGRAM).dll $(DLLDIR) > null
		@$(CP) $(PROGRAM).a $(DLLLIBDIR) > null
		@$(POST_PROCESS) 
endif
ifeq ($(COMPILER), MICROSOFT)

orb.dll: $(OBJS)
		@echo Link orb.dll
		@echo NAME $(PROGRAM).dll > $(LNK)
		@echo $(FILE) $(LIBS) >> $(LNK)
		@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)
		$(CP) $(PROGRAM).dll $(DLLDIR) > null
		$(CP) $(PROGRAM).lib $(DLLLIBDIR) > null
		@$(POST_PROCESS) 
endif
clean:
		-@rm *.exp *.err *.ilk *.lib *.lk1 *.mk1 *.map *.mk *.mk1 *.sym *.obj *.o *.idb *.pch *.pdb
		-@rm -f *.bak
		-@rm *.dll
distclean:
		-@rm *.o
		-@rm makefile
		-@rm *.log
		-@rm *.so.*
