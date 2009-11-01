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

all: .depend client1 server1 client2 server2

DIR_PREFIX=../
include ../../MakeVars

INSTALL_DIR     = boa/activate
INSTALL_SRCS    = Makefile client.cc server.cc hello.idl
INSTALL_SCRIPTS = hello-shared hello-unshared hello-permethod

client1: hello.h hello.o client1.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) hello.o client1.o $(LDLIBS) -o $@

server1: hello.h hello.o server1.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) hello.o server1.o $(LDLIBS) -o $@

client2: hello.h hello.o client2.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) hello.o client2.o $(LDLIBS) -o $@

server2: hello.h hello.o server2.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) hello.o server2.o $(LDLIBS) -o $@

hello.h hello.cc : hello.idl $(IDLGEN)
	$(IDL) hello.idl

client1.o: client.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

client2.o: client.cc
	$(CXX) -DPERMETHOD $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

server1.o: server.cc
	$(CXX) -DSHARED $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

server2.o: server.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f hello.cc hello.h *.o core client? server? *~ .depend
