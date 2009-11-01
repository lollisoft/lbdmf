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

#ifndef __corba_h__
#define __corba_h__


/***************************** C headers ****************************/

#include <mico/assert.h>
#include <stddef.h> // for wchar_t
#include <sys/types.h>

/***************************** config *******************************/

#ifdef _WINDOWS
#include <mico/config-win32.h>
#else
#include <mico/config.h>
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#if (defined(PIC) && defined(HAVE_SHARED_EXCEPTS)) || \
    (!defined(PIC) && defined(HAVE_EXCEPTS))
#define HAVE_EXCEPTIONS 1
#endif

#ifdef MICO_CONF_NO_EXCEPTIONS
#undef HAVE_EXCEPTS
#undef HAVE_SHARED_EXCEPTS
#undef HAVE_EXCEPTIONS
#endif


#ifdef HAVE_NAMESPACE
#define MICO_NAMESPACE_DECL namespace
#define MICO_EXPORT_DECL extern
#define MICO_EXPORT_FCT_DECL extern
#define MICO_INLINE_FCT_DECL static inline
#define MICO_EXPORT_VAR_DECL extern
#define MICO_EXPORT_TYPEVAR_DECL extern
#else
#define MICO_NAMESPACE_DECL struct
#define MICO_EXPORT_DECL static
#define MICO_EXPORT_FCT_DECL static
#define MICO_INLINE_FCT_DECL static
#define MICO_EXPORT_VAR_DECL static
#define MICO_EXPORT_TYPEVAR_DECL static
#endif

#define MICO_EXPORT_CONST_DECL MICO_EXPORT_VAR_DECL
#define MICO_SCOPE(S,V) S::V


// This Macro is used in the idl compiler even on unix
#define _VC_NAMESPACE_HACK "_VCHACK__"

#ifdef _WINDOWS
#undef environ

// Assume that Namespace handling is buggy in Visual
#define _VC_NAMESPACE_BUG

#undef MICO_SCOPE
#define MICO_SCOPE(S,V) V
    
#ifdef BUILD_MICO_DLL
#undef  MICO_EXPORT_VAR_DECL
#undef  MICO_EXPORT_CONST_DECL
#define MICO_EXPORT_VAR_DECL extern
#define MICO_EXPORT_CONST_DECL extern
#define MICO_EXPORT_TYPEVAR_DECL extern
#else
#undef  MICO_EXPORT_VAR_DECL
#undef  MICO_EXPORT_CONST_DECL
#define MICO_EXPORT_VAR_DECL __declspec(dllimport) 
#define MICO_EXPORT_CONST_DECL extern __declspec(dllimport) 
#define MICO_EXPORT_TYPEVAR_DECL extern
#endif
#endif

/***************************** STL headers **************************/


#ifdef HAVE_MINI_STL
#include <ministl/string>
#include <ministl/vector>
#include <ministl/map>
#include <ministl/set>
#include <ministl/list>
#else
#ifdef _WINDOWS

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <limits>

#else
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#endif

#ifdef HAVE_NAMESPACE
namespace std {
    typedef int ____foo____;
};
using namespace std;
#endif

#endif


typedef vector<int>::size_type mico_vec_size_type;

/************************** CORBA 2.1 compliance ********************/

#ifdef USE_CORBA_2_1
// Defines for 2.1 compliance

#define EXCEPTION_DOWNCAST _narrow


#else
// Defines for most recent CORBA compliance

#define EXCEPTION_DOWNCAST _downcast

#endif

/************************** MICO templates **************************/

#include <mico/version.h>
#include <mico/types.h>
#include <mico/sequence.h>
#include <mico/sequence_special.h>
#include <mico/array.h>
#include <mico/var.h>
#include <mico/fixed.h>
#include <mico/native.h>

/*************************** module CORBA ***************************/

#define MICO_NO_TOPLEVEL_MODULES

MICO_NAMESPACE_DECL CORBA {
#ifdef _WINDOWS
	using namespace CORBA;
#endif
#define MICO_MODULE_CORBA
#include <mico/basic.h>
#include <mico/magic.h>
#include <mico/address.h>
#include <mico/ior.h>
#include <mico/transport.h>
#include <mico/buffer.h>
#include <mico/codeset.h>
#include <mico/codec.h>
#include <mico/string.h>
#include <mico/except.h>
#include <mico/orb_excepts.h>
#include <mico/any.h>
#include <mico/object.h>
#include <mico/value.h>
#include <mico/basic_seq.h>
#include <mico/ioptypes.h>
#include <mico/orb_fwd.h>
#include <mico/boa.h>
#include <mico/dii.h>
#include <mico/dsi.h>
#include <mico/static.h>
#include <mico/dispatch.h>
#include <mico/static-dispatch.h>
#include <mico/tcconst.h>
#include <mico/ir_base.h>
#ifndef MICO_CONF_NO_IR
#include <mico/ir.h>
#endif
#include <mico/tckind.h>
#include <mico/typecode.h>
#include <mico/service_info.h>
#include <mico/orb.h>
#ifndef MICO_CONF_NO_IMR
#include <mico/imr.h>
#endif
#include <mico/current.h>
#include <mico/policy.h>
#include <mico/valuetype.h>
#include <mico/valuetype_impl.h>
#undef MICO_MODULE_CORBA
};

/********************** module PortableServer ***************************/

#ifndef MICO_CONF_NO_POA
MICO_NAMESPACE_DECL PortableServer {
#ifdef _WINDOWS
	using namespace PortableServer;
#endif
#define MICO_MODULE_PortableServer
class ServantBase;
#include <mico/poa.h>
#include <mico/poa_base.h>
#include <mico/poa_stubs.h>
#undef MICO_MODULE_PortableServer
};
#endif

/********************** module POA_PortableServer ***********************/

#ifndef MICO_CONF_NO_POA
MICO_NAMESPACE_DECL POA_PortableServer {
#ifdef _WINDOWS
      using namespace POA_PortableServer;
#endif
#define MICO_MODULE_POA_PortableServer
#include <mico/poa_stubs.h>
#undef MICO_MODULE_POA_PortableServer
};
#endif

/********************** Global ******************************************/

#define MICO_MODULE__GLOBAL
#include <mico/dispatch.h>
#include <mico/static-dispatch.h>
#include <mico/ir_base.h>
#include <mico/basic_seq.h>
#ifndef MICO_CONF_NO_IR
#include <mico/ir.h>
#endif
#ifndef MICO_CONF_NO_IMR
#include <mico/imr.h>
#endif
#ifndef MICO_CONF_NO_POA
#include <mico/poa.h>
#include <mico/poa_base.h>
#include <mico/poa_stubs.h>
#endif
#include <mico/valuetype.h>
#undef MICO_MODULE__GLOBAL

#undef MICO_NO_TOPLEVEL_MODULES

#ifndef MICO_CONF_NO_DYNANY
#include <mico/dynany.h>
#endif

#ifndef MICO_CONF_NO_INTERCEPT
#include <mico/intercept.h>
#endif

#include <mico/operators.h>
#include <mico/policy2.h>

#endif // __corba_h__
