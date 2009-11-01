#
# MICO --- a free CORBA implementation
# Copyright (C) 1997 Kay Roemer & Arno Puder
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# Send comments and/or bug reports to:
#                mico@informatik.uni-frankfurt.de
#

include ../MakeVars

CXXFLAGS := -I../include $(CXXFLAGS)
EH_CXXFLAGS := $(CXXFLAGS)

ifeq ($(HAVE_ORB_EXCEPTS), no)
CXXFLAGS := $(CXXFLAGS) -DMICO_CONF_NO_EXCEPTIONS
else
ifeq ($(HAVE_EXCEPTIONS), yes)
NOPICFLAGS := $(NOPICFLAGS) $(EHOPTFLAGS)
endif
ifeq ($(HAVE_SHARED_EXCEPTS), yes)
PICFLAGS := $(PICFLAGS) $(EHOPTFLAGS)
endif
endif

EH_SRCS = except2.cc
UNI_SRCS = uni_base64.cc uni_unicode.cc uni_fromuni.cc uni_touni.cc

ifeq ($(HAVE_MEMCHECK), yes)
SRCS = memcheck.cc
ifeq ($(USE_MEMTRACE), yes)
SRCS := $(SRCS) memtrace.cc
endif
endif

ifeq ($(HAVE_FINAL), yes)
SRCS := orb_all.cc $(SRCS) $(EH_SRCS) $(UNI_SRCS)
STATIC_OBJS = $(SRCS:.cc=.o)
ALL_STATIC_OBJS = $(STATIC_OBJS) ../ir/ir_all.o ../imr/imr_all.o
else
SRCS := $(SRCS) dii.cc typecode.cc any.cc codec.cc buffer.cc context.cc \
  except.cc dispatch.cc string.cc object.cc address.cc ior.cc \
  orb.cc boa.cc dsi.cc transport.cc iop.cc util.cc basic_seq.cc \
  ssl.cc fixed.cc intercept.cc codeset.cc queue.cc static.cc \
  current.cc policy_impl.cc service_info.cc ioptypes.cc ssliop.cc \
  value.cc valuetype.cc valuetype_impl.cc dynany_impl.cc os-unix.cc \
  policy2.cc tckind.cc orb_excepts.cc policy.cc poa.cc poa_base.cc \
  poa_impl.cc dynany.cc $(UNI_SRCS) $(EH_SRCS)
STATIC_OBJS = $(SRCS:.cc=.o)
ALL_STATIC_OBJS = $(STATIC_OBJS) ../ir/ir_impl.o ../ir/ir.o ../ir/ir_skel.o \
  ../ir/ir_base.o ../imr/imr_impl.o ../imr/imr.o
endif

SHARED_OBJS = $(STATIC_OBJS:.o=.pic.o)
ALL_SHARED_OBJS = $(ALL_STATIC_OBJS:.o=.pic.o)
EH_STATIC_OBJS=$(EH_SRCS:.cc=.o)
EH_SHARED_OBJS=$(EH_SRCS:.cc=.pic.o)

REG_FILES = ../admin/code_set_registry.txt ../admin/mico_code_set_registry.txt

all: lib prg

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend $(STATIC_OBJS) $(SHARED_OBJS)
prg: .depend libmico$(VERSION).$(SOEXT) libmico$(VERSION).a
else
lib: .depend $(SHARED_OBJS)
prg: .depend libmico$(VERSION).$(SOEXT)
endif
else
lib: .depend $(STATIC_OBJS)
prg: .depend libmico$(VERSION).a
endif

$(EH_STATIC_OBJS):
	$(CXX) $(EH_CXXFLAGS) $(CPPFLAGS) $(NOPICFLAGS) $(EHOPTFLAGS) -c $(@:.o=.cc) -o $@

$(EH_SHARED_OBJS):
	$(CXX) $(EH_CXXFLAGS) $(CPPFLAGS) $(PICFLAGS) $(EHOPTFLAGS) -c $(@:.pic.o=.cc) -o $@


codeset.cc: ../include/mico/code_set_registry.h

../include/mico/code_set_registry.h: $(REG_FILES)
	../admin/mkcsreg $(REG_FILES) > $@

# shared

ifeq ($(HAVE_SHARED), yes)
libmico$(VERSION).$(SOEXT): $(ALL_SHARED_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(ALL_SHARED_OBJS) $(LDFLAGS) $(CONFLIBS)
endif
	$(RM) $@
	$(LDSO) -o libmico$(VERSION) $(ALL_SHARED_OBJS)
	$(IDIRCMD) ../libs
	cd ../libs; $(RM) $@; $(LN) ../orb/$@ .
endif

# static

libmico$(VERSION).a: $(ALL_STATIC_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(ALL_STATIC_OBJS) $(LDFLAGS) $(CONFLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(ALL_STATIC_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; $(RM) $@; $(LN) ../orb/$@ .


generate:
	../admin/mkcsreg $(REG_FILES) > ../include/mico/code_set_registry.h
	$(IDL) --name current --windows-dll --pseudo --mico-core \
		../include/mico/current.idl
	mv current.h ../include/mico/current.h
	$(IDL) --name policy --windows-dll --relative-paths -I../include \
		--pseudo --mico-core ../include/mico/policy.idl
	patch < policy.cc.diffs
	$(RM) policy.*.orig
	mv policy.h ../include/mico/policy.h
	$(IDL) --name policy2 --any --windows-dll --relative-paths \
		-I../include --pseudo --mico-core ../include/mico/policy2.idl
	mv policy2.h ../include/mico/policy2.h
	$(IDL) --any --name poa --windows-dll --relative-paths \
		-I../include --pseudo --mico-core ../include/mico/poa.idl
	mv poa.h ../include/mico/poa.h
	$(IDL) --name service_info --windows-dll --pseudo --mico-core \
		../include/mico/service_info.idl
	mv service_info.h ../include/mico/service_info.h
	$(IDL) --name orb_excepts --windows-dll --pseudo --mico-core \
		../include/mico/orb_excepts.idl
	mv orb_excepts.h ../include/mico/orb_excepts.h
	$(IDL) --name dynany --windows-dll --pseudo --mico-core \
		-I../include ../include/mico/dynany.idl
	mv dynany.h ../include/mico/dynany.h
	$(IDL) --name ioptypes --windows-dll --pseudo --mico-core \
		../include/mico/ioptypes.idl
	mv ioptypes.h ../include/mico/ioptypes.h
	$(IDL) --name ssliop --windows-dll --pseudo ../include/mico/ssliop.idl
	patch < ssliop.cc.diffs
	$(RM) ssliop.*.orig
	mv ssliop.h ../include/mico/ssliop.h
	$(IDL) --name valuetype --windows-dll --pseudo --any \
		--mico-core -I../include ../include/mico/valuetype.idl
	mv valuetype.h ../include/mico/valuetype.h
	$(IDL) --name tckind --windows-dll --pseudo \
		--mico-core ../include/mico/tckind.idl
	mv tckind.h ../include/mico/tckind.h

diffs:
	mkdir orig
	cd orig; $(IDL) --name policy --windows-dll --relative-paths \
	  -I../../include --pseudo ../../include/mico/policy.idl
	$(RM) policy.cc.diffs
	diff -c orig/policy.cc policy.cc > policy.cc.diffs || true
	cd ../include/mico; diff -c ../../orb/orig/policy.h policy.h \
	  >> ../../orb/policy.cc.diffs || true
	$(RM) -r orig
	mkdir orig
	cd orig; $(IDL) --name ssliop --pseudo --windows-dll \
	  ../../include/mico/ssliop.idl
	$(RM) ssliop.cc.diffs
	diff -c orig/ssliop.cc ssliop.cc \
	      > ssliop.cc.diffs || true
	cd ../include/mico; diff -c ../../orb/orig/ssliop.h \
	  ssliop.h >> ../../orb/ssliop.cc.diffs || true
	$(RM) -r orig

clean:
	$(RM) *.rpo *.a *.o *~ *.$(SOEXT) .depend

install:
	$(IDIRCMD) $(INSTDIR)/lib
ifeq ($(HAVE_STATIC), yes)
	$(ILIBCMD) libmico$(VERSION).a $(INSTDIR)/lib
endif
ifeq ($(HAVE_SHARED), yes)
	$(ILIBCMD) libmico$(VERSION).$(SOEXT) $(INSTDIR)/lib
endif

install-cd: install

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend

