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
LDFLAGS  := -L.. -L../../orb $(LDFLAGS)
CXXFLAGS := -I. -I../../include $(CXXFLAGS) $(EHFLAGS)

# generated files

CLNT_OBJS = NamingClient.o nsadmin.o
SRV_OBJS  = Naming_impl.o nsd.o CosNaming_skel.o

# normal rules

all: lib prg

ifeq ($(HAVE_SHARED_EXCEPTS), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend CosNaming.o CosNaming.pic.o
else
lib: .depend CosNaming.pic.o
endif
else
lib: .depend CosNaming.o
endif

prg: .depend nsd nsadmin


nsd: $(SRV_OBJS) ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRV_OBJS) $(LDLIBS) -o nsd
	$(POSTLD) $@

nsadmin: $(CLNT_OBJS) ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CLNT_OBJS) $(LDLIBS) -o nsadmin
	$(POSTLD) $@


CosNaming.h CosNaming.cc CosNaming_skel.cc: ../../include/mico/CosNaming.idl $(IDL)
	$(IDL) --c++-skel --poa --no-boa --name CosNaming \
		../../include/mico/CosNaming.idl
	cp CosNaming.h ../../include/mico

# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo *.objid nsd nsadmin
	-$(RM) .depend TAGS core nohup.out
	-$(RM) CosNaming.h CosNaming.cc ../../include/mico/CosNaming.h \
		CosNaming_skel.cc

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) nsd $(INSTDIR)/bin
	$(IBINCMD) nsadmin $(INSTDIR)/bin

ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend
