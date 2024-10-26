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

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::Bounds::Bounds()
{
}

CORBA::Bounds::Bounds( const Bounds& _s )
{
}

CORBA::Bounds::~Bounds()
{
}

CORBA::Bounds&
CORBA::Bounds::operator=( const Bounds& _s )
{
  return *this;
}
#endif

void CORBA::Bounds::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw Bounds_var( (CORBA::Bounds*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::Bounds::_repoid() const
{
  return "IDL:omg.org/CORBA/Bounds:1.0";
}

void CORBA::Bounds::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::Bounds::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::Bounds::_clone() const
{
  return new Bounds( *this );
}

CORBA::Bounds *CORBA::Bounds::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/Bounds:1.0" ) )
    return (Bounds *) _ex;
  return NULL;
}

const CORBA::Bounds *CORBA::Bounds::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/Bounds:1.0" ) )
    return (Bounds *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::WrongTransaction::WrongTransaction()
{
}

CORBA::WrongTransaction::WrongTransaction( const WrongTransaction& _s )
{
}

CORBA::WrongTransaction::~WrongTransaction()
{
}

CORBA::WrongTransaction&
CORBA::WrongTransaction::operator=( const WrongTransaction& _s )
{
  return *this;
}
#endif

void CORBA::WrongTransaction::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw WrongTransaction_var( (CORBA::WrongTransaction*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::WrongTransaction::_repoid() const
{
  return "IDL:omg.org/CORBA/WrongTransaction:1.0";
}

void CORBA::WrongTransaction::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::WrongTransaction::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::WrongTransaction::_clone() const
{
  return new WrongTransaction( *this );
}

CORBA::WrongTransaction *CORBA::WrongTransaction::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/WrongTransaction:1.0" ) )
    return (WrongTransaction *) _ex;
  return NULL;
}

const CORBA::WrongTransaction *CORBA::WrongTransaction::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/WrongTransaction:1.0" ) )
    return (WrongTransaction *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ORB_InconsistentTypeCode::ORB_InconsistentTypeCode()
{
}

CORBA::ORB_InconsistentTypeCode::ORB_InconsistentTypeCode( const ORB_InconsistentTypeCode& _s )
{
}

CORBA::ORB_InconsistentTypeCode::~ORB_InconsistentTypeCode()
{
}

CORBA::ORB_InconsistentTypeCode&
CORBA::ORB_InconsistentTypeCode::operator=( const ORB_InconsistentTypeCode& _s )
{
  return *this;
}
#endif

void CORBA::ORB_InconsistentTypeCode::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ORB_InconsistentTypeCode_var( (CORBA::ORB_InconsistentTypeCode*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::ORB_InconsistentTypeCode::_repoid() const
{
  return "IDL:omg.org/CORBA/ORB/InconsistentTypeCode:1.0";
}

void CORBA::ORB_InconsistentTypeCode::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::ORB_InconsistentTypeCode::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::ORB_InconsistentTypeCode::_clone() const
{
  return new ORB_InconsistentTypeCode( *this );
}

CORBA::ORB_InconsistentTypeCode *CORBA::ORB_InconsistentTypeCode::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/ORB/InconsistentTypeCode:1.0" ) )
    return (ORB_InconsistentTypeCode *) _ex;
  return NULL;
}

const CORBA::ORB_InconsistentTypeCode *CORBA::ORB_InconsistentTypeCode::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/ORB/InconsistentTypeCode:1.0" ) )
    return (ORB_InconsistentTypeCode *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ORB_InvalidName::ORB_InvalidName()
{
}

CORBA::ORB_InvalidName::ORB_InvalidName( const ORB_InvalidName& _s )
{
}

CORBA::ORB_InvalidName::~ORB_InvalidName()
{
}

CORBA::ORB_InvalidName&
CORBA::ORB_InvalidName::operator=( const ORB_InvalidName& _s )
{
  return *this;
}
#endif

void CORBA::ORB_InvalidName::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ORB_InvalidName_var( (CORBA::ORB_InvalidName*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::ORB_InvalidName::_repoid() const
{
  return "IDL:omg.org/CORBA/ORB/InvalidName:1.0";
}

void CORBA::ORB_InvalidName::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::ORB_InvalidName::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::ORB_InvalidName::_clone() const
{
  return new ORB_InvalidName( *this );
}

CORBA::ORB_InvalidName *CORBA::ORB_InvalidName::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/ORB/InvalidName:1.0" ) )
    return (ORB_InvalidName *) _ex;
  return NULL;
}

const CORBA::ORB_InvalidName *CORBA::ORB_InvalidName::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/ORB/InvalidName:1.0" ) )
    return (ORB_InvalidName *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::TypeCode_Bounds::TypeCode_Bounds()
{
}

CORBA::TypeCode_Bounds::TypeCode_Bounds( const TypeCode_Bounds& _s )
{
}

CORBA::TypeCode_Bounds::~TypeCode_Bounds()
{
}

CORBA::TypeCode_Bounds&
CORBA::TypeCode_Bounds::operator=( const TypeCode_Bounds& _s )
{
  return *this;
}
#endif

void CORBA::TypeCode_Bounds::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw TypeCode_Bounds_var( (CORBA::TypeCode_Bounds*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::TypeCode_Bounds::_repoid() const
{
  return "IDL:omg.org/CORBA/TypeCode/InvalidName:1.0";
}

void CORBA::TypeCode_Bounds::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::TypeCode_Bounds::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::TypeCode_Bounds::_clone() const
{
  return new TypeCode_Bounds( *this );
}

CORBA::TypeCode_Bounds *CORBA::TypeCode_Bounds::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/TypeCode/InvalidName:1.0" ) )
    return (TypeCode_Bounds *) _ex;
  return NULL;
}

const CORBA::TypeCode_Bounds *CORBA::TypeCode_Bounds::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/TypeCode/InvalidName:1.0" ) )
    return (TypeCode_Bounds *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::TypeCode_BadKind::TypeCode_BadKind()
{
}

CORBA::TypeCode_BadKind::TypeCode_BadKind( const TypeCode_BadKind& _s )
{
}

CORBA::TypeCode_BadKind::~TypeCode_BadKind()
{
}

CORBA::TypeCode_BadKind&
CORBA::TypeCode_BadKind::operator=( const TypeCode_BadKind& _s )
{
  return *this;
}
#endif

void CORBA::TypeCode_BadKind::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw TypeCode_BadKind_var( (CORBA::TypeCode_BadKind*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *CORBA::TypeCode_BadKind::_repoid() const
{
  return "IDL:omg.org/CORBA/TypeCode/BadKind:1.0";
}

void CORBA::TypeCode_BadKind::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void CORBA::TypeCode_BadKind::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *CORBA::TypeCode_BadKind::_clone() const
{
  return new TypeCode_BadKind( *this );
}

CORBA::TypeCode_BadKind *CORBA::TypeCode_BadKind::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/TypeCode/BadKind:1.0" ) )
    return (TypeCode_BadKind *) _ex;
  return NULL;
}

const CORBA::TypeCode_BadKind *CORBA::TypeCode_BadKind::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/CORBA/TypeCode/BadKind:1.0" ) )
    return (TypeCode_BadKind *) _ex;
  return NULL;
}

struct __tc_init_ORB_EXCEPTS {
  __tc_init_ORB_EXCEPTS()
  {
  }
};

static __tc_init_ORB_EXCEPTS __init_ORB_EXCEPTS;

