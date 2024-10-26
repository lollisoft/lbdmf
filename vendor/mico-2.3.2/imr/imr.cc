/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#ifdef __MINGW32__
#include <cstring>
#include <mico/util.h>
#endif
#include <CORBA.h>
#include <mico/throw.h>
#include <mico/template_impl.h>

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ImplementationDef::_tc_ActivationMode; };
#else
CORBA::TypeCodeConst CORBA::ImplementationDef::_tc_ActivationMode;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ImplementationDef::ActivationMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef_ActivationMode, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ImplementationDef::ActivationMode &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef_ActivationMode, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_ImplementationDef_ActivationMode : public CORBA::StaticTypeInfo {
    typedef CORBA::ImplementationDef::ActivationMode _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ImplementationDef_ActivationMode::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ImplementationDef_ActivationMode::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ImplementationDef_ActivationMode::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ImplementationDef_ActivationMode::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_ImplementationDef_ActivationMode::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ImplementationDef_ActivationMode::typecode()
{
  return CORBA::ImplementationDef::_tc_ActivationMode;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef_ActivationMode;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ImplementationDef::_tc_ObjectTag; };
#else
CORBA::TypeCodeConst CORBA::ImplementationDef::_tc_ObjectTag;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ImplementationDef::_tc_ObjectInfo; };
#else
CORBA::TypeCodeConst CORBA::ImplementationDef::_tc_ObjectInfo;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ImplementationDef::ObjectInfo::ObjectInfo()
{
}

CORBA::ImplementationDef::ObjectInfo::ObjectInfo( const ObjectInfo& _s )
{
  repoid = ((ObjectInfo&)_s).repoid;
  tag = ((ObjectInfo&)_s).tag;
}

CORBA::ImplementationDef::ObjectInfo::~ObjectInfo()
{
}

CORBA::ImplementationDef::ObjectInfo&
CORBA::ImplementationDef::ObjectInfo::operator=( const ObjectInfo& _s )
{
  repoid = ((ObjectInfo&)_s).repoid;
  tag = ((ObjectInfo&)_s).tag;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ImplementationDef::ObjectInfo &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef_ObjectInfo, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ImplementationDef::ObjectInfo *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ImplementationDef::ObjectInfo &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef_ObjectInfo, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ImplementationDef::ObjectInfo *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ImplementationDef_ObjectInfo, (void *&)_s);
}

class _Marshaller_CORBA_ImplementationDef_ObjectInfo : public CORBA::StaticTypeInfo {
    typedef CORBA::ImplementationDef::ObjectInfo _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ImplementationDef_ObjectInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ImplementationDef_ObjectInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ImplementationDef_ObjectInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ImplementationDef_ObjectInfo::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->repoid.inout() ) &&
    CORBA::_stcseq_octet->demarshal( dc, &((_MICO_T*)v)->tag ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ImplementationDef_ObjectInfo::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->repoid.inout() );
  CORBA::_stcseq_octet->marshal( ec, &((_MICO_T*)v)->tag );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ImplementationDef_ObjectInfo::typecode()
{
  return CORBA::ImplementationDef::_tc_ObjectInfo;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef_ObjectInfo;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ImplementationDef::_tc_ObjectInfoList; };
#else
CORBA::TypeCodeConst CORBA::ImplementationDef::_tc_ObjectInfoList;
#endif


// Stub interface ImplementationDef
CORBA::ImplementationDef::~ImplementationDef()
{
}

void *CORBA::ImplementationDef::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ImplementationDef:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::ImplementationDef::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ImplementationDef:1.0" ) == 0) {
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

CORBA::ImplementationDef_ptr CORBA::ImplementationDef::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ImplementationDef:1.0" )))
      return _duplicate( (CORBA::ImplementationDef_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ImplementationDef:1.0" ) ) ) {
      _o = new CORBA::ImplementationDef_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ImplementationDef_ptr
CORBA::ImplementationDef::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ImplementationDef_stub::~ImplementationDef_stub()
{
}

CORBA::ImplementationDef::ActivationMode CORBA::ImplementationDef_stub::mode()
{
  CORBA::ImplementationDef::ActivationMode _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef_ActivationMode, &_res );

  CORBA::StaticRequest __req( this, "_get_mode" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ImplementationDef_stub::mode( CORBA::ImplementationDef::ActivationMode _value )
{
  CORBA::StaticAny __value( _marshaller_CORBA_ImplementationDef_ActivationMode, &_value );
  CORBA::StaticRequest __req( this, "_set_mode" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ImplementationDef::ObjectInfoList* CORBA::ImplementationDef_stub::objs()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo );

  CORBA::StaticRequest __req( this, "_get_objs" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ImplementationDef::ObjectInfoList*) __res._retn();
}


void CORBA::ImplementationDef_stub::objs( const CORBA::ImplementationDef::ObjectInfoList& _value )
{
  CORBA::StaticAny __value( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &_value );
  CORBA::StaticRequest __req( this, "_set_objs" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


char* CORBA::ImplementationDef_stub::name()
{
  char* _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_name" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


char* CORBA::ImplementationDef_stub::command()
{
  char* _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_command" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ImplementationDef_stub::command( const char* _value )
{
  CORBA::StaticAny __value( CORBA::_stc_string, &_value );
  CORBA::StaticRequest __req( this, "_set_command" );
  __req.add_in_arg( &__value );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


char* CORBA::ImplementationDef_stub::tostring()
{
  char* _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "_get_tostring" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ImplementationDef::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ImplementationDef::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ImplementationDef; };
#else
CORBA::TypeCodeConst CORBA::_tc_ImplementationDef;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ImplementationDef_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ImplementationDef_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplementationDef, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ImplementationDef_ptr &_obj )
{
  CORBA::ImplementationDef_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ImplementationDef, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ImplementationDef : public CORBA::StaticTypeInfo {
    typedef CORBA::ImplementationDef_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ImplementationDef::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ImplementationDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ImplementationDef::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ImplementationDef::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ImplementationDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ImplementationDef::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ImplementationDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ImplementationDef::typecode()
{
  return CORBA::_tc_ImplementationDef;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst ImplRepository::_tc_ImplDefSeq; };
#else
CORBA::TypeCodeConst CORBA::ImplRepository::_tc_ImplDefSeq;
#endif


// Stub interface ImplRepository
CORBA::ImplRepository::~ImplRepository()
{
}

void *CORBA::ImplRepository::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/ImplRepository:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::ImplRepository::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/ImplRepository:1.0" ) == 0) {
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

CORBA::ImplRepository_ptr CORBA::ImplRepository::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::ImplRepository_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/ImplRepository:1.0" )))
      return _duplicate( (CORBA::ImplRepository_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/ImplRepository:1.0" ) ) ) {
      _o = new CORBA::ImplRepository_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::ImplRepository_ptr
CORBA::ImplRepository::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::ImplRepository_stub::~ImplRepository_stub()
{
}

CORBA::ImplementationDef_ptr CORBA::ImplRepository_stub::restore( const char* asstring )
{
  CORBA::StaticAny _asstring( CORBA::_stc_string, &asstring );
  CORBA::ImplementationDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef, &_res );

  CORBA::StaticRequest __req( this, "restore" );
  __req.add_in_arg( &_asstring );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::ImplementationDef_ptr CORBA::ImplRepository_stub::create( CORBA::ImplementationDef::ActivationMode mode, const CORBA::ImplementationDef::ObjectInfoList& objs, const char* name, const char* command )
{
  CORBA::StaticAny _mode( _marshaller_CORBA_ImplementationDef_ActivationMode, &mode );
  CORBA::StaticAny _objs( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &objs );
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny _command( CORBA::_stc_string, &command );
  CORBA::ImplementationDef_ptr _res;
  CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef, &_res );

  CORBA::StaticRequest __req( this, "create" );
  __req.add_in_arg( &_mode );
  __req.add_in_arg( &_objs );
  __req.add_in_arg( &_name );
  __req.add_in_arg( &_command );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::ImplRepository_stub::destroy( CORBA::ImplementationDef_ptr impl_def )
{
  CORBA::StaticAny _impl_def( _marshaller_CORBA_ImplementationDef, &impl_def );
  CORBA::StaticRequest __req( this, "destroy" );
  __req.add_in_arg( &_impl_def );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::ImplRepository::ImplDefSeq* CORBA::ImplRepository_stub::find_by_name( const char* name )
{
  CORBA::StaticAny _name( CORBA::_stc_string, &name );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );

  CORBA::StaticRequest __req( this, "find_by_name" );
  __req.add_in_arg( &_name );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ImplRepository::ImplDefSeq*) __res._retn();
}


CORBA::ImplRepository::ImplDefSeq* CORBA::ImplRepository_stub::find_by_repoid( const char* repoid )
{
  CORBA::StaticAny _repoid( CORBA::_stc_string, &repoid );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );

  CORBA::StaticRequest __req( this, "find_by_repoid" );
  __req.add_in_arg( &_repoid );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ImplRepository::ImplDefSeq*) __res._retn();
}


CORBA::ImplRepository::ImplDefSeq* CORBA::ImplRepository_stub::find_by_repoid_tag( const char* repoid, const CORBA::ImplementationDef::ObjectTag& tag )
{
  CORBA::StaticAny _repoid( CORBA::_stc_string, &repoid );
  CORBA::StaticAny _tag( CORBA::_stcseq_octet, &tag );
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );

  CORBA::StaticRequest __req( this, "find_by_repoid_tag" );
  __req.add_in_arg( &_repoid );
  __req.add_in_arg( &_tag );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ImplRepository::ImplDefSeq*) __res._retn();
}


CORBA::ImplRepository::ImplDefSeq* CORBA::ImplRepository_stub::find_all()
{
  CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );

  CORBA::StaticRequest __req( this, "find_all" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::ImplRepository::ImplDefSeq*) __res._retn();
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * ImplRepository::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::ImplRepository::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ImplRepository; };
#else
CORBA::TypeCodeConst CORBA::_tc_ImplRepository;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::ImplRepository_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplRepository, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::ImplRepository_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ImplRepository, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::ImplRepository_ptr &_obj )
{
  CORBA::ImplRepository_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_ImplRepository, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_ImplRepository : public CORBA::StaticTypeInfo {
    typedef CORBA::ImplRepository_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ImplRepository::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_ImplRepository::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::ImplRepository::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_ImplRepository::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ImplRepository::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::ImplRepository::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_ImplRepository::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ImplRepository::typecode()
{
  return CORBA::_tc_ImplRepository;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ImplRepository;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst OAServer::_tc_ObjSeq; };
#else
CORBA::TypeCodeConst CORBA::OAServer::_tc_ObjSeq;
#endif


// Stub interface OAServer
CORBA::OAServer::~OAServer()
{
}

void *CORBA::OAServer::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/OAServer:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::OAServer::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/OAServer:1.0" ) == 0) {
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

CORBA::OAServer_ptr CORBA::OAServer::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::OAServer_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/OAServer:1.0" )))
      return _duplicate( (CORBA::OAServer_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/OAServer:1.0" ) ) ) {
      _o = new CORBA::OAServer_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::OAServer_ptr
CORBA::OAServer::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::OAServer_stub::~OAServer_stub()
{
}

void CORBA::OAServer_stub::restore_request( const CORBA::OAServer::ObjSeq& objs )
{
  CORBA::StaticAny _objs( CORBA::_stcseq_Object, &objs );
  CORBA::StaticRequest __req( this, "restore_request" );
  __req.add_in_arg( &_objs );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAServer_stub::obj_inactive( CORBA::Object_ptr obj )
{
  CORBA::StaticAny _obj( CORBA::_stc_Object, &obj );
  CORBA::StaticRequest __req( this, "obj_inactive" );
  __req.add_in_arg( &_obj );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAServer_stub::impl_inactive()
{
  CORBA::StaticRequest __req( this, "impl_inactive" );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * OAServer::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::OAServer::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OAServer; };
#else
CORBA::TypeCodeConst CORBA::_tc_OAServer;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::OAServer_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OAServer, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::OAServer_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OAServer, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::OAServer_ptr &_obj )
{
  CORBA::OAServer_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_OAServer, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_OAServer : public CORBA::StaticTypeInfo {
    typedef CORBA::OAServer_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_OAServer::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_OAServer::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::OAServer::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_OAServer::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_OAServer::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::OAServer::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_OAServer::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_OAServer::typecode()
{
  return CORBA::_tc_OAServer;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_OAServer;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst OAMediator::_tc_RefData; };
#else
CORBA::TypeCodeConst CORBA::OAMediator::_tc_RefData;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst OAMediator::_tc_ObjSeq; };
#else
CORBA::TypeCodeConst CORBA::OAMediator::_tc_ObjSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst OAMediator::_tc_ServerId; };
#else
CORBA::TypeCodeConst CORBA::OAMediator::_tc_ServerId;
#endif


// Stub interface OAMediator
CORBA::OAMediator::~OAMediator()
{
}

void *CORBA::OAMediator::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/OAMediator:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::OAMediator::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/OAMediator:1.0" ) == 0) {
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

CORBA::OAMediator_ptr CORBA::OAMediator::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::OAMediator_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/OAMediator:1.0" )))
      return _duplicate( (CORBA::OAMediator_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/OAMediator:1.0" ) ) ) {
      _o = new CORBA::OAMediator_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::OAMediator_ptr
CORBA::OAMediator::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::OAMediator_stub::~OAMediator_stub()
{
}

void CORBA::OAMediator_stub::create_obj( CORBA::Object_ptr objref, const CORBA::OAMediator::RefData& id, CORBA::Object_ptr& remote_objref, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _id( CORBA::_stcseq_octet, &id );
  CORBA::StaticAny _remote_objref( CORBA::_stc_Object, &remote_objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "create_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_id );
  __req.add_out_arg( &_remote_objref );
  __req.add_in_arg( &_svid );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::restore_obj( CORBA::Object_ptr objref, CORBA::Object_ptr& remote_objref, CORBA::OAMediator::RefData*& id, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _remote_objref( CORBA::_stc_Object, &remote_objref );
  CORBA::StaticAny _id( CORBA::_stcseq_octet );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "restore_obj" );
  __req.add_in_arg( &_objref );
  __req.add_inout_arg( &_remote_objref );
  __req.add_out_arg( &_id );
  __req.add_in_arg( &_svid );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  id = (CORBA::OAMediator::RefData*) _id._retn();
}


void CORBA::OAMediator_stub::activate_obj( CORBA::Object_ptr objref, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "activate_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_svid );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::deactivate_obj( CORBA::Object_ptr objref, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "deactivate_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_svid );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::migrate_obj( CORBA::Object_ptr objref, CORBA::OAMediator::ServerId svid, CORBA::ImplementationDef_ptr impl )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl );
  CORBA::StaticRequest __req( this, "migrate_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_svid );
  __req.add_in_arg( &_impl );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::orphan_obj( CORBA::Object_ptr objref, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "orphan_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_svid );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::dispose_obj( CORBA::Object_ptr objref, CORBA::OAMediator::ServerId svid )
{
  CORBA::StaticAny _objref( CORBA::_stc_Object, &objref );
  CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
  CORBA::StaticRequest __req( this, "dispose_obj" );
  __req.add_in_arg( &_objref );
  __req.add_in_arg( &_svid );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::create_impl( CORBA::ImplementationDef_ptr impl, CORBA::OAServer_ptr server, CORBA::OAMediator::ServerId& id )
{
  CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl );
  CORBA::StaticAny _server( _marshaller_CORBA_OAServer, &server );
  CORBA::StaticAny _id( CORBA::_stc_ulong, &id );
  CORBA::StaticRequest __req( this, "create_impl" );
  __req.add_in_arg( &_impl );
  __req.add_in_arg( &_server );
  __req.add_inout_arg( &_id );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::activate_impl( CORBA::OAMediator::ServerId id )
{
  CORBA::StaticAny _id( CORBA::_stc_ulong, &id );
  CORBA::StaticRequest __req( this, "activate_impl" );
  __req.add_in_arg( &_id );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::OAMediator_stub::deactivate_impl( CORBA::OAMediator::ServerId id )
{
  CORBA::StaticAny _id( CORBA::_stc_ulong, &id );
  CORBA::StaticRequest __req( this, "deactivate_impl" );
  __req.add_in_arg( &_id );

  __req.oneway();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Object_ptr CORBA::OAMediator_stub::get_remote_object( const CORBA::OAMediator::RefData& key )
{
  CORBA::StaticAny _key( CORBA::_stcseq_octet, &key );
  CORBA::Object_ptr _res;
  CORBA::StaticAny __res( CORBA::_stc_Object, &_res );

  CORBA::StaticRequest __req( this, "get_remote_object" );
  __req.add_in_arg( &_key );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::OAMediator_stub::dispose_impl( CORBA::OAMediator::ServerId id )
{
  CORBA::StaticAny _id( CORBA::_stc_ulong, &id );
  CORBA::StaticRequest __req( this, "dispose_impl" );
  __req.add_in_arg( &_id );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::OAMediator::ObjSeq* CORBA::OAMediator_stub::get_restore_objs( CORBA::OAMediator::ServerId id )
{
  CORBA::StaticAny _id( CORBA::_stc_ulong, &id );
  CORBA::StaticAny __res( CORBA::_stcseq_Object );

  CORBA::StaticRequest __req( this, "get_restore_objs" );
  __req.add_in_arg( &_id );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (CORBA::OAMediator::ObjSeq*) __res._retn();
}


CORBA::Boolean CORBA::OAMediator_stub::force_activation( CORBA::ImplementationDef_ptr impl )
{
  CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "force_activation" );
  __req.add_in_arg( &_impl );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * OAMediator::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::OAMediator::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_OAMediator; };
#else
CORBA::TypeCodeConst CORBA::_tc_OAMediator;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::OAMediator_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OAMediator, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::OAMediator_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_OAMediator, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::OAMediator_ptr &_obj )
{
  CORBA::OAMediator_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_OAMediator, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_OAMediator : public CORBA::StaticTypeInfo {
    typedef CORBA::OAMediator_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_OAMediator::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_OAMediator::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::OAMediator::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_OAMediator::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_OAMediator::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::OAMediator::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_OAMediator::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_OAMediator::typecode()
{
  return CORBA::_tc_OAMediator;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_OAMediator;


// Stub interface POAMediator
CORBA::POAMediator::~POAMediator()
{
}

void *CORBA::POAMediator::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/POAMediator:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::POAMediator::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/POAMediator:1.0" ) == 0) {
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

CORBA::POAMediator_ptr CORBA::POAMediator::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::POAMediator_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/POAMediator:1.0" )))
      return _duplicate( (CORBA::POAMediator_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/POAMediator:1.0" ) ) ) {
      _o = new CORBA::POAMediator_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::POAMediator_ptr
CORBA::POAMediator::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::POAMediator_stub::~POAMediator_stub()
{
}

char* CORBA::POAMediator_stub::create_impl( const char* svid, const char* ior )
{
  CORBA::StaticAny _svid( CORBA::_stc_string, &svid );
  CORBA::StaticAny _ior( CORBA::_stc_string, &ior );
  char* _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "create_impl" );
  __req.add_in_arg( &_svid );
  __req.add_in_arg( &_ior );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::POAMediator_stub::activate_impl( const char* svid )
{
  CORBA::StaticAny _svid( CORBA::_stc_string, &svid );
  CORBA::StaticRequest __req( this, "activate_impl" );
  __req.add_in_arg( &_svid );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void CORBA::POAMediator_stub::deactivate_impl( const char* svid )
{
  CORBA::StaticAny _svid( CORBA::_stc_string, &svid );
  CORBA::StaticRequest __req( this, "deactivate_impl" );
  __req.add_in_arg( &_svid );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean CORBA::POAMediator_stub::force_activation( CORBA::ImplementationDef_ptr impl )
{
  CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "force_activation" );
  __req.add_in_arg( &_impl );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * POAMediator::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::POAMediator::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_POAMediator; };
#else
CORBA::TypeCodeConst CORBA::_tc_POAMediator;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::POAMediator_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_POAMediator, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::POAMediator_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_POAMediator, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::POAMediator_ptr &_obj )
{
  CORBA::POAMediator_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_POAMediator, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_POAMediator : public CORBA::StaticTypeInfo {
    typedef CORBA::POAMediator_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_POAMediator::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_POAMediator::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::POAMediator::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_POAMediator::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_POAMediator::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::POAMediator::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_POAMediator::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_POAMediator::typecode()
{
  return CORBA::_tc_POAMediator;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_POAMediator;

class _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ImplementationDef_ObjectInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ImplementationDef_ObjectInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "0000000000000013000000e4000000000000000f000000d4000000000000"
    "003349444c3a6f6d672e6f72672f434f5242412f496d706c656d656e7461"
    "74696f6e4465662f4f626a656374496e666f3a312e3000000000000b4f62"
    "6a656374496e666f000000000002000000077265706f6964000000000012"
    "000000000000000474616700000000150000006000000000000000324944"
    "4c3a6f6d672e6f72672f434f5242412f496d706c656d656e746174696f6e"
    "4465662f4f626a6563745461673a312e300000000000000a4f626a656374"
    "546167000000000000130000000c000000000000000a0000000000000000"
    ))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ImplementationDef_ObjectInfo;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ImplementationDef_ObjectInfo, (void *&)_s);
}


class _Marshaller__seq_CORBA_ImplementationDef : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ImplementationDef::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ImplementationDef::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ImplementationDef::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ImplementationDef::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ImplementationDef->demarshal( dc, &(*(_MICO_T*)v)[i].inout() ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ImplementationDef::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ImplementationDef->marshal( ec, &(*(_MICO_T*)v)[i].inout() );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ImplementationDef::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "000000000000001300000058000000000000000e00000046000000000000"
    "002849444c3a6f6d672e6f72672f434f5242412f496d706c656d656e7461"
    "74696f6e4465663a312e300000000012496d706c656d656e746174696f6e"
    "44656600000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ImplementationDef::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ImplementationDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ImplementationDef, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ImplementationDef, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ImplementationDef, (void *&)_s);
}


struct __tc_init_IMR {
  __tc_init_IMR()
  {
    CORBA::ImplementationDef::_tc_ActivationMode = 
    "0000000000000011000000d8000000000000003749444c3a6f6d672e6f72"
    "672f434f5242412f496d706c656d656e746174696f6e4465662f41637469"
    "766174696f6e4d6f64653a312e3000000000000f41637469766174696f6e"
    "4d6f64650000000000060000000f41637469766174655368617265640000"
    "000000114163746976617465556e73686172656400000000000000124163"
    "7469766174655065724d6574686f64000000000000134163746976617465"
    "50657273697374656e7400000000001041637469766174654c6962726172"
    "79000000000c4163746976617465504f4100";
    _marshaller_CORBA_ImplementationDef_ActivationMode = new _Marshaller_CORBA_ImplementationDef_ActivationMode;
    CORBA::ImplementationDef::_tc_ObjectTag = 
    "000000000000001500000060000000000000003249444c3a6f6d672e6f72"
    "672f434f5242412f496d706c656d656e746174696f6e4465662f4f626a65"
    "63745461673a312e300000000000000a4f626a6563745461670000000000"
    "00130000000c000000000000000a00000000";
    CORBA::ImplementationDef::_tc_ObjectInfo = 
    "000000000000000f000000d4000000000000003349444c3a6f6d672e6f72"
    "672f434f5242412f496d706c656d656e746174696f6e4465662f4f626a65"
    "6374496e666f3a312e3000000000000b4f626a656374496e666f00000000"
    "0002000000077265706f6964000000000012000000000000000474616700"
    "0000001500000060000000000000003249444c3a6f6d672e6f72672f434f"
    "5242412f496d706c656d656e746174696f6e4465662f4f626a6563745461"
    "673a312e300000000000000a4f626a656374546167000000000000130000"
    "000c000000000000000a00000000";
    _marshaller_CORBA_ImplementationDef_ObjectInfo = new _Marshaller_CORBA_ImplementationDef_ObjectInfo;
    CORBA::ImplementationDef::_tc_ObjectInfoList = 
    "000000000000001500000140000000000000003749444c3a6f6d672e6f72"
    "672f434f5242412f496d706c656d656e746174696f6e4465662f4f626a65"
    "6374496e666f4c6973743a312e3000000000000f4f626a656374496e666f"
    "4c697374000000000013000000e4000000000000000f000000d400000000"
    "0000003349444c3a6f6d672e6f72672f434f5242412f496d706c656d656e"
    "746174696f6e4465662f4f626a656374496e666f3a312e3000000000000b"
    "4f626a656374496e666f000000000002000000077265706f696400000000"
    "001200000000000000047461670000000015000000600000000000000032"
    "49444c3a6f6d672e6f72672f434f5242412f496d706c656d656e74617469"
    "6f6e4465662f4f626a6563745461673a312e300000000000000a4f626a65"
    "6374546167000000000000130000000c000000000000000a000000000000"
    "0000";
    CORBA::_tc_ImplementationDef = 
    "000000000000000e00000046000000000000002849444c3a6f6d672e6f72"
    "672f434f5242412f496d706c656d656e746174696f6e4465663a312e3000"
    "00000012496d706c656d656e746174696f6e44656600";
    _marshaller_CORBA_ImplementationDef = new _Marshaller_CORBA_ImplementationDef;
    CORBA::ImplRepository::_tc_ImplDefSeq = 
    "0000000000000015000000a8000000000000003049444c3a6f6d672e6f72"
    "672f434f5242412f496d706c5265706f7369746f72792f496d706c446566"
    "5365713a312e30000000000b496d706c4465665365710000000000130000"
    "0058000000000000000e00000046000000000000002849444c3a6f6d672e"
    "6f72672f434f5242412f496d706c656d656e746174696f6e4465663a312e"
    "300000000012496d706c656d656e746174696f6e44656600000000000000"
    ;
    CORBA::_tc_ImplRepository = 
    "000000000000000e00000043000000000000002549444c3a6f6d672e6f72"
    "672f434f5242412f496d706c5265706f7369746f72793a312e3000000000"
    "0000000f496d706c5265706f7369746f727900";
    _marshaller_CORBA_ImplRepository = new _Marshaller_CORBA_ImplRepository;
    CORBA::OAServer::_tc_ObjSeq = 
    "000000000000001500000088000000000000002649444c3a6f6d672e6f72"
    "672f434f5242412f4f415365727665722f4f626a5365713a312e30000000"
    "000000074f626a53657100000000001300000044000000000000000e0000"
    "0033000000000000001d49444c3a6f6d672e6f72672f434f5242412f4f62"
    "6a6563743a312e3000000000000000074f626a656374000000000000";
    CORBA::_tc_OAServer = 
    "000000000000000e00000035000000000000001f49444c3a6f6d672e6f72"
    "672f434f5242412f4f415365727665723a312e300000000000094f415365"
    "7276657200";
    _marshaller_CORBA_OAServer = new _Marshaller_CORBA_OAServer;
    CORBA::OAMediator::_tc_RefData = 
    "000000000000001500000054000000000000002949444c3a6f6d672e6f72"
    "672f434f5242412f4f414d65646961746f722f526566446174613a312e30"
    "00000000000000085265664461746100000000130000000c000000000000"
    "000a00000000";
    CORBA::OAMediator::_tc_ObjSeq = 
    "000000000000001500000088000000000000002849444c3a6f6d672e6f72"
    "672f434f5242412f4f414d65646961746f722f4f626a5365713a312e3000"
    "000000074f626a53657100000000001300000044000000000000000e0000"
    "0033000000000000001d49444c3a6f6d672e6f72672f434f5242412f4f62"
    "6a6563743a312e3000000000000000074f626a656374000000000000";
    CORBA::OAMediator::_tc_ServerId = 
    "000000000000001500000048000000000000002a49444c3a6f6d672e6f72"
    "672f434f5242412f4f414d65646961746f722f53657276657249643a312e"
    "300000000000000953657276657249640000000000000005";
    CORBA::_tc_OAMediator = 
    "000000000000000e0000003b000000000000002149444c3a6f6d672e6f72"
    "672f434f5242412f4f414d65646961746f723a312e30000000000000000b"
    "4f414d65646961746f7200";
    _marshaller_CORBA_OAMediator = new _Marshaller_CORBA_OAMediator;
    CORBA::_tc_POAMediator = 
    "000000000000000e0000003c000000000000002249444c3a6f6d672e6f72"
    "672f434f5242412f504f414d65646961746f723a312e300000000000000c"
    "504f414d65646961746f7200";
    _marshaller_CORBA_POAMediator = new _Marshaller_CORBA_POAMediator;
    _marshaller__seq_CORBA_ImplementationDef_ObjectInfo = new _Marshaller__seq_CORBA_ImplementationDef_ObjectInfo;
    _marshaller__seq_CORBA_ImplementationDef = new _Marshaller__seq_CORBA_ImplementationDef;
  }
};

static __tc_init_IMR __init_IMR;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

CORBA::ImplementationDef_skel::ImplementationDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  /*
   * this one is special: we cannot create an ImplementationDef for
   * ImplementationDef...
   * use a NIL ImplementationDef and pass in the repository id as 4th
   * argument to create_ref()
   */
  _create_ref (_id, CORBA::InterfaceDef::_nil(),
	       CORBA::ImplementationDef::_nil(),
	       "IDL:omg.org/CORBA/ImplementationDef:1.0");
  
  register_dispatcher (
 	new StaticInterfaceDispatcherWrapper<ImplementationDef_skel> (this));
}

CORBA::ImplementationDef_skel::ImplementationDef_skel( CORBA::Object_ptr _obj )
{
  /*
   * this one is special: we cannot create an ImplementationDef for
   * ImplementationDef...
   * use a NIL ImplementationDef and pass in the repository id as 4th
   * argument to create_ref()
   */
  _restore_ref (_obj,
		CORBA::BOA::ReferenceData(),
		CORBA::InterfaceDef::_nil(),
		CORBA::ImplementationDef::_nil());
 
  register_dispatcher (
 	new StaticInterfaceDispatcherWrapper<ImplementationDef_skel> (this));
}

CORBA::ImplementationDef_skel::~ImplementationDef_skel()
{
}

bool CORBA::ImplementationDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 13)) {
    case 1:
      if( strcmp( _req->op_name(), "_get_name" ) == 0 ) {
        char* _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = name();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_get_objs" ) == 0 ) {
        ObjectInfoList* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = objs();
        __res.value( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "_get_tostring" ) == 0 ) {
        char* _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = tostring();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 9:
      if( strcmp( _req->op_name(), "_get_mode" ) == 0 ) {
        ActivationMode _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef_ActivationMode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = mode();
        _req->write_results();
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "_get_command" ) == 0 ) {
        char* _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = command();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 11:
      if( strcmp( _req->op_name(), "_set_mode" ) == 0 ) {
        ActivationMode _value;
        CORBA::StaticAny __value( _marshaller_CORBA_ImplementationDef_ActivationMode, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        mode( _value );
        _req->write_results();
        return true;
      }
      break;
    case 12:
      if( strcmp( _req->op_name(), "_set_objs" ) == 0 ) {
        ObjectInfoList _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        objs( _value );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_command" ) == 0 ) {
        CORBA::String_var _value;
        CORBA::StaticAny __value( CORBA::_stc_string, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        command( _value );
        _req->write_results();
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    _req->set_exception( _ex->_clone() );
    _req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

CORBA::ImplementationDef_ptr CORBA::ImplementationDef_skel::_this()
{
  return CORBA::ImplementationDef::_duplicate( this );
}


CORBA::ImplRepository_skel::ImplRepository_skel( const CORBA::BOA::ReferenceData &_id )
{
  /*
   * this one is special: we can not create an ImplementationDef for
   * ImplRepository, because creating an ImplementationDef needs
   * a running ImplRespository...
   * use a NIL ImplementationDef and pass in the repository id as 4th
   * argument to create_ref()
   */
  _create_ref (_id, CORBA::InterfaceDef::_nil(),
	       CORBA::ImplementationDef::_nil(),
	       "IDL:omg.org/CORBA/ImplRepository:1.0");
  
  register_dispatcher (
	   new StaticInterfaceDispatcherWrapper<ImplRepository_skel> (this));
}

CORBA::ImplRepository_skel::ImplRepository_skel( CORBA::Object_ptr _obj )
{
  /*
   * this one is special: we can not create an ImplementationDef for
   * ImplRepository, because creating an ImplementationDef needs
   * a running ImplRespository...
   * use a NIL ImplementationDef and pass in the repository id as 4th
   * argument to create_ref()
   */
  _restore_ref (_obj,
		CORBA::BOA::ReferenceData(),
		CORBA::InterfaceDef::_nil(),
		CORBA::ImplementationDef::_nil());
  
  register_dispatcher (
	   new StaticInterfaceDispatcherWrapper<ImplRepository_skel> (this));
}

CORBA::ImplRepository_skel::~ImplRepository_skel()
{
}

bool CORBA::ImplRepository_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 11)) {
    case 1:
      if( strcmp( _req->op_name(), "destroy" ) == 0 ) {
        ImplementationDef_var impl_def;
        CORBA::StaticAny _impl_def( _marshaller_CORBA_ImplementationDef, &impl_def.inout() );

        _req->add_in_arg( &_impl_def );

        if( !_req->read_args() )
          return true;

        destroy( impl_def );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "find_by_name" ) == 0 ) {
        CORBA::String_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );

        ImplDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );
        _req->add_in_arg( &_name );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find_by_name( name );
        __res.value( _marshaller__seq_CORBA_ImplementationDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "find_by_repoid" ) == 0 ) {
        CORBA::String_var repoid;
        CORBA::StaticAny _repoid( CORBA::_stc_string, &repoid.inout() );

        ImplDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );
        _req->add_in_arg( &_repoid );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find_by_repoid( repoid );
        __res.value( _marshaller__seq_CORBA_ImplementationDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "create" ) == 0 ) {
        ImplementationDef::ActivationMode mode;
        CORBA::StaticAny _mode( _marshaller_CORBA_ImplementationDef_ActivationMode, &mode );
        ImplementationDef::ObjectInfoList objs;
        CORBA::StaticAny _objs( _marshaller__seq_CORBA_ImplementationDef_ObjectInfo, &objs );
        CORBA::String_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        CORBA::String_var command;
        CORBA::StaticAny _command( CORBA::_stc_string, &command.inout() );

        ImplementationDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef, &_res );
        _req->add_in_arg( &_mode );
        _req->add_in_arg( &_objs );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_command );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create( mode, objs, name, command );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "find_by_repoid_tag" ) == 0 ) {
        CORBA::String_var repoid;
        CORBA::StaticAny _repoid( CORBA::_stc_string, &repoid.inout() );
        ImplementationDef::ObjectTag tag;
        CORBA::StaticAny _tag( CORBA::_stcseq_octet, &tag );

        ImplDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );
        _req->add_in_arg( &_repoid );
        _req->add_in_arg( &_tag );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find_by_repoid_tag( repoid, tag );
        __res.value( _marshaller__seq_CORBA_ImplementationDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 9:
      if( strcmp( _req->op_name(), "restore" ) == 0 ) {
        CORBA::String_var asstring;
        CORBA::StaticAny _asstring( CORBA::_stc_string, &asstring.inout() );

        ImplementationDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ImplementationDef, &_res );
        _req->add_in_arg( &_asstring );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = restore( asstring );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "find_all" ) == 0 ) {
        ImplDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ImplementationDef );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find_all();
        __res.value( _marshaller__seq_CORBA_ImplementationDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    _req->set_exception( _ex->_clone() );
    _req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

CORBA::ImplRepository_ptr CORBA::ImplRepository_skel::_this()
{
  return CORBA::ImplRepository::_duplicate( this );
}


CORBA::OAServer_skel::OAServer_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OAServer:1.0", "OAServer" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/OAServer:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OAServer_skel>( this ) );
}

CORBA::OAServer_skel::OAServer_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OAServer:1.0", "OAServer" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OAServer_skel>( this ) );
}

CORBA::OAServer_skel::~OAServer_skel()
{
}

bool CORBA::OAServer_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "restore_request" ) == 0 ) {
      ObjSeq objs;
      CORBA::StaticAny _objs( CORBA::_stcseq_Object, &objs );

      _req->add_in_arg( &_objs );

      if( !_req->read_args() )
        return true;

      restore_request( objs );
      _req->write_results();
      return true;
    }
    if( strcmp( _req->op_name(), "obj_inactive" ) == 0 ) {
      CORBA::Object_var obj;
      CORBA::StaticAny _obj( CORBA::_stc_Object, &obj.inout() );

      _req->add_in_arg( &_obj );

      if( !_req->read_args() )
        return true;

      obj_inactive( obj );
      _req->write_results();
      return true;
    }
    if( strcmp( _req->op_name(), "impl_inactive" ) == 0 ) {

      if( !_req->read_args() )
        return true;

      impl_inactive();
      _req->write_results();
      return true;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    _req->set_exception( _ex->_clone() );
    _req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

CORBA::OAServer_ptr CORBA::OAServer_skel::_this()
{
  return CORBA::OAServer::_duplicate( this );
}


CORBA::OAMediator_skel::OAMediator_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OAMediator:1.0", "OAMediator" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/OAMediator:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OAMediator_skel>( this ) );
}

CORBA::OAMediator_skel::OAMediator_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OAMediator:1.0", "OAMediator" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OAMediator_skel>( this ) );
}

CORBA::OAMediator_skel::~OAMediator_skel()
{
}

bool CORBA::OAMediator_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 23)) {
    case 0:
      if( strcmp( _req->op_name(), "force_activation" ) == 0 ) {
        ImplementationDef_var impl;
        CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl.inout() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->add_in_arg( &_impl );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = force_activation( impl );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "dispose_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        dispose_obj( objref, svid );
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "deactivate_impl" ) == 0 ) {
        ServerId id;
        CORBA::StaticAny _id( CORBA::_stc_ulong, &id );

        _req->add_in_arg( &_id );

        if( !_req->read_args() )
          return true;

        deactivate_impl( id );
        _req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "deactivate_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        deactivate_obj( objref, svid );
        _req->write_results();
        return true;
      }
      break;
    case 9:
      if( strcmp( _req->op_name(), "activate_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        activate_obj( objref, svid );
        _req->write_results();
        return true;
      }
      break;
    case 11:
      if( strcmp( _req->op_name(), "restore_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        CORBA::Object_var remote_objref ((CORBA::Boolean)FALSE);
        CORBA::StaticAny _remote_objref( CORBA::_stc_Object, &remote_objref.inout() );
        RefData* id;
        CORBA::StaticAny _id( CORBA::_stcseq_octet );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_inout_arg( &_remote_objref );
        _req->add_out_arg( &_id );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        restore_obj( objref, remote_objref, id, svid );
        _id.value( CORBA::_stcseq_octet, id );
        _req->write_results();
        delete id;
        return true;
      }
      break;
    case 12:
      if( strcmp( _req->op_name(), "migrate_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );
        ImplementationDef_var impl;
        CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl.inout() );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_svid );
        _req->add_in_arg( &_impl );

        if( !_req->read_args() )
          return true;

        migrate_obj( objref, svid, impl );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "activate_impl" ) == 0 ) {
        ServerId id;
        CORBA::StaticAny _id( CORBA::_stc_ulong, &id );

        _req->add_in_arg( &_id );

        if( !_req->read_args() )
          return true;

        activate_impl( id );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "dispose_impl" ) == 0 ) {
        ServerId id;
        CORBA::StaticAny _id( CORBA::_stc_ulong, &id );

        _req->add_in_arg( &_id );

        if( !_req->read_args() )
          return true;

        dispose_impl( id );
        _req->write_results();
        return true;
      }
      break;
    case 13:
      if( strcmp( _req->op_name(), "orphan_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        orphan_obj( objref, svid );
        _req->write_results();
        return true;
      }
      break;
    case 16:
      if( strcmp( _req->op_name(), "create_obj" ) == 0 ) {
        CORBA::Object_var objref;
        CORBA::StaticAny _objref( CORBA::_stc_Object, &objref.inout() );
        RefData id;
        CORBA::StaticAny _id( CORBA::_stcseq_octet, &id );
        CORBA::Object_ptr remote_objref;
        CORBA::StaticAny _remote_objref( CORBA::_stc_Object, &remote_objref );
        ServerId svid;
        CORBA::StaticAny _svid( CORBA::_stc_ulong, &svid );

        _req->add_in_arg( &_objref );
        _req->add_in_arg( &_id );
        _req->add_out_arg( &_remote_objref );
        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        create_obj( objref, id, remote_objref, svid );
        _req->write_results();
        CORBA::release( remote_objref );
        return true;
      }
      break;
    case 18:
      if( strcmp( _req->op_name(), "get_remote_object" ) == 0 ) {
        RefData key;
        CORBA::StaticAny _key( CORBA::_stcseq_octet, &key );

        CORBA::Object_ptr _res;
        CORBA::StaticAny __res( CORBA::_stc_Object, &_res );
        _req->add_in_arg( &_key );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = get_remote_object( key );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 21:
      if( strcmp( _req->op_name(), "create_impl" ) == 0 ) {
        ImplementationDef_var impl;
        CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl.inout() );
        OAServer_var server;
        CORBA::StaticAny _server( _marshaller_CORBA_OAServer, &server.inout() );
        ServerId id;
        CORBA::StaticAny _id( CORBA::_stc_ulong, &id );

        _req->add_in_arg( &_impl );
        _req->add_in_arg( &_server );
        _req->add_inout_arg( &_id );

        if( !_req->read_args() )
          return true;

        create_impl( impl, server, id );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "get_restore_objs" ) == 0 ) {
        ServerId id;
        CORBA::StaticAny _id( CORBA::_stc_ulong, &id );

        ObjSeq* _res;
        CORBA::StaticAny __res( CORBA::_stcseq_Object );
        _req->add_in_arg( &_id );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = get_restore_objs( id );
        __res.value( CORBA::_stcseq_Object, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    _req->set_exception( _ex->_clone() );
    _req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

CORBA::OAMediator_ptr CORBA::OAMediator_skel::_this()
{
  return CORBA::OAMediator::_duplicate( this );
}


CORBA::POAMediator_skel::POAMediator_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/POAMediator:1.0", "POAMediator" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/POAMediator:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<POAMediator_skel>( this ) );
}

CORBA::POAMediator_skel::POAMediator_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/POAMediator:1.0", "POAMediator" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<POAMediator_skel>( this ) );
}

CORBA::POAMediator_skel::~POAMediator_skel()
{
}

bool CORBA::POAMediator_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 1:
      if( strcmp( _req->op_name(), "deactivate_impl" ) == 0 ) {
        CORBA::String_var svid;
        CORBA::StaticAny _svid( CORBA::_stc_string, &svid.inout() );

        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        deactivate_impl( svid );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "activate_impl" ) == 0 ) {
        CORBA::String_var svid;
        CORBA::StaticAny _svid( CORBA::_stc_string, &svid.inout() );

        _req->add_in_arg( &_svid );

        if( !_req->read_args() )
          return true;

        activate_impl( svid );
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "force_activation" ) == 0 ) {
        ImplementationDef_var impl;
        CORBA::StaticAny _impl( _marshaller_CORBA_ImplementationDef, &impl.inout() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->add_in_arg( &_impl );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = force_activation( impl );
        _req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "create_impl" ) == 0 ) {
        CORBA::String_var svid;
        CORBA::StaticAny _svid( CORBA::_stc_string, &svid.inout() );
        CORBA::String_var ior;
        CORBA::StaticAny _ior( CORBA::_stc_string, &ior.inout() );

        char* _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->add_in_arg( &_svid );
        _req->add_in_arg( &_ior );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_impl( svid, ior );
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    _req->set_exception( _ex->_clone() );
    _req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

CORBA::POAMediator_ptr CORBA::POAMediator_skel::_this()
{
  return CORBA::POAMediator::_duplicate( this );
}

