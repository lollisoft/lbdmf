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

# delete rules for .ll and .yy defined in ../MakeVars
%.cc: %.ll
%.cc: %.yy


LDFLAGS  := -L. -L../orb $(LDFLAGS)
LDLIBS   := -lmico$(VERSION) $(CONFLIBS)
CXXFLAGS := -DCPP=\"mico-cpp\" -I. -I../include $(CXXFLAGS) $(EHFLAGS)
CFLAGS   := -DHAVE_CONFIG_H -I. -I../cpp -I../include $(CFLAGS)

# generated files

GENERATED=yacc.output

OBJS=params.o parser.o yacc.o scanner.o parsenode.o idlparser.o \
     codegen.o codegen-c++-util.o codegen-c++-common.o \
     codegen-c++-stub.o codegen-c++-skel.o codegen-c++-impl.o \
     codegen-c++.o codegen-idl.o codegen-midl.o dep.o error.o const.o \
     db.o prepro.o ../cpp/alloca.o

ifeq ($(HAVE_SHARED), yes)
ifeq ($(HAVE_SHARED_EXCEPTS), no)
ifeq ($(HAVE_EXCEPTIONS), yes)
IR_OBJS=../ir/ir_impl.o
endif
endif
endif

# normal rules

all: lib prg

prg: .depend libidl.a idl

lib: .depend $(OBJS)

libidl.a: $(OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(OBJS)
	$(RANLIB) $@

idl: libidl.a main.o ../orb/$(LIBMICO) $(IR_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o $(IR_OBJS) -lidl $(LDLIBS) -o idl
	$(POSTLD) $@

main.o:

# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo idl idl idl.install
	-$(RM) .depend TAGS core nohup.out $(GENERATED)


install: all
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) idl $(INSTDIR)/bin

install-cd: install


generate:
	$(BISON) -d -t -v -o yacc.c yacc.yy
	mv yacc.c yacc.cc
	$(FLEX) -B -8 -oscanner.cc scanner.ll

# dependencies

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend

