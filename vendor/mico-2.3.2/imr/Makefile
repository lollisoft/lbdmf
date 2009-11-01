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

LDLIBS    = -lmico$(VERSION) $(CONFLIBS)
LDFLAGS  := -L../orb $(LDFLAGS)
CXXFLAGS := -I. -I../include $(CXXFLAGS)

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

# generated files

ifeq ($(HAVE_FINAL), yes)
STATIC_LIBOBJS=imr_all.o
else
STATIC_LIBOBJS=imr.o imr_impl.o
endif
SHARED_LIBOBJS=$(STATIC_LIBOBJS:.o=.pic.o)

IMROBJS=imr_client.o

# normal rules

all: lib prg

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend $(STATIC_LIBOBJS) $(SHARED_LIBOBJS)
else
lib: .depend $(SHARED_LIBOBJS)
endif
else
lib: .depend $(STATIC_LIBOBJS)
endif

prg: .depend imr


imr: $(IMROBJS) ../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(IMROBJS) $(LDLIBS) -o $@
	$(POSTLD) $@

generate:
	mv imr.cc imr.cc.backup
	cd ../include/mico; mv imr.h imr.h.backup
	$(IDL) --any --name imr --windows-dll --mico-core \
		../include/mico/imr.idl
	sleep 1
	patch < imr.cc.diffs
	$(RM) imr.*.orig
	mv imr.h ../include/mico

ungenerate:
	mv imr.cc.backup imr.cc
	mv ../include/mico/imr.h.backup ../include/mico/imr.h

diffs:
	mkdir orig; cd orig; $(IDL) --any --name imr \
	  --windows-dll --mico-core ../../include/mico/imr.idl
	$(RM) imr.cc.diffs
	cd ../include/mico; diff -c ../../imr/orig/imr.h imr.h \
	  > ../../imr/imr.cc.diffs || true
	diff -c orig/imr.cc imr.cc >> imr.cc.diffs || true
	$(RM) -rf orig

# cleaning

clean:
	-$(RM) *.o *.o0 *.a *~ *.rpo imr
	-$(RM) .depend TAGS core nohup.out

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) imr $(INSTDIR)/bin

install-cd: install

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend
