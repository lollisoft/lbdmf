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
IDLFLAGS := -I../../include --poa --no-boa --relative-paths

# generated files

OMG_SRCS = CosObjectIdentity.cc CosRelationships.cc CosGraphs.cc \
  CosContainment.cc CosReference.cc CosGraphsExtension.cc

IMPL_SRCS = IdentifiableObject_impl.cc Role_impl.cc Relationship_impl.cc \
  RelationshipIterator_impl.cc TraversalFactory_impl.cc Traversal_impl.cc \
  TraversalCriteria_impl.cc Node_impl.cc GraphsRole_impl.cc EdgeIterator_impl.cc \
  CosContainment_impl.cc CosReference_impl.cc \
  GenericCriteriaFactory_impl.cc

EXT_SRCS = CosGraphsExtension.cc RandomGenerator.cc random.cc

EXT_IMPL_SRCS = GenericCriteriaFactory_impl.cc RandomGenerator_impl.cc

UTIL_SRCS = InterfaceDefsHelper.cc NamedRoleTypesHelper.cc

#DAEMONS_SRCS = traversald.cc noded.cc containmentd.cc referenced.cc randomd.cc \
#  proxyd.cc

SRCS = $(OMG_SRCS) $(EXT_SRCS) $(IMPL_SRCS) $(EXT_IMPL_SRCS) $(UTIL_SRCS)

STATIC_OBJS = $(SRCS:.cc=.o)
SHARED_OBJS = $(SRCS:.cc=.pic.o)

# normal rules

all: lib prg

ifeq ($(HAVE_SHARED_EXCEPTS), yes)
ifeq ($(HAVE_STATIC), yes)
lib: .depend $(STATIC_OBJS) $(SHARED_OBJS)
else
lib: .depend $(SHARED_OBJS)
endif
else
lib: .depend $(STATIC_OBJS)
endif

prg: .depend traversald noded containmentd referenced randomd proxyd

traversald: traversald.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) traversald.o $(LDLIBS) -o traversald
	$(POSTLD) $@

noded: noded.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) noded.o $(LDLIBS) -o noded
	$(POSTLD) $@

containmentd: containmentd.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) containmentd.o $(LDLIBS) -o containmentd
	$(POSTLD) $@

referenced: referenced.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) referenced.o $(LDLIBS) -o referenced
	$(POSTLD) $@

randomd: randomd.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) randomd.o $(LDLIBS) -o randomd
	$(POSTLD) $@

proxyd: proxyd.o ../../orb/$(LIBMICO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) proxyd.o $(LDLIBS) -o proxyd
	$(POSTLD) $@

CosObjectIdentity.h CosObjectIdentity.cc: \
		../../include/mico/CosObjectIdentity.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosObjectIdentity \
		../../include/mico/CosObjectIdentity.idl
	cp CosObjectIdentity.h ../../include/mico

CosRelationships.h CosRelationships.cc: \
		../../include/mico/CosRelationships.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosRelationships \
		../../include/mico/CosRelationships.idl
	cp CosRelationships.h ../../include/mico

CosGraphs.h CosGraphs.cc: \
		../../include/mico/CosGraphs.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosGraphs \
		../../include/mico/CosGraphs.idl
	cp CosGraphs.h ../../include/mico

CosContainment.h CosContainment.cc: \
		../../include/mico/CosContainment.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosContainment \
		../../include/mico/CosContainment.idl
	cp CosContainment.h ../../include/mico

CosReference.h CosReference.cc: \
		../../include/mico/CosReference.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosReference \
		../../include/mico/CosReference.idl
	cp CosReference.h ../../include/mico

CosGraphsExtension.h CosGraphsExtension.cc: \
		../../include/mico/CosGraphsExtension.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name CosGraphsExtension \
		../../include/mico/CosGraphsExtension.idl
	cp CosGraphsExtension.h ../../include/mico

RandomGenerator.h RandomGenerator.cc: \
		../../include/mico/RandomGenerator.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name RandomGenerator \
		../../include/mico/RandomGenerator.idl
	cp RandomGenerator.h ../../include/mico

random.h random.cc: \
		../../include/mico/random.idl $(IDL)
	$(IDL) $(IDLFLAGS) --name random \
		../../include/mico/random.idl
	cp random.h ../../include/mico


# cleaning

clean:
	-$(RM) *.o *.a *~ *.rpo *.objid traversald noded containmentd referenced randomd proxyd
	-$(RM) .depend TAGS core nohup.out
	-$(RM) CosObjectIdentity.h CosObjectIdentity.cc
	-$(RM) ../../include/mico/CosObjectIdentity.h
	-$(RM) CosRelationships.h CosRelationships.cc
	-$(RM) ../../include/mico/CosRelationships.h
	-$(RM) CosGraphs.h CosGraphs.cc
	-$(RM) ../../include/mico/CosGraphs.h
	-$(RM) CosContainment.h CosContainment.cc
	-$(RM) ../../include/mico/CosContainment.h
	-$(RM) CosReference.h CosReference.cc
	-$(RM) ../../include/mico/CosReference.h
	-$(RM) CosGraphsExtension.h CosGraphsExtension.cc
	-$(RM) ../../include/mico/CosGraphsExtension.h
	-$(RM) RandomGenerator.h RandomGenerator.cc
	-$(RM) ../../include/mico/RandomGenerator.h
	-$(RM) random.h random.cc
	-$(RM) ../../include/mico/random.h

install:
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) traversald $(INSTDIR)/bin
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) noded $(INSTDIR)/bin
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) containmentd $(INSTDIR)/bin
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) referenced $(INSTDIR)/bin
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) randomd $(INSTDIR)/bin
	$(IDIRCMD) $(INSTDIR)/bin
	$(IBINCMD) proxyd $(INSTDIR)/bin


ifeq (.depend, $(wildcard .depend))
include .depend
endif

.depend :
	echo '# Module dependencies' > .depend
	$(MKDEPEND) $(CXXFLAGS) *.cc >> .depend

