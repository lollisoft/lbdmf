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

include ../../MakeVars

LDLIBS    = -lmicocoss$(VERSION) -lmico$(VERSION) $(CONFLIBS)
LDFLAGS  := -L.. -L.. -L../../orb $(LDFLAGS)
CXXFLAGS := -I. -I../../include $(CXXFLAGS) $(EHFLAGS)
IDLFLAGS := -I../../include --poa --no-boa --relative-paths

# generated files

SRV_OBJS=TimeService_help.o TimeService_impl.o TimeService_tio.o \
  TimeService_uto.o main.o

# normal rules

all: lib prg

ifeq ($(HAVE_SHARED_EXCEPTS), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend CosTime.o CosTime.pic.o
else
lib: .depend CosTime.pic.o
endif
else
lib: .depend CosTime.o
endif

prg: .depend timed


timed: $(SRV_OBJS) ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRV_OBJS) $(LDLIBS) -o timed
	$(POSTLD) $@

CosTime.h CosTime.cc: ../../include/mico/CosTime.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosTime \
		../../include/mico/CosTime.idl
	cp CosTime.h ../../include/mico

# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo *.objid timed
	-$(RM) .depend TAGS core nohup.out
	-$(RM) CosTime.h CosTime.cc
	-$(RM) ../../include/mico/CosTime.h

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) timed $(INSTDIR)/bin

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend
