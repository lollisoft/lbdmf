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

all: subs

include ../MakeVars

DIRS=Calc-1 Calc-2 Calc-3 Calc-4 Hello-1 Hello-2 Hello-3 Hello-4

subs:
	for i in $(DIRS); do $(MAKE) -C $$i || exit 1; done

clean:
	for i in $(DIRS); do $(MAKE) -C $$i clean || exit 1; done

install:
	$(IDIRCMD) $(INSTDIR)/doc/mico/examples/redlich
	$(ISRCCMD) Makefile $(INSTDIR)/doc/mico/examples/redlich
	$(ISRCCMD) README $(INSTDIR)/doc/mico/examples/redlich
	for i in $(DIRS); do $(MAKE) -C $$i install || exit 1; done
