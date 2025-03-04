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
namespace CORBA { CORBA::TypeCodeConst _tc_Identifier; };
#else
CORBA::TypeCodeConst CORBA::_tc_Identifier;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_VersionSpec; };
#else
CORBA::TypeCodeConst CORBA::_tc_VersionSpec;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_RepositoryId; };
#else
CORBA::TypeCodeConst CORBA::_tc_RepositoryId;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_DefinitionKind; };
#else
CORBA::TypeCodeConst CORBA::_tc_DefinitionKind;
#endif

void operator<<=( CORBA::Any &_a, const CORBA::DefinitionKind &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_DefinitionKind, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::DefinitionKind &_e )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_DefinitionKind, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_CORBA_DefinitionKind : public CORBA::StaticTypeInfo {
    typedef CORBA::DefinitionKind _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_DefinitionKind::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_DefinitionKind::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_DefinitionKind::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_DefinitionKind::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_CORBA_DefinitionKind::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_DefinitionKind::typecode()
{
  return CORBA::_tc_DefinitionKind;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_DefinitionKind;


// Stub interface IRObject
CORBA::IRObject::~IRObject()
{
}

void *CORBA::IRObject::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/IRObject:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

bool CORBA::IRObject::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/IRObject:1.0" ) == 0) {
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

CORBA::IRObject_ptr CORBA::IRObject::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::IRObject_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/IRObject:1.0" )))
      return _duplicate( (CORBA::IRObject_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/IRObject:1.0" ) ) ) {
      _o = new CORBA::IRObject_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::IRObject_ptr
CORBA::IRObject::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::IRObject_stub::~IRObject_stub()
{
}

CORBA::DefinitionKind CORBA::IRObject_stub::def_kind()
{
  CORBA::DefinitionKind _res;
  CORBA::StaticAny __res( _marshaller_CORBA_DefinitionKind, &_res );

  CORBA::StaticRequest __req( this, "_get_def_kind" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void CORBA::IRObject_stub::destroy()
{
  CORBA::StaticRequest __req( this, "destroy" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * IRObject::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::IRObject::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_IRObject; };
#else
CORBA::TypeCodeConst CORBA::_tc_IRObject;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::IRObject_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_IRObject, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::IRObject_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_IRObject, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::IRObject_ptr &_obj )
{
  CORBA::IRObject_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_IRObject, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_IRObject : public CORBA::StaticTypeInfo {
    typedef CORBA::IRObject_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_IRObject::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_IRObject::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::IRObject::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_IRObject::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_IRObject::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::IRObject::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_IRObject::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_IRObject::typecode()
{
  return CORBA::_tc_IRObject;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_IRObject;


// Stub interface IDLType
CORBA::IDLType::~IDLType()
{
}

void *CORBA::IDLType::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/CORBA/IDLType:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = IRObject::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

bool CORBA::IDLType::_narrow_helper2( CORBA::Object_ptr _obj )
{
  if( strcmp( _obj->_repoid(), "IDL:omg.org/CORBA/IDLType:1.0" ) == 0) {
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

CORBA::IDLType_ptr CORBA::IDLType::_narrow( CORBA::Object_ptr _obj )
{
  CORBA::IDLType_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/CORBA/IDLType:1.0" )))
      return _duplicate( (CORBA::IDLType_ptr) _p );
    if( _narrow_helper2( _obj ) ||
       ( _obj->_is_a_remote( "IDL:omg.org/CORBA/IDLType:1.0" ) ) ) {
      _o = new CORBA::IDLType_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CORBA::IDLType_ptr
CORBA::IDLType::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

CORBA::IDLType_stub::~IDLType_stub()
{
}

CORBA::TypeCode_ptr CORBA::IDLType_stub::type()
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


struct _global_init_CORBA_IDLType {
  _global_init_CORBA_IDLType()
  {
    if( ::CORBA::IRObject::_narrow_helpers == NULL )
      ::CORBA::IRObject::_narrow_helpers = new vector<CORBA::Narrow_proto>;
    ::CORBA::IRObject::_narrow_helpers->push_back( CORBA::IDLType::_narrow_helper2 );
  }
} __global_init_CORBA_IDLType;

#ifdef HAVE_NAMESPACE
namespace CORBA { vector<CORBA::Narrow_proto> * IDLType::_narrow_helpers; };
#else
vector<CORBA::Narrow_proto> * CORBA::IDLType::_narrow_helpers;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_IDLType; };
#else
CORBA::TypeCodeConst CORBA::_tc_IDLType;
#endif

void
operator<<=( CORBA::Any &_a, const CORBA::IDLType_ptr _obj )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_IDLType, &_obj);
  _a.from_static_any (_sa);
}

void
operator<<=( CORBA::Any &_a, CORBA::IDLType_ptr* _obj_ptr )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_IDLType, _obj_ptr);
  _a.from_static_any (_sa);
  CORBA::release (*_obj_ptr);
}

CORBA::Boolean
operator>>=( const CORBA::Any &_a, CORBA::IDLType_ptr &_obj )
{
  CORBA::IDLType_ptr *p;
  if (_a.to_static_any (_marshaller_CORBA_IDLType, (void *&)p)) {
    _obj = *p;
    return TRUE;
  }
  return FALSE;
}

class _Marshaller_CORBA_IDLType : public CORBA::StaticTypeInfo {
    typedef CORBA::IDLType_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_IDLType::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CORBA_IDLType::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CORBA::IDLType::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CORBA_IDLType::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_IDLType::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CORBA::IDLType::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CORBA_IDLType::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::TypeCode_ptr _Marshaller_CORBA_IDLType::typecode()
{
  return CORBA::_tc_IDLType;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_IDLType;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_StructMember; };
#else
CORBA::TypeCodeConst CORBA::_tc_StructMember;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::StructMember::StructMember()
{
}

CORBA::StructMember::StructMember( const StructMember& _s )
{
  name = ((StructMember&)_s).name;
  type = ((StructMember&)_s).type;
  type_def = ((StructMember&)_s).type_def;
}

CORBA::StructMember::~StructMember()
{
}

CORBA::StructMember&
CORBA::StructMember::operator=( const StructMember& _s )
{
  name = ((StructMember&)_s).name;
  type = ((StructMember&)_s).type;
  type_def = ((StructMember&)_s).type_def;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::StructMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StructMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::StructMember *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::StructMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_StructMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::StructMember *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_StructMember, (void *&)_s);
}

class _Marshaller_CORBA_StructMember : public CORBA::StaticTypeInfo {
    typedef CORBA::StructMember _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_StructMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_StructMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_StructMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_StructMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    _marshaller_CORBA_IDLType->demarshal( dc, &((_MICO_T*)v)->type_def.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_StructMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  _marshaller_CORBA_IDLType->marshal( ec, &((_MICO_T*)v)->type_def.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_StructMember::typecode()
{
  return CORBA::_tc_StructMember;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_StructMember;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_StructMemberSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_StructMemberSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_UnionMember; };
#else
CORBA::TypeCodeConst CORBA::_tc_UnionMember;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::UnionMember::UnionMember()
{
}

CORBA::UnionMember::UnionMember( const UnionMember& _s )
{
  name = ((UnionMember&)_s).name;
  label = ((UnionMember&)_s).label;
  type = ((UnionMember&)_s).type;
  type_def = ((UnionMember&)_s).type_def;
}

CORBA::UnionMember::~UnionMember()
{
}

CORBA::UnionMember&
CORBA::UnionMember::operator=( const UnionMember& _s )
{
  name = ((UnionMember&)_s).name;
  label = ((UnionMember&)_s).label;
  type = ((UnionMember&)_s).type;
  type_def = ((UnionMember&)_s).type_def;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::UnionMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_UnionMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::UnionMember *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::UnionMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_UnionMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::UnionMember *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_UnionMember, (void *&)_s);
}

class _Marshaller_CORBA_UnionMember : public CORBA::StaticTypeInfo {
    typedef CORBA::UnionMember _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_UnionMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_UnionMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_UnionMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_UnionMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_any->demarshal( dc, &((_MICO_T*)v)->label ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    _marshaller_CORBA_IDLType->demarshal( dc, &((_MICO_T*)v)->type_def.inout() ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_UnionMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_any->marshal( ec, &((_MICO_T*)v)->label );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  _marshaller_CORBA_IDLType->marshal( ec, &((_MICO_T*)v)->type_def.inout() );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_UnionMember::typecode()
{
  return CORBA::_tc_UnionMember;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_UnionMember;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_UnionMemberSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_UnionMemberSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_EnumMemberSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_EnumMemberSeq;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_Visibility; };
#else
CORBA::TypeCodeConst CORBA::_tc_Visibility;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short PRIVATE_MEMBER = 0; };
#else
const CORBA::Short CORBA::PRIVATE_MEMBER = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short PUBLIC_MEMBER = 1; };
#else
const CORBA::Short CORBA::PUBLIC_MEMBER = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueModifier; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueModifier;
#endif

#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short VM_NONE = 0; };
#else
const CORBA::Short CORBA::VM_NONE = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short VM_CUSTOM = 1; };
#else
const CORBA::Short CORBA::VM_CUSTOM = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short VM_ABSTRACT = 2; };
#else
const CORBA::Short CORBA::VM_ABSTRACT = 2;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { const CORBA::Short VM_TRUNCATABLE = 3; };
#else
const CORBA::Short CORBA::VM_TRUNCATABLE = 3;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueMember; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueMember;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::ValueMember::ValueMember()
{
}

CORBA::ValueMember::ValueMember( const ValueMember& _s )
{
  name = ((ValueMember&)_s).name;
  id = ((ValueMember&)_s).id;
  defined_in = ((ValueMember&)_s).defined_in;
  version = ((ValueMember&)_s).version;
  type = ((ValueMember&)_s).type;
  type_def = ((ValueMember&)_s).type_def;
  access = ((ValueMember&)_s).access;
}

CORBA::ValueMember::~ValueMember()
{
}

CORBA::ValueMember&
CORBA::ValueMember::operator=( const ValueMember& _s )
{
  name = ((ValueMember&)_s).name;
  id = ((ValueMember&)_s).id;
  defined_in = ((ValueMember&)_s).defined_in;
  version = ((ValueMember&)_s).version;
  type = ((ValueMember&)_s).type;
  type_def = ((ValueMember&)_s).type_def;
  access = ((ValueMember&)_s).access;
  return *this;
}
#endif

void operator<<=( CORBA::Any &_a, const CORBA::ValueMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, CORBA::ValueMember *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueMember &_s )
{
  CORBA::StaticAny _sa (_marshaller_CORBA_ValueMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, CORBA::ValueMember *&_s )
{
  return _a.to_static_any (_marshaller_CORBA_ValueMember, (void *&)_s);
}

class _Marshaller_CORBA_ValueMember : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueMember _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_CORBA_ValueMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_CORBA_ValueMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_CORBA_ValueMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_CORBA_ValueMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->name.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->id.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->defined_in.inout() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->version.inout() ) &&
    CORBA::_stc_TypeCode->demarshal( dc, &((_MICO_T*)v)->type.inout() ) &&
    _marshaller_CORBA_IDLType->demarshal( dc, &((_MICO_T*)v)->type_def.inout() ) &&
    CORBA::_stc_short->demarshal( dc, &((_MICO_T*)v)->access ) &&
    dc.struct_end();
}

void _Marshaller_CORBA_ValueMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->id.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->defined_in.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->version.inout() );
  CORBA::_stc_TypeCode->marshal( ec, &((_MICO_T*)v)->type.inout() );
  _marshaller_CORBA_IDLType->marshal( ec, &((_MICO_T*)v)->type_def.inout() );
  CORBA::_stc_short->marshal( ec, &((_MICO_T*)v)->access );
  ec.struct_end();
}

CORBA::TypeCode_ptr _Marshaller_CORBA_ValueMember::typecode()
{
  return CORBA::_tc_ValueMember;
}

CORBA::StaticTypeInfo *_marshaller_CORBA_ValueMember;

#ifdef HAVE_NAMESPACE
namespace CORBA { CORBA::TypeCodeConst _tc_ValueMemberSeq; };
#else
CORBA::TypeCodeConst CORBA::_tc_ValueMemberSeq;
#endif

class _Marshaller__seq_CORBA_StructMember : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_StructMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_StructMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_StructMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_StructMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_StructMember->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_StructMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_StructMember->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_StructMember::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000008010000010000000f000000f8000000010000002300"
    "000049444c3a6f6d672e6f72672f434f5242412f5374727563744d656d62"
    "65723a312e3000000d0000005374727563744d656d626572000000000300"
    "0000050000006e616d650000000015000000440000000100000021000000"
    "49444c3a6f6d672e6f72672f434f5242412f4964656e7469666965723a31"
    "2e30000000000b0000004964656e74696669657200001200000000000000"
    "0500000074797065000000000c00000009000000747970655f6465660000"
    "00000e00000034000000010000001e00000049444c3a6f6d672e6f72672f"
    "434f5242412f49444c547970653a312e300000000800000049444c547970"
    "650000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_StructMember::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_StructMember;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_StructMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_StructMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_StructMember, (void *&)_s);
}


class _Marshaller__seq_CORBA_UnionMember : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_UnionMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_UnionMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_UnionMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_UnionMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_UnionMember->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_UnionMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_UnionMember->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_UnionMember::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000014010000010000000f00000004010000010000002200"
    "000049444c3a6f6d672e6f72672f434f5242412f556e696f6e4d656d6265"
    "723a312e300000000c000000556e696f6e4d656d62657200040000000500"
    "00006e616d65000000001500000044000000010000002100000049444c3a"
    "6f6d672e6f72672f434f5242412f4964656e7469666965723a312e300000"
    "00000b0000004964656e7469666965720000120000000000000006000000"
    "6c6162656c0000000b0000000500000074797065000000000c0000000900"
    "0000747970655f646566000000000e00000034000000010000001e000000"
    "49444c3a6f6d672e6f72672f434f5242412f49444c547970653a312e3000"
    "00000800000049444c547970650000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_UnionMember::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_UnionMember;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_UnionMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_UnionMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_UnionMember, (void *&)_s);
}


class _Marshaller__seq_CORBA_ValueMember : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_CORBA_ValueMember::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_CORBA_ValueMember::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_CORBA_ValueMember::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_CORBA_ValueMember::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_CORBA_ValueMember->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_CORBA_ValueMember::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( CORBA::ULong i = 0; i < len; i++ )
    _marshaller_CORBA_ValueMember->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ValueMember::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000068020000010000000f00000058020000010000002200"
    "000049444c3a6f6d672e6f72672f434f5242412f56616c75654d656d6265"
    "723a312e300000000c00000056616c75654d656d62657200070000000500"
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
    "300000000c00000056657273696f6e537065630012000000000000000500"
    "000074797065000000000c00000009000000747970655f64656600000000"
    "0e00000034000000010000001e00000049444c3a6f6d672e6f72672f434f"
    "5242412f49444c547970653a312e300000000800000049444c5479706500"
    "070000006163636573730000150000004000000001000000210000004944"
    "4c3a6f6d672e6f72672f434f5242412f5669736962696c6974793a312e30"
    "000000000b0000005669736962696c69747900000200000000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_CORBA_ValueMember::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ValueMember;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ValueMember, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_CORBA_ValueMember, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> *&_s )
{
  return _a.to_static_any (_marshaller__seq_CORBA_ValueMember, (void *&)_s);
}


struct __tc_init_IR_BASE {
  __tc_init_IR_BASE()
  {
    CORBA::_tc_Identifier = 
    "010000001500000044000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f4964656e7469666965723a312e30000000000b000000"
    "4964656e74696669657200001200000000000000";
    CORBA::_tc_VersionSpec = 
    "010000001500000044000000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f56657273696f6e537065633a312e300000000c000000"
    "56657273696f6e53706563001200000000000000";
    CORBA::_tc_RepositoryId = 
    "010000001500000048000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5265706f7369746f727949643a312e3000000d000000"
    "5265706f7369746f72794964000000001200000000000000";
    CORBA::_tc_DefinitionKind = 
    "0100000011000000d6010000010000002500000049444c3a6f6d672e6f72"
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
    "6500";
    _marshaller_CORBA_DefinitionKind = new _Marshaller_CORBA_DefinitionKind;
    CORBA::_tc_IRObject = 
    "010000000e00000035000000010000001f00000049444c3a6f6d672e6f72"
    "672f434f5242412f49524f626a6563743a312e3000000900000049524f62"
    "6a65637400";
    _marshaller_CORBA_IRObject = new _Marshaller_CORBA_IRObject;
    CORBA::_tc_IDLType = 
    "010000000e00000034000000010000001e00000049444c3a6f6d672e6f72"
    "672f434f5242412f49444c547970653a312e300000000800000049444c54"
    "79706500";
    _marshaller_CORBA_IDLType = new _Marshaller_CORBA_IDLType;
    CORBA::_tc_StructMember = 
    "010000000f000000f8000000010000002300000049444c3a6f6d672e6f72"
    "672f434f5242412f5374727563744d656d6265723a312e3000000d000000"
    "5374727563744d656d6265720000000003000000050000006e616d650000"
    "00001500000044000000010000002100000049444c3a6f6d672e6f72672f"
    "434f5242412f4964656e7469666965723a312e30000000000b0000004964"
    "656e74696669657200001200000000000000050000007479706500000000"
    "0c00000009000000747970655f646566000000000e000000340000000100"
    "00001e00000049444c3a6f6d672e6f72672f434f5242412f49444c547970"
    "653a312e300000000800000049444c5479706500";
    _marshaller_CORBA_StructMember = new _Marshaller_CORBA_StructMember;
    CORBA::_tc_StructMemberSeq = 
    "010000001500000054010000010000002600000049444c3a6f6d672e6f72"
    "672f434f5242412f5374727563744d656d6265725365713a312e30000000"
    "100000005374727563744d656d6265725365710013000000080100000100"
    "00000f000000f8000000010000002300000049444c3a6f6d672e6f72672f"
    "434f5242412f5374727563744d656d6265723a312e3000000d0000005374"
    "727563744d656d6265720000000003000000050000006e616d6500000000"
    "1500000044000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f4964656e7469666965723a312e30000000000b0000004964656e"
    "746966696572000012000000000000000500000074797065000000000c00"
    "000009000000747970655f646566000000000e0000003400000001000000"
    "1e00000049444c3a6f6d672e6f72672f434f5242412f49444c547970653a"
    "312e300000000800000049444c547970650000000000";
    CORBA::_tc_UnionMember = 
    "010000000f00000004010000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f556e696f6e4d656d6265723a312e300000000c000000"
    "556e696f6e4d656d6265720004000000050000006e616d65000000001500"
    "000044000000010000002100000049444c3a6f6d672e6f72672f434f5242"
    "412f4964656e7469666965723a312e30000000000b0000004964656e7469"
    "6669657200001200000000000000060000006c6162656c0000000b000000"
    "0500000074797065000000000c00000009000000747970655f6465660000"
    "00000e00000034000000010000001e00000049444c3a6f6d672e6f72672f"
    "434f5242412f49444c547970653a312e300000000800000049444c547970"
    "6500";
    _marshaller_CORBA_UnionMember = new _Marshaller_CORBA_UnionMember;
    CORBA::_tc_UnionMemberSeq = 
    "010000001500000060010000010000002500000049444c3a6f6d672e6f72"
    "672f434f5242412f556e696f6e4d656d6265725365713a312e3000000000"
    "0f000000556e696f6e4d656d626572536571000013000000140100000100"
    "00000f00000004010000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f556e696f6e4d656d6265723a312e300000000c000000556e"
    "696f6e4d656d6265720004000000050000006e616d650000000015000000"
    "44000000010000002100000049444c3a6f6d672e6f72672f434f5242412f"
    "4964656e7469666965723a312e30000000000b0000004964656e74696669"
    "657200001200000000000000060000006c6162656c0000000b0000000500"
    "000074797065000000000c00000009000000747970655f64656600000000"
    "0e00000034000000010000001e00000049444c3a6f6d672e6f72672f434f"
    "5242412f49444c547970653a312e300000000800000049444c5479706500"
    "00000000";
    CORBA::_tc_EnumMemberSeq = 
    "01000000150000009c000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f456e756d4d656d6265725365713a312e30000e000000"
    "456e756d4d656d6265725365710000001300000054000000010000001500"
    "000044000000010000002100000049444c3a6f6d672e6f72672f434f5242"
    "412f4964656e7469666965723a312e30000000000b0000004964656e7469"
    "666965720000120000000000000000000000";
    CORBA::_tc_Visibility = 
    "010000001500000040000000010000002100000049444c3a6f6d672e6f72"
    "672f434f5242412f5669736962696c6974793a312e30000000000b000000"
    "5669736962696c697479000002000000";
    CORBA::_tc_ValueModifier = 
    "010000001500000044000000010000002400000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654d6f6469666965723a312e30000e000000"
    "56616c75654d6f64696669657200000002000000";
    CORBA::_tc_ValueMember = 
    "010000000f00000058020000010000002200000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654d656d6265723a312e300000000c000000"
    "56616c75654d656d6265720007000000050000006e616d65000000001500"
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
    "696f6e537065630012000000000000000500000074797065000000000c00"
    "000009000000747970655f646566000000000e0000003400000001000000"
    "1e00000049444c3a6f6d672e6f72672f434f5242412f49444c547970653a"
    "312e300000000800000049444c5479706500070000006163636573730000"
    "1500000040000000010000002100000049444c3a6f6d672e6f72672f434f"
    "5242412f5669736962696c6974793a312e30000000000b00000056697369"
    "62696c697479000002000000";
    _marshaller_CORBA_ValueMember = new _Marshaller_CORBA_ValueMember;
    CORBA::_tc_ValueMemberSeq = 
    "0100000015000000b4020000010000002500000049444c3a6f6d672e6f72"
    "672f434f5242412f56616c75654d656d6265725365713a312e3000000000"
    "0f00000056616c75654d656d626572536571000013000000680200000100"
    "00000f00000058020000010000002200000049444c3a6f6d672e6f72672f"
    "434f5242412f56616c75654d656d6265723a312e300000000c0000005661"
    "6c75654d656d6265720007000000050000006e616d650000000015000000"
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
    "09000000747970655f646566000000000e00000034000000010000001e00"
    "000049444c3a6f6d672e6f72672f434f5242412f49444c547970653a312e"
    "300000000800000049444c54797065000700000061636365737300001500"
    "000040000000010000002100000049444c3a6f6d672e6f72672f434f5242"
    "412f5669736962696c6974793a312e30000000000b000000566973696269"
    "6c69747900000200000000000000";
    _marshaller__seq_CORBA_StructMember = new _Marshaller__seq_CORBA_StructMember;
    _marshaller__seq_CORBA_UnionMember = new _Marshaller__seq_CORBA_UnionMember;
    _marshaller__seq_CORBA_ValueMember = new _Marshaller__seq_CORBA_ValueMember;
  }
};

static __tc_init_IR_BASE __init_IR_BASE;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

CORBA::IRObject_skel::IRObject_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/IRObject:1.0", "IRObject" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/IRObject:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<IRObject_skel>( this ) );
}

CORBA::IRObject_skel::IRObject_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/IRObject:1.0", "IRObject" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<IRObject_skel>( this ) );
}

CORBA::IRObject_skel::~IRObject_skel()
{
}

bool CORBA::IRObject_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_def_kind" ) == 0 ) {
      DefinitionKind _res;
      CORBA::StaticAny __res( _marshaller_CORBA_DefinitionKind, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = def_kind();
      _req->write_results();
      return true;
    }
    if( strcmp( _req->op_name(), "destroy" ) == 0 ) {

      if( !_req->read_args() )
        return true;

      destroy();
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

CORBA::IRObject_ptr CORBA::IRObject_skel::_this()
{
  return CORBA::IRObject::_duplicate( this );
}


CORBA::IDLType_skel::IDLType_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/IDLType:1.0", "IDLType" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/IDLType:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<IDLType_skel>( this ) );
}

CORBA::IDLType_skel::IDLType_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/IDLType:1.0", "IDLType" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<IDLType_skel>( this ) );
}

CORBA::IDLType_skel::~IDLType_skel()
{
}

bool CORBA::IDLType_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_type" ) == 0 ) {
      CORBA::TypeCode_ptr _res;
      CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = type();
      _req->write_results();
      CORBA::release( _res );
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

CORBA::IDLType_ptr CORBA::IDLType_skel::_this()
{
  return CORBA::IDLType::_duplicate( this );
}

