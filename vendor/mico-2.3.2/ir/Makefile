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

LDLIBS    = -lidl -lmico$(VERSION) $(CONFLIBS)
LDFLAGS  := -L../idl -L../orb $(LDFLAGS)
CXXFLAGS := -DCPP=\"mico-cpp\" -I. -I../idl -I../include $(CXXFLAGS)

ifeq ($(HAVE_EXCEPTIONS), yes)
NOPICFLAGS := $(NOPICFLAGS) $(EHOPTFLAGS)
endif
ifeq ($(HAVE_SHARED_EXCEPTS), yes)
PICFLAGS := $(PICFLAGS) $(EHOPTFLAGS)
endif

# generated files

ifeq ($(HAVE_FINAL), yes)
STATIC_OBJS=ir_all.o ir_impl.o
else
STATIC_OBJS=ir.o ir_skel.o ir_base.o ir_impl.o
endif
SHARED_OBJS=$(STATIC_OBJS:.o=.pic.o)

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_EXCEPTIONS), yes)
ifeq ($(HAVE_SHARED_EXCEPTS), no)
IR_OBJS=ir_impl.o
endif
endif
endif

# normal rules

all: lib prg

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend $(STATIC_OBJS) $(SHARED_OBJS) $(IR_OBJS)
else
lib: .depend $(SHARED_OBJS) $(IR_OBJS)
endif
else
lib: .depend $(STATIC_OBJS) $(IR_OBJS)
endif

prg: .depend ird

ird: main.o ../idl/libidl.a ../orb/$(LIBMICO) ir_impl.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o $(IR_OBJS) $(LDLIBS) -o ird
	$(POSTLD) $@

generate:
	-mv ir.cc ir.cc.backup
	-mv ir_skel.cc ir_skel.cc.backup
	-mv ir_base.cc ir_base.cc.backup
	-cd ../include/mico; mv ir.h ir.h.backup
	-cd ../include/mico; mv ir_base.h ir_base.h.backup
	$(IDL) --c++-skel --windows-dll --any --relative-paths --mico-core \
		-I../include --name ir ../include/mico/ir.idl
	$(IDL) --any --windows-dll --relative-paths -I../include --mico-core \
                --name ir_base ../include/mico/ir_base.idl
	sleep 1
	patch < ir.cc.diffs
	$(RM) ir.*.orig ir_base.*.orig
	mv ir.h ir_base.h ../include/mico

ungenerate:
	-mv ir.cc.backup ir.cc
	-mv ir_skel.cc.backup ir_skel.cc
	-mv ir_base.cc.backup ir_base.cc
	-mv ../include/mico/ir.h.backup ../include/mico/ir.h
	-mv ../include/mico/ir_base.h.backup ../include/mico/ir_base.h

diffs:
	mkdir orig; cd orig; $(IDL) --c++-skel --windows-dll --mico-core \
		--any --relative-paths -I../../include --name ir \
		../../include/mico/ir.idl
	cd orig; $(IDL) --any --windows-dll --relative-paths --mico-core \
		-I../../include --name ir_base ../../include/mico/ir_base.idl
	$(RM) ir.cc.diffs
	cd ../include/mico; diff -c ../../ir/orig/ir.h ir.h \
	  > ../../ir/ir.cc.diffs || true
	cd ../include/mico; diff -c ../../ir/orig/ir_base.h ir_base.h \
	  >> ../../ir/ir.cc.diffs || true
	diff -c orig/ir.cc ir.cc >> ir.cc.diffs || true
	diff -c orig/ir_skel.cc ir_skel.cc >> ir.cc.diffs || true
	diff -c orig/ir_base.cc ir_base.cc >> ir.cc.diffs || true
	$(RM) -rf orig

# cleaning

clean:
	-$(RM) -f libs
	-$(RM) *.o *.o0 *.a *~ *.rpo *.objid ird
	-$(RM) .depend TAGS core nohup.out

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) ird $(INSTDIR)/bin

install-cd: install

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend




