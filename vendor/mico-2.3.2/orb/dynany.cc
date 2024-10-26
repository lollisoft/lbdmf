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
DynamicAny::DynAny::InvalidValue::InvalidValue()
{
}

DynamicAny::DynAny::InvalidValue::InvalidValue( const InvalidValue& _s )
{
}

DynamicAny::DynAny::InvalidValue::~InvalidValue()
{
}

DynamicAny::DynAny::InvalidValue&
DynamicAny::DynAny::InvalidValue::operator=( const InvalidValue& _s )
{
  return *this;
}
#endif

void DynamicAny::DynAny::InvalidValue::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw InvalidValue_var( (DynamicAny::DynAny::InvalidValue*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *DynamicAny::DynAny::InvalidValue::_repoid() const
{
  return "IDL:omg.org/DynamicAny/DynAny/InvalidValue:1.0";
}

void DynamicAny::DynAny::InvalidValue::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void DynamicAny::DynAny::InvalidValue::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *DynamicAny::DynAny::InvalidValue::_clone() const
{
  return new InvalidValue( *this );
}

DynamicAny::DynAny::InvalidValue *DynamicAny::DynAny::InvalidValue::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAny/InvalidValue:1.0" ) )
    return (InvalidValue *) _ex;
  return NULL;
}

const DynamicAny::DynAny::InvalidValue *DynamicAny::DynAny::InvalidValue::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAny/InvalidValue:1.0" ) )
    return (InvalidValue *) _ex;
  return NULL;
}


#ifdef HAVE_EXPLICIT_STRUCT_OPS
DynamicAny::DynAny::TypeMismatch::TypeMismatch()
{
}

DynamicAny::DynAny::TypeMismatch::TypeMismatch( const TypeMismatch& _s )
{
}

DynamicAny::DynAny::TypeMismatch::~TypeMismatch()
{
}

DynamicAny::DynAny::TypeMismatch&
DynamicAny::DynAny::TypeMismatch::operator=( const TypeMismatch& _s )
{
  return *this;
}
#endif

void DynamicAny::DynAny::TypeMismatch::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw TypeMismatch_var( (DynamicAny::DynAny::TypeMismatch*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *DynamicAny::DynAny::TypeMismatch::_repoid() const
{
  return "IDL:omg.org/DynamicAny/DynAny/TypeMismatch:1.0";
}

void DynamicAny::DynAny::TypeMismatch::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void DynamicAny::DynAny::TypeMismatch::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *DynamicAny::DynAny::TypeMismatch::_clone() const
{
  return new TypeMismatch( *this );
}

DynamicAny::DynAny::TypeMismatch *DynamicAny::DynAny::TypeMismatch::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAny/TypeMismatch:1.0" ) )
    return (TypeMismatch *) _ex;
  return NULL;
}

const DynamicAny::DynAny::TypeMismatch *DynamicAny::DynAny::TypeMismatch::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAny/TypeMismatch:1.0" ) )
    return (TypeMismatch *) _ex;
  return NULL;
}


// Stub interface DynAny
DynamicAny::DynAny::~DynAny()
{
}

void *DynamicAny::DynAny::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynAny:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

DynamicAny::DynAny_ptr DynamicAny::DynAny::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynAny:1.0" )))
      return _duplicate( (DynamicAny::DynAny_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynAny_ptr
DynamicAny::DynAny::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynBasic
DynamicAny::DynBasic::~DynBasic()
{
}

void *DynamicAny::DynBasic::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynBasic:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynBasic_ptr DynamicAny::DynBasic::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynBasic:1.0" )))
      return _duplicate( (DynamicAny::DynBasic_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynBasic_ptr
DynamicAny::DynBasic::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynFixed
DynamicAny::DynFixed::~DynFixed()
{
}

void *DynamicAny::DynFixed::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynFixed:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynFixed_ptr DynamicAny::DynFixed::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynFixed:1.0" )))
      return _duplicate( (DynamicAny::DynFixed_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynFixed_ptr
DynamicAny::DynFixed::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynEnum
DynamicAny::DynEnum::~DynEnum()
{
}

void *DynamicAny::DynEnum::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynEnum:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynEnum_ptr DynamicAny::DynEnum::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynEnum:1.0" )))
      return _duplicate( (DynamicAny::DynEnum_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynEnum_ptr
DynamicAny::DynEnum::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



#ifdef HAVE_EXPLICIT_STRUCT_OPS
DynamicAny::NameValuePair::NameValuePair()
{
}

DynamicAny::NameValuePair::NameValuePair( const NameValuePair& _s )
{
  id = ((NameValuePair&)_s).id;
  value = ((NameValuePair&)_s).value;
}

DynamicAny::NameValuePair::~NameValuePair()
{
}

DynamicAny::NameValuePair&
DynamicAny::NameValuePair::operator=( const NameValuePair& _s )
{
  id = ((NameValuePair&)_s).id;
  value = ((NameValuePair&)_s).value;
  return *this;
}
#endif


#ifdef HAVE_EXPLICIT_STRUCT_OPS
DynamicAny::NameDynAnyPair::NameDynAnyPair()
{
}

DynamicAny::NameDynAnyPair::NameDynAnyPair( const NameDynAnyPair& _s )
{
  id = ((NameDynAnyPair&)_s).id;
  value = ((NameDynAnyPair&)_s).value;
}

DynamicAny::NameDynAnyPair::~NameDynAnyPair()
{
}

DynamicAny::NameDynAnyPair&
DynamicAny::NameDynAnyPair::operator=( const NameDynAnyPair& _s )
{
  id = ((NameDynAnyPair&)_s).id;
  value = ((NameDynAnyPair&)_s).value;
  return *this;
}
#endif



// Stub interface DynStruct
DynamicAny::DynStruct::~DynStruct()
{
}

void *DynamicAny::DynStruct::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynStruct:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynStruct_ptr DynamicAny::DynStruct::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynStruct:1.0" )))
      return _duplicate( (DynamicAny::DynStruct_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynStruct_ptr
DynamicAny::DynStruct::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynUnion
DynamicAny::DynUnion::~DynUnion()
{
}

void *DynamicAny::DynUnion::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynUnion:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynUnion_ptr DynamicAny::DynUnion::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynUnion:1.0" )))
      return _duplicate( (DynamicAny::DynUnion_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynUnion_ptr
DynamicAny::DynUnion::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}





// Stub interface DynSequence
DynamicAny::DynSequence::~DynSequence()
{
}

void *DynamicAny::DynSequence::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynSequence:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynSequence_ptr DynamicAny::DynSequence::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynSequence:1.0" )))
      return _duplicate( (DynamicAny::DynSequence_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynSequence_ptr
DynamicAny::DynSequence::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynArray
DynamicAny::DynArray::~DynArray()
{
}

void *DynamicAny::DynArray::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynArray:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynArray_ptr DynamicAny::DynArray::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynArray:1.0" )))
      return _duplicate( (DynamicAny::DynArray_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynArray_ptr
DynamicAny::DynArray::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface DynValue
DynamicAny::DynValue::~DynValue()
{
}

void *DynamicAny::DynValue::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynValue:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = DynAny::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

DynamicAny::DynValue_ptr DynamicAny::DynValue::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynValue:1.0" )))
      return _duplicate( (DynamicAny::DynValue_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynValue_ptr
DynamicAny::DynValue::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



#ifdef HAVE_EXPLICIT_STRUCT_OPS
DynamicAny::DynAnyFactory::InconsistentTypeCode::InconsistentTypeCode()
{
}

DynamicAny::DynAnyFactory::InconsistentTypeCode::InconsistentTypeCode( const InconsistentTypeCode& _s )
{
}

DynamicAny::DynAnyFactory::InconsistentTypeCode::~InconsistentTypeCode()
{
}

DynamicAny::DynAnyFactory::InconsistentTypeCode&
DynamicAny::DynAnyFactory::InconsistentTypeCode::operator=( const InconsistentTypeCode& _s )
{
  return *this;
}
#endif

void DynamicAny::DynAnyFactory::InconsistentTypeCode::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw InconsistentTypeCode_var( (DynamicAny::DynAnyFactory::InconsistentTypeCode*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *DynamicAny::DynAnyFactory::InconsistentTypeCode::_repoid() const
{
  return "IDL:omg.org/DynamicAny/DynAnyFactory/InconsistentTypeCode:1.0";
}

void DynamicAny::DynAnyFactory::InconsistentTypeCode::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void DynamicAny::DynAnyFactory::InconsistentTypeCode::_encode_any( CORBA::Any &_a ) const
{
  // use --any to make this work!
  assert(0);
}

CORBA::Exception *DynamicAny::DynAnyFactory::InconsistentTypeCode::_clone() const
{
  return new InconsistentTypeCode( *this );
}

DynamicAny::DynAnyFactory::InconsistentTypeCode *DynamicAny::DynAnyFactory::InconsistentTypeCode::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAnyFactory/InconsistentTypeCode:1.0" ) )
    return (InconsistentTypeCode *) _ex;
  return NULL;
}

const DynamicAny::DynAnyFactory::InconsistentTypeCode *DynamicAny::DynAnyFactory::InconsistentTypeCode::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/DynamicAny/DynAnyFactory/InconsistentTypeCode:1.0" ) )
    return (InconsistentTypeCode *) _ex;
  return NULL;
}


// Stub interface DynAnyFactory
DynamicAny::DynAnyFactory::~DynAnyFactory()
{
}

void *DynamicAny::DynAnyFactory::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/DynamicAny/DynAnyFactory:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

DynamicAny::DynAnyFactory_ptr DynamicAny::DynAnyFactory::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/DynamicAny/DynAnyFactory:1.0" )))
      return _duplicate( (DynamicAny::DynAnyFactory_ptr) _p );
  }
  return _nil();
}

DynamicAny::DynAnyFactory_ptr
DynamicAny::DynAnyFactory::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


struct __tc_init_DYNANY {
  __tc_init_DYNANY()
  {
  }
};

static __tc_init_DYNANY __init_DYNANY;

