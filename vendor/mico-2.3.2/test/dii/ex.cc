/*
 *  MICO --- a CORBA 2.0 implementation
 *  Copyright (C) 1997 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "ex.h"

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------
CORBA::TypeCode_ptr _tc_SomeExcept = (new CORBA::TypeCode(
  "010000001600000040000000010000001300000049444c3a536f6d654578"
  "636570743a312e3000000b000000536f6d65457863657074000001000000"
  "040000006d7367001200000000000000" ))->mk_constant();

void operator<<=( CORBA::Any &a, const SomeExcept &s )
{
  a.set_type( _tc_SomeExcept );
  a.except_put_begin("IDL:SomeExcept:1.0");
  a <<= ((SomeExcept&)s).msg;
  a.except_put_end();
}

CORBA::Boolean operator>>=( const CORBA::Any &a, SomeExcept &s )
{
  CORBA::String_var repoid;
  return (a.except_get_begin(repoid) &&
    (a >>= s.msg) &&
    a.except_get_end() );
}


// Stub interface SomeIface
SomeIface_ptr SomeIface::_duplicate( SomeIface_ptr obj )
{
  if( !CORBA::is_nil( obj ) )
    obj->_ref();
  return obj;
}

bool SomeIface::_narrow_helper( CORBA::Object_ptr obj )
{
  if( strcmp( obj->_repoid(), "IDL:SomeIface:1.0" ) == 0 )
    return true;
  return false;
}

SomeIface_ptr SomeIface::_narrow( CORBA::Object_ptr obj )
{
  if( CORBA::is_nil( obj ) || !SomeIface::_narrow_helper( obj ) )
    return SomeIface::_nil();
  SomeIface_ptr o = new SomeIface_stub;
  o->CORBA::Object::operator=( *obj );
  return o;
}

SomeIface_ptr SomeIface::_nil()
{
  return NULL;
}

void SomeIface_stub::f()
{
  CORBA::Request_var _req = this->_request( "f" );
  _req->result()->value()->set_type( CORBA::_tc_void );
  _req->invoke();
  if (_req->env()->exception()) {
      CORBA::Exception *ex = _req->env()->exception();
      CORBA::UnknownUserException *uuex =
	  CORBA::UnknownUserException::EXCEPTION_DOWNCAST (ex);
      if (uuex) {
	  if (!strcmp (uuex->_except_repoid(), "IDL:SomeExcept:1.0")) {
	      CORBA::Any &a = uuex->exception (_tc_SomeExcept);
	      SomeExcept sex;
	      CORBA::Boolean r = (a >>= sex);
	      assert (r);
	      mico_throw (sex);
	  }
	  mico_throw (CORBA::UNKNOWN());
      } else {
	  mico_throw (*ex);
      }
  }
}


CORBA::TypeCode_ptr _tc_SomeIface = (new CORBA::TypeCode(
  "010000000e0000002a000000010000001200000049444c3a536f6d654966"
  "6163653a312e300000000a000000536f6d65496661636500" ))->mk_constant();

void
operator<<=( CORBA::Any &a, const SomeIface_ptr obj )
{
  a <<= CORBA::Any::from_object( obj, "SomeIface" );
}

CORBA::Boolean
operator>>=( const CORBA::Any &a, SomeIface_ptr &obj )
{
  CORBA::Object_var o;
  if( !(a >>= CORBA::Any::to_object( o )) )
    return FALSE;
  if( CORBA::is_nil( o ) ) {
    obj = ::SomeIface::_nil();
    return TRUE;
  }

  // XXX catch error if narrow fails ...
  obj = ::SomeIface::_narrow( o );
  return TRUE;
}

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// Dynamic Implementation Routine for interface SomeIface
SomeIface_skel::SomeIface_skel()
{
  CORBA::ImplementationDef_var impl =
    _find_impl( "IDL:SomeIface:1.0", "SomeIface" );
  assert( !CORBA::is_nil( impl ) );
  _create_ref( CORBA::BOA::ReferenceData(),
    CORBA::InterfaceDef::_nil(),
    impl,
    "IDL:SomeIface:1.0" );
  register_dispatcher( new InterfaceDispatcherWrapper<SomeIface_skel>( this ) );
}

SomeIface_skel::SomeIface_skel( CORBA::Object_ptr obj )
{
  CORBA::ImplementationDef_var impl =
    _find_impl( "IDL:SomeIface:1.0", "SomeIface" );
  assert( !CORBA::is_nil( impl ) );
  _restore_ref( obj,
    CORBA::BOA::ReferenceData(),
    CORBA::InterfaceDef::_nil(),
    impl );
  register_dispatcher( new InterfaceDispatcherWrapper<SomeIface_skel>( this ) );
}

bool SomeIface_skel::dispatch( CORBA::ServerRequest_ptr _req, CORBA::Environment &_env )
{
  if( strcmp( _req->op_name(), "f" ) == 0 ) {
    CORBA::NVList_ptr _args;
    _orbnc()->create_list( 0, _args );

    _req->params( _args );

    try {
	f();
    } catch (SomeExcept_catch &ex) {
	_req->exception (ex->_clone ());
    } catch (...) {
	assert (0);
    }
    return true;
  }
  return false;
}

//--------------------------------------------------------
// Exceptions
//--------------------------------------------------------

void
SomeExcept::_throwit () const
{
#ifdef HAVE_EXCEPTIONS
#ifdef HAVE_STD_EH
    throw *this;
#else
    throw SomeExcept_var ((SomeExcept*)_clone());
#endif
#else
    assert (0);
#endif
}

const char *
SomeExcept::_repoid () const
{
    return "IDL:SomeExcept:1.0";
}

void
SomeExcept::_encode (CORBA::DataEncoder &ec) const
{
    CORBA::Any a;
    a <<= *this;
    a.marshal (ec);
}

CORBA::Exception *
SomeExcept::_clone () const
{
    return new SomeExcept (*this);
}

SomeExcept *
SomeExcept::_narrow (CORBA::Exception *ex)
{
    if (ex && !strcmp (ex->_repoid(), "IDL:SomeExcept:1.0"))
	return (SomeExcept *)ex;
    return NULL;
}
