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

DIRS = boa bench dynany interop redlich siegel henning interceptor \
  codesets poa random obv services dispatcher mcast

INST_DIRS = $(DIRS) shlib ssl

ifeq ($(HAVE_DYNAMIC), yes)
DIRS := $(DIRS) shlib
endif

ifeq ($(HAVE_SSL), yes)
DIRS := $(DIRS) ssl
endif

all: prg

prg:
	for i in $(DIRS); do $(MAKE) -C $$i || exit 1; done

clean:
	for i in $(DIRS); do $(MAKE) -C $$i clean || exit 1; done

install:
	$(IDIRCMD) $(INSTDIR)/doc/mico/examples
	sed -e s/@MICO_VERSION@/$(VERSION)/g \
		< MakeVars.install > MakeVars.install.ver
	$(ISRCCMD) MakeVars.install.ver $(INSTDIR)/doc/mico/examples/MakeVars
	rm -f MakeVars.install.ver
	$(ISRCCMD) README $(INSTDIR)/doc/mico/examples
	for i in $(INST_DIRS); do $(MAKE) -C $$i install || exit 1; done

install-cd: install

