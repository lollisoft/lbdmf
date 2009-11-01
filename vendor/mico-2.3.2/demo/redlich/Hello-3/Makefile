#
# MICO --- a CORBA 2.0 implementation
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

all: .depend client server

DIR_PREFIX=../
include ../../MakeVars

INSTALL_DIR     = redlich/Hello-3
INSTALL_SRCS    = Makefile client.cc server.cc tty.idl ttyplus.idl
INSTALL_SCRIPTS =

server: tty.h tty.o ttyplus.h ttyplus.o server.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) tty.o ttyplus.o server.o $(LDLIBS) -o server

client: tty.h tty.o ttyplus.h ttyplus.o client.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) tty.o ttyplus.o client.o $(LDLIBS) -o client 
	

tty.h tty.cc : tty.idl $(IDLGEN)
	$(IDL) tty.idl

ttyplus.h ttyplus.cc : ttyplus.idl $(IDLGEN)
	$(IDL) ttyplus.idl

clean:
	rm -f tty.cc tty.h ttyplus.cc ttyplus.h *.o core client server *~ .depend
