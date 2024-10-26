/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#ifdef __MINGW32__
#include <cstring>
#endif
#include <mico/ssliop.h>

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong NoProtection = 1; };
#else
const CORBA::ULong Security::NoProtection = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong Integrity = 2; };
#else
const CORBA::ULong Security::Integrity = 2;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong Confidentiality = 4; };
#else
const CORBA::ULong Security::Confidentiality = 4;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong DetectReplay = 8; };
#else
const CORBA::ULong Security::DetectReplay = 8;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong DetectMisordering = 16; };
#else
const CORBA::ULong Security::DetectMisordering = 16;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong EstablishTrustInTarget = 32; };
#else
const CORBA::ULong Security::EstablishTrustInTarget = 32;
#endif
#ifdef HAVE_NAMESPACE
namespace Security { const CORBA::ULong EstablishTrustInClient = 64; };
#else
const CORBA::ULong Security::EstablishTrustInClient = 64;
#endif
#ifdef HAVE_EXPLICIT_STRUCT_OPS
SSLIOP::SSL::SSL()
{
}

SSLIOP::SSL::SSL( const SSL& _s )
{
  target_supports = ((SSL&)_s).target_supports;
  target_requires = ((SSL&)_s).target_requires;
  port = ((SSL&)_s).port;
}

SSLIOP::SSL::~SSL()
{
}

SSLIOP::SSL&
SSLIOP::SSL::operator=( const SSL& _s )
{
  target_supports = ((SSL&)_s).target_supports;
  target_requires = ((SSL&)_s).target_requires;
  port = ((SSL&)_s).port;
  return *this;
}
#endif

struct __tc_init_SSLIOP {
  __tc_init_SSLIOP()
  {
  }
};

static __tc_init_SSLIOP __init_SSLIOP;

