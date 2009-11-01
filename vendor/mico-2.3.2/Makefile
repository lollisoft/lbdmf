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

include MakeVars

ADMDIRS = admin include
LIBDIRS = orb ir imr idl auxdir coss
PRGDIRS = orb idl cpp ir imr daemon auxdir coss tools
EXTRADIRS = test demo
ALLDIRS = admin orb ir imr daemon idl cpp auxdir coss test tools demo
INSTALLDIRS = admin orb ir imr daemon idl cpp auxdir coss tools include man demo

all: system

world: system extra

system:
	for i in $(ADMDIRS); do $(MAKE) -C $$i adm || exit 1; done
	for i in $(LIBDIRS); do $(MAKE) -C $$i lib || exit 1; done
	for i in $(PRGDIRS); do $(MAKE) -C $$i prg || exit 1; done

extra:
	for i in $(EXTRADIRS); do $(MAKE) -C $$i prg || exit 1; done

clean:
	find . -name '*~' | xargs rm -f foobarbazbummbang
	for i in $(ALLDIRS); do $(MAKE) -C $$i clean || exit 1; done
	if test -f doc/Makefile; then $(MAKE) -C doc clean || exit 1; fi
	rm -rf libs
	rm -f FAQ core

distclean: clean
	rm -f demo/MakeVars.install admin/mico-c++ admin/mico-shc++
	rm -f admin/mico-ld admin/mico-shld admin/mico-ar admin/mico-setup.sh
	rm -f admin/mico-setup.csh demo/siegel/diffs
	rm -f MakeVars
	rm -f config.*
	rm -f include/mico/config.h

install:
	for i in $(INSTALLDIRS); do $(MAKE) -C $$i install || exit 1; done
	if test -f doc/doc.ps; then \
		$(IDIRCMD) $(SHARED_INSTDIR)/doc/mico; \
		$(IMANCMD) doc/doc.ps $(SHARED_INSTDIR)/doc/mico/manual.ps; \
	fi
	-ldconfig

install-cd:
	for i in $(INSTALLDIRS); do $(MAKE) -C $$i install-cd || exit 1; done
	if test -f doc/doc.ps; then \
		$(IDIRCMD) $(SHARED_INSTDIR)/doc/mico; \
		$(IMANCMD) doc/doc.ps $(SHARED_INSTDIR)/doc/mico/manual.ps; \
	fi

dist:
	admin/mksrcdist

release:
	admin/mkrelease

manifest: distclean
	admin/mkmanifest
