// -*- c++ -*-
/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#ifndef __mico_impl_h__
#define __mico_impl_h__

#include <mico/util.h>

#ifdef _WINDOWS
#include <sys/timeb.h>
#include <winsock2.h>
#else
#include <sys/time.h>
#include <sys/socket.h>
#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

MICO_NAMESPACE_DECL MICO {
#ifdef _WINDOWS
	using namespace MICO;
#endif
#include <mico/shlib.h>
#include <mico/process.h>
#include <mico/address_impl.h>
#include <mico/ior_impl.h>
#include <mico/transport_impl.h>
#include <mico/shlib_impl.h>
#include <mico/process_impl.h>
#include <mico/codec_impl.h>
#include <mico/codeset_impl.h>
#include <mico/orb_impl.h>
#include <mico/boa_impl.h>
#include <mico/iop.h>
#include <mico/policy_impl.h>
};

#endif // __mico_impl_h__
