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
namespace CORBA { CORBA::TypeCodeConst _tc_ScopedName; };
#else
CORBA::TypeCodeConst CORBA::_tc_ScopedName;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst Contained::_tc_Description; };
#else
CORBA::TypeCodeConst CORBA::Contained::_tc_Description;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::Contained::Description::Description()
{
}

CORBA::Contained::Description::Description( const Description& _s )
{
  kind = ((Description&)_s).kind;
  value = ((Description&)_s).value;
}

CORBA::Contained::Description::~Description()
{
}

CORBA::Contained::Description&
CORBA::Contained::Description::operator=( const Description& _s )
{
  kind = ((Description&)_s).kind;
  value = ((Description&)_s).value;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::Contained::Description &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Contained_Description, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::Contained::Description *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Contained::Description &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Contained_Description, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Contained::Description *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_Contained_Description, (void *&)_s);
}

class _Marshaller_CORBA_Contained_Description : public CORBA::StaticTypeInfo {
    typedef CORBA::Contained::Description _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Contained_Description::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_Contained_Description::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_Contained_Description::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Contained_Description::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    _marshaller_CORBA_DefinitionKind->demarshal( dc, &((_MICO_T*)v)->kind ) &&
    CORBA::_stc_any->demarshal( dc, &((_MICO_T*)v)->value ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_Contained_Description::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  _marshaller_CORBA_DefinitionKind->marshal( ec, &((_MICO_T*)v)->kind );
  CORBA::_stc_any->marshal( ec, &((_MICO_T*)v)->value );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Contained_Description::typecode()
{
  return CORBA::Contained::_tc_Description;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Contained_Description;


// Stub interface Contained
CORBA::Contained::~Contained()
{
}

void *CORBA::Contained::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/Contained:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IRObject::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::Contained::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/Contained:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::Contained_ptr CORBA::Contained::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::Contained_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/Contained:1.0" )))
      return _duplicate( (CORBA::Contained_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/Contained:1.0" ) ) ) {
      _o = new CORBA::Contained_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::Contained_ptr
CORBA::Contained::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::Contained_stub::~Contained_stub()
{
}

char* CORBA::Contained_stub::id()
{
  CORBA::RepositoryId _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_id" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::Contained_stub::id( const char* _value )
{
  CORBA::StaticAny __value( CORBA::_stc_string, &_value );
  CORBA::StaticRequest __req( this, "_set_id" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


char* CORBA::Contained_stub::name()
{
  CORBA::Identifier _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_name" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::Contained_stub::name( const char* _value )
{
  CORBA::StaticAny __value( CORBA::_stc_string, &_value );
  CORBA::StaticRequest __req( this, "_set_name" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


char* CORBA::Contained_stub::version()
{
  CORBA::VersionSpec _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_version" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::Contained_stub::version( const char* _value )
{
  CORBA::StaticAny __value( CORBA::_stc_string, &_value );
  CORBA::StaticRequest __req( this, "_set_version" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Container_ptr CORBA::Contained_stub::defined_in()
{
  CORBA::Container_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Container, &_res );

  CORBA::StaticRequest __req( this, "_get_defined_in" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


char* CORBA::Contained_stub::absolute_name()
{
  CORBA::ScopedName _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_absolute_name" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::Repository_ptr CORBA::Contained_stub::containing_repository()
{
  CORBA::Repository_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Repository, &_res );

  CORBA::StaticRequest __req( this, "_get_containing_repository" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::Contained::Description* CORBA::Contained_stub::describe()
{
  CORBA::StaticAny __res( _marshaller_CORBA_Contained_Description );

  CORBA::StaticRequest __req( this, "describe" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::Contained::Description*) __res._retn();
}


void CORBA::Contained_stub::move( CORBA::Container_ptr new_container, const char* new_name, const char* new_version )
{
  CORBA::StaticAny _new_container( _marshaller_CORBA_Container, &new_container );
  CORBA::StaticAny _new_name( CORBA::_stc_string, &new_name );
  CORBA::StaticAny _new_version( CORBA::_stc_string, &new_version );
  CORBA::StaticRequest __req( this, "move" );
  __req.add_in_arg( &_new_container );
  __req.add_in_arg( &_new_name );
  __req.add_in_arg( &_new_version );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_Contained {
  _global_init_CORBA_Contained()
  {
    if( ::CORBA::IRObject::_narrow_helpers == NULL )
      ::CORBA::IRObject::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IRObject::_narrow_helpers->push_back( CORBA::Contained::_narrow_helper2 );
  }
} __global_init_CORBA_Contained;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * Contained::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::Contained::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_Contained; };
#else
CORBA::TypeCodeConst CORBA::_tc_Contained;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::Contained_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Contained, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::Contained_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Contained, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::Contained_ptr &_obj )
{
  CORBA::Contained_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_Contained, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_Contained : public CORBA::StaticTypeInfo {
    typedef CORBA::Contained_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Contained::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_Contained::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::Contained::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_Contained::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Contained::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::Contained::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_Contained::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Contained::typecode()
{
  return CORBA::_tc_Contained;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Contained;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueDefSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueDefSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_InterfaceDefSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_InterfaceDefSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ContainedSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ContainedSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_Initializer; };
#else
CORBA::TypeCodeConst CORBA::_tc_Initializer;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::Initializer::Initializer()
{
}

CORBA::Initializer::Initializer( const Initializer& _s )
{
  members = ((Initializer&)_s).members;
  name = ((Initializer&)_s).name;
}

CORBA::Initializer::~Initializer()
{
}

CORBA::Initializer&
CORBA::Initializer::operator=( const Initializer& _s )
{
  members = ((Initializer&)_s).members;
  name = ((Initializer&)_s).name;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::Initializer &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Initializer, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::Initializer *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Initializer &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Initializer, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Initializer *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_Initializer, (void *&)_s);
}

class _Marshaller_CORBA_Initializer : public CORBA::StaticTypeInfo {
    typedef CORBA::Initializer _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Initializer::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_Initializer::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_Initializer::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Initializer::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    _marshaller__seq_CORBA_StructMember->demarshal( dc, &((_MICO_T*)v)->members ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_Initializer::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  _marshaller__seq_CORBA_StructMember->marshal( ec, &((_MICO_T*)v)->members );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Initializer::typecode()
{
  return CORBA::_tc_Initializer;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Initializer;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_InitializerSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_InitializerSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst Container::_tc_Description; };
#else
CORBA::TypeCodeConst CORBA::Container::_tc_Description;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::Container::Description::Description()
{
}

CORBA::Container::Description::Description( const Description& _s )
{
  contained_object = ((Description&)_s).contained_object;
  kind = ((Description&)_s).kind;
  value = ((Description&)_s).value;
}

CORBA::Container::Description::~Description()
{
}

CORBA::Container::Description&
CORBA::Container::Description::operator=( const Description& _s )
{
  contained_object = ((Description&)_s).contained_object;
  kind = ((Description&)_s).kind;
  value = ((Description&)_s).value;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::Container::Description &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Container_Description, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::Container::Description *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Container::Description &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Container_Description, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::Container::Description *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_Container_Description, (void *&)_s);
}

class _Marshaller_CORBA_Container_Description : public CORBA::StaticTypeInfo {
    typedef CORBA::Container::Description _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Container_Description::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_Container_Description::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_Container_Description::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Container_Description::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    _marshaller_CORBA_Contained->demarshal( dc, &((_MICO_T*)v)->contained_object.inout() ) &&
    _marshaller_CORBA_DefinitionKind->demarshal( dc, &((_MICO_T*)v)->kind ) &&
    CORBA::_stc_any->demarshal( dc, &((_MICO_T*)v)->value ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_Container_Description::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  _marshaller_CORBA_Contained->marshal( ec, &((_MICO_T*)v)->contained_object.inout() );
  _marshaller_CORBA_DefinitionKind->marshal( ec, &((_MICO_T*)v)->kind );
  CORBA::_stc_any->marshal( ec, &((_MICO_T*)v)->value );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Container_Description::typecode()
{
  return CORBA::Container::_tc_Description;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Container_Description;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst Container::_tc_DescriptionSeq; };
#else
CORBA::TypeCodeConst CORBA::Container::_tc_DescriptionSeq;
#endif


// Stub interface Container
CORBA::Container::~Container()
{
}

void *CORBA::Container::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/Container:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IRObject::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::Container::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/Container:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::Container_ptr CORBA::Container::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::Container_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/Container:1.0" )))
      return _duplicate( (CORBA::Container_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/Container:1.0" ) ) ) {
      _o = new CORBA::Container_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::Container_ptr
CORBA::Container::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::Container_stub::~Container_stub()
{
}

CORBA::Contained_ptr CORBA::Container_stub::lookup( const char* search_name )
{
  CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name );
  CORBA::Contained_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );

  CORBA::StaticRequest __req( this, "lookup" );
  __req.add_in_arg( &_search_name );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ContainedSeq* CORBA::Container_stub::contents( CORBA::DefinitionKind limit_type, CORBA::Boolean exclude_inherited )
{
  CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
  CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );

  CORBA::StaticRequest __req( this, "contents" );
  __req.add_in_arg( &_limit_type );
  __req.add_in_arg( &_exclude_inherited );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ContainedSeq*) __res._retn();
}


CORBA::ContainedSeq* CORBA::Container_stub::lookup_name( const char* search_name, CORBA::Long levels_to_search, CORBA::DefinitionKind limit_type, CORBA::Boolean exclude_inherited )
{
  CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name );
  CORBA::StaticAny _levels_to_search( CORBA::_stc_long, &levels_to_search );
  CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
  CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );

  CORBA::StaticRequest __req( this, "lookup_name" );
  __req.add_in_arg( &_search_name );
  __req.add_in_arg( &_levels_to_search );
  __req.add_in_arg( &_limit_type );
  __req.add_in_arg( &_exclude_inherited );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ContainedSeq*) __res._retn();
}


CORBA::Container::DescriptionSeq* CORBA::Container_stub::describe_contents( CORBA::DefinitionKind limit_type, CORBA::Boolean exclude_inherited, CORBA::Long max_returned_objs )
{
  CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
  CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );
  CORBA::StaticAny _max_returned_objs( CORBA::_stc_long, &max_returned_objs );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_Container_Description );

  CORBA::StaticRequest __req( this, "describe_contents" );
  __req.add_in_arg( &_limit_type );
  __req.add_in_arg( &_exclude_inherited );
  __req.add_in_arg( &_max_returned_objs );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::Container::DescriptionSeq*) __res._retn();
}


CORBA::ModuleDef_ptr CORBA::Container_stub::create_module( const char* id, const char* name, const char* version )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::ModuleDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ModuleDef, &_res );

  CORBA::StaticRequest __req( this, "create_module" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ConstantDef_ptr CORBA::Container_stub::create_constant( const char* id, const char* name, const char* version, CORBA::IDLType_ptr type, const CORBA::Any& value )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type );
  CORBA::StaticAny _value( CORBA::_stc_any, &value );
  CORBA::ConstantDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ConstantDef, &_res );

  CORBA::StaticRequest __req( this, "create_constant" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_type );
  __req.add_in_arg( &_value );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::StructDef_ptr CORBA::Container_stub::create_struct( const char* id, const char* name, const char* version, const CORBA::StructMemberSeq& members )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _members( _marshaller__seq_CORBA_StructMember, &members );
  CORBA::StructDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_StructDef, &_res );

  CORBA::StaticRequest __req( this, "create_struct" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_members );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ExceptionDef_ptr CORBA::Container_stub::create_exception( const char* id, const char* name, const char* version, const CORBA::StructMemberSeq& members )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _members( _marshaller__seq_CORBA_StructMember, &members );
  CORBA::ExceptionDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ExceptionDef, &_res );

  CORBA::StaticRequest __req( this, "create_exception" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_members );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::UnionDef_ptr CORBA::Container_stub::create_union( const char* id, const char* name, const char* version, CORBA::IDLType_ptr discriminator_type, const CORBA::UnionMemberSeq& members )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _discriminator_type( _marshaller_CORBA_IDLType, &discriminator_type );
  CORBA::StaticAny _members( _marshaller__seq_CORBA_UnionMember, &members );
  CORBA::UnionDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_UnionDef, &_res );

  CORBA::StaticRequest __req( this, "create_union" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_discriminator_type );
  __req.add_in_arg( &_members );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::EnumDef_ptr CORBA::Container_stub::create_enum( const char* id, const char* name, const char* version, const CORBA::EnumMemberSeq& members )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _members( CORBA::_stcseq_string, &members );
  CORBA::EnumDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_EnumDef, &_res );

  CORBA::StaticRequest __req( this, "create_enum" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_members );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::AliasDef_ptr CORBA::Container_stub::create_alias( const char* id, const char* name, const char* version, CORBA::IDLType_ptr original_type )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _original_type( _marshaller_CORBA_IDLType, &original_type );
  CORBA::AliasDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_AliasDef, &_res );

  CORBA::StaticRequest __req( this, "create_alias" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_original_type );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::InterfaceDef_ptr CORBA::Container_stub::create_interface( const char* id, const char* name, const char* version, const CORBA::InterfaceDefSeq& base_interfaces, CORBA::Boolean is_abstract )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _base_interfaces( _marshaller__seq_CORBA_InterfaceDef, &base_interfaces );
  CORBA::StaticAny _is_abstract( CORBA::_stc_boolean, &is_abstract );
  CORBA::InterfaceDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_InterfaceDef, &_res );

  CORBA::StaticRequest __req( this, "create_interface" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_base_interfaces );
  __req.add_in_arg( &_is_abstract );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ValueDef_ptr CORBA::Container_stub::create_value( const char* id, const char* name, const char* version, CORBA::Boolean is_custom, CORBA::Boolean is_abstract, CORBA::ValueDef_ptr base_value, CORBA::Boolean is_truncatable, const CORBA::ValueDefSeq& abstract_base_values, const CORBA::InterfaceDefSeq& supported_interfaces, const CORBA::InitializerSeq& initializers )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _is_custom( CORBA::_stc_boolean, &is_custom );
  CORBA::StaticAny _is_abstract( CORBA::_stc_boolean, &is_abstract );
  CORBA::StaticAny _base_value( _marshaller_CORBA_ValueDef, &base_value );
  CORBA::StaticAny _is_truncatable( CORBA::_stc_boolean, &is_truncatable );
  CORBA::StaticAny _abstract_base_values( _marshaller__seq_CORBA_ValueDef, &abstract_base_values );
  CORBA::StaticAny _supported_interfaces( _marshaller__seq_CORBA_InterfaceDef, &supported_interfaces );
  CORBA::StaticAny _initializers( _marshaller__seq_CORBA_Initializer, &initializers );
  CORBA::ValueDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ValueDef, &_res );

  CORBA::StaticRequest __req( this, "create_value" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_is_custom );
  __req.add_in_arg( &_is_abstract );
  __req.add_in_arg( &_base_value );
  __req.add_in_arg( &_is_truncatable );
  __req.add_in_arg( &_abstract_base_values );
  __req.add_in_arg( &_supported_interfaces );
  __req.add_in_arg( &_initializers );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ValueBoxDef_ptr CORBA::Container_stub::create_value_box( const char* id, const char* name, const char* version, CORBA::IDLType_ptr original_type_def )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _original_type_def( _marshaller_CORBA_IDLType, &original_type_def );
  CORBA::ValueBoxDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ValueBoxDef, &_res );

  CORBA::StaticRequest __req( this, "create_value_box" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_original_type_def );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::NativeDef_ptr CORBA::Container_stub::create_native( const char* id, const char* name, const char* version )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::NativeDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_NativeDef, &_res );

  CORBA::StaticRequest __req( this, "create_native" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::Contained_ptr CORBA::Container_stub::find( const char* search_name )
{
  CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name );
  CORBA::Contained_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );

  CORBA::StaticRequest __req( this, "find" );
  __req.add_in_arg( &_search_name );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ContainedSeq* CORBA::Container_stub::find_name( const char* search_name, CORBA::DefinitionKind limit_type )
{
  CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name );
  CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );

  CORBA::StaticRequest __req( this, "find_name" );
  __req.add_in_arg( &_search_name );
  __req.add_in_arg( &_limit_type );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ContainedSeq*) __res._retn();
}


CORBA::Contained_ptr CORBA::Container_stub::locate_id( const char* id )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::Contained_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );

  CORBA::StaticRequest __req( this, "locate_id" );
  __req.add_in_arg( &_id );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::Contained_ptr CORBA::Container_stub::locate_name( const char* name, CORBA::Boolean include_enclosing_scopes, CORBA::Boolean is_first_level )
{
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _include_enclosing_scopes( CORBA::_stc_boolean, &include_enclosing_scopes );
  CORBA::StaticAny _is_first_level( CORBA::_stc_boolean, &is_first_level );
  CORBA::Contained_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );

  CORBA::StaticRequest __req( this, "locate_name" );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_include_enclosing_scopes );
  __req.add_in_arg( &_is_first_level );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::Container_stub::remove_contained( CORBA::Contained_ptr con )
{
  CORBA::StaticAny _con( _marshaller_CORBA_Contained, &con );
  CORBA::StaticRequest __req( this, "remove_contained" );
  __req.add_in_arg( &_con );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::Container_stub::add_contained( CORBA::Contained_ptr con )
{
  CORBA::StaticAny _con( _marshaller_CORBA_Contained, &con );
  CORBA::StaticRequest __req( this, "add_contained" );
  __req.add_in_arg( &_con );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_Container {
  _global_init_CORBA_Container()
  {
    if( ::CORBA::IRObject::_narrow_helpers == NULL )
      ::CORBA::IRObject::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IRObject::_narrow_helpers->push_back( CORBA::Container::_narrow_helper2 );
  }
} __global_init_CORBA_Container;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * Container::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::Container::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_Container; };
#else
CORBA::TypeCodeConst CORBA::_tc_Container;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::Container_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Container, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::Container_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Container, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::Container_ptr &_obj )
{
  CORBA::Container_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_Container, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_Container : public CORBA::StaticTypeInfo {
    typedef CORBA::Container_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Container::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_Container::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::Container::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_Container::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Container::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::Container::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_Container::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Container::typecode()
{
  return CORBA::_tc_Container;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Container;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_PrimitiveKind; };
#else
CORBA::TypeCodeConst CORBA::_tc_PrimitiveKind;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::PrimitiveKind &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_PrimitiveKind, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::PrimitiveKind &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_PrimitiveKind, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_PrimitiveKind : public CORBA::StaticTypeInfo {
    typedef CORBA::PrimitiveKind _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_PrimitiveKind::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_PrimitiveKind::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_PrimitiveKind::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_PrimitiveKind::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_PrimitiveKind::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_PrimitiveKind::typecode()
{
  return CORBA::_tc_PrimitiveKind;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_PrimitiveKind;


// Stub interface Repository
CORBA::Repository::~Repository()
{
}

void *CORBA::Repository::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/Repository:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::Repository::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/Repository:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::Repository_ptr CORBA::Repository::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::Repository_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/Repository:1.0" )))
      return _duplicate( (CORBA::Repository_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/Repository:1.0" ) ) ) {
      _o = new CORBA::Repository_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::Repository_ptr
CORBA::Repository::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::Repository_stub::~Repository_stub()
{
}

CORBA::Contained_ptr CORBA::Repository_stub::lookup_id( const char* search_id )
{
  CORBA::StaticAny _search_id( CORBA::_stc_string, &search_id );
  CORBA::Contained_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );

  CORBA::StaticRequest __req( this, "lookup_id" );
  __req.add_in_arg( &_search_id );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::PrimitiveDef_ptr CORBA::Repository_stub::get_primitive( CORBA::PrimitiveKind kind )
{
  CORBA::StaticAny _kind( _marshaller_CORBA_PrimitiveKind, &kind );
  CORBA::PrimitiveDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_PrimitiveDef, &_res );

  CORBA::StaticRequest __req( this, "get_primitive" );
  __req.add_in_arg( &_kind );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::StringDef_ptr CORBA::Repository_stub::create_string( CORBA::ULong bound )
{
  CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );
  CORBA::StringDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_StringDef, &_res );

  CORBA::StaticRequest __req( this, "create_string" );
  __req.add_in_arg( &_bound );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::WstringDef_ptr CORBA::Repository_stub::create_wstring( CORBA::ULong bound )
{
  CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );
  CORBA::WstringDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_WstringDef, &_res );

  CORBA::StaticRequest __req( this, "create_wstring" );
  __req.add_in_arg( &_bound );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::SequenceDef_ptr CORBA::Repository_stub::create_sequence( CORBA::ULong bound, CORBA::IDLType_ptr element_type )
{
  CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );
  CORBA::StaticAny _element_type( _marshaller_CORBA_IDLType, &element_type );
  CORBA::SequenceDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_SequenceDef, &_res );

  CORBA::StaticRequest __req( this, "create_sequence" );
  __req.add_in_arg( &_bound );
  __req.add_in_arg( &_element_type );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ArrayDef_ptr CORBA::Repository_stub::create_array( CORBA::ULong length, CORBA::IDLType_ptr element_type )
{
  CORBA::StaticAny _length( CORBA::_stc_ulong, &length );
  CORBA::StaticAny _element_type( _marshaller_CORBA_IDLType, &element_type );
  CORBA::ArrayDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ArrayDef, &_res );

  CORBA::StaticRequest __req( this, "create_array" );
  __req.add_in_arg( &_length );
  __req.add_in_arg( &_element_type );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::FixedDef_ptr CORBA::Repository_stub::create_fixed( CORBA::UShort digits, CORBA::Short scale )
{
  CORBA::StaticAny _digits( CORBA::_stc_ushort, &digits );
  CORBA::StaticAny _scale( CORBA::_stc_short, &scale );
  CORBA::FixedDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_FixedDef, &_res );

  CORBA::StaticRequest __req( this, "create_fixed" );
  __req.add_in_arg( &_digits );
  __req.add_in_arg( &_scale );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


struct _global_init_CORBA_Repository {
  _global_init_CORBA_Repository()
  {
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::Repository::_narrow_helper2 );
  }
} __global_init_CORBA_Repository;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * Repository::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::Repository::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_Repository; };
#else
CORBA::TypeCodeConst CORBA::_tc_Repository;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::Repository_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Repository, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::Repository_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_Repository, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::Repository_ptr &_obj )
{
  CORBA::Repository_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_Repository, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_Repository : public CORBA::StaticTypeInfo {
    typedef CORBA::Repository_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_Repository::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_Repository::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::Repository::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_Repository::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_Repository::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::Repository::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_Repository::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_Repository::typecode()
{
  return CORBA::_tc_Repository;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_Repository;


// Stub interface ModuleDef
CORBA::ModuleDef::~ModuleDef()
{
}

void *CORBA::ModuleDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ModuleDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ModuleDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ModuleDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ModuleDef_ptr CORBA::ModuleDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ModuleDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ModuleDef:1.0" )))
      return _duplicate( (CORBA::ModuleDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ModuleDef:1.0" ) ) ) {
      _o = new CORBA::ModuleDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ModuleDef_ptr
CORBA::ModuleDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ModuleDef_stub::~ModuleDef_stub()
{
}

struct _global_init_CORBA_ModuleDef {
  _global_init_CORBA_ModuleDef()
  {
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::ModuleDef::_narrow_helper2 );
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::ModuleDef::_narrow_helper2 );
  }
} __global_init_CORBA_ModuleDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ModuleDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ModuleDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ModuleDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ModuleDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ModuleDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ModuleDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ModuleDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ModuleDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ModuleDef_ptr &_obj )
{
  CORBA::ModuleDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ModuleDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ModuleDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ModuleDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ModuleDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ModuleDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ModuleDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ModuleDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ModuleDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ModuleDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ModuleDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ModuleDef::typecode()
{
  return CORBA::_tc_ModuleDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ModuleDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ModuleDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_ModuleDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ModuleDescription::ModuleDescription()
{
}

CORBA::ModuleDescription::ModuleDescription( const ModuleDescription& _s )
{
  name = ((ModuleDescription&)_s).name;
  id = ((ModuleDescription&)_s).id;
  defined_in = ((ModuleDescription&)_s).defined_in;
  version = ((ModuleDescription&)_s).version;
}

CORBA::ModuleDescription::~ModuleDescription()
{
}

CORBA::ModuleDescription&
CORBA::ModuleDescription::operator=( const ModuleDescription& _s )
{
  name = ((ModuleDescription&)_s).name;
  id = ((ModuleDescription&)_s).id;
  defined_in = ((ModuleDescription&)_s).defined_in;
  version = ((ModuleDescription&)_s).version;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ModuleDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ModuleDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ModuleDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ModuleDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ModuleDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ModuleDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ModuleDescription, (void *&)_s);
}

class _Marshaller_CORBA_ModuleDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ModuleDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ModuleDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ModuleDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ModuleDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ModuleDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ModuleDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ModuleDescription::typecode()
{
  return CORBA::_tc_ModuleDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ModuleDescription;


// Stub interface ConstantDef
CORBA::ConstantDef::~ConstantDef()
{
}

void *CORBA::ConstantDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ConstantDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ConstantDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ConstantDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ConstantDef_ptr CORBA::ConstantDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ConstantDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ConstantDef:1.0" )))
      return _duplicate( (CORBA::ConstantDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ConstantDef:1.0" ) ) ) {
      _o = new CORBA::ConstantDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ConstantDef_ptr
CORBA::ConstantDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ConstantDef_stub::~ConstantDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::ConstantDef_stub::type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::ConstantDef_stub::type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ConstantDef_stub::type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Any* CORBA::ConstantDef_stub::value()
{
  CORBA::StaticAny __res( CORBA::_stc_any );

  CORBA::StaticRequest __req( this, "_get_value" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::Any*) __res._retn();
}


void CORBA::ConstantDef_stub::value( const CORBA::Any& _value )
{
  CORBA::StaticAny __value( CORBA::_stc_any, &_value );
  CORBA::StaticRequest __req( this, "_set_value" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_ConstantDef {
  _global_init_CORBA_ConstantDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::ConstantDef::_narrow_helper2 );
  }
} __global_init_CORBA_ConstantDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ConstantDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ConstantDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ConstantDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ConstantDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ConstantDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ConstantDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ConstantDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ConstantDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ConstantDef_ptr &_obj )
{
  CORBA::ConstantDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ConstantDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ConstantDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ConstantDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ConstantDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ConstantDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ConstantDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ConstantDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ConstantDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ConstantDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ConstantDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ConstantDef::typecode()
{
  return CORBA::_tc_ConstantDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ConstantDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ConstantDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_ConstantDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ConstantDescription::ConstantDescription()
{
}

CORBA::ConstantDescription::ConstantDescription( const ConstantDescription& _s )
{
  name = ((ConstantDescription&)_s).name;
  id = ((ConstantDescription&)_s).id;
  defined_in = ((ConstantDescription&)_s).defined_in;
  version = ((ConstantDescription&)_s).version;
  type = ((ConstantDescription&)_s).type;
  value = ((ConstantDescription&)_s).value;
}

CORBA::ConstantDescription::~ConstantDescription()
{
}

CORBA::ConstantDescription&
CORBA::ConstantDescription::operator=( const ConstantDescription& _s )
{
  name = ((ConstantDescription&)_s).name;
  id = ((ConstantDescription&)_s).id;
  defined_in = ((ConstantDescription&)_s).defined_in;
  version = ((ConstantDescription&)_s).version;
  type = ((ConstantDescription&)_s).type;
  value = ((ConstantDescription&)_s).value;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ConstantDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ConstantDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ConstantDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ConstantDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ConstantDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ConstantDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ConstantDescription, (void *&)_s);
}

class _Marshaller_CORBA_ConstantDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ConstantDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ConstantDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ConstantDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ConstantDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ConstantDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    CORBA::_stc_any->demarshal( dc, &((_MICO_T*)v)->value ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ConstantDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  CORBA::_stc_any->marshal( ec, &((_MICO_T*)v)->value );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ConstantDescription::typecode()
{
  return CORBA::_tc_ConstantDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ConstantDescription;


// Stub interface TypedefDef
CORBA::TypedefDef::~TypedefDef()
{
}

void *CORBA::TypedefDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/TypedefDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::TypedefDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/TypedefDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::TypedefDef_ptr CORBA::TypedefDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::TypedefDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/TypedefDef:1.0" )))
      return _duplicate( (CORBA::TypedefDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/TypedefDef:1.0" ) ) ) {
      _o = new CORBA::TypedefDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::TypedefDef_ptr
CORBA::TypedefDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::TypedefDef_stub::~TypedefDef_stub()
{
}

struct _global_init_CORBA_TypedefDef {
  _global_init_CORBA_TypedefDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::TypedefDef::_narrow_helper2 );
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::TypedefDef::_narrow_helper2 );
  }
} __global_init_CORBA_TypedefDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * TypedefDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::TypedefDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_TypedefDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_TypedefDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::TypedefDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_TypedefDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::TypedefDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_TypedefDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::TypedefDef_ptr &_obj )
{
  CORBA::TypedefDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_TypedefDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_TypedefDef : public CORBA::StaticTypeInfo {
    typedef CORBA::TypedefDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_TypedefDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_TypedefDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::TypedefDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_TypedefDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_TypedefDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::TypedefDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_TypedefDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_TypedefDef::typecode()
{
  return CORBA::_tc_TypedefDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_TypedefDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_TypeDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_TypeDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::TypeDescription::TypeDescription()
{
}

CORBA::TypeDescription::TypeDescription( const TypeDescription& _s )
{
  name = ((TypeDescription&)_s).name;
  id = ((TypeDescription&)_s).id;
  defined_in = ((TypeDescription&)_s).defined_in;
  version = ((TypeDescription&)_s).version;
  type = ((TypeDescription&)_s).type;
}

CORBA::TypeDescription::~TypeDescription()
{
}

CORBA::TypeDescription&
CORBA::TypeDescription::operator=( const TypeDescription& _s )
{
  name = ((TypeDescription&)_s).name;
  id = ((TypeDescription&)_s).id;
  defined_in = ((TypeDescription&)_s).defined_in;
  version = ((TypeDescription&)_s).version;
  type = ((TypeDescription&)_s).type;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::TypeDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_TypeDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::TypeDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::TypeDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_TypeDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::TypeDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_TypeDescription, (void *&)_s);
}

class _Marshaller_CORBA_TypeDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::TypeDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_TypeDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_TypeDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_TypeDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_TypeDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_TypeDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_TypeDescription::typecode()
{
  return CORBA::_tc_TypeDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_TypeDescription;


// Stub interface StructDef
CORBA::StructDef::~StructDef()
{
}

void *CORBA::StructDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/StructDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::StructDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/StructDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::StructDef_ptr CORBA::StructDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::StructDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/StructDef:1.0" )))
      return _duplicate( (CORBA::StructDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/StructDef:1.0" ) ) ) {
      _o = new CORBA::StructDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::StructDef_ptr
CORBA::StructDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::StructDef_stub::~StructDef_stub()
{
}

CORBA::StructMemberSeq* CORBA::StructDef_stub::members()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_StructMember );

  CORBA::StaticRequest __req( this, "_get_members" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::StructMemberSeq*) __res._retn();
}


void CORBA::StructDef_stub::members( const CORBA::StructMemberSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_StructMember, &_value );
  CORBA::StaticRequest __req( this, "_set_members" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_StructDef {
  _global_init_CORBA_StructDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::StructDef::_narrow_helper2 );
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::StructDef::_narrow_helper2 );
  }
} __global_init_CORBA_StructDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * StructDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::StructDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_StructDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_StructDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::StructDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StructDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::StructDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StructDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::StructDef_ptr &_obj )
{
  CORBA::StructDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_StructDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_StructDef : public CORBA::StaticTypeInfo {
    typedef CORBA::StructDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_StructDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_StructDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::StructDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_StructDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_StructDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::StructDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_StructDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_StructDef::typecode()
{
  return CORBA::_tc_StructDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_StructDef;


// Stub interface UnionDef
CORBA::UnionDef::~UnionDef()
{
}

void *CORBA::UnionDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/UnionDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::UnionDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/UnionDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::UnionDef_ptr CORBA::UnionDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::UnionDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/UnionDef:1.0" )))
      return _duplicate( (CORBA::UnionDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/UnionDef:1.0" ) ) ) {
      _o = new CORBA::UnionDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::UnionDef_ptr
CORBA::UnionDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::UnionDef_stub::~UnionDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::UnionDef_stub::discriminator_type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_discriminator_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::UnionDef_stub::discriminator_type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_discriminator_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::UnionDef_stub::discriminator_type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_discriminator_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::UnionMemberSeq* CORBA::UnionDef_stub::members()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_UnionMember );

  CORBA::StaticRequest __req( this, "_get_members" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::UnionMemberSeq*) __res._retn();
}


void CORBA::UnionDef_stub::members( const CORBA::UnionMemberSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_UnionMember, &_value );
  CORBA::StaticRequest __req( this, "_set_members" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_UnionDef {
  _global_init_CORBA_UnionDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::UnionDef::_narrow_helper2 );
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::UnionDef::_narrow_helper2 );
  }
} __global_init_CORBA_UnionDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * UnionDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::UnionDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_UnionDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_UnionDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::UnionDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_UnionDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::UnionDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_UnionDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::UnionDef_ptr &_obj )
{
  CORBA::UnionDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_UnionDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_UnionDef : public CORBA::StaticTypeInfo {
    typedef CORBA::UnionDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_UnionDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_UnionDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::UnionDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_UnionDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_UnionDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::UnionDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_UnionDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_UnionDef::typecode()
{
  return CORBA::_tc_UnionDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_UnionDef;


// Stub interface EnumDef
CORBA::EnumDef::~EnumDef()
{
}

void *CORBA::EnumDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/EnumDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::EnumDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/EnumDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::EnumDef_ptr CORBA::EnumDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::EnumDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/EnumDef:1.0" )))
      return _duplicate( (CORBA::EnumDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/EnumDef:1.0" ) ) ) {
      _o = new CORBA::EnumDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::EnumDef_ptr
CORBA::EnumDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::EnumDef_stub::~EnumDef_stub()
{
}

CORBA::EnumMemberSeq* CORBA::EnumDef_stub::members()
{
  CORBA::StaticAny __res( CORBA::_stcseq_string );

  CORBA::StaticRequest __req( this, "_get_members" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::EnumMemberSeq*) __res._retn();
}


void CORBA::EnumDef_stub::members( const CORBA::EnumMemberSeq& _value )
{
  CORBA::StaticAny __value( CORBA::_stcseq_string, &_value );
  CORBA::StaticRequest __req( this, "_set_members" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_EnumDef {
  _global_init_CORBA_EnumDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::EnumDef::_narrow_helper2 );
  }
} __global_init_CORBA_EnumDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * EnumDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::EnumDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_EnumDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_EnumDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::EnumDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_EnumDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::EnumDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_EnumDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::EnumDef_ptr &_obj )
{
  CORBA::EnumDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_EnumDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_EnumDef : public CORBA::StaticTypeInfo {
    typedef CORBA::EnumDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_EnumDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_EnumDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::EnumDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_EnumDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_EnumDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::EnumDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_EnumDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_EnumDef::typecode()
{
  return CORBA::_tc_EnumDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_EnumDef;


// Stub interface AliasDef
CORBA::AliasDef::~AliasDef()
{
}

void *CORBA::AliasDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/AliasDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::AliasDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/AliasDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::AliasDef_ptr CORBA::AliasDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::AliasDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/AliasDef:1.0" )))
      return _duplicate( (CORBA::AliasDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/AliasDef:1.0" ) ) ) {
      _o = new CORBA::AliasDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::AliasDef_ptr
CORBA::AliasDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::AliasDef_stub::~AliasDef_stub()
{
}

CORBA::IDLType_ptr CORBA::AliasDef_stub::original_type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_original_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::AliasDef_stub::original_type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_original_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_AliasDef {
  _global_init_CORBA_AliasDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::AliasDef::_narrow_helper2 );
  }
} __global_init_CORBA_AliasDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * AliasDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::AliasDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_AliasDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_AliasDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::AliasDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AliasDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::AliasDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AliasDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::AliasDef_ptr &_obj )
{
  CORBA::AliasDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_AliasDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_AliasDef : public CORBA::StaticTypeInfo {
    typedef CORBA::AliasDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_AliasDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_AliasDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::AliasDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_AliasDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_AliasDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::AliasDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_AliasDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_AliasDef::typecode()
{
  return CORBA::_tc_AliasDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_AliasDef;


// Stub interface NativeDef
CORBA::NativeDef::~NativeDef()
{
}

void *CORBA::NativeDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/NativeDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::NativeDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/NativeDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::NativeDef_ptr CORBA::NativeDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::NativeDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/NativeDef:1.0" )))
      return _duplicate( (CORBA::NativeDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/NativeDef:1.0" ) ) ) {
      _o = new CORBA::NativeDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::NativeDef_ptr
CORBA::NativeDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::NativeDef_stub::~NativeDef_stub()
{
}

struct _global_init_CORBA_NativeDef {
  _global_init_CORBA_NativeDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::NativeDef::_narrow_helper2 );
  }
} __global_init_CORBA_NativeDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * NativeDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::NativeDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_NativeDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_NativeDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::NativeDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_NativeDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::NativeDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_NativeDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::NativeDef_ptr &_obj )
{
  CORBA::NativeDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_NativeDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_NativeDef : public CORBA::StaticTypeInfo {
    typedef CORBA::NativeDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_NativeDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_NativeDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::NativeDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_NativeDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_NativeDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::NativeDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_NativeDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_NativeDef::typecode()
{
  return CORBA::_tc_NativeDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_NativeDef;


// Stub interface PrimitiveDef
CORBA::PrimitiveDef::~PrimitiveDef()
{
}

void *CORBA::PrimitiveDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/PrimitiveDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::PrimitiveDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/PrimitiveDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::PrimitiveDef_ptr CORBA::PrimitiveDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::PrimitiveDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/PrimitiveDef:1.0" )))
      return _duplicate( (CORBA::PrimitiveDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/PrimitiveDef:1.0" ) ) ) {
      _o = new CORBA::PrimitiveDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::PrimitiveDef_ptr
CORBA::PrimitiveDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::PrimitiveDef_stub::~PrimitiveDef_stub()
{
}

CORBA::PrimitiveKind CORBA::PrimitiveDef_stub::kind()
{
  CORBA::PrimitiveKind _res;
  CORBA::StaticAny __res( _marshaller_CORBA_PrimitiveKind, &_res );

  CORBA::StaticRequest __req( this, "_get_kind" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


struct _global_init_CORBA_PrimitiveDef {
  _global_init_CORBA_PrimitiveDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::PrimitiveDef::_narrow_helper2 );
  }
} __global_init_CORBA_PrimitiveDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * PrimitiveDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::PrimitiveDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_PrimitiveDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_PrimitiveDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::PrimitiveDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_PrimitiveDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::PrimitiveDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_PrimitiveDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::PrimitiveDef_ptr &_obj )
{
  CORBA::PrimitiveDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_PrimitiveDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_PrimitiveDef : public CORBA::StaticTypeInfo {
    typedef CORBA::PrimitiveDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_PrimitiveDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_PrimitiveDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::PrimitiveDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_PrimitiveDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_PrimitiveDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::PrimitiveDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_PrimitiveDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_PrimitiveDef::typecode()
{
  return CORBA::_tc_PrimitiveDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_PrimitiveDef;


// Stub interface StringDef
CORBA::StringDef::~StringDef()
{
}

void *CORBA::StringDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/StringDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::StringDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/StringDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::StringDef_ptr CORBA::StringDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::StringDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/StringDef:1.0" )))
      return _duplicate( (CORBA::StringDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/StringDef:1.0" ) ) ) {
      _o = new CORBA::StringDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::StringDef_ptr
CORBA::StringDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::StringDef_stub::~StringDef_stub()
{
}

CORBA::ULong CORBA::StringDef_stub::bound()
{
  CORBA::ULong _res;
  CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );

  CORBA::StaticRequest __req( this, "_get_bound" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::StringDef_stub::bound( CORBA::ULong _value )
{
  CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );
  CORBA::StaticRequest __req( this, "_set_bound" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_StringDef {
  _global_init_CORBA_StringDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::StringDef::_narrow_helper2 );
  }
} __global_init_CORBA_StringDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * StringDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::StringDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_StringDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_StringDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::StringDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StringDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::StringDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StringDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::StringDef_ptr &_obj )
{
  CORBA::StringDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_StringDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_StringDef : public CORBA::StaticTypeInfo {
    typedef CORBA::StringDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_StringDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_StringDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::StringDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_StringDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_StringDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::StringDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_StringDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_StringDef::typecode()
{
  return CORBA::_tc_StringDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_StringDef;


// Stub interface WstringDef
CORBA::WstringDef::~WstringDef()
{
}

void *CORBA::WstringDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/WstringDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::WstringDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/WstringDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::WstringDef_ptr CORBA::WstringDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::WstringDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/WstringDef:1.0" )))
      return _duplicate( (CORBA::WstringDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/WstringDef:1.0" ) ) ) {
      _o = new CORBA::WstringDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::WstringDef_ptr
CORBA::WstringDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::WstringDef_stub::~WstringDef_stub()
{
}

CORBA::ULong CORBA::WstringDef_stub::bound()
{
  CORBA::ULong _res;
  CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );

  CORBA::StaticRequest __req( this, "_get_bound" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::WstringDef_stub::bound( CORBA::ULong _value )
{
  CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );
  CORBA::StaticRequest __req( this, "_set_bound" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_WstringDef {
  _global_init_CORBA_WstringDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::WstringDef::_narrow_helper2 );
  }
} __global_init_CORBA_WstringDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * WstringDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::WstringDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_WstringDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_WstringDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::WstringDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_WstringDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::WstringDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_WstringDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::WstringDef_ptr &_obj )
{
  CORBA::WstringDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_WstringDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_WstringDef : public CORBA::StaticTypeInfo {
    typedef CORBA::WstringDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_WstringDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_WstringDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::WstringDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_WstringDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_WstringDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::WstringDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_WstringDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_WstringDef::typecode()
{
  return CORBA::_tc_WstringDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_WstringDef;


// Stub interface FixedDef
CORBA::FixedDef::~FixedDef()
{
}

void *CORBA::FixedDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/FixedDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::FixedDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/FixedDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::FixedDef_ptr CORBA::FixedDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::FixedDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/FixedDef:1.0" )))
      return _duplicate( (CORBA::FixedDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/FixedDef:1.0" ) ) ) {
      _o = new CORBA::FixedDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::FixedDef_ptr
CORBA::FixedDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::FixedDef_stub::~FixedDef_stub()
{
}

CORBA::UShort CORBA::FixedDef_stub::digits()
{
  CORBA::UShort _res;
  CORBA::StaticAny __res( CORBA::_stc_ushort, &_res );

  CORBA::StaticRequest __req( this, "_get_digits" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::FixedDef_stub::digits( CORBA::UShort _value )
{
  CORBA::StaticAny __value( CORBA::_stc_ushort, &_value );
  CORBA::StaticRequest __req( this, "_set_digits" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Short CORBA::FixedDef_stub::scale()
{
  CORBA::Short _res;
  CORBA::StaticAny __res( CORBA::_stc_short, &_res );

  CORBA::StaticRequest __req( this, "_get_scale" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::FixedDef_stub::scale( CORBA::Short _value )
{
  CORBA::StaticAny __value( CORBA::_stc_short, &_value );
  CORBA::StaticRequest __req( this, "_set_scale" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_FixedDef {
  _global_init_CORBA_FixedDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::FixedDef::_narrow_helper2 );
  }
} __global_init_CORBA_FixedDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * FixedDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::FixedDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_FixedDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_FixedDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::FixedDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_FixedDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::FixedDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_FixedDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::FixedDef_ptr &_obj )
{
  CORBA::FixedDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_FixedDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_FixedDef : public CORBA::StaticTypeInfo {
    typedef CORBA::FixedDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_FixedDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_FixedDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::FixedDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_FixedDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_FixedDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::FixedDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_FixedDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_FixedDef::typecode()
{
  return CORBA::_tc_FixedDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_FixedDef;


// Stub interface SequenceDef
CORBA::SequenceDef::~SequenceDef()
{
}

void *CORBA::SequenceDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/SequenceDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::SequenceDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/SequenceDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::SequenceDef_ptr CORBA::SequenceDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::SequenceDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/SequenceDef:1.0" )))
      return _duplicate( (CORBA::SequenceDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/SequenceDef:1.0" ) ) ) {
      _o = new CORBA::SequenceDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::SequenceDef_ptr
CORBA::SequenceDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::SequenceDef_stub::~SequenceDef_stub()
{
}

CORBA::ULong CORBA::SequenceDef_stub::bound()
{
  CORBA::ULong _res;
  CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );

  CORBA::StaticRequest __req( this, "_get_bound" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::SequenceDef_stub::bound( CORBA::ULong _value )
{
  CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );
  CORBA::StaticRequest __req( this, "_set_bound" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::TypeCode_ptr CORBA::SequenceDef_stub::element_type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_element_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::SequenceDef_stub::element_type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_element_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::SequenceDef_stub::element_type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_element_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_SequenceDef {
  _global_init_CORBA_SequenceDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::SequenceDef::_narrow_helper2 );
  }
} __global_init_CORBA_SequenceDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * SequenceDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::SequenceDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_SequenceDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_SequenceDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::SequenceDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_SequenceDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::SequenceDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_SequenceDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::SequenceDef_ptr &_obj )
{
  CORBA::SequenceDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_SequenceDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_SequenceDef : public CORBA::StaticTypeInfo {
    typedef CORBA::SequenceDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_SequenceDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_SequenceDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::SequenceDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_SequenceDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_SequenceDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::SequenceDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_SequenceDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_SequenceDef::typecode()
{
  return CORBA::_tc_SequenceDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_SequenceDef;


// Stub interface ArrayDef
CORBA::ArrayDef::~ArrayDef()
{
}

void *CORBA::ArrayDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ArrayDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ArrayDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ArrayDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ArrayDef_ptr CORBA::ArrayDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ArrayDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ArrayDef:1.0" )))
      return _duplicate( (CORBA::ArrayDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ArrayDef:1.0" ) ) ) {
      _o = new CORBA::ArrayDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ArrayDef_ptr
CORBA::ArrayDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ArrayDef_stub::~ArrayDef_stub()
{
}

CORBA::ULong CORBA::ArrayDef_stub::length()
{
  CORBA::ULong _res;
  CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );

  CORBA::StaticRequest __req( this, "_get_length" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ArrayDef_stub::length( CORBA::ULong _value )
{
  CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );
  CORBA::StaticRequest __req( this, "_set_length" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::TypeCode_ptr CORBA::ArrayDef_stub::element_type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_element_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::ArrayDef_stub::element_type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_element_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ArrayDef_stub::element_type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_element_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_ArrayDef {
  _global_init_CORBA_ArrayDef()
  {
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::ArrayDef::_narrow_helper2 );
  }
} __global_init_CORBA_ArrayDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ArrayDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ArrayDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ArrayDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ArrayDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ArrayDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ArrayDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ArrayDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ArrayDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ArrayDef_ptr &_obj )
{
  CORBA::ArrayDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ArrayDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ArrayDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ArrayDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ArrayDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ArrayDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ArrayDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ArrayDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ArrayDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ArrayDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ArrayDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ArrayDef::typecode()
{
  return CORBA::_tc_ArrayDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ArrayDef;


// Stub interface ExceptionDef
CORBA::ExceptionDef::~ExceptionDef()
{
}

void *CORBA::ExceptionDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ExceptionDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ExceptionDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ExceptionDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ExceptionDef_ptr CORBA::ExceptionDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ExceptionDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ExceptionDef:1.0" )))
      return _duplicate( (CORBA::ExceptionDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ExceptionDef:1.0" ) ) ) {
      _o = new CORBA::ExceptionDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ExceptionDef_ptr
CORBA::ExceptionDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ExceptionDef_stub::~ExceptionDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::ExceptionDef_stub::type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::StructMemberSeq* CORBA::ExceptionDef_stub::members()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_StructMember );

  CORBA::StaticRequest __req( this, "_get_members" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::StructMemberSeq*) __res._retn();
}


void CORBA::ExceptionDef_stub::members( const CORBA::StructMemberSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_StructMember, &_value );
  CORBA::StaticRequest __req( this, "_set_members" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_ExceptionDef {
  _global_init_CORBA_ExceptionDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::ExceptionDef::_narrow_helper2 );
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::ExceptionDef::_narrow_helper2 );
  }
} __global_init_CORBA_ExceptionDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ExceptionDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ExceptionDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ExceptionDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ExceptionDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ExceptionDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ExceptionDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ExceptionDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ExceptionDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ExceptionDef_ptr &_obj )
{
  CORBA::ExceptionDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ExceptionDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ExceptionDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ExceptionDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ExceptionDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ExceptionDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ExceptionDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ExceptionDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ExceptionDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ExceptionDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ExceptionDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ExceptionDef::typecode()
{
  return CORBA::_tc_ExceptionDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ExceptionDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ExceptionDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_ExceptionDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ExceptionDescription::ExceptionDescription()
{
}

CORBA::ExceptionDescription::ExceptionDescription( const ExceptionDescription& _s )
{
  name = ((ExceptionDescription&)_s).name;
  id = ((ExceptionDescription&)_s).id;
  defined_in = ((ExceptionDescription&)_s).defined_in;
  version = ((ExceptionDescription&)_s).version;
  type = ((ExceptionDescription&)_s).type;
}

CORBA::ExceptionDescription::~ExceptionDescription()
{
}

CORBA::ExceptionDescription&
CORBA::ExceptionDescription::operator=( const ExceptionDescription& _s )
{
  name = ((ExceptionDescription&)_s).name;
  id = ((ExceptionDescription&)_s).id;
  defined_in = ((ExceptionDescription&)_s).defined_in;
  version = ((ExceptionDescription&)_s).version;
  type = ((ExceptionDescription&)_s).type;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ExceptionDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ExceptionDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ExceptionDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ExceptionDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ExceptionDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ExceptionDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ExceptionDescription, (void *&)_s);
}

class _Marshaller_CORBA_ExceptionDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ExceptionDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ExceptionDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ExceptionDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ExceptionDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ExceptionDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ExceptionDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ExceptionDescription::typecode()
{
  return CORBA::_tc_ExceptionDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ExceptionDescription;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_AttributeMode; };
#else
CORBA::TypeCodeConst CORBA::_tc_AttributeMode;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::AttributeMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeMode, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::AttributeMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeMode, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_AttributeMode : public CORBA::StaticTypeInfo {
    typedef CORBA::AttributeMode _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_AttributeMode::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_AttributeMode::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_AttributeMode::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_AttributeMode::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_AttributeMode::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_AttributeMode::typecode()
{
  return CORBA::_tc_AttributeMode;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeMode;


// Stub interface AttributeDef
CORBA::AttributeDef::~AttributeDef()
{
}

void *CORBA::AttributeDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/AttributeDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::AttributeDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/AttributeDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::AttributeDef_ptr CORBA::AttributeDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::AttributeDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/AttributeDef:1.0" )))
      return _duplicate( (CORBA::AttributeDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/AttributeDef:1.0" ) ) ) {
      _o = new CORBA::AttributeDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::AttributeDef_ptr
CORBA::AttributeDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::AttributeDef_stub::~AttributeDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::AttributeDef_stub::type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::AttributeDef_stub::type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::AttributeDef_stub::type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::AttributeMode CORBA::AttributeDef_stub::mode()
{
  CORBA::AttributeMode _res;
  CORBA::StaticAny __res( _marshaller_CORBA_AttributeMode, &_res );

  CORBA::StaticRequest __req( this, "_get_mode" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::AttributeDef_stub::mode( CORBA::AttributeMode _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_AttributeMode, &_value );
  CORBA::StaticRequest __req( this, "_set_mode" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_AttributeDef {
  _global_init_CORBA_AttributeDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::AttributeDef::_narrow_helper2 );
  }
} __global_init_CORBA_AttributeDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * AttributeDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::AttributeDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_AttributeDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_AttributeDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::AttributeDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::AttributeDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::AttributeDef_ptr &_obj )
{
  CORBA::AttributeDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_AttributeDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_AttributeDef : public CORBA::StaticTypeInfo {
    typedef CORBA::AttributeDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_AttributeDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_AttributeDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::AttributeDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_AttributeDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_AttributeDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::AttributeDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_AttributeDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_AttributeDef::typecode()
{
  return CORBA::_tc_AttributeDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_AttributeDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_AttributeDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::AttributeDescription::AttributeDescription()
{
}

CORBA::AttributeDescription::AttributeDescription( const AttributeDescription& _s )
{
  name = ((AttributeDescription&)_s).name;
  id = ((AttributeDescription&)_s).id;
  defined_in = ((AttributeDescription&)_s).defined_in;
  version = ((AttributeDescription&)_s).version;
  type = ((AttributeDescription&)_s).type;
  mode = ((AttributeDescription&)_s).mode;
}

CORBA::AttributeDescription::~AttributeDescription()
{
}

CORBA::AttributeDescription&
CORBA::AttributeDescription::operator=( const AttributeDescription& _s )
{
  name = ((AttributeDescription&)_s).name;
  id = ((AttributeDescription&)_s).id;
  defined_in = ((AttributeDescription&)_s).defined_in;
  version = ((AttributeDescription&)_s).version;
  type = ((AttributeDescription&)_s).type;
  mode = ((AttributeDescription&)_s).mode;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::AttributeDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::AttributeDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::AttributeDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_AttributeDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::AttributeDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_AttributeDescription, (void *&)_s);
}

class _Marshaller_CORBA_AttributeDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::AttributeDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_AttributeDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_AttributeDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_AttributeDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_AttributeDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    _marshaller_CORBA_AttributeMode->demarshal( dc, &((_MICO_T*)v)->mode ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_AttributeDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  _marshaller_CORBA_AttributeMode->marshal( ec, &((_MICO_T*)v)->mode );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_AttributeDescription::typecode()
{
  return CORBA::_tc_AttributeDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeDescription;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OperationMode; };
#else
CORBA::TypeCodeConst CORBA::_tc_OperationMode;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::OperationMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationMode, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::OperationMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationMode, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_OperationMode : public CORBA::StaticTypeInfo {
    typedef CORBA::OperationMode _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_OperationMode::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_OperationMode::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_OperationMode::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_OperationMode::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_OperationMode::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_OperationMode::typecode()
{
  return CORBA::_tc_OperationMode;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_OperationMode;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ParameterMode; };
#else
CORBA::TypeCodeConst CORBA::_tc_ParameterMode;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ParameterMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ParameterMode, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ParameterMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ParameterMode, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_ParameterMode : public CORBA::StaticTypeInfo {
    typedef CORBA::ParameterMode _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ParameterMode::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ParameterMode::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ParameterMode::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ParameterMode::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_ParameterMode::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ParameterMode::typecode()
{
  return CORBA::_tc_ParameterMode;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ParameterMode;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ParameterDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_ParameterDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ParameterDescription::ParameterDescription()
{
}

CORBA::ParameterDescription::ParameterDescription( const ParameterDescription& _s )
{
  name = ((ParameterDescription&)_s).name;
  type = ((ParameterDescription&)_s).type;
  type_def = ((ParameterDescription&)_s).type_def;
  mode = ((ParameterDescription&)_s).mode;
}

CORBA::ParameterDescription::~ParameterDescription()
{
}

CORBA::ParameterDescription&
CORBA::ParameterDescription::operator=( const ParameterDescription& _s )
{
  name = ((ParameterDescription&)_s).name;
  type = ((ParameterDescription&)_s).type;
  type_def = ((ParameterDescription&)_s).type_def;
  mode = ((ParameterDescription&)_s).mode;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ParameterDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ParameterDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ParameterDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ParameterDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ParameterDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ParameterDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ParameterDescription, (void *&)_s);
}

class _Marshaller_CORBA_ParameterDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ParameterDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ParameterDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ParameterDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ParameterDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ParameterDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    _marshaller_CORBA_IDLType->demarshal( dc, &((_MICO_T*)v)->type_def.inout() ) &&
    _marshaller_CORBA_ParameterMode->demarshal( dc, &((_MICO_T*)v)->mode ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ParameterDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  _marshaller_CORBA_IDLType->marshal( ec, &((_MICO_T*)v)->type_def.inout() );
  _marshaller_CORBA_ParameterMode->marshal( ec, &((_MICO_T*)v)->mode );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ParameterDescription::typecode()
{
  return CORBA::_tc_ParameterDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ParameterDescription;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ParDescriptionSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ParDescriptionSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ContextIdentifier; };
#else
CORBA::TypeCodeConst CORBA::_tc_ContextIdentifier;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ContextIdSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ContextIdSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ExceptionDefSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ExceptionDefSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ExcDescriptionSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ExcDescriptionSeq;
#endif


// Stub interface OperationDef
CORBA::OperationDef::~OperationDef()
{
}

void *CORBA::OperationDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/OperationDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::OperationDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/OperationDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::OperationDef_ptr CORBA::OperationDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::OperationDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/OperationDef:1.0" )))
      return _duplicate( (CORBA::OperationDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/OperationDef:1.0" ) ) ) {
      _o = new CORBA::OperationDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::OperationDef_ptr
CORBA::OperationDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::OperationDef_stub::~OperationDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::OperationDef_stub::result()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_result" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::OperationDef_stub::result_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_result_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::OperationDef_stub::result_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_result_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ParDescriptionSeq* CORBA::OperationDef_stub::params()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ParameterDescription );

  CORBA::StaticRequest __req( this, "_get_params" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ParDescriptionSeq*) __res._retn();
}


void CORBA::OperationDef_stub::params( const CORBA::ParDescriptionSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_ParameterDescription, &_value );
  CORBA::StaticRequest __req( this, "_set_params" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::OperationMode CORBA::OperationDef_stub::mode()
{
  CORBA::OperationMode _res;
  CORBA::StaticAny __res( _marshaller_CORBA_OperationMode, &_res );

  CORBA::StaticRequest __req( this, "_get_mode" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::OperationDef_stub::mode( CORBA::OperationMode _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_OperationMode, &_value );
  CORBA::StaticRequest __req( this, "_set_mode" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ContextIdSeq* CORBA::OperationDef_stub::contexts()
{
  CORBA::StaticAny __res( CORBA::_stcseq_string );

  CORBA::StaticRequest __req( this, "_get_contexts" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ContextIdSeq*) __res._retn();
}


void CORBA::OperationDef_stub::contexts( const CORBA::ContextIdSeq& _value )
{
  CORBA::StaticAny __value( CORBA::_stcseq_string, &_value );
  CORBA::StaticRequest __req( this, "_set_contexts" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ExceptionDefSeq* CORBA::OperationDef_stub::exceptions()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ExceptionDef );

  CORBA::StaticRequest __req( this, "_get_exceptions" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ExceptionDefSeq*) __res._retn();
}


void CORBA::OperationDef_stub::exceptions( const CORBA::ExceptionDefSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_ExceptionDef, &_value );
  CORBA::StaticRequest __req( this, "_set_exceptions" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_OperationDef {
  _global_init_CORBA_OperationDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::OperationDef::_narrow_helper2 );
  }
} __global_init_CORBA_OperationDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * OperationDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::OperationDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OperationDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_OperationDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::OperationDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::OperationDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::OperationDef_ptr &_obj )
{
  CORBA::OperationDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_OperationDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_OperationDef : public CORBA::StaticTypeInfo {
    typedef CORBA::OperationDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_OperationDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_OperationDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::OperationDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_OperationDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_OperationDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::OperationDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_OperationDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_OperationDef::typecode()
{
  return CORBA::_tc_OperationDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_OperationDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OperationDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_OperationDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::OperationDescription::OperationDescription()
{
}

CORBA::OperationDescription::OperationDescription( const OperationDescription& _s )
{
  name = ((OperationDescription&)_s).name;
  id = ((OperationDescription&)_s).id;
  defined_in = ((OperationDescription&)_s).defined_in;
  version = ((OperationDescription&)_s).version;
  result = ((OperationDescription&)_s).result;
  mode = ((OperationDescription&)_s).mode;
  contexts = ((OperationDescription&)_s).contexts;
  parameters = ((OperationDescription&)_s).parameters;
  exceptions = ((OperationDescription&)_s).exceptions;
}

CORBA::OperationDescription::~OperationDescription()
{
}

CORBA::OperationDescription&
CORBA::OperationDescription::operator=( const OperationDescription& _s )
{
  name = ((OperationDescription&)_s).name;
  id = ((OperationDescription&)_s).id;
  defined_in = ((OperationDescription&)_s).defined_in;
  version = ((OperationDescription&)_s).version;
  result = ((OperationDescription&)_s).result;
  mode = ((OperationDescription&)_s).mode;
  contexts = ((OperationDescription&)_s).contexts;
  parameters = ((OperationDescription&)_s).parameters;
  exceptions = ((OperationDescription&)_s).exceptions;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::OperationDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::OperationDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::OperationDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OperationDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::OperationDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_OperationDescription, (void *&)_s);
}

class _Marshaller_CORBA_OperationDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::OperationDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_OperationDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_OperationDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_OperationDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_OperationDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->result.inout() ) &&
    _marshaller_CORBA_OperationMode->demarshal( dc, &((_MICO_T*)v)->mode ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->contexts ) &&
    _marshaller__seq_CORBA_ParameterDescription->demarshal( dc, &((_MICO_T*)v)->parameters ) &&
    _marshaller__seq_CORBA_ExceptionDescription->demarshal( dc, &((_MICO_T*)v)->exceptions ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_OperationDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->result.inout() );
  _marshaller_CORBA_OperationMode->marshal( ec, &((_MICO_T*)v)->mode );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->contexts );
  _marshaller__seq_CORBA_ParameterDescription->marshal( ec, &((_MICO_T*)v)->parameters );
  _marshaller__seq_CORBA_ExceptionDescription->marshal( ec, &((_MICO_T*)v)->exceptions );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_OperationDescription::typecode()
{
  return CORBA::_tc_OperationDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_OperationDescription;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_RepositoryIdSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_RepositoryIdSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OpDescriptionSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_OpDescriptionSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_AttrDescriptionSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_AttrDescriptionSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst InterfaceDef::_tc_FullInterfaceDescription; };
#else
CORBA::TypeCodeConst CORBA::InterfaceDef::_tc_FullInterfaceDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::InterfaceDef::FullInterfaceDescription::FullInterfaceDescription()
{
}

CORBA::InterfaceDef::FullInterfaceDescription::FullInterfaceDescription( const FullInterfaceDescription& _s )
{
  name = ((FullInterfaceDescription&)_s).name;
  id = ((FullInterfaceDescription&)_s).id;
  defined_in = ((FullInterfaceDescription&)_s).defined_in;
  version = ((FullInterfaceDescription&)_s).version;
  operations = ((FullInterfaceDescription&)_s).operations;
  attributes = ((FullInterfaceDescription&)_s).attributes;
  base_interfaces = ((FullInterfaceDescription&)_s).base_interfaces;
  type = ((FullInterfaceDescription&)_s).type;
  is_abstract = ((FullInterfaceDescription&)_s).is_abstract;
}

CORBA::InterfaceDef::FullInterfaceDescription::~FullInterfaceDescription()
{
}

CORBA::InterfaceDef::FullInterfaceDescription&
CORBA::InterfaceDef::FullInterfaceDescription::operator=( const FullInterfaceDescription& _s )
{
  name = ((FullInterfaceDescription&)_s).name;
  id = ((FullInterfaceDescription&)_s).id;
  defined_in = ((FullInterfaceDescription&)_s).defined_in;
  version = ((FullInterfaceDescription&)_s).version;
  operations = ((FullInterfaceDescription&)_s).operations;
  attributes = ((FullInterfaceDescription&)_s).attributes;
  base_interfaces = ((FullInterfaceDescription&)_s).base_interfaces;
  type = ((FullInterfaceDescription&)_s).type;
  is_abstract = ((FullInterfaceDescription&)_s).is_abstract;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::InterfaceDef::FullInterfaceDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDef_FullInterfaceDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::InterfaceDef::FullInterfaceDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::InterfaceDef::FullInterfaceDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDef_FullInterfaceDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::InterfaceDef::FullInterfaceDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_InterfaceDef_FullInterfaceDescription, (void *&)_s);
}

class _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::InterfaceDef::FullInterfaceDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    _marshaller__seq_CORBA_OperationDescription->demarshal( dc, &((_MICO_T*)v)->operations ) &&
    _marshaller__seq_CORBA_AttributeDescription->demarshal( dc, &((_MICO_T*)v)->attributes ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->base_interfaces ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_abstract ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  _marshaller__seq_CORBA_OperationDescription->marshal( ec, &((_MICO_T*)v)->operations );
  _marshaller__seq_CORBA_AttributeDescription->marshal( ec, &((_MICO_T*)v)->attributes );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->base_interfaces );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_abstract );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription::typecode()
{
  return CORBA::InterfaceDef::_tc_FullInterfaceDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDef_FullInterfaceDescription;


// Stub interface InterfaceDef
CORBA::InterfaceDef::~InterfaceDef()
{
}

void *CORBA::InterfaceDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/InterfaceDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::InterfaceDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/InterfaceDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::InterfaceDef_ptr CORBA::InterfaceDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::InterfaceDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/InterfaceDef:1.0" )))
      return _duplicate( (CORBA::InterfaceDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/InterfaceDef:1.0" ) ) ) {
      _o = new CORBA::InterfaceDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::InterfaceDef_ptr
CORBA::InterfaceDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::InterfaceDef_stub::~InterfaceDef_stub()
{
}

CORBA::InterfaceDefSeq* CORBA::InterfaceDef_stub::base_interfaces()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_InterfaceDef );

  CORBA::StaticRequest __req( this, "_get_base_interfaces" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::InterfaceDefSeq*) __res._retn();
}


void CORBA::InterfaceDef_stub::base_interfaces( const CORBA::InterfaceDefSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_InterfaceDef, &_value );
  CORBA::StaticRequest __req( this, "_set_base_interfaces" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::InterfaceDef_stub::is_abstract()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "_get_is_abstract" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::InterfaceDef_stub::is_abstract( CORBA::Boolean _value )
{
  CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );
  CORBA::StaticRequest __req( this, "_set_is_abstract" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::InterfaceDef_stub::is_a( const char* interface_id )
{
  CORBA::StaticAny _interface_id( CORBA::_stc_string, &interface_id );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "is_a" );
  __req.add_in_arg( &_interface_id );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::InterfaceDef::FullInterfaceDescription* CORBA::InterfaceDef_stub::describe_interface()
{
  CORBA::StaticAny __res( _marshaller_CORBA_InterfaceDef_FullInterfaceDescription );

  CORBA::StaticRequest __req( this, "describe_interface" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::InterfaceDef::FullInterfaceDescription*) __res._retn();
}


CORBA::AttributeDef_ptr CORBA::InterfaceDef_stub::create_attribute( const char* id, const char* name, const char* version, CORBA::IDLType_ptr type, CORBA::AttributeMode mode )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type );
  CORBA::StaticAny _mode( _marshaller_CORBA_AttributeMode, &mode );
  CORBA::AttributeDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_AttributeDef, &_res );

  CORBA::StaticRequest __req( this, "create_attribute" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_type );
  __req.add_in_arg( &_mode );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::OperationDef_ptr CORBA::InterfaceDef_stub::create_operation( const char* id, const char* name, const char* version, CORBA::IDLType_ptr result, CORBA::OperationMode mode, const CORBA::ParDescriptionSeq& params, const CORBA::ExceptionDefSeq& exceptions, const CORBA::ContextIdSeq& contexts )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _result( _marshaller_CORBA_IDLType, &result );
  CORBA::StaticAny _mode( _marshaller_CORBA_OperationMode, &mode );
  CORBA::StaticAny _params( _marshaller__seq_CORBA_ParameterDescription, &params );
  CORBA::StaticAny _exceptions( _marshaller__seq_CORBA_ExceptionDef, &exceptions );
  CORBA::StaticAny _contexts( CORBA::_stcseq_string, &contexts );
  CORBA::OperationDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_OperationDef, &_res );

  CORBA::StaticRequest __req( this, "create_operation" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_result );
  __req.add_in_arg( &_mode );
  __req.add_in_arg( &_params );
  __req.add_in_arg( &_exceptions );
  __req.add_in_arg( &_contexts );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


struct _global_init_CORBA_InterfaceDef {
  _global_init_CORBA_InterfaceDef()
  {
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::InterfaceDef::_narrow_helper2 );
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::InterfaceDef::_narrow_helper2 );
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::InterfaceDef::_narrow_helper2 );
  }
} __global_init_CORBA_InterfaceDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * InterfaceDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::InterfaceDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_InterfaceDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_InterfaceDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::InterfaceDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::InterfaceDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::InterfaceDef_ptr &_obj )
{
  CORBA::InterfaceDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_InterfaceDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_InterfaceDef : public CORBA::StaticTypeInfo {
    typedef CORBA::InterfaceDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_InterfaceDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_InterfaceDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::InterfaceDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_InterfaceDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_InterfaceDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::InterfaceDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_InterfaceDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_InterfaceDef::typecode()
{
  return CORBA::_tc_InterfaceDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_InterfaceDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_InterfaceDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::InterfaceDescription::InterfaceDescription()
{
}

CORBA::InterfaceDescription::InterfaceDescription( const InterfaceDescription& _s )
{
  name = ((InterfaceDescription&)_s).name;
  id = ((InterfaceDescription&)_s).id;
  defined_in = ((InterfaceDescription&)_s).defined_in;
  version = ((InterfaceDescription&)_s).version;
  base_interfaces = ((InterfaceDescription&)_s).base_interfaces;
  is_abstract = ((InterfaceDescription&)_s).is_abstract;
}

CORBA::InterfaceDescription::~InterfaceDescription()
{
}

CORBA::InterfaceDescription&
CORBA::InterfaceDescription::operator=( const InterfaceDescription& _s )
{
  name = ((InterfaceDescription&)_s).name;
  id = ((InterfaceDescription&)_s).id;
  defined_in = ((InterfaceDescription&)_s).defined_in;
  version = ((InterfaceDescription&)_s).version;
  base_interfaces = ((InterfaceDescription&)_s).base_interfaces;
  is_abstract = ((InterfaceDescription&)_s).is_abstract;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::InterfaceDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::InterfaceDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::InterfaceDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_InterfaceDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::InterfaceDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_InterfaceDescription, (void *&)_s);
}

class _Marshaller_CORBA_InterfaceDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::InterfaceDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_InterfaceDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_InterfaceDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_InterfaceDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_InterfaceDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->base_interfaces ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_abstract ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_InterfaceDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->base_interfaces );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_abstract );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_InterfaceDescription::typecode()
{
  return CORBA::_tc_InterfaceDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDescription;


// Stub interface ValueMemberDef
CORBA::ValueMemberDef::~ValueMemberDef()
{
}

void *CORBA::ValueMemberDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ValueMemberDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ValueMemberDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ValueMemberDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ValueMemberDef_ptr CORBA::ValueMemberDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ValueMemberDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ValueMemberDef:1.0" )))
      return _duplicate( (CORBA::ValueMemberDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ValueMemberDef:1.0" ) ) ) {
      _o = new CORBA::ValueMemberDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ValueMemberDef_ptr
CORBA::ValueMemberDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ValueMemberDef_stub::~ValueMemberDef_stub()
{
}

CORBA::TypeCode_ptr CORBA::ValueMemberDef_stub::type()
{
  CORBA::TypeCode_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );

  CORBA::StaticRequest __req( this, "_get_type" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::IDLType_ptr CORBA::ValueMemberDef_stub::type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueMemberDef_stub::type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Visibility CORBA::ValueMemberDef_stub::access()
{
  CORBA::Visibility _res;
  CORBA::StaticAny __res( CORBA::_stc_short, &_res );

  CORBA::StaticRequest __req( this, "_get_access" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueMemberDef_stub::access( CORBA::Visibility _value )
{
  CORBA::StaticAny __value( CORBA::_stc_short, &_value );
  CORBA::StaticRequest __req( this, "_set_access" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_ValueMemberDef {
  _global_init_CORBA_ValueMemberDef()
  {
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::ValueMemberDef::_narrow_helper2 );
  }
} __global_init_CORBA_ValueMemberDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ValueMemberDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ValueMemberDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueMemberDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueMemberDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ValueMemberDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueMemberDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ValueMemberDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueMemberDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ValueMemberDef_ptr &_obj )
{
  CORBA::ValueMemberDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ValueMemberDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ValueMemberDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueMemberDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueMemberDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ValueMemberDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ValueMemberDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ValueMemberDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueMemberDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ValueMemberDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ValueMemberDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueMemberDef::typecode()
{
  return CORBA::_tc_ValueMemberDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueMemberDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ValueDef::_tc_FullValueDescription; };
#else
CORBA::TypeCodeConst CORBA::ValueDef::_tc_FullValueDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ValueDef::FullValueDescription::FullValueDescription()
{
}

CORBA::ValueDef::FullValueDescription::FullValueDescription( const FullValueDescription& _s )
{
  name = ((FullValueDescription&)_s).name;
  id = ((FullValueDescription&)_s).id;
  is_abstract = ((FullValueDescription&)_s).is_abstract;
  is_custom = ((FullValueDescription&)_s).is_custom;
  defined_in = ((FullValueDescription&)_s).defined_in;
  version = ((FullValueDescription&)_s).version;
  operations = ((FullValueDescription&)_s).operations;
  attributes = ((FullValueDescription&)_s).attributes;
  members = ((FullValueDescription&)_s).members;
  initializers = ((FullValueDescription&)_s).initializers;
  supported_interfaces = ((FullValueDescription&)_s).supported_interfaces;
  abstract_base_values = ((FullValueDescription&)_s).abstract_base_values;
  is_truncatable = ((FullValueDescription&)_s).is_truncatable;
  base_value = ((FullValueDescription&)_s).base_value;
  type = ((FullValueDescription&)_s).type;
}

CORBA::ValueDef::FullValueDescription::~FullValueDescription()
{
}

CORBA::ValueDef::FullValueDescription&
CORBA::ValueDef::FullValueDescription::operator=( const FullValueDescription& _s )
{
  name = ((FullValueDescription&)_s).name;
  id = ((FullValueDescription&)_s).id;
  is_abstract = ((FullValueDescription&)_s).is_abstract;
  is_custom = ((FullValueDescription&)_s).is_custom;
  defined_in = ((FullValueDescription&)_s).defined_in;
  version = ((FullValueDescription&)_s).version;
  operations = ((FullValueDescription&)_s).operations;
  attributes = ((FullValueDescription&)_s).attributes;
  members = ((FullValueDescription&)_s).members;
  initializers = ((FullValueDescription&)_s).initializers;
  supported_interfaces = ((FullValueDescription&)_s).supported_interfaces;
  abstract_base_values = ((FullValueDescription&)_s).abstract_base_values;
  is_truncatable = ((FullValueDescription&)_s).is_truncatable;
  base_value = ((FullValueDescription&)_s).base_value;
  type = ((FullValueDescription&)_s).type;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ValueDef::FullValueDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDef_FullValueDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ValueDef::FullValueDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueDef::FullValueDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDef_FullValueDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueDef::FullValueDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ValueDef_FullValueDescription, (void *&)_s);
}

class _Marshaller_CORBA_ValueDef_FullValueDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueDef::FullValueDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueDef_FullValueDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ValueDef_FullValueDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ValueDef_FullValueDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueDef_FullValueDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_abstract ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_custom ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    _marshaller__seq_CORBA_OperationDescription->demarshal( dc, &((_MICO_T*)v)->operations ) &&
    _marshaller__seq_CORBA_AttributeDescription->demarshal( dc, &((_MICO_T*)v)->attributes ) &&
    _marshaller__seq_CORBA_ValueMember->demarshal( dc, &((_MICO_T*)v)->members ) &&
    _marshaller__seq_CORBA_Initializer->demarshal( dc, &((_MICO_T*)v)->initializers ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->supported_interfaces ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->abstract_base_values ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_truncatable ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->base_value.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ValueDef_FullValueDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_abstract );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_custom );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  _marshaller__seq_CORBA_OperationDescription->marshal( ec, &((_MICO_T*)v)->operations );
  _marshaller__seq_CORBA_AttributeDescription->marshal( ec, &((_MICO_T*)v)->attributes );
  _marshaller__seq_CORBA_ValueMember->marshal( ec, &((_MICO_T*)v)->members );
  _marshaller__seq_CORBA_Initializer->marshal( ec, &((_MICO_T*)v)->initializers );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->supported_interfaces );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->abstract_base_values );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_truncatable );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->base_value.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueDef_FullValueDescription::typecode()
{
  return CORBA::ValueDef::_tc_FullValueDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDef_FullValueDescription;


// Stub interface ValueDef
CORBA::ValueDef::~ValueDef()
{
}

void *CORBA::ValueDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ValueDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = Container::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = Contained::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if( (_p = IDLType::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ValueDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ValueDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ValueDef_ptr CORBA::ValueDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ValueDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ValueDef:1.0" )))
      return _duplicate( (CORBA::ValueDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ValueDef:1.0" ) ) ) {
      _o = new CORBA::ValueDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ValueDef_ptr
CORBA::ValueDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ValueDef_stub::~ValueDef_stub()
{
}

CORBA::InterfaceDefSeq* CORBA::ValueDef_stub::supported_interfaces()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_InterfaceDef );

  CORBA::StaticRequest __req( this, "_get_supported_interfaces" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::InterfaceDefSeq*) __res._retn();
}


void CORBA::ValueDef_stub::supported_interfaces( const CORBA::InterfaceDefSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_InterfaceDef, &_value );
  CORBA::StaticRequest __req( this, "_set_supported_interfaces" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::InitializerSeq* CORBA::ValueDef_stub::initializers()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_Initializer );

  CORBA::StaticRequest __req( this, "_get_initializers" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::InitializerSeq*) __res._retn();
}


void CORBA::ValueDef_stub::initializers( const CORBA::InitializerSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_Initializer, &_value );
  CORBA::StaticRequest __req( this, "_set_initializers" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ValueDef_ptr CORBA::ValueDef_stub::base_value()
{
  CORBA::ValueDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ValueDef, &_res );

  CORBA::StaticRequest __req( this, "_get_base_value" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueDef_stub::base_value( CORBA::ValueDef_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_ValueDef, &_value );
  CORBA::StaticRequest __req( this, "_set_base_value" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ValueDefSeq* CORBA::ValueDef_stub::abstract_base_values()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ValueDef );

  CORBA::StaticRequest __req( this, "_get_abstract_base_values" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ValueDefSeq*) __res._retn();
}


void CORBA::ValueDef_stub::abstract_base_values( const CORBA::ValueDefSeq& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_ValueDef, &_value );
  CORBA::StaticRequest __req( this, "_set_abstract_base_values" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::ValueDef_stub::is_abstract()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "_get_is_abstract" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueDef_stub::is_abstract( CORBA::Boolean _value )
{
  CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );
  CORBA::StaticRequest __req( this, "_set_is_abstract" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::ValueDef_stub::is_custom()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "_get_is_custom" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueDef_stub::is_custom( CORBA::Boolean _value )
{
  CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );
  CORBA::StaticRequest __req( this, "_set_is_custom" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::ValueDef_stub::is_truncatable()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "_get_is_truncatable" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueDef_stub::is_truncatable( CORBA::Boolean _value )
{
  CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );
  CORBA::StaticRequest __req( this, "_set_is_truncatable" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::ValueDef_stub::is_a( const char* value_id )
{
  CORBA::StaticAny _value_id( CORBA::_stc_string, &value_id );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "is_a" );
  __req.add_in_arg( &_value_id );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ValueDef::FullValueDescription* CORBA::ValueDef_stub::describe_value()
{
  CORBA::StaticAny __res( _marshaller_CORBA_ValueDef_FullValueDescription );

  CORBA::StaticRequest __req( this, "describe_value" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ValueDef::FullValueDescription*) __res._retn();
}


CORBA::ValueMemberDef_ptr CORBA::ValueDef_stub::create_value_member( const char* id, const char* name, const char* version, CORBA::IDLType_ptr type, CORBA::Visibility access )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type );
  CORBA::StaticAny _access( CORBA::_stc_short, &access );
  CORBA::ValueMemberDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ValueMemberDef, &_res );

  CORBA::StaticRequest __req( this, "create_value_member" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_type );
  __req.add_in_arg( &_access );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::AttributeDef_ptr CORBA::ValueDef_stub::create_attribute( const char* id, const char* name, const char* version, CORBA::IDLType_ptr type, CORBA::AttributeMode mode )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type );
  CORBA::StaticAny _mode( _marshaller_CORBA_AttributeMode, &mode );
  CORBA::AttributeDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_AttributeDef, &_res );

  CORBA::StaticRequest __req( this, "create_attribute" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_type );
  __req.add_in_arg( &_mode );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::OperationDef_ptr CORBA::ValueDef_stub::create_operation( const char* id, const char* name, const char* version, CORBA::IDLType_ptr result, CORBA::OperationMode mode, const CORBA::ParDescriptionSeq& params, const CORBA::ExceptionDefSeq& exceptions, const CORBA::ContextIdSeq& contexts )
{
  CORBA::StaticAny _id( CORBA::_stc_string, &id );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _version( CORBA::_stc_string, &version );
  CORBA::StaticAny _result( _marshaller_CORBA_IDLType, &result );
  CORBA::StaticAny _mode( _marshaller_CORBA_OperationMode, &mode );
  CORBA::StaticAny _params( _marshaller__seq_CORBA_ParameterDescription, &params );
  CORBA::StaticAny _exceptions( _marshaller__seq_CORBA_ExceptionDef, &exceptions );
  CORBA::StaticAny _contexts( CORBA::_stcseq_string, &contexts );
  CORBA::OperationDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_OperationDef, &_res );

  CORBA::StaticRequest __req( this, "create_operation" );
  __req.add_in_arg( &_id );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_version );
  __req.add_in_arg( &_result );
  __req.add_in_arg( &_mode );
  __req.add_in_arg( &_params );
  __req.add_in_arg( &_exceptions );
  __req.add_in_arg( &_contexts );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


struct _global_init_CORBA_ValueDef {
  _global_init_CORBA_ValueDef()
  {
    if( ::CORBA::Container::_narrow_helpers == NULL )
      ::CORBA::Container::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Container::_narrow_helpers->push_back( CORBA::ValueDef::_narrow_helper2 );
    if( ::CORBA::Contained::_narrow_helpers == NULL )
      ::CORBA::Contained::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::Contained::_narrow_helpers->push_back( CORBA::ValueDef::_narrow_helper2 );
    if( ::CORBA::IDLType::_narrow_helpers == NULL )
      ::CORBA::IDLType::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IDLType::_narrow_helpers->push_back( CORBA::ValueDef::_narrow_helper2 );
  }
} __global_init_CORBA_ValueDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ValueDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ValueDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ValueDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ValueDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ValueDef_ptr &_obj )
{
  CORBA::ValueDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ValueDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ValueDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ValueDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ValueDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ValueDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ValueDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ValueDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueDef::typecode()
{
  return CORBA::_tc_ValueDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueDescription; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueDescription;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ValueDescription::ValueDescription()
{
}

CORBA::ValueDescription::ValueDescription( const ValueDescription& _s )
{
  name = ((ValueDescription&)_s).name;
  id = ((ValueDescription&)_s).id;
  is_abstract = ((ValueDescription&)_s).is_abstract;
  is_custom = ((ValueDescription&)_s).is_custom;
  defined_in = ((ValueDescription&)_s).defined_in;
  version = ((ValueDescription&)_s).version;
  supported_interfaces = ((ValueDescription&)_s).supported_interfaces;
  abstract_base_values = ((ValueDescription&)_s).abstract_base_values;
  is_truncatable = ((ValueDescription&)_s).is_truncatable;
  base_value = ((ValueDescription&)_s).base_value;
}

CORBA::ValueDescription::~ValueDescription()
{
}

CORBA::ValueDescription&
CORBA::ValueDescription::operator=( const ValueDescription& _s )
{
  name = ((ValueDescription&)_s).name;
  id = ((ValueDescription&)_s).id;
  is_abstract = ((ValueDescription&)_s).is_abstract;
  is_custom = ((ValueDescription&)_s).is_custom;
  defined_in = ((ValueDescription&)_s).defined_in;
  version = ((ValueDescription&)_s).version;
  supported_interfaces = ((ValueDescription&)_s).supported_interfaces;
  abstract_base_values = ((ValueDescription&)_s).abstract_base_values;
  is_truncatable = ((ValueDescription&)_s).is_truncatable;
  base_value = ((ValueDescription&)_s).base_value;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ValueDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ValueDescription *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueDescription &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueDescription *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ValueDescription, (void *&)_s);
}

class _Marshaller_CORBA_ValueDescription : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueDescription _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ValueDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ValueDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_abstract ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_custom ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->supported_interfaces ) &&
    CORBA::_stcseq_string->demarshal( dc, &((_MICO_T*)v)->abstract_base_values ) &&
    CORBA::_stc_boolean->demarshal( dc, &((_MICO_T*)v)->is_truncatable ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->base_value.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ValueDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_abstract );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_custom );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->supported_interfaces );
  CORBA::_stcseq_string->marshal( ec, &((_MICO_T*)v)->abstract_base_values );
  CORBA::_stc_boolean->marshal( ec, &((_MICO_T*)v)->is_truncatable );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->base_value.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueDescription::typecode()
{
  return CORBA::_tc_ValueDescription;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDescription;


// Stub interface ValueBoxDef
CORBA::ValueBoxDef::~ValueBoxDef()
{
}

void *CORBA::ValueBoxDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ValueBoxDef:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = TypedefDef::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::ValueBoxDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ValueBoxDef:1.0" ) == 0) {
    return true;
  }
  for( vector<CORBA::Narrow_proto>::size_type _i = 0;
       _narrow_helpers && _i < _narrow_helpers->size(); _i++ ) {
    bool _res = (*(*_narrow_helpers)[ _i ])( _obj );
    if( _res )
      return true;
  }
  return false;
}

CORBA::ValueBoxDef_ptr CORBA::ValueBoxDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ValueBoxDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ValueBoxDef:1.0" )))
      return _duplicate( (CORBA::ValueBoxDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ValueBoxDef:1.0" ) ) ) {
      _o = new CORBA::ValueBoxDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ValueBoxDef_ptr
CORBA::ValueBoxDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ValueBoxDef_stub::~ValueBoxDef_stub()
{
}

CORBA::IDLType_ptr CORBA::ValueBoxDef_stub::original_type_def()
{
  CORBA::IDLType_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );

  CORBA::StaticRequest __req( this, "_get_original_type_def" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ValueBoxDef_stub::original_type_def( CORBA::IDLType_ptr _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value );
  CORBA::StaticRequest __req( this, "_set_original_type_def" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct _global_init_CORBA_ValueBoxDef {
  _global_init_CORBA_ValueBoxDef()
  {
    if( ::CORBA::TypedefDef::_narrow_helpers == NULL )
      ::CORBA::TypedefDef::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::TypedefDef::_narrow_helpers->push_back( CORBA::ValueBoxDef::_narrow_helper2 );
  }
} __global_init_CORBA_ValueBoxDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ValueBoxDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ValueBoxDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueBoxDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueBoxDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ValueBoxDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueBoxDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ValueBoxDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueBoxDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ValueBoxDef_ptr &_obj )
{
  CORBA::ValueBoxDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ValueBoxDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ValueBoxDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueBoxDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueBoxDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ValueBoxDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ValueBoxDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ValueBoxDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueBoxDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ValueBoxDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ValueBoxDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueBoxDef::typecode()
{
  return CORBA::_tc_ValueBoxDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueBoxDef;

class _Marshaller__seq_CORBA_ValueDef : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ValueDef::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ValueDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ValueDef::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ValueDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ValueDef->demarshal( dc, &(*(_MICO_T*)v)[i].inout() ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ValueDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ValueDef->marshal( ec, &(*(_MICO_T*)v)[i].inout() );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ValueDef::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000048000000010000000e00000035000000010000001f00"
    "000049444c3a6f6d672e6f72672f434f5242412f56616c75654465663a31"
    "2e3000000900000056616c75654465660000000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ValueDef::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ValueDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ValueDef, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ValueDef, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ValueDef, (void *&)_s);
}


class _Marshaller__seq_CORBA_InterfaceDef : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_InterfaceDef::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_InterfaceDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_InterfaceDef::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_InterfaceDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_InterfaceDef->demarshal( dc, &(*(_MICO_T*)v)[i].inout() ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_InterfaceDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_InterfaceDef->marshal( ec, &(*(_MICO_T*)v)[i].inout() );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_InterfaceDef::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000050000000010000000e0000003d000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f496e7465726661636544"
    "65663a312e3000000d000000496e74657266616365446566000000000000"
    "0000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_InterfaceDef::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_InterfaceDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_InterfaceDef, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_InterfaceDef, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_InterfaceDef, (void *&)_s);
}


class _Marshaller__seq_CORBA_Contained : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_Contained::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_Contained::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_Contained::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_Contained::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_Contained->demarshal( dc, &(*(_MICO_T*)v)[i].inout() ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_Contained::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_Contained->marshal( ec, &(*(_MICO_T*)v)[i].inout() );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Contained::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000048000000010000000e00000036000000010000002000"
    "000049444c3a6f6d672e6f72672f434f5242412f436f6e7461696e65643a"
    "312e30000a000000436f6e7461696e656400000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Contained::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Contained;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Contained, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Contained, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_Contained, (void *&)_s);
}


class _Marshaller__seq_CORBA_Initializer : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_Initializer::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_Initializer::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_Initializer::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_Initializer::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_Initializer->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_Initializer::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_Initializer->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Initializer::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000010020000010000000f00000000020000010000002200"
    "000049444c3a6f6d672e6f72672f434f5242412f496e697469616c697a65"
    "723a312e300000000c000000496e697469616c697a657200020000000800"
    "00006d656d62657273001500000054010000010000002600000049444c3a"
    "6f6d672e6f72672f434f5242412f5374727563744d656d6265725365713a"
    "312e30000000100000005374727563744d656d6265725365710013000000"
    "08010000010000000f000000f8000000010000002300000049444c3a6f6d"
    "672e6f72672f434f5242412f5374727563744d656d6265723a312e300000"
    "0d0000005374727563744d656d6265720000000003000000050000006e61"
    "6d65000000001500000044000000010000002100000049444c3a6f6d672e"
    "6f72672f434f5242412f4964656e7469666965723a312e30000000000b00"
    "00004964656e746966696572000012000000000000000500000074797065"
    "000000000c00000009000000747970655f646566000000000e0000003400"
    "0000010000001e00000049444c3a6f6d672e6f72672f434f5242412f4944"
    "4c547970653a312e300000000800000049444c5479706500000000000500"
    "00006e616d65000000001500000044000000010000002100000049444c3a"
    "6f6d672e6f72672f434f5242412f4964656e7469666965723a312e300000"
    "00000b0000004964656e7469666965720000120000000000000000000000"
    ))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Initializer::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Initializer;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Initializer, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Initializer, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_Initializer, (void *&)_s);
}


class _Marshaller__seq_CORBA_Container_Description : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_Container_Description::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_Container_Description::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_Container_Description::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_Container_Description::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_Container_Description->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_Container_Description::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_Container_Description->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Container_Description::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "0100000013000000ac020000010000000f0000009c020000010000002c00"
    "000049444c3a6f6d672e6f72672f434f5242412f436f6e7461696e65722f"
    "4465736372697074696f6e3a312e30000c0000004465736372697074696f"
    "6e000300000011000000636f6e7461696e65645f6f626a65637400000000"
    "0e00000036000000010000002000000049444c3a6f6d672e6f72672f434f"
    "5242412f436f6e7461696e65643a312e30000a000000436f6e7461696e65"
    "64000000050000006b696e640000000011000000d6010000010000002500"
    "000049444c3a6f6d672e6f72672f434f5242412f446566696e6974696f6e"
    "4b696e643a312e30000000000f000000446566696e6974696f6e4b696e64"
    "00001800000008000000646b5f6e6f6e650007000000646b5f616c6c0000"
    "0d000000646b5f417474726962757465000000000c000000646b5f436f6e"
    "7374616e74000d000000646b5f457863657074696f6e000000000d000000"
    "646b5f496e74657266616365000000000a000000646b5f4d6f64756c6500"
    "00000d000000646b5f4f7065726174696f6e000000000b000000646b5f54"
    "797065646566000009000000646b5f416c696173000000000a000000646b"
    "5f53747275637400000009000000646b5f556e696f6e0000000008000000"
    "646b5f456e756d000d000000646b5f5072696d6974697665000000000a00"
    "0000646b5f537472696e670000000c000000646b5f53657175656e636500"
    "09000000646b5f4172726179000000000e000000646b5f5265706f736974"
    "6f72790000000b000000646b5f57737472696e67000009000000646b5f46"
    "697865640000000009000000646b5f56616c7565000000000c000000646b"
    "5f56616c7565426f78000f000000646b5f56616c75654d656d6265720000"
    "0a000000646b5f4e61746976650000000600000076616c75650000000b00"
    "000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_Container_Description::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Container_Description;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Container_Description, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_Container_Description, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_Container_Description, (void *&)_s);
}


class _Marshaller__seq_CORBA_ParameterDescription : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ParameterDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ParameterDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ParameterDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ParameterDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ParameterDescription->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ParameterDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ParameterDescription->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ParameterDescription::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "0100000013000000a0010000010000000f00000090010000010000002b00"
    "000049444c3a6f6d672e6f72672f434f5242412f506172616d6574657244"
    "65736372697074696f6e3a312e30000015000000506172616d6574657244"
    "65736372697074696f6e0000000004000000050000006e616d6500000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "746966696572000012000000000000000500000074797065000000000c00"
    "000009000000747970655f646566000000000e0000003400000001000000"
    "1e00000049444c3a6f6d672e6f72672f434f5242412f49444c547970653a"
    "312e300000000800000049444c5479706500050000006d6f646500000000"
    "1100000074000000010000002400000049444c3a6f6d672e6f72672f434f"
    "5242412f506172616d657465724d6f64653a312e30000e00000050617261"
    "6d657465724d6f64650000000300000009000000504152414d5f494e0000"
    "00000a000000504152414d5f4f55540000000c000000504152414d5f494e"
    "4f55540000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ParameterDescription::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ParameterDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ParameterDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ParameterDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ParameterDescription, (void *&)_s);
}


class _Marshaller__seq_CORBA_ExceptionDef : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ExceptionDef::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ExceptionDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ExceptionDef::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ExceptionDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ExceptionDef->demarshal( dc, &(*(_MICO_T*)v)[i].inout() ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ExceptionDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ExceptionDef->marshal( ec, &(*(_MICO_T*)v)[i].inout() );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ExceptionDef::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000050000000010000000e0000003d000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f457863657074696f6e44"
    "65663a312e3000000d000000457863657074696f6e446566000000000000"
    "0000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ExceptionDef::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ExceptionDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ExceptionDef, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ExceptionDef, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ExceptionDef, (void *&)_s);
}


class _Marshaller__seq_CORBA_ExceptionDescription : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ExceptionDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ExceptionDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ExceptionDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ExceptionDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ExceptionDescription->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ExceptionDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ExceptionDescription->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ExceptionDescription::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "0100000013000000dc010000010000000f000000cc010000010000002b00"
    "000049444c3a6f6d672e6f72672f434f5242412f457863657074696f6e44"
    "65736372697074696f6e3a312e30000015000000457863657074696f6e44"
    "65736372697074696f6e0000000005000000050000006e616d6500000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "746966696572000012000000000000000300000069640000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "49640000000012000000000000000b000000646566696e65645f696e0000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000800000076657273696f"
    "6e001500000044000000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f56657273696f6e537065633a312e300000000c0000005665"
    "7273696f6e53706563001200000000000000050000007479706500000000"
    "0c00000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ExceptionDescription::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ExceptionDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ExceptionDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ExceptionDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ExceptionDescription, (void *&)_s);
}


class _Marshaller__seq_CORBA_OperationDescription : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_OperationDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_OperationDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_OperationDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_OperationDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_OperationDescription->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_OperationDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_OperationDescription->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_OperationDescription::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "0100000013000000a4070000010000000f00000094070000010000002b00"
    "000049444c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e44"
    "65736372697074696f6e3a312e300000150000004f7065726174696f6e44"
    "65736372697074696f6e0000000009000000050000006e616d6500000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "746966696572000012000000000000000300000069640000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "49640000000012000000000000000b000000646566696e65645f696e0000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000800000076657273696f"
    "6e001500000044000000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f56657273696f6e537065633a312e300000000c0000005665"
    "7273696f6e5370656300120000000000000007000000726573756c740000"
    "0c000000050000006d6f6465000000001100000062000000010000002400"
    "000049444c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e4d"
    "6f64653a312e30000e0000004f7065726174696f6e4d6f64650000000200"
    "00000a0000004f505f4e4f524d414c0000000a0000004f505f4f4e455741"
    "5900000009000000636f6e74657874730000000015000000ec0000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f436f6e746578"
    "7449645365713a312e3000000d000000436f6e7465787449645365710000"
    "000013000000a40000000100000015000000940000000100000028000000"
    "49444c3a6f6d672e6f72672f434f5242412f436f6e746578744964656e74"
    "69666965723a312e300012000000436f6e746578744964656e7469666965"
    "720000001500000044000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f4964656e7469666965723a312e30000000000b000000"
    "4964656e74696669657200001200000000000000000000000b0000007061"
    "72616d6574657273000015000000f0010000010000002800000049444c3a"
    "6f6d672e6f72672f434f5242412f5061724465736372697074696f6e5365"
    "713a312e3000120000005061724465736372697074696f6e536571000000"
    "13000000a0010000010000000f00000090010000010000002b0000004944"
    "4c3a6f6d672e6f72672f434f5242412f506172616d657465724465736372"
    "697074696f6e3a312e30000015000000506172616d657465724465736372"
    "697074696f6e0000000004000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "6572000012000000000000000500000074797065000000000c0000000900"
    "0000747970655f646566000000000e00000034000000010000001e000000"
    "49444c3a6f6d672e6f72672f434f5242412f49444c547970653a312e3000"
    "00000800000049444c5479706500050000006d6f64650000000011000000"
    "74000000010000002400000049444c3a6f6d672e6f72672f434f5242412f"
    "506172616d657465724d6f64653a312e30000e000000506172616d657465"
    "724d6f64650000000300000009000000504152414d5f494e000000000a00"
    "0000504152414d5f4f55540000000c000000504152414d5f494e4f555400"
    "000000000b000000657863657074696f6e730000150000002c0200000100"
    "00002800000049444c3a6f6d672e6f72672f434f5242412f457863446573"
    "6372697074696f6e5365713a312e30001200000045786344657363726970"
    "74696f6e53657100000013000000dc010000010000000f000000cc010000"
    "010000002b00000049444c3a6f6d672e6f72672f434f5242412f45786365"
    "7074696f6e4465736372697074696f6e3a312e3000001500000045786365"
    "7074696f6e4465736372697074696f6e0000000005000000050000006e61"
    "6d65000000001500000044000000010000002100000049444c3a6f6d672e"
    "6f72672f434f5242412f4964656e7469666965723a312e30000000000b00"
    "00004964656e746966696572000012000000000000000300000069640000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000b000000646566696e65"
    "645f696e00001500000048000000010000002300000049444c3a6f6d672e"
    "6f72672f434f5242412f5265706f7369746f727949643a312e3000000d00"
    "00005265706f7369746f7279496400000000120000000000000008000000"
    "76657273696f6e001500000044000000010000002200000049444c3a6f6d"
    "672e6f72672f434f5242412f56657273696f6e537065633a312e30000000"
    "0c00000056657273696f6e53706563001200000000000000050000007479"
    "7065000000000c0000000000000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_OperationDescription::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_OperationDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_OperationDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_OperationDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_OperationDescription, (void *&)_s);
}


class _Marshaller__seq_CORBA_AttributeDescription : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_AttributeDescription::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_AttributeDescription::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_AttributeDescription::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_AttributeDescription::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_AttributeDescription->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_AttributeDescription::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_AttributeDescription->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_AttributeDescription::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000058020000010000000f00000046020000010000002b00"
    "000049444c3a6f6d672e6f72672f434f5242412f41747472696275746544"
    "65736372697074696f6e3a312e3000001500000041747472696275746544"
    "65736372697074696f6e0000000006000000050000006e616d6500000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "746966696572000012000000000000000300000069640000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "49640000000012000000000000000b000000646566696e65645f696e0000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000800000076657273696f"
    "6e001500000044000000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f56657273696f6e537065633a312e300000000c0000005665"
    "7273696f6e53706563001200000000000000050000007479706500000000"
    "0c000000050000006d6f6465000000001100000066000000010000002400"
    "000049444c3a6f6d672e6f72672f434f5242412f4174747269627574654d"
    "6f64653a312e30000e0000004174747269627574654d6f64650000000200"
    "00000c000000415454525f4e4f524d414c000e000000415454525f524541"
    "444f4e4c5900000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_AttributeDescription::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_AttributeDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_AttributeDescription, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_AttributeDescription, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_AttributeDescription, (void *&)_s);
}


struct __tc_init_IR {
  __tc_init_IR()
  {
    CORBA::_tc_ScopedName = 
    "010000001500000044000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f53636f7065644e616d653a312e30000000000b000000"
    "53636f7065644e616d6500001200000000000000";
    CORBA::Contained::_tc_Description = 
    "010000000f00000044020000010000002c00000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65642f4465736372697074696f6e3a"
    "312e30000c0000004465736372697074696f6e0002000000050000006b69"
    "6e640000000011000000d6010000010000002500000049444c3a6f6d672e"
    "6f72672f434f5242412f446566696e6974696f6e4b696e643a312e300000"
    "00000f000000446566696e6974696f6e4b696e6400001800000008000000"
    "646b5f6e6f6e650007000000646b5f616c6c00000d000000646b5f417474"
    "726962757465000000000c000000646b5f436f6e7374616e74000d000000"
    "646b5f457863657074696f6e000000000d000000646b5f496e7465726661"
    "6365000000000a000000646b5f4d6f64756c650000000d000000646b5f4f"
    "7065726174696f6e000000000b000000646b5f5479706564656600000900"
    "0000646b5f416c696173000000000a000000646b5f537472756374000000"
    "09000000646b5f556e696f6e0000000008000000646b5f456e756d000d00"
    "0000646b5f5072696d6974697665000000000a000000646b5f537472696e"
    "670000000c000000646b5f53657175656e63650009000000646b5f417272"
    "6179000000000e000000646b5f5265706f7369746f72790000000b000000"
    "646b5f57737472696e67000009000000646b5f4669786564000000000900"
    "0000646b5f56616c7565000000000c000000646b5f56616c7565426f7800"
    "0f000000646b5f56616c75654d656d62657200000a000000646b5f4e6174"
    "6976650000000600000076616c75650000000b000000";
    _marshaller_CORBA_Contained_Description = new _Marshaller_CORBA_Contained_Description;
    CORBA::_tc_Contained = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65643a312e30000a000000436f6e74"
    "61696e656400";
    _marshaller_CORBA_Contained = new _Marshaller_CORBA_Contained;
    CORBA::_tc_ValueDefSeq = 
    "01000000150000008c000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654465665365713a312e300000000c000000"
    "56616c7565446566536571001300000048000000010000000e0000003500"
    "0000010000001f00000049444c3a6f6d672e6f72672f434f5242412f5661"
    "6c75654465663a312e3000000900000056616c7565446566000000000000"
    "0000";
    CORBA::_tc_InterfaceDefSeq = 
    "01000000150000009c000000010000002600000049444c3a6f6d672e6f72"
    "672f434f5242412f496e746572666163654465665365713a312e30000000"
    "10000000496e746572666163654465665365710013000000500000000100"
    "00000e0000003d000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f496e746572666163654465663a312e3000000d000000496e"
    "746572666163654465660000000000000000";
    CORBA::_tc_ContainedSeq = 
    "010000001500000090000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65645365713a312e3000000d000000"
    "436f6e7461696e6564536571000000001300000048000000010000000e00"
    "000036000000010000002000000049444c3a6f6d672e6f72672f434f5242"
    "412f436f6e7461696e65643a312e30000a000000436f6e7461696e656400"
    "000000000000";
    CORBA::_tc_Initializer = 
    "010000000f00000000020000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f496e697469616c697a65723a312e300000000c000000"
    "496e697469616c697a65720002000000080000006d656d62657273001500"
    "000054010000010000002600000049444c3a6f6d672e6f72672f434f5242"
    "412f5374727563744d656d6265725365713a312e30000000100000005374"
    "727563744d656d626572536571001300000008010000010000000f000000"
    "f8000000010000002300000049444c3a6f6d672e6f72672f434f5242412f"
    "5374727563744d656d6265723a312e3000000d0000005374727563744d65"
    "6d6265720000000003000000050000006e616d6500000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "000012000000000000000500000074797065000000000c00000009000000"
    "747970655f646566000000000e00000034000000010000001e0000004944"
    "4c3a6f6d672e6f72672f434f5242412f49444c547970653a312e30000000"
    "0800000049444c547970650000000000050000006e616d65000000001500"
    "000044000000010000002100000049444c3a6f6d672e6f72672f434f5242"
    "412f4964656e7469666965723a312e30000000000b0000004964656e7469"
    "6669657200001200000000000000";
    _marshaller_CORBA_Initializer = new _Marshaller_CORBA_Initializer;
    CORBA::_tc_InitializerSeq = 
    "01000000150000005c020000010000002500000049444c3a6f6d672e6f72"
    "672f434f5242412f496e697469616c697a65725365713a312e3000000000"
    "0f000000496e697469616c697a6572536571000013000000100200000100"
    "00000f00000000020000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f496e697469616c697a65723a312e300000000c000000496e"
    "697469616c697a65720002000000080000006d656d626572730015000000"
    "54010000010000002600000049444c3a6f6d672e6f72672f434f5242412f"
    "5374727563744d656d6265725365713a312e300000001000000053747275"
    "63744d656d626572536571001300000008010000010000000f000000f800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5374"
    "727563744d656d6265723a312e3000000d0000005374727563744d656d62"
    "65720000000003000000050000006e616d65000000001500000044000000"
    "010000002100000049444c3a6f6d672e6f72672f434f5242412f4964656e"
    "7469666965723a312e30000000000b0000004964656e7469666965720000"
    "12000000000000000500000074797065000000000c000000090000007479"
    "70655f646566000000000e00000034000000010000001e00000049444c3a"
    "6f6d672e6f72672f434f5242412f49444c547970653a312e300000000800"
    "000049444c547970650000000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "65720000120000000000000000000000";
    CORBA::Container::_tc_Description = 
    "010000000f0000009c020000010000002c00000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65722f4465736372697074696f6e3a"
    "312e30000c0000004465736372697074696f6e000300000011000000636f"
    "6e7461696e65645f6f626a656374000000000e0000003600000001000000"
    "2000000049444c3a6f6d672e6f72672f434f5242412f436f6e7461696e65"
    "643a312e30000a000000436f6e7461696e6564000000050000006b696e64"
    "0000000011000000d6010000010000002500000049444c3a6f6d672e6f72"
    "672f434f5242412f446566696e6974696f6e4b696e643a312e3000000000"
    "0f000000446566696e6974696f6e4b696e6400001800000008000000646b"
    "5f6e6f6e650007000000646b5f616c6c00000d000000646b5f4174747269"
    "62757465000000000c000000646b5f436f6e7374616e74000d000000646b"
    "5f457863657074696f6e000000000d000000646b5f496e74657266616365"
    "000000000a000000646b5f4d6f64756c650000000d000000646b5f4f7065"
    "726174696f6e000000000b000000646b5f54797065646566000009000000"
    "646b5f416c696173000000000a000000646b5f5374727563740000000900"
    "0000646b5f556e696f6e0000000008000000646b5f456e756d000d000000"
    "646b5f5072696d6974697665000000000a000000646b5f537472696e6700"
    "00000c000000646b5f53657175656e63650009000000646b5f4172726179"
    "000000000e000000646b5f5265706f7369746f72790000000b000000646b"
    "5f57737472696e67000009000000646b5f46697865640000000009000000"
    "646b5f56616c7565000000000c000000646b5f56616c7565426f78000f00"
    "0000646b5f56616c75654d656d62657200000a000000646b5f4e61746976"
    "650000000600000076616c75650000000b000000";
    _marshaller_CORBA_Container_Description = new _Marshaller_CORBA_Container_Description;
    CORBA::Container::_tc_DescriptionSeq = 
    "010000001500000000030000010000002f00000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65722f4465736372697074696f6e53"
    "65713a312e3000000f0000004465736372697074696f6e53657100001300"
    "0000ac020000010000000f0000009c020000010000002c00000049444c3a"
    "6f6d672e6f72672f434f5242412f436f6e7461696e65722f446573637269"
    "7074696f6e3a312e30000c0000004465736372697074696f6e0003000000"
    "11000000636f6e7461696e65645f6f626a656374000000000e0000003600"
    "0000010000002000000049444c3a6f6d672e6f72672f434f5242412f436f"
    "6e7461696e65643a312e30000a000000436f6e7461696e65640000000500"
    "00006b696e640000000011000000d6010000010000002500000049444c3a"
    "6f6d672e6f72672f434f5242412f446566696e6974696f6e4b696e643a31"
    "2e30000000000f000000446566696e6974696f6e4b696e64000018000000"
    "08000000646b5f6e6f6e650007000000646b5f616c6c00000d000000646b"
    "5f417474726962757465000000000c000000646b5f436f6e7374616e7400"
    "0d000000646b5f457863657074696f6e000000000d000000646b5f496e74"
    "657266616365000000000a000000646b5f4d6f64756c650000000d000000"
    "646b5f4f7065726174696f6e000000000b000000646b5f54797065646566"
    "000009000000646b5f416c696173000000000a000000646b5f5374727563"
    "7400000009000000646b5f556e696f6e0000000008000000646b5f456e75"
    "6d000d000000646b5f5072696d6974697665000000000a000000646b5f53"
    "7472696e670000000c000000646b5f53657175656e63650009000000646b"
    "5f4172726179000000000e000000646b5f5265706f7369746f7279000000"
    "0b000000646b5f57737472696e67000009000000646b5f46697865640000"
    "000009000000646b5f56616c7565000000000c000000646b5f56616c7565"
    "426f78000f000000646b5f56616c75654d656d62657200000a000000646b"
    "5f4e61746976650000000600000076616c75650000000b00000000000000"
    ;
    CORBA::_tc_Container = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7461696e65723a312e30000a000000436f6e74"
    "61696e657200";
    _marshaller_CORBA_Container = new _Marshaller_CORBA_Container;
    CORBA::_tc_PrimitiveKind = 
    "01000000110000009e010000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f5072696d69746976654b696e643a312e30000e000000"
    "5072696d69746976654b696e640000001600000008000000706b5f6e756c"
    "6c0008000000706b5f766f69640009000000706b5f73686f727400000000"
    "08000000706b5f6c6f6e67000a000000706b5f7573686f72740000000900"
    "0000706b5f756c6f6e670000000009000000706b5f666c6f617400000000"
    "0a000000706b5f646f75626c650000000b000000706b5f626f6f6c65616e"
    "000008000000706b5f636861720009000000706b5f6f6374657400000000"
    "07000000706b5f616e7900000c000000706b5f54797065436f6465000d00"
    "0000706b5f5072696e636970616c000000000a000000706b5f737472696e"
    "670000000a000000706b5f6f626a7265660000000c000000706b5f6c6f6e"
    "676c6f6e67000d000000706b5f756c6f6e676c6f6e67000000000e000000"
    "706b5f6c6f6e67646f75626c6500000009000000706b5f77636861720000"
    "00000b000000706b5f77737472696e6700000e000000706b5f76616c7565"
    "5f6261736500";
    _marshaller_CORBA_PrimitiveKind = new _Marshaller_CORBA_PrimitiveKind;
    CORBA::_tc_Repository = 
    "010000000e0000003b000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f72793a312e30000000000b000000"
    "5265706f7369746f727900";
    _marshaller_CORBA_Repository = new _Marshaller_CORBA_Repository;
    CORBA::_tc_ModuleDef = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f4d6f64756c654465663a312e30000a0000004d6f6475"
    "6c6544656600";
    _marshaller_CORBA_ModuleDef = new _Marshaller_CORBA_ModuleDef;
    CORBA::_tc_ModuleDescription = 
    "010000000f000000b4010000010000002800000049444c3a6f6d672e6f72"
    "672f434f5242412f4d6f64756c654465736372697074696f6e3a312e3000"
    "120000004d6f64756c654465736372697074696f6e000000040000000500"
    "00006e616d65000000001500000044000000010000002100000049444c3a"
    "6f6d672e6f72672f434f5242412f4964656e7469666965723a312e300000"
    "00000b0000004964656e7469666965720000120000000000000003000000"
    "696400001500000048000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949643a312e3000000d000000"
    "5265706f7369746f727949640000000012000000000000000b0000006465"
    "66696e65645f696e00001500000048000000010000002300000049444c3a"
    "6f6d672e6f72672f434f5242412f5265706f7369746f727949643a312e30"
    "00000d0000005265706f7369746f72794964000000001200000000000000"
    "0800000076657273696f6e00150000004400000001000000220000004944"
    "4c3a6f6d672e6f72672f434f5242412f56657273696f6e537065633a312e"
    "300000000c00000056657273696f6e53706563001200000000000000";
    _marshaller_CORBA_ModuleDescription = new _Marshaller_CORBA_ModuleDescription;
    CORBA::_tc_ConstantDef = 
    "010000000e0000003c000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7374616e744465663a312e300000000c000000"
    "436f6e7374616e7444656600";
    _marshaller_CORBA_ConstantDef = new _Marshaller_CORBA_ConstantDef;
    CORBA::_tc_ConstantDescription = 
    "010000000f000000d8010000010000002a00000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7374616e744465736372697074696f6e3a312e"
    "3000000014000000436f6e7374616e744465736372697074696f6e000600"
    "0000050000006e616d650000000015000000440000000100000021000000"
    "49444c3a6f6d672e6f72672f434f5242412f4964656e7469666965723a31"
    "2e30000000000b0000004964656e74696669657200001200000000000000"
    "03000000696400001500000048000000010000002300000049444c3a6f6d"
    "672e6f72672f434f5242412f5265706f7369746f727949643a312e300000"
    "0d0000005265706f7369746f727949640000000012000000000000000b00"
    "0000646566696e65645f696e000015000000480000000100000023000000"
    "49444c3a6f6d672e6f72672f434f5242412f5265706f7369746f72794964"
    "3a312e3000000d0000005265706f7369746f727949640000000012000000"
    "000000000800000076657273696f6e001500000044000000010000002200"
    "000049444c3a6f6d672e6f72672f434f5242412f56657273696f6e537065"
    "633a312e300000000c00000056657273696f6e5370656300120000000000"
    "00000500000074797065000000000c0000000600000076616c7565000000"
    "0b000000";
    _marshaller_CORBA_ConstantDescription = new _Marshaller_CORBA_ConstantDescription;
    CORBA::_tc_TypedefDef = 
    "010000000e0000003b000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f547970656465664465663a312e30000000000b000000"
    "5479706564656644656600";
    _marshaller_CORBA_TypedefDef = new _Marshaller_CORBA_TypedefDef;
    CORBA::_tc_TypeDescription = 
    "010000000f000000c0010000010000002600000049444c3a6f6d672e6f72"
    "672f434f5242412f547970654465736372697074696f6e3a312e30000000"
    "10000000547970654465736372697074696f6e0005000000050000006e61"
    "6d65000000001500000044000000010000002100000049444c3a6f6d672e"
    "6f72672f434f5242412f4964656e7469666965723a312e30000000000b00"
    "00004964656e746966696572000012000000000000000300000069640000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000b000000646566696e65"
    "645f696e00001500000048000000010000002300000049444c3a6f6d672e"
    "6f72672f434f5242412f5265706f7369746f727949643a312e3000000d00"
    "00005265706f7369746f7279496400000000120000000000000008000000"
    "76657273696f6e001500000044000000010000002200000049444c3a6f6d"
    "672e6f72672f434f5242412f56657273696f6e537065633a312e30000000"
    "0c00000056657273696f6e53706563001200000000000000050000007479"
    "7065000000000c000000";
    _marshaller_CORBA_TypeDescription = new _Marshaller_CORBA_TypeDescription;
    CORBA::_tc_StructDef = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f5374727563744465663a312e30000a00000053747275"
    "637444656600";
    _marshaller_CORBA_StructDef = new _Marshaller_CORBA_StructDef;
    CORBA::_tc_UnionDef = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f556e696f6e4465663a312e30000009000000556e696f"
    "6e44656600";
    _marshaller_CORBA_UnionDef = new _Marshaller_CORBA_UnionDef;
    CORBA::_tc_EnumDef = 
    "010000000e00000034000000010000001e00000049444c3a6f6d672e6f72"
    "672f434f5242412f456e756d4465663a312e3000000008000000456e756d"
    "44656600";
    _marshaller_CORBA_EnumDef = new _Marshaller_CORBA_EnumDef;
    CORBA::_tc_AliasDef = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f416c6961734465663a312e30000009000000416c6961"
    "7344656600";
    _marshaller_CORBA_AliasDef = new _Marshaller_CORBA_AliasDef;
    CORBA::_tc_NativeDef = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f4e61746976654465663a312e30000a0000004e617469"
    "766544656600";
    _marshaller_CORBA_NativeDef = new _Marshaller_CORBA_NativeDef;
    CORBA::_tc_PrimitiveDef = 
    "010000000e0000003d000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5072696d69746976654465663a312e3000000d000000"
    "5072696d697469766544656600";
    _marshaller_CORBA_PrimitiveDef = new _Marshaller_CORBA_PrimitiveDef;
    CORBA::_tc_StringDef = 
    "010000000e00000036000000010000002000000049444c3a6f6d672e6f72"
    "672f434f5242412f537472696e674465663a312e30000a00000053747269"
    "6e6744656600";
    _marshaller_CORBA_StringDef = new _Marshaller_CORBA_StringDef;
    CORBA::_tc_WstringDef = 
    "010000000e0000003b000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f57737472696e674465663a312e30000000000b000000"
    "57737472696e6744656600";
    _marshaller_CORBA_WstringDef = new _Marshaller_CORBA_WstringDef;
    CORBA::_tc_FixedDef = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f46697865644465663a312e3000000900000046697865"
    "6444656600";
    _marshaller_CORBA_FixedDef = new _Marshaller_CORBA_FixedDef;
    CORBA::_tc_SequenceDef = 
    "010000000e0000003c000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f53657175656e63654465663a312e300000000c000000"
    "53657175656e636544656600";
    _marshaller_CORBA_SequenceDef = new _Marshaller_CORBA_SequenceDef;
    CORBA::_tc_ArrayDef = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f41727261794465663a312e3000000900000041727261"
    "7944656600";
    _marshaller_CORBA_ArrayDef = new _Marshaller_CORBA_ArrayDef;
    CORBA::_tc_ExceptionDef = 
    "010000000e0000003d000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f457863657074696f6e4465663a312e3000000d000000"
    "457863657074696f6e44656600";
    _marshaller_CORBA_ExceptionDef = new _Marshaller_CORBA_ExceptionDef;
    CORBA::_tc_ExceptionDescription = 
    "010000000f000000cc010000010000002b00000049444c3a6f6d672e6f72"
    "672f434f5242412f457863657074696f6e4465736372697074696f6e3a31"
    "2e30000015000000457863657074696f6e4465736372697074696f6e0000"
    "000005000000050000006e616d6500000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "000000000300000069640000150000004800000001000000230000004944"
    "4c3a6f6d672e6f72672f434f5242412f5265706f7369746f727949643a31"
    "2e3000000d0000005265706f7369746f7279496400000000120000000000"
    "00000b000000646566696e65645f696e0000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000800000076657273696f6e0015000000440000000100"
    "00002200000049444c3a6f6d672e6f72672f434f5242412f56657273696f"
    "6e537065633a312e300000000c00000056657273696f6e53706563001200"
    "0000000000000500000074797065000000000c000000";
    _marshaller_CORBA_ExceptionDescription = new _Marshaller_CORBA_ExceptionDescription;
    CORBA::_tc_AttributeMode = 
    "010000001100000066000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f4174747269627574654d6f64653a312e30000e000000"
    "4174747269627574654d6f6465000000020000000c000000415454525f4e"
    "4f524d414c000e000000415454525f524541444f4e4c5900";
    _marshaller_CORBA_AttributeMode = new _Marshaller_CORBA_AttributeMode;
    CORBA::_tc_AttributeDef = 
    "010000000e0000003d000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f4174747269627574654465663a312e3000000d000000"
    "41747472696275746544656600";
    _marshaller_CORBA_AttributeDef = new _Marshaller_CORBA_AttributeDef;
    CORBA::_tc_AttributeDescription = 
    "010000000f00000046020000010000002b00000049444c3a6f6d672e6f72"
    "672f434f5242412f4174747269627574654465736372697074696f6e3a31"
    "2e300000150000004174747269627574654465736372697074696f6e0000"
    "000006000000050000006e616d6500000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "000000000300000069640000150000004800000001000000230000004944"
    "4c3a6f6d672e6f72672f434f5242412f5265706f7369746f727949643a31"
    "2e3000000d0000005265706f7369746f7279496400000000120000000000"
    "00000b000000646566696e65645f696e0000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000800000076657273696f6e0015000000440000000100"
    "00002200000049444c3a6f6d672e6f72672f434f5242412f56657273696f"
    "6e537065633a312e300000000c00000056657273696f6e53706563001200"
    "0000000000000500000074797065000000000c000000050000006d6f6465"
    "000000001100000066000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f4174747269627574654d6f64653a312e30000e000000"
    "4174747269627574654d6f6465000000020000000c000000415454525f4e"
    "4f524d414c000e000000415454525f524541444f4e4c5900";
    _marshaller_CORBA_AttributeDescription = new _Marshaller_CORBA_AttributeDescription;
    CORBA::_tc_OperationMode = 
    "010000001100000062000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f4f7065726174696f6e4d6f64653a312e30000e000000"
    "4f7065726174696f6e4d6f6465000000020000000a0000004f505f4e4f52"
    "4d414c0000000a0000004f505f4f4e4557415900";
    _marshaller_CORBA_OperationMode = new _Marshaller_CORBA_OperationMode;
    CORBA::_tc_ParameterMode = 
    "010000001100000074000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f506172616d657465724d6f64653a312e30000e000000"
    "506172616d657465724d6f64650000000300000009000000504152414d5f"
    "494e000000000a000000504152414d5f4f55540000000c00000050415241"
    "4d5f494e4f555400";
    _marshaller_CORBA_ParameterMode = new _Marshaller_CORBA_ParameterMode;
    CORBA::_tc_ParameterDescription = 
    "010000000f00000090010000010000002b00000049444c3a6f6d672e6f72"
    "672f434f5242412f506172616d657465724465736372697074696f6e3a31"
    "2e30000015000000506172616d657465724465736372697074696f6e0000"
    "000004000000050000006e616d6500000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "000000000500000074797065000000000c00000009000000747970655f64"
    "6566000000000e00000034000000010000001e00000049444c3a6f6d672e"
    "6f72672f434f5242412f49444c547970653a312e30000000080000004944"
    "4c5479706500050000006d6f646500000000110000007400000001000000"
    "2400000049444c3a6f6d672e6f72672f434f5242412f506172616d657465"
    "724d6f64653a312e30000e000000506172616d657465724d6f6465000000"
    "0300000009000000504152414d5f494e000000000a000000504152414d5f"
    "4f55540000000c000000504152414d5f494e4f555400";
    _marshaller_CORBA_ParameterDescription = new _Marshaller_CORBA_ParameterDescription;
    CORBA::_tc_ParDescriptionSeq = 
    "0100000015000000f0010000010000002800000049444c3a6f6d672e6f72"
    "672f434f5242412f5061724465736372697074696f6e5365713a312e3000"
    "120000005061724465736372697074696f6e53657100000013000000a001"
    "0000010000000f00000090010000010000002b00000049444c3a6f6d672e"
    "6f72672f434f5242412f506172616d657465724465736372697074696f6e"
    "3a312e30000015000000506172616d657465724465736372697074696f6e"
    "0000000004000000050000006e616d650000000015000000440000000100"
    "00002100000049444c3a6f6d672e6f72672f434f5242412f4964656e7469"
    "666965723a312e30000000000b0000004964656e74696669657200001200"
    "0000000000000500000074797065000000000c0000000900000074797065"
    "5f646566000000000e00000034000000010000001e00000049444c3a6f6d"
    "672e6f72672f434f5242412f49444c547970653a312e3000000008000000"
    "49444c5479706500050000006d6f64650000000011000000740000000100"
    "00002400000049444c3a6f6d672e6f72672f434f5242412f506172616d65"
    "7465724d6f64653a312e30000e000000506172616d657465724d6f646500"
    "00000300000009000000504152414d5f494e000000000a00000050415241"
    "4d5f4f55540000000c000000504152414d5f494e4f55540000000000";
    CORBA::_tc_ContextIdentifier = 
    "010000001500000094000000010000002800000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e746578744964656e7469666965723a312e3000"
    "12000000436f6e746578744964656e746966696572000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "00001200000000000000";
    CORBA::_tc_ContextIdSeq = 
    "0100000015000000ec000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e7465787449645365713a312e3000000d000000"
    "436f6e7465787449645365710000000013000000a4000000010000001500"
    "000094000000010000002800000049444c3a6f6d672e6f72672f434f5242"
    "412f436f6e746578744964656e7469666965723a312e300012000000436f"
    "6e746578744964656e746966696572000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "0000000000000000";
    CORBA::_tc_ExceptionDefSeq = 
    "01000000150000009c000000010000002600000049444c3a6f6d672e6f72"
    "672f434f5242412f457863657074696f6e4465665365713a312e30000000"
    "10000000457863657074696f6e4465665365710013000000500000000100"
    "00000e0000003d000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f457863657074696f6e4465663a312e3000000d0000004578"
    "63657074696f6e4465660000000000000000";
    CORBA::_tc_ExcDescriptionSeq = 
    "01000000150000002c020000010000002800000049444c3a6f6d672e6f72"
    "672f434f5242412f4578634465736372697074696f6e5365713a312e3000"
    "120000004578634465736372697074696f6e53657100000013000000dc01"
    "0000010000000f000000cc010000010000002b00000049444c3a6f6d672e"
    "6f72672f434f5242412f457863657074696f6e4465736372697074696f6e"
    "3a312e30000015000000457863657074696f6e4465736372697074696f6e"
    "0000000005000000050000006e616d650000000015000000440000000100"
    "00002100000049444c3a6f6d672e6f72672f434f5242412f4964656e7469"
    "666965723a312e30000000000b0000004964656e74696669657200001200"
    "000000000000030000006964000015000000480000000100000023000000"
    "49444c3a6f6d672e6f72672f434f5242412f5265706f7369746f72794964"
    "3a312e3000000d0000005265706f7369746f727949640000000012000000"
    "000000000b000000646566696e65645f696e000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000800000076657273696f6e001500000044000000"
    "010000002200000049444c3a6f6d672e6f72672f434f5242412f56657273"
    "696f6e537065633a312e300000000c00000056657273696f6e5370656300"
    "12000000000000000500000074797065000000000c00000000000000";
    CORBA::_tc_OperationDef = 
    "010000000e0000003d000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f4f7065726174696f6e4465663a312e3000000d000000"
    "4f7065726174696f6e44656600";
    _marshaller_CORBA_OperationDef = new _Marshaller_CORBA_OperationDef;
    CORBA::_tc_OperationDescription = 
    "010000000f00000094070000010000002b00000049444c3a6f6d672e6f72"
    "672f434f5242412f4f7065726174696f6e4465736372697074696f6e3a31"
    "2e300000150000004f7065726174696f6e4465736372697074696f6e0000"
    "000009000000050000006e616d6500000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "000000000300000069640000150000004800000001000000230000004944"
    "4c3a6f6d672e6f72672f434f5242412f5265706f7369746f727949643a31"
    "2e3000000d0000005265706f7369746f7279496400000000120000000000"
    "00000b000000646566696e65645f696e0000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000800000076657273696f6e0015000000440000000100"
    "00002200000049444c3a6f6d672e6f72672f434f5242412f56657273696f"
    "6e537065633a312e300000000c00000056657273696f6e53706563001200"
    "00000000000007000000726573756c7400000c000000050000006d6f6465"
    "000000001100000062000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f4f7065726174696f6e4d6f64653a312e30000e000000"
    "4f7065726174696f6e4d6f6465000000020000000a0000004f505f4e4f52"
    "4d414c0000000a0000004f505f4f4e4557415900000009000000636f6e74"
    "657874730000000015000000ec000000010000002300000049444c3a6f6d"
    "672e6f72672f434f5242412f436f6e7465787449645365713a312e300000"
    "0d000000436f6e7465787449645365710000000013000000a40000000100"
    "00001500000094000000010000002800000049444c3a6f6d672e6f72672f"
    "434f5242412f436f6e746578744964656e7469666965723a312e30001200"
    "0000436f6e746578744964656e7469666965720000001500000044000000"
    "010000002100000049444c3a6f6d672e6f72672f434f5242412f4964656e"
    "7469666965723a312e30000000000b0000004964656e7469666965720000"
    "1200000000000000000000000b000000706172616d657465727300001500"
    "0000f0010000010000002800000049444c3a6f6d672e6f72672f434f5242"
    "412f5061724465736372697074696f6e5365713a312e3000120000005061"
    "724465736372697074696f6e53657100000013000000a001000001000000"
    "0f00000090010000010000002b00000049444c3a6f6d672e6f72672f434f"
    "5242412f506172616d657465724465736372697074696f6e3a312e300000"
    "15000000506172616d657465724465736372697074696f6e000000000400"
    "0000050000006e616d650000000015000000440000000100000021000000"
    "49444c3a6f6d672e6f72672f434f5242412f4964656e7469666965723a31"
    "2e30000000000b0000004964656e74696669657200001200000000000000"
    "0500000074797065000000000c00000009000000747970655f6465660000"
    "00000e00000034000000010000001e00000049444c3a6f6d672e6f72672f"
    "434f5242412f49444c547970653a312e300000000800000049444c547970"
    "6500050000006d6f64650000000011000000740000000100000024000000"
    "49444c3a6f6d672e6f72672f434f5242412f506172616d657465724d6f64"
    "653a312e30000e000000506172616d657465724d6f646500000003000000"
    "09000000504152414d5f494e000000000a000000504152414d5f4f555400"
    "00000c000000504152414d5f494e4f555400000000000b00000065786365"
    "7074696f6e730000150000002c020000010000002800000049444c3a6f6d"
    "672e6f72672f434f5242412f4578634465736372697074696f6e5365713a"
    "312e3000120000004578634465736372697074696f6e5365710000001300"
    "0000dc010000010000000f000000cc010000010000002b00000049444c3a"
    "6f6d672e6f72672f434f5242412f457863657074696f6e44657363726970"
    "74696f6e3a312e30000015000000457863657074696f6e44657363726970"
    "74696f6e0000000005000000050000006e616d6500000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "000012000000000000000300000069640000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000b000000646566696e65645f696e0000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "49640000000012000000000000000800000076657273696f6e0015000000"
    "44000000010000002200000049444c3a6f6d672e6f72672f434f5242412f"
    "56657273696f6e537065633a312e300000000c00000056657273696f6e53"
    "7065630012000000000000000500000074797065000000000c0000000000"
    "0000";
    _marshaller_CORBA_OperationDescription = new _Marshaller_CORBA_OperationDescription;
    CORBA::_tc_RepositoryIdSeq = 
    "0100000015000000a4000000010000002600000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949645365713a312e30000000"
    "100000005265706f7369746f727949645365710013000000580000000100"
    "00001500000048000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f5265706f7369746f727949643a312e3000000d0000005265"
    "706f7369746f7279496400000000120000000000000000000000";
    CORBA::_tc_OpDescriptionSeq = 
    "0100000015000000f4070000010000002700000049444c3a6f6d672e6f72"
    "672f434f5242412f4f704465736372697074696f6e5365713a312e300000"
    "110000004f704465736372697074696f6e5365710000000013000000a407"
    "0000010000000f00000094070000010000002b00000049444c3a6f6d672e"
    "6f72672f434f5242412f4f7065726174696f6e4465736372697074696f6e"
    "3a312e300000150000004f7065726174696f6e4465736372697074696f6e"
    "0000000009000000050000006e616d650000000015000000440000000100"
    "00002100000049444c3a6f6d672e6f72672f434f5242412f4964656e7469"
    "666965723a312e30000000000b0000004964656e74696669657200001200"
    "000000000000030000006964000015000000480000000100000023000000"
    "49444c3a6f6d672e6f72672f434f5242412f5265706f7369746f72794964"
    "3a312e3000000d0000005265706f7369746f727949640000000012000000"
    "000000000b000000646566696e65645f696e000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000800000076657273696f6e001500000044000000"
    "010000002200000049444c3a6f6d672e6f72672f434f5242412f56657273"
    "696f6e537065633a312e300000000c00000056657273696f6e5370656300"
    "120000000000000007000000726573756c7400000c000000050000006d6f"
    "6465000000001100000062000000010000002400000049444c3a6f6d672e"
    "6f72672f434f5242412f4f7065726174696f6e4d6f64653a312e30000e00"
    "00004f7065726174696f6e4d6f6465000000020000000a0000004f505f4e"
    "4f524d414c0000000a0000004f505f4f4e4557415900000009000000636f"
    "6e74657874730000000015000000ec000000010000002300000049444c3a"
    "6f6d672e6f72672f434f5242412f436f6e7465787449645365713a312e30"
    "00000d000000436f6e7465787449645365710000000013000000a4000000"
    "010000001500000094000000010000002800000049444c3a6f6d672e6f72"
    "672f434f5242412f436f6e746578744964656e7469666965723a312e3000"
    "12000000436f6e746578744964656e746966696572000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "00001200000000000000000000000b000000706172616d65746572730000"
    "15000000f0010000010000002800000049444c3a6f6d672e6f72672f434f"
    "5242412f5061724465736372697074696f6e5365713a312e300012000000"
    "5061724465736372697074696f6e53657100000013000000a00100000100"
    "00000f00000090010000010000002b00000049444c3a6f6d672e6f72672f"
    "434f5242412f506172616d657465724465736372697074696f6e3a312e30"
    "000015000000506172616d657465724465736372697074696f6e00000000"
    "04000000050000006e616d65000000001500000044000000010000002100"
    "000049444c3a6f6d672e6f72672f434f5242412f4964656e746966696572"
    "3a312e30000000000b0000004964656e7469666965720000120000000000"
    "00000500000074797065000000000c00000009000000747970655f646566"
    "000000000e00000034000000010000001e00000049444c3a6f6d672e6f72"
    "672f434f5242412f49444c547970653a312e300000000800000049444c54"
    "79706500050000006d6f6465000000001100000074000000010000002400"
    "000049444c3a6f6d672e6f72672f434f5242412f506172616d657465724d"
    "6f64653a312e30000e000000506172616d657465724d6f64650000000300"
    "000009000000504152414d5f494e000000000a000000504152414d5f4f55"
    "540000000c000000504152414d5f494e4f555400000000000b0000006578"
    "63657074696f6e730000150000002c020000010000002800000049444c3a"
    "6f6d672e6f72672f434f5242412f4578634465736372697074696f6e5365"
    "713a312e3000120000004578634465736372697074696f6e536571000000"
    "13000000dc010000010000000f000000cc010000010000002b0000004944"
    "4c3a6f6d672e6f72672f434f5242412f457863657074696f6e4465736372"
    "697074696f6e3a312e30000015000000457863657074696f6e4465736372"
    "697074696f6e0000000005000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "657200001200000000000000030000006964000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000b000000646566696e65645f696e000015000000"
    "48000000010000002300000049444c3a6f6d672e6f72672f434f5242412f"
    "5265706f7369746f727949643a312e3000000d0000005265706f7369746f"
    "727949640000000012000000000000000800000076657273696f6e001500"
    "000044000000010000002200000049444c3a6f6d672e6f72672f434f5242"
    "412f56657273696f6e537065633a312e300000000c00000056657273696f"
    "6e537065630012000000000000000500000074797065000000000c000000"
    "0000000000000000";
    CORBA::_tc_AttrDescriptionSeq = 
    "0100000015000000ac020000010000002900000049444c3a6f6d672e6f72"
    "672f434f5242412f417474724465736372697074696f6e5365713a312e30"
    "0000000013000000417474724465736372697074696f6e53657100001300"
    "000058020000010000000f00000046020000010000002b00000049444c3a"
    "6f6d672e6f72672f434f5242412f41747472696275746544657363726970"
    "74696f6e3a312e3000001500000041747472696275746544657363726970"
    "74696f6e0000000006000000050000006e616d6500000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "000012000000000000000300000069640000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000b000000646566696e65645f696e0000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "49640000000012000000000000000800000076657273696f6e0015000000"
    "44000000010000002200000049444c3a6f6d672e6f72672f434f5242412f"
    "56657273696f6e537065633a312e300000000c00000056657273696f6e53"
    "7065630012000000000000000500000074797065000000000c0000000500"
    "00006d6f6465000000001100000066000000010000002400000049444c3a"
    "6f6d672e6f72672f434f5242412f4174747269627574654d6f64653a312e"
    "30000e0000004174747269627574654d6f6465000000020000000c000000"
    "415454525f4e4f524d414c000e000000415454525f524541444f4e4c5900"
    "000000000000";
    CORBA::InterfaceDef::_tc_FullInterfaceDescription = 
    "010000000f000000840d0000010000003c00000049444c3a6f6d672e6f72"
    "672f434f5242412f496e746572666163654465662f46756c6c496e746572"
    "666163654465736372697074696f6e3a312e30001900000046756c6c496e"
    "746572666163654465736372697074696f6e000000000900000005000000"
    "6e616d65000000001500000044000000010000002100000049444c3a6f6d"
    "672e6f72672f434f5242412f4964656e7469666965723a312e3000000000"
    "0b0000004964656e74696669657200001200000000000000030000006964"
    "00001500000048000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f5265706f7369746f727949643a312e3000000d0000005265"
    "706f7369746f727949640000000012000000000000000b00000064656669"
    "6e65645f696e00001500000048000000010000002300000049444c3a6f6d"
    "672e6f72672f434f5242412f5265706f7369746f727949643a312e300000"
    "0d0000005265706f7369746f727949640000000012000000000000000800"
    "000076657273696f6e001500000044000000010000002200000049444c3a"
    "6f6d672e6f72672f434f5242412f56657273696f6e537065633a312e3000"
    "00000c00000056657273696f6e537065630012000000000000000b000000"
    "6f7065726174696f6e73000015000000f407000001000000270000004944"
    "4c3a6f6d672e6f72672f434f5242412f4f704465736372697074696f6e53"
    "65713a312e300000110000004f704465736372697074696f6e5365710000"
    "000013000000a4070000010000000f00000094070000010000002b000000"
    "49444c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e446573"
    "6372697074696f6e3a312e300000150000004f7065726174696f6e446573"
    "6372697074696f6e0000000009000000050000006e616d65000000001500"
    "000044000000010000002100000049444c3a6f6d672e6f72672f434f5242"
    "412f4964656e7469666965723a312e30000000000b0000004964656e7469"
    "666965720000120000000000000003000000696400001500000048000000"
    "010000002300000049444c3a6f6d672e6f72672f434f5242412f5265706f"
    "7369746f727949643a312e3000000d0000005265706f7369746f72794964"
    "0000000012000000000000000b000000646566696e65645f696e00001500"
    "000048000000010000002300000049444c3a6f6d672e6f72672f434f5242"
    "412f5265706f7369746f727949643a312e3000000d0000005265706f7369"
    "746f727949640000000012000000000000000800000076657273696f6e00"
    "1500000044000000010000002200000049444c3a6f6d672e6f72672f434f"
    "5242412f56657273696f6e537065633a312e300000000c00000056657273"
    "696f6e5370656300120000000000000007000000726573756c7400000c00"
    "0000050000006d6f64650000000011000000620000000100000024000000"
    "49444c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e4d6f64"
    "653a312e30000e0000004f7065726174696f6e4d6f646500000002000000"
    "0a0000004f505f4e4f524d414c0000000a0000004f505f4f4e4557415900"
    "000009000000636f6e74657874730000000015000000ec00000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f436f6e7465787449"
    "645365713a312e3000000d000000436f6e74657874496453657100000000"
    "13000000a400000001000000150000009400000001000000280000004944"
    "4c3a6f6d672e6f72672f434f5242412f436f6e746578744964656e746966"
    "6965723a312e300012000000436f6e746578744964656e74696669657200"
    "00001500000044000000010000002100000049444c3a6f6d672e6f72672f"
    "434f5242412f4964656e7469666965723a312e30000000000b0000004964"
    "656e74696669657200001200000000000000000000000b00000070617261"
    "6d6574657273000015000000f0010000010000002800000049444c3a6f6d"
    "672e6f72672f434f5242412f5061724465736372697074696f6e5365713a"
    "312e3000120000005061724465736372697074696f6e5365710000001300"
    "0000a0010000010000000f00000090010000010000002b00000049444c3a"
    "6f6d672e6f72672f434f5242412f506172616d6574657244657363726970"
    "74696f6e3a312e30000015000000506172616d6574657244657363726970"
    "74696f6e0000000004000000050000006e616d6500000000150000004400"
    "0000010000002100000049444c3a6f6d672e6f72672f434f5242412f4964"
    "656e7469666965723a312e30000000000b0000004964656e746966696572"
    "000012000000000000000500000074797065000000000c00000009000000"
    "747970655f646566000000000e00000034000000010000001e0000004944"
    "4c3a6f6d672e6f72672f434f5242412f49444c547970653a312e30000000"
    "0800000049444c5479706500050000006d6f646500000000110000007400"
    "0000010000002400000049444c3a6f6d672e6f72672f434f5242412f5061"
    "72616d657465724d6f64653a312e30000e000000506172616d657465724d"
    "6f64650000000300000009000000504152414d5f494e000000000a000000"
    "504152414d5f4f55540000000c000000504152414d5f494e4f5554000000"
    "00000b000000657863657074696f6e730000150000002c02000001000000"
    "2800000049444c3a6f6d672e6f72672f434f5242412f4578634465736372"
    "697074696f6e5365713a312e300012000000457863446573637269707469"
    "6f6e53657100000013000000dc010000010000000f000000cc0100000100"
    "00002b00000049444c3a6f6d672e6f72672f434f5242412f457863657074"
    "696f6e4465736372697074696f6e3a312e30000015000000457863657074"
    "696f6e4465736372697074696f6e0000000005000000050000006e616d65"
    "000000001500000044000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f4964656e7469666965723a312e30000000000b000000"
    "4964656e7469666965720000120000000000000003000000696400001500"
    "000048000000010000002300000049444c3a6f6d672e6f72672f434f5242"
    "412f5265706f7369746f727949643a312e3000000d0000005265706f7369"
    "746f727949640000000012000000000000000b000000646566696e65645f"
    "696e00001500000048000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949643a312e3000000d000000"
    "5265706f7369746f72794964000000001200000000000000080000007665"
    "7273696f6e001500000044000000010000002200000049444c3a6f6d672e"
    "6f72672f434f5242412f56657273696f6e537065633a312e300000000c00"
    "000056657273696f6e537065630012000000000000000500000074797065"
    "000000000c00000000000000000000000b00000061747472696275746573"
    "000015000000ac020000010000002900000049444c3a6f6d672e6f72672f"
    "434f5242412f417474724465736372697074696f6e5365713a312e300000"
    "000013000000417474724465736372697074696f6e536571000013000000"
    "58020000010000000f00000046020000010000002b00000049444c3a6f6d"
    "672e6f72672f434f5242412f417474726962757465446573637269707469"
    "6f6e3a312e30000015000000417474726962757465446573637269707469"
    "6f6e0000000006000000050000006e616d65000000001500000044000000"
    "010000002100000049444c3a6f6d672e6f72672f434f5242412f4964656e"
    "7469666965723a312e30000000000b0000004964656e7469666965720000"
    "120000000000000003000000696400001500000048000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f7279"
    "49643a312e3000000d0000005265706f7369746f72794964000000001200"
    "0000000000000b000000646566696e65645f696e00001500000048000000"
    "010000002300000049444c3a6f6d672e6f72672f434f5242412f5265706f"
    "7369746f727949643a312e3000000d0000005265706f7369746f72794964"
    "0000000012000000000000000800000076657273696f6e00150000004400"
    "0000010000002200000049444c3a6f6d672e6f72672f434f5242412f5665"
    "7273696f6e537065633a312e300000000c00000056657273696f6e537065"
    "630012000000000000000500000074797065000000000c00000005000000"
    "6d6f6465000000001100000066000000010000002400000049444c3a6f6d"
    "672e6f72672f434f5242412f4174747269627574654d6f64653a312e3000"
    "0e0000004174747269627574654d6f6465000000020000000c0000004154"
    "54525f4e4f524d414c000e000000415454525f524541444f4e4c59000000"
    "0000000010000000626173655f696e74657266616365730015000000a400"
    "0000010000002600000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949645365713a312e30000000100000005265706f7369"
    "746f72794964536571001300000058000000010000001500000048000000"
    "010000002300000049444c3a6f6d672e6f72672f434f5242412f5265706f"
    "7369746f727949643a312e3000000d0000005265706f7369746f72794964"
    "000000001200000000000000000000000500000074797065000000000c00"
    "00000c00000069735f61627374726163740008000000";
    _marshaller_CORBA_InterfaceDef_FullInterfaceDescription = new _Marshaller_CORBA_InterfaceDef_FullInterfaceDescription;
    CORBA::_tc_InterfaceDef = 
    "010000000e0000003d000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f496e746572666163654465663a312e3000000d000000"
    "496e7465726661636544656600";
    _marshaller_CORBA_InterfaceDef = new _Marshaller_CORBA_InterfaceDef;
    CORBA::_tc_InterfaceDescription = 
    "010000000f00000090020000010000002b00000049444c3a6f6d672e6f72"
    "672f434f5242412f496e746572666163654465736372697074696f6e3a31"
    "2e30000015000000496e746572666163654465736372697074696f6e0000"
    "000006000000050000006e616d6500000000150000004400000001000000"
    "2100000049444c3a6f6d672e6f72672f434f5242412f4964656e74696669"
    "65723a312e30000000000b0000004964656e746966696572000012000000"
    "000000000300000069640000150000004800000001000000230000004944"
    "4c3a6f6d672e6f72672f434f5242412f5265706f7369746f727949643a31"
    "2e3000000d0000005265706f7369746f7279496400000000120000000000"
    "00000b000000646566696e65645f696e0000150000004800000001000000"
    "2300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f"
    "727949643a312e3000000d0000005265706f7369746f7279496400000000"
    "12000000000000000800000076657273696f6e0015000000440000000100"
    "00002200000049444c3a6f6d672e6f72672f434f5242412f56657273696f"
    "6e537065633a312e300000000c00000056657273696f6e53706563001200"
    "00000000000010000000626173655f696e74657266616365730015000000"
    "a4000000010000002600000049444c3a6f6d672e6f72672f434f5242412f"
    "5265706f7369746f727949645365713a312e30000000100000005265706f"
    "7369746f7279496453657100130000005800000001000000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "4964000000001200000000000000000000000c00000069735f6162737472"
    "6163740008000000";
    _marshaller_CORBA_InterfaceDescription = new _Marshaller_CORBA_InterfaceDescription;
    CORBA::_tc_ValueMemberDef = 
    "010000000e00000043000000010000002500000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654d656d6265724465663a312e3000000000"
    "0f00000056616c75654d656d62657244656600";
    _marshaller_CORBA_ValueMemberDef = new _Marshaller_CORBA_ValueMemberDef;
    CORBA::ValueDef::_tc_FullValueDescription = 
    "010000000f00000014140000010000003400000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654465662f46756c6c56616c756544657363"
    "72697074696f6e3a312e30001500000046756c6c56616c75654465736372"
    "697074696f6e000000000f000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "657200001200000000000000030000006964000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000c00000069735f61627374726163740008000000"
    "0a00000069735f637573746f6d000000080000000b000000646566696e65"
    "645f696e00001500000048000000010000002300000049444c3a6f6d672e"
    "6f72672f434f5242412f5265706f7369746f727949643a312e3000000d00"
    "00005265706f7369746f7279496400000000120000000000000008000000"
    "76657273696f6e001500000044000000010000002200000049444c3a6f6d"
    "672e6f72672f434f5242412f56657273696f6e537065633a312e30000000"
    "0c00000056657273696f6e537065630012000000000000000b0000006f70"
    "65726174696f6e73000015000000f4070000010000002700000049444c3a"
    "6f6d672e6f72672f434f5242412f4f704465736372697074696f6e536571"
    "3a312e300000110000004f704465736372697074696f6e53657100000000"
    "13000000a4070000010000000f00000094070000010000002b0000004944"
    "4c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e4465736372"
    "697074696f6e3a312e300000150000004f7065726174696f6e4465736372"
    "697074696f6e0000000009000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "657200001200000000000000030000006964000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000b000000646566696e65645f696e000015000000"
    "48000000010000002300000049444c3a6f6d672e6f72672f434f5242412f"
    "5265706f7369746f727949643a312e3000000d0000005265706f7369746f"
    "727949640000000012000000000000000800000076657273696f6e001500"
    "000044000000010000002200000049444c3a6f6d672e6f72672f434f5242"
    "412f56657273696f6e537065633a312e300000000c00000056657273696f"
    "6e5370656300120000000000000007000000726573756c7400000c000000"
    "050000006d6f646500000000110000006200000001000000240000004944"
    "4c3a6f6d672e6f72672f434f5242412f4f7065726174696f6e4d6f64653a"
    "312e30000e0000004f7065726174696f6e4d6f6465000000020000000a00"
    "00004f505f4e4f524d414c0000000a0000004f505f4f4e45574159000000"
    "09000000636f6e74657874730000000015000000ec000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f436f6e74657874496453"
    "65713a312e3000000d000000436f6e746578744964536571000000001300"
    "0000a4000000010000001500000094000000010000002800000049444c3a"
    "6f6d672e6f72672f434f5242412f436f6e746578744964656e7469666965"
    "723a312e300012000000436f6e746578744964656e746966696572000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "74696669657200001200000000000000000000000b000000706172616d65"
    "74657273000015000000f0010000010000002800000049444c3a6f6d672e"
    "6f72672f434f5242412f5061724465736372697074696f6e5365713a312e"
    "3000120000005061724465736372697074696f6e53657100000013000000"
    "a0010000010000000f00000090010000010000002b00000049444c3a6f6d"
    "672e6f72672f434f5242412f506172616d65746572446573637269707469"
    "6f6e3a312e30000015000000506172616d65746572446573637269707469"
    "6f6e0000000004000000050000006e616d65000000001500000044000000"
    "010000002100000049444c3a6f6d672e6f72672f434f5242412f4964656e"
    "7469666965723a312e30000000000b0000004964656e7469666965720000"
    "12000000000000000500000074797065000000000c000000090000007479"
    "70655f646566000000000e00000034000000010000001e00000049444c3a"
    "6f6d672e6f72672f434f5242412f49444c547970653a312e300000000800"
    "000049444c5479706500050000006d6f6465000000001100000074000000"
    "010000002400000049444c3a6f6d672e6f72672f434f5242412f50617261"
    "6d657465724d6f64653a312e30000e000000506172616d657465724d6f64"
    "650000000300000009000000504152414d5f494e000000000a0000005041"
    "52414d5f4f55540000000c000000504152414d5f494e4f55540000000000"
    "0b000000657863657074696f6e730000150000002c020000010000002800"
    "000049444c3a6f6d672e6f72672f434f5242412f45786344657363726970"
    "74696f6e5365713a312e3000120000004578634465736372697074696f6e"
    "53657100000013000000dc010000010000000f000000cc01000001000000"
    "2b00000049444c3a6f6d672e6f72672f434f5242412f457863657074696f"
    "6e4465736372697074696f6e3a312e30000015000000457863657074696f"
    "6e4465736372697074696f6e0000000005000000050000006e616d650000"
    "00001500000044000000010000002100000049444c3a6f6d672e6f72672f"
    "434f5242412f4964656e7469666965723a312e30000000000b0000004964"
    "656e74696669657200001200000000000000030000006964000015000000"
    "48000000010000002300000049444c3a6f6d672e6f72672f434f5242412f"
    "5265706f7369746f727949643a312e3000000d0000005265706f7369746f"
    "727949640000000012000000000000000b000000646566696e65645f696e"
    "00001500000048000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f5265706f7369746f727949643a312e3000000d0000005265"
    "706f7369746f727949640000000012000000000000000800000076657273"
    "696f6e001500000044000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f56657273696f6e537065633a312e300000000c000000"
    "56657273696f6e5370656300120000000000000005000000747970650000"
    "00000c00000000000000000000000b000000617474726962757465730000"
    "15000000ac020000010000002900000049444c3a6f6d672e6f72672f434f"
    "5242412f417474724465736372697074696f6e5365713a312e3000000000"
    "13000000417474724465736372697074696f6e5365710000130000005802"
    "0000010000000f00000046020000010000002b00000049444c3a6f6d672e"
    "6f72672f434f5242412f4174747269627574654465736372697074696f6e"
    "3a312e300000150000004174747269627574654465736372697074696f6e"
    "0000000006000000050000006e616d650000000015000000440000000100"
    "00002100000049444c3a6f6d672e6f72672f434f5242412f4964656e7469"
    "666965723a312e30000000000b0000004964656e74696669657200001200"
    "000000000000030000006964000015000000480000000100000023000000"
    "49444c3a6f6d672e6f72672f434f5242412f5265706f7369746f72794964"
    "3a312e3000000d0000005265706f7369746f727949640000000012000000"
    "000000000b000000646566696e65645f696e000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000800000076657273696f6e001500000044000000"
    "010000002200000049444c3a6f6d672e6f72672f434f5242412f56657273"
    "696f6e537065633a312e300000000c00000056657273696f6e5370656300"
    "12000000000000000500000074797065000000000c000000050000006d6f"
    "6465000000001100000066000000010000002400000049444c3a6f6d672e"
    "6f72672f434f5242412f4174747269627574654d6f64653a312e30000e00"
    "00004174747269627574654d6f6465000000020000000c00000041545452"
    "5f4e4f524d414c000e000000415454525f524541444f4e4c590000000000"
    "0000080000006d656d626572730015000000b40200000100000025000000"
    "49444c3a6f6d672e6f72672f434f5242412f56616c75654d656d62657253"
    "65713a312e30000000000f00000056616c75654d656d6265725365710000"
    "1300000068020000010000000f0000005802000001000000220000004944"
    "4c3a6f6d672e6f72672f434f5242412f56616c75654d656d6265723a312e"
    "300000000c00000056616c75654d656d6265720007000000050000006e61"
    "6d65000000001500000044000000010000002100000049444c3a6f6d672e"
    "6f72672f434f5242412f4964656e7469666965723a312e30000000000b00"
    "00004964656e746966696572000012000000000000000300000069640000"
    "1500000048000000010000002300000049444c3a6f6d672e6f72672f434f"
    "5242412f5265706f7369746f727949643a312e3000000d0000005265706f"
    "7369746f727949640000000012000000000000000b000000646566696e65"
    "645f696e00001500000048000000010000002300000049444c3a6f6d672e"
    "6f72672f434f5242412f5265706f7369746f727949643a312e3000000d00"
    "00005265706f7369746f7279496400000000120000000000000008000000"
    "76657273696f6e001500000044000000010000002200000049444c3a6f6d"
    "672e6f72672f434f5242412f56657273696f6e537065633a312e30000000"
    "0c00000056657273696f6e53706563001200000000000000050000007479"
    "7065000000000c00000009000000747970655f646566000000000e000000"
    "34000000010000001e00000049444c3a6f6d672e6f72672f434f5242412f"
    "49444c547970653a312e300000000800000049444c547970650007000000"
    "61636365737300001500000040000000010000002100000049444c3a6f6d"
    "672e6f72672f434f5242412f5669736962696c6974793a312e3000000000"
    "0b0000005669736962696c697479000002000000000000000d000000696e"
    "697469616c697a65727300000000150000005c0200000100000025000000"
    "49444c3a6f6d672e6f72672f434f5242412f496e697469616c697a657253"
    "65713a312e30000000000f000000496e697469616c697a65725365710000"
    "1300000010020000010000000f0000000002000001000000220000004944"
    "4c3a6f6d672e6f72672f434f5242412f496e697469616c697a65723a312e"
    "300000000c000000496e697469616c697a65720002000000080000006d65"
    "6d62657273001500000054010000010000002600000049444c3a6f6d672e"
    "6f72672f434f5242412f5374727563744d656d6265725365713a312e3000"
    "0000100000005374727563744d656d626572536571001300000008010000"
    "010000000f000000f8000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5374727563744d656d6265723a312e3000000d000000"
    "5374727563744d656d6265720000000003000000050000006e616d650000"
    "00001500000044000000010000002100000049444c3a6f6d672e6f72672f"
    "434f5242412f4964656e7469666965723a312e30000000000b0000004964"
    "656e74696669657200001200000000000000050000007479706500000000"
    "0c00000009000000747970655f646566000000000e000000340000000100"
    "00001e00000049444c3a6f6d672e6f72672f434f5242412f49444c547970"
    "653a312e300000000800000049444c547970650000000000050000006e61"
    "6d65000000001500000044000000010000002100000049444c3a6f6d672e"
    "6f72672f434f5242412f4964656e7469666965723a312e30000000000b00"
    "00004964656e746966696572000012000000000000000000000015000000"
    "737570706f727465645f696e74657266616365730000000015000000a400"
    "0000010000002600000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949645365713a312e30000000100000005265706f7369"
    "746f72794964536571001300000058000000010000001500000048000000"
    "010000002300000049444c3a6f6d672e6f72672f434f5242412f5265706f"
    "7369746f727949643a312e3000000d0000005265706f7369746f72794964"
    "000000001200000000000000000000001500000061627374726163745f62"
    "6173655f76616c7565730000000015000000a40000000100000026000000"
    "49444c3a6f6d672e6f72672f434f5242412f5265706f7369746f72794964"
    "5365713a312e30000000100000005265706f7369746f7279496453657100"
    "130000005800000001000000150000004800000001000000230000004944"
    "4c3a6f6d672e6f72672f434f5242412f5265706f7369746f727949643a31"
    "2e3000000d0000005265706f7369746f7279496400000000120000000000"
    "0000000000000f00000069735f7472756e63617461626c65000008000000"
    "0b000000626173655f76616c756500001500000048000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f5265706f7369746f7279"
    "49643a312e3000000d0000005265706f7369746f72794964000000001200"
    "0000000000000500000074797065000000000c000000";
    _marshaller_CORBA_ValueDef_FullValueDescription = new _Marshaller_CORBA_ValueDef_FullValueDescription;
    CORBA::_tc_ValueDef = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654465663a312e3000000900000056616c75"
    "6544656600";
    _marshaller_CORBA_ValueDef = new _Marshaller_CORBA_ValueDef;
    CORBA::_tc_ValueDescription = 
    "010000000f000000e4030000010000002700000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654465736372697074696f6e3a312e300000"
    "1100000056616c75654465736372697074696f6e000000000a0000000500"
    "00006e616d65000000001500000044000000010000002100000049444c3a"
    "6f6d672e6f72672f434f5242412f4964656e7469666965723a312e300000"
    "00000b0000004964656e7469666965720000120000000000000003000000"
    "696400001500000048000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949643a312e3000000d000000"
    "5265706f7369746f727949640000000012000000000000000c0000006973"
    "5f616273747261637400080000000a00000069735f637573746f6d000000"
    "080000000b000000646566696e65645f696e000015000000480000000100"
    "00002300000049444c3a6f6d672e6f72672f434f5242412f5265706f7369"
    "746f727949643a312e3000000d0000005265706f7369746f727949640000"
    "000012000000000000000800000076657273696f6e001500000044000000"
    "010000002200000049444c3a6f6d672e6f72672f434f5242412f56657273"
    "696f6e537065633a312e300000000c00000056657273696f6e5370656300"
    "120000000000000015000000737570706f727465645f696e746572666163"
    "65730000000015000000a4000000010000002600000049444c3a6f6d672e"
    "6f72672f434f5242412f5265706f7369746f727949645365713a312e3000"
    "0000100000005265706f7369746f72794964536571001300000058000000"
    "010000001500000048000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949643a312e3000000d000000"
    "5265706f7369746f72794964000000001200000000000000000000001500"
    "000061627374726163745f626173655f76616c7565730000000015000000"
    "a4000000010000002600000049444c3a6f6d672e6f72672f434f5242412f"
    "5265706f7369746f727949645365713a312e30000000100000005265706f"
    "7369746f7279496453657100130000005800000001000000150000004800"
    "0000010000002300000049444c3a6f6d672e6f72672f434f5242412f5265"
    "706f7369746f727949643a312e3000000d0000005265706f7369746f7279"
    "4964000000001200000000000000000000000f00000069735f7472756e63"
    "617461626c650000080000000b000000626173655f76616c756500001500"
    "000048000000010000002300000049444c3a6f6d672e6f72672f434f5242"
    "412f5265706f7369746f727949643a312e3000000d0000005265706f7369"
    "746f72794964000000001200000000000000";
    _marshaller_CORBA_ValueDescription = new _Marshaller_CORBA_ValueDescription;
    CORBA::_tc_ValueBoxDef = 
    "010000000e0000003c000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c7565426f784465663a312e300000000c000000"
    "56616c7565426f7844656600";
    _marshaller_CORBA_ValueBoxDef = new _Marshaller_CORBA_ValueBoxDef;
    _marshaller__seq_CORBA_ValueDef = new _Marshaller__seq_CORBA_ValueDef;
    _marshaller__seq_CORBA_InterfaceDef = new _Marshaller__seq_CORBA_InterfaceDef;
    _marshaller__seq_CORBA_Contained = new _Marshaller__seq_CORBA_Contained;
    _marshaller__seq_CORBA_Initializer = new _Marshaller__seq_CORBA_Initializer;
    _marshaller__seq_CORBA_Container_Description = new _Marshaller__seq_CORBA_Container_Description;
    _marshaller__seq_CORBA_ParameterDescription = new _Marshaller__seq_CORBA_ParameterDescription;
    _marshaller__seq_CORBA_ExceptionDef = new _Marshaller__seq_CORBA_ExceptionDef;
    _marshaller__seq_CORBA_ExceptionDescription = new _Marshaller__seq_CORBA_ExceptionDescription;
    _marshaller__seq_CORBA_OperationDescription = new _Marshaller__seq_CORBA_OperationDescription;
    _marshaller__seq_CORBA_AttributeDescription = new _Marshaller__seq_CORBA_AttributeDescription;
  }
};

static __tc_init_IR __init_IR;

