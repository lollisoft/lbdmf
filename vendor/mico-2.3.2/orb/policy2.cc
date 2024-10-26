/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#ifdef __MINGW32__
#include <cstring>
#endif
#include <CORBA.h>
#include <mico/throw.h>
#include <mico/template_impl.h>

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------
#ifdef HAVE_NAMESPACE
namespace MICOPolicy { const CORBA::ULong TRANSPORTPREF_POLICY_TYPE = 1000; };
#else
const CORBA::ULong MICOPolicy::TRANSPORTPREF_POLICY_TYPE = 1000;
#endif
#ifdef HAVE_NAMESPACE
namespace MICOPolicy { CORBA::TypeCodeConst TransportPrefPolicy::_tc_ProfileTag; };
#else
CORBA::TypeCodeConst MICOPolicy::TransportPrefPolicy::_tc_ProfileTag;
#endif

#ifdef HAVE_NAMESPACE
namespace MICOPolicy { CORBA::TypeCodeConst TransportPrefPolicy::_tc_ProfileTagSeq; };
#else
CORBA::TypeCodeConst MICOPolicy::TransportPrefPolicy::_tc_ProfileTagSeq;
#endif


// Stub interface TransportPrefPolicy
MICOPolicy::TransportPrefPolicy::~TransportPrefPolicy()
{
}

void *MICOPolicy::TransportPrefPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/MICOPolicy/TransportPrefPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

MICOPolicy::TransportPrefPolicy_ptr MICOPolicy::TransportPrefPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/MICOPolicy/TransportPrefPolicy:1.0" )))
      return _duplicate( (MICOPolicy::TransportPrefPolicy_ptr) _p );
  }
  return _nil();
}

MICOPolicy::TransportPrefPolicy_ptr
MICOPolicy::TransportPrefPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace BiDirPolicy { CORBA::TypeCodeConst _tc_BidirectionalPolicyValue; };
#else
CORBA::TypeCodeConst BiDirPolicy::_tc_BidirectionalPolicyValue;
#endif

#ifdef HAVE_NAMESPACE
namespace BiDirPolicy { const CORBA::UShort NORMAL = 0; };
#else
const CORBA::UShort BiDirPolicy::NORMAL = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace BiDirPolicy { const CORBA::UShort BOTH = 1; };
#else
const CORBA::UShort BiDirPolicy::BOTH = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace BiDirPolicy { const CORBA::ULong BIDIRECTIONAL_POLICY_TYPE = 37; };
#else
const CORBA::ULong BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE = 37;
#endif

// Stub interface BidirectionalPolicy
BiDirPolicy::BidirectionalPolicy::~BidirectionalPolicy()
{
}

void *BiDirPolicy::BidirectionalPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/BiDirPolicy/BidirectionalPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

BiDirPolicy::BidirectionalPolicy_ptr BiDirPolicy::BidirectionalPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/BiDirPolicy/BidirectionalPolicy:1.0" )))
      return _duplicate( (BiDirPolicy::BidirectionalPolicy_ptr) _p );
  }
  return _nil();
}

BiDirPolicy::BidirectionalPolicy_ptr
BiDirPolicy::BidirectionalPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


struct __tc_init_POLICY2 {
  __tc_init_POLICY2()
  {
    MICOPolicy::TransportPrefPolicy::_tc_ProfileTag = 
    "000000000000001500000058000000000000003a49444c3a6f6d672e6f72"
    "672f4d49434f506f6c6963792f5472616e73706f727450726566506f6c69"
    "63792f50726f66696c655461673a312e300000000000000b50726f66696c"
    "65546167000000000005";
    MICOPolicy::TransportPrefPolicy::_tc_ProfileTagSeq = 
    "0000000000000015000000cc000000000000003d49444c3a6f6d672e6f72"
    "672f4d49434f506f6c6963792f5472616e73706f727450726566506f6c69"
    "63792f50726f66696c655461675365713a312e30000000000000000e5072"
    "6f66696c6554616753657100000000000013000000680000000000000015"
    "00000058000000000000003a49444c3a6f6d672e6f72672f4d49434f506f"
    "6c6963792f5472616e73706f727450726566506f6c6963792f50726f6669"
    "6c655461673a312e300000000000000b50726f66696c6554616700000000"
    "000500000000";
    BiDirPolicy::_tc_BidirectionalPolicyValue = 
    "000000000000001500000064000000000000003549444c3a6f6d672e6f72"
    "672f4269446972506f6c6963792f4269646972656374696f6e616c506f6c"
    "69637956616c75653a312e3000000000000000194269646972656374696f"
    "6e616c506f6c69637956616c75650000000000000004";
  }
};

static __tc_init_POLICY2 __init_POLICY2;

