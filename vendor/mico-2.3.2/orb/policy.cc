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


// Stub interface Policy
CORBA::Policy::~Policy()
{
}

void *CORBA::Policy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/Policy:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

CORBA::Policy_ptr CORBA::Policy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/Policy:1.0" )))
      return _duplicate( (CORBA::Policy_ptr) _p );
  }
  return _nil();
}

CORBA::Policy_ptr
CORBA::Policy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}





// Stub interface DomainManager
CORBA::DomainManager::~DomainManager()
{
}

void *CORBA::DomainManager::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/DomainManager:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

CORBA::DomainManager_ptr CORBA::DomainManager::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/DomainManager:1.0" )))
      return _duplicate( (CORBA::DomainManager_ptr) _p );
  }
  return _nil();
}

CORBA::DomainManager_ptr
CORBA::DomainManager::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::ULong SecConstruction = 11; };
#else
const CORBA::ULong CORBA::SecConstruction = 11;
#endif

// Stub interface ConstructionPolicy
CORBA::ConstructionPolicy::~ConstructionPolicy()
{
}

void *CORBA::ConstructionPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ConstructionPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Policy::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

CORBA::ConstructionPolicy_ptr CORBA::ConstructionPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ConstructionPolicy:1.0" )))
      return _duplicate( (CORBA::ConstructionPolicy_ptr) _p );
  }
  return _nil();
}

CORBA::ConstructionPolicy_ptr
CORBA::ConstructionPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}




#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short BAD_POLICY = 0; };
#else
const CORBA::Short CORBA::BAD_POLICY = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short UNSUPPORTED_POLICY = 1; };
#else
const CORBA::Short CORBA::UNSUPPORTED_POLICY = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short BAD_POLICY_TYPE = 2; };
#else
const CORBA::Short CORBA::BAD_POLICY_TYPE = 2;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short BAD_POLICY_VALUE = 3; };
#else
const CORBA::Short CORBA::BAD_POLICY_VALUE = 3;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short UNSUPPORTED_POLICY_VALUE = 4; };
#else
const CORBA::Short CORBA::UNSUPPORTED_POLICY_VALUE = 4;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::PolicyError::PolicyError()
{
}

CORBA::PolicyError::PolicyError( const PolicyError& _s )
{
  reason = ((PolicyError&)_s).reason;
}

CORBA::PolicyError::~PolicyError()
{
}

CORBA::PolicyError&
CORBA::PolicyError::operator=( const PolicyError& _s )
{
  reason = ((PolicyError&)_s).reason;
  return *this;
}
#endif

#ifndef HAVE_EXPLICIT_STRUCT_OPS
CORBA::PolicyError::PolicyError()
{
}

#endif

CORBA::PolicyError::PolicyError( CORBA::PolicyErrorCode _m0 )
{
  reason = _m0;
}

void CORBA::PolicyError::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw PolicyError_var( (CORBA::PolicyError*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::PolicyError::_repoid() const
{
  return "IDL:omg.org/CORBA/PolicyError:1.0";
}

void CORBA::PolicyError::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::PolicyError::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::PolicyError::_clone() const
{
  return new PolicyError( *this );
}

CORBA::PolicyError *CORBA::PolicyError::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/PolicyError:1.0" ) )
    return (PolicyError *) _ex;
  return NULL;
}

const CORBA::PolicyError *CORBA::PolicyError::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/PolicyError:1.0" ) )
    return (PolicyError *) _ex;
  return NULL;
}

struct __tc_init_POLICY {
  __tc_init_POLICY()
  {
  }
};

static __tc_init_POLICY __init_POLICY;

