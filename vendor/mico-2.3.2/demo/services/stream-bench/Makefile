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

all: .depend stream_client stream_server req_client req_server

DIR_PREFIX=../
include ../../MakeVars

CXXFLAGS  := $(COS_CXXFLAGS) $(CXXFLAGS)
LDLIBS    := $(COS_LDLIBS) $(LDLIBS)
LDFLAGS   := $(COS_LDFLAGS) $(LDFLAGS)
DEPS      := $(COS_DEPS) $(DEPS)

INSTALL_DIR     = services/stream-bench
INSTALL_SRCS    = Makefile req.idl req_client.cc req_server.cc \
  stream_client.cc stream_server.cc
INSTALL_SCRIPTS = bench

req_client: req.o req_client.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) req.o req_client.o $(LDLIBS) -o $@

req_server: req.o req_server.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) req.o req_server.o $(LDLIBS) -o $@

stream_client: stream_client.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) stream_client.o $(LDLIBS) -o $@

stream_server: stream_server.o $(DEPS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) stream_server.o $(LDLIBS) -o $@

req.h req.cc : req.idl $(IDLGEN)
	$(IDL) req.idl

clean:
	rm -f req.cc req.h *.o core *client *server *~ .depend
