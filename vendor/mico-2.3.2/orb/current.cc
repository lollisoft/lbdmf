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

// Stub interface Current
CORBA::Current::~Current()
{
}

void *CORBA::Current::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/Current:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

CORBA::Current_ptr CORBA::Current::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/Current:1.0" )))
      return _duplicate( (CORBA::Current_ptr) _p );
  }
  return _nil();
}

CORBA::Current_ptr
CORBA::Current::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


struct __tc_init_CURRENT {
  __tc_init_CURRENT()
  {
  }
};

static __tc_init_CURRENT __init_CURRENT;

