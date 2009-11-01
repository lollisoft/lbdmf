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

LDFLAGS  := -L../orb $(LDFLAGS)
LDLIBS   := -lmico$(VERSION) $(CONFLIBS)
CXXFLAGS := -I. -I../include $(CXXFLAGS)

# generated files

OBJS=mediator.o poamediator.o main.o

# normal rules

all: prg

prg: .depend micod

micod: $(OBJS) ../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	$(POSTLD) $@

# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo micod
	-$(RM) .depend TAGS core nohup.out


install: all
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) micod $(INSTDIR)/bin

install-cd: install

# dependencies

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend:
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend

