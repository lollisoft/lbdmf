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

CXXFLAGS := -I. -I../../include $(CXXFLAGS) $(EHFLAGS)
LDFLAGS  := -L../../orb $(LDFLAGS)
LDLIBS    = -lmico$(VERSION) $(CONFLIBS)

# generated files

GEN  =
SRCS = iordump.cc
OBJS = ${SRCS:.cc=.o}

# normal rules

all: .depend iordump

iordump: $(OBJS) ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -L../../idl $(OBJS) -lidl $(LDLIBS) -o $@
	$(POSTLD) $@

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) iordump $(INSTDIR)/bin

# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo *.class iordump
	-$(RM) .depend TAGS core nohup.out $(GENERATED)


# dependencies

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend
