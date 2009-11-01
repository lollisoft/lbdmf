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


ifeq ($(USE_NAMING), yes)
SUBDIRS := $(SUBDIRS) naming
endif

ifeq ($(USE_EVENTS), yes)
SUBDIRS := $(SUBDIRS) events
endif

ifeq ($(USE_STREAMS), yes)
SUBDIRS := $(SUBDIRS) streams
endif

ifeq ($(USE_RELSHIP), yes)
SUBDIRS := $(SUBDIRS) relship
endif

ifeq ($(USE_PROPERTY), yes)
SUBDIRS := $(SUBDIRS) property
endif

ifeq ($(USE_TRADER), yes)
SUBDIRS := $(SUBDIRS) trader
endif

ifeq ($(USE_TIME), yes)
SUBDIRS := $(SUBDIRS) time
endif

CLEANDIRS = naming events streams relship property trader time
LDFLAGS := -L../orb -lmico$(VERSION) $(LDFLAGS)

#STATIC_OBJS = \

ifeq ($(USE_NAMING), yes)
  STATIC_OBJS += naming/CosNaming.o
endif

ifeq ($(USE_EVENTS), yes)
  STATIC_OBJS += events/CosEventComm.o events/CosEventChannelAdmin.o
endif

ifeq ($(USE_STREAMS), yes)
  STATIC_OBJS += streams/stream.o streams/stream_impl.o
endif

ifeq ($(USE_RELSHIP), yes)
  STATIC_OBJS += relship/CosObjectIdentity.o relship/CosRelationships.o
  STATIC_OBJS += relship/CosGraphs.o
  STATIC_OBJS += relship/CosContainment.o relship/CosReference.o
  STATIC_OBJS += relship/CosGraphsExtension.o
  STATIC_OBJS += relship/IdentifiableObject_impl.o relship/Role_impl.o
  STATIC_OBJS += relship/Relationship_impl.o relship/RelationshipIterator_impl.o 
  STATIC_OBJS += relship/TraversalFactory_impl.o relship/Traversal_impl.o
  STATIC_OBJS += relship/TraversalCriteria_impl.o relship/Node_impl.o
  STATIC_OBJS += relship/GraphsRole_impl.o relship/EdgeIterator_impl.o
  STATIC_OBJS += relship/CosContainment_impl.o relship/CosReference_impl.o
  STATIC_OBJS += relship/GenericCriteriaFactory_impl.o
  STATIC_OBJS += relship/RandomGenerator.o relship/random.o
  STATIC_OBJS += relship/RandomGenerator_impl.o
  STATIC_OBJS += relship/InterfaceDefsHelper.o relship/NamedRoleTypesHelper.o
endif

ifeq ($(USE_PROPERTY), yes)
  STATIC_OBJS +=   property/PropertyService_impl.o property/PropertyService.o
endif

ifeq ($(USE_TRADER), yes)
  STATIC_OBJS += trader/CosTrading.o trader/CosTradingRepos.o
endif

ifeq ($(USE_TIME), yes)
  STATIC_OBJS += time/CosTime.o
endif

SHARED_OBJS = $(STATIC_OBJS:.o=.pic.o)


all: lib prg


lib:

ifneq ($(strip $(SUBDIRS)),)
ifeq ($(HAVE_SHARED_EXCEPTS), yes)
ifeq ($(HAVE_STATIC), yes)
prg: sublib libmicocoss$(VERSION).a libmicocoss$(VERSION).$(SOEXT) subprg
else
prg: sublib libmicocoss$(VERSION).$(SOEXT) subprg
endif
else
prg: sublib libmicocoss$(VERSION).a subprg
endif
else
prg:
endif

sublib:
	for i in $(SUBDIRS); do $(MAKE) -C $$i lib || exit 1; done

subprg:
	for i in $(SUBDIRS); do $(MAKE) -C $$i prg || exit 1; done


# shared 

ifeq ($(HAVE_SHARED_EXCEPTS), yes)
libmicocoss$(VERSION).$(SOEXT): $(SHARED_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(SHARED_OBJS) $(LDFLAGS) $(CONFLIBS)
endif
	$(RM) $@
	$(LDSO) -o libmicocoss$(VERSION) $(SHARED_OBJS) \
		-L../libs -lmico$(VERSION)
	$(IDIRCMD) ../libs
	cd ../libs; $(RM) $@; $(LN) ../coss/$@ .
endif

# static

libmicocoss$(VERSION).a: $(STATIC_OBJS)
ifeq ($(HAVE_REPO), yes)
	-$(CXX) $(CXXFLAGS) $(STATIC_OBJS) $(LDFLAGS) $(CONFLIBS)
endif
	$(AR) $(ARFLAGS) $@ $(STATIC_OBJS)
	$(RANLIB) $@
	$(IDIRCMD) ../libs
	cd ../libs; $(RM) $@; $(LN) ../coss/$@ .


clean:
	for i in $(CLEANDIRS); do $(MAKE) -C $$i clean || exit 1; done
	$(RM) *.a *.$(SOEXT)

install:
	$(IDIRCMD) $(INSTDIR)/lib
ifneq ($(strip $(SUBDIRS)),)
ifeq ($(HAVE_SHARED_EXCEPTS), yes)
	$(ILIBCMD) libmicocoss$(VERSION).$(SOEXT) $(INSTDIR)/lib
ifeq ($(HAVE_STATIC), yes)
	$(ILIBCMD) libmicocoss$(VERSION).a $(INSTDIR)/lib
endif
else
	$(ILIBCMD) libmicocoss$(VERSION).a $(INSTDIR)/lib
endif
	for i in $(SUBDIRS); do $(MAKE) -C $$i install || exit 1; done	
endif

install-cd: install

