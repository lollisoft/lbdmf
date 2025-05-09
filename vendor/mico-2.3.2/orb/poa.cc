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
namespace PortableServer { CORBA::TypeCodeConst _tc_POAList; };
#else
CORBA::TypeCodeConst PortableServer::_tc_POAList;
#endif

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_ObjectId; };
#else
CORBA::TypeCodeConst PortableServer::_tc_ObjectId;
#endif

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_ForwardRequest; };
#else
CORBA::TypeCodeConst PortableServer::_tc_ForwardRequest;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::ForwardRequest::ForwardRequest()
{
}

PortableServer::ForwardRequest::ForwardRequest( const ForwardRequest& _s )
{
  forward_reference = ((ForwardRequest&)_s).forward_reference;
}

PortableServer::ForwardRequest::~ForwardRequest()
{
}

PortableServer::ForwardRequest&
PortableServer::ForwardRequest::operator=( const ForwardRequest& _s )
{
  forward_reference = ((ForwardRequest&)_s).forward_reference;
  return *this;
}
#endif

#ifndef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::ForwardRequest::ForwardRequest()
{
}

#endif

PortableServer::ForwardRequest::ForwardRequest( CORBA::Object_ptr _m0 )
{
  forward_reference = CORBA::Object::_duplicate( _m0 );
}

class _Marshaller_PortableServer_ForwardRequest : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::ForwardRequest _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_ForwardRequest::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_ForwardRequest::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_ForwardRequest::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_ForwardRequest::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    CORBA::_stc_Object->demarshal( dc, &((_MICO_T*)v)->forward_reference.inout() ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_ForwardRequest::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/ForwardRequest:1.0" );
  CORBA::_stc_Object->marshal( ec, &((_MICO_T*)v)->forward_reference.inout() );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_ForwardRequest::typecode()
{
  return PortableServer::_tc_ForwardRequest;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_ForwardRequest;

void operator<<=( CORBA::Any &_a, const PortableServer::ForwardRequest &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ForwardRequest, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::ForwardRequest *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::ForwardRequest &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ForwardRequest, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::ForwardRequest *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_ForwardRequest, (void *&)_e);
}

void PortableServer::ForwardRequest::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ForwardRequest_var( (PortableServer::ForwardRequest*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::ForwardRequest::_repoid() const
{
  return "IDL:omg.org/PortableServer/ForwardRequest:1.0";
}

void PortableServer::ForwardRequest::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::ForwardRequest::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::ForwardRequest::_clone() const
{
  return new ForwardRequest( *this );
}

PortableServer::ForwardRequest *PortableServer::ForwardRequest::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/ForwardRequest:1.0" ) )
    return (ForwardRequest *) _ex;
  return NULL;
}

const PortableServer::ForwardRequest *PortableServer::ForwardRequest::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/ForwardRequest:1.0" ) )
    return (ForwardRequest *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong THREAD_POLICY_ID = 16; };
#else
const CORBA::ULong PortableServer::THREAD_POLICY_ID = 16;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong LIFESPAN_POLICY_ID = 17; };
#else
const CORBA::ULong PortableServer::LIFESPAN_POLICY_ID = 17;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong ID_UNIQUENESS_POLICY_ID = 18; };
#else
const CORBA::ULong PortableServer::ID_UNIQUENESS_POLICY_ID = 18;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong ID_ASSIGNMENT_POLICY_ID = 19; };
#else
const CORBA::ULong PortableServer::ID_ASSIGNMENT_POLICY_ID = 19;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong IMPLICIT_ACTIVATION_POLICY_ID = 20; };
#else
const CORBA::ULong PortableServer::IMPLICIT_ACTIVATION_POLICY_ID = 20;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong SERVANT_RETENTION_POLICY_ID = 21; };
#else
const CORBA::ULong PortableServer::SERVANT_RETENTION_POLICY_ID = 21;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { const CORBA::ULong REQUEST_PROCESSING_POLICY_ID = 22; };
#else
const CORBA::ULong PortableServer::REQUEST_PROCESSING_POLICY_ID = 22;
#endif
#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_ThreadPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_ThreadPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::ThreadPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ThreadPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::ThreadPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ThreadPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_ThreadPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::ThreadPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_ThreadPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_ThreadPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_ThreadPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_ThreadPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_ThreadPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_ThreadPolicyValue::typecode()
{
  return PortableServer::_tc_ThreadPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_ThreadPolicyValue;


// Stub interface ThreadPolicy
PortableServer::ThreadPolicy::~ThreadPolicy()
{
}

void *PortableServer::ThreadPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ThreadPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::ThreadPolicy_ptr PortableServer::ThreadPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ThreadPolicy:1.0" )))
      return _duplicate( (PortableServer::ThreadPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::ThreadPolicy_ptr
PortableServer::ThreadPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_LifespanPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_LifespanPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::LifespanPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_LifespanPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::LifespanPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_LifespanPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_LifespanPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::LifespanPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_LifespanPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_LifespanPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_LifespanPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_LifespanPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_LifespanPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_LifespanPolicyValue::typecode()
{
  return PortableServer::_tc_LifespanPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_LifespanPolicyValue;


// Stub interface LifespanPolicy
PortableServer::LifespanPolicy::~LifespanPolicy()
{
}

void *PortableServer::LifespanPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/LifespanPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::LifespanPolicy_ptr PortableServer::LifespanPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/LifespanPolicy:1.0" )))
      return _duplicate( (PortableServer::LifespanPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::LifespanPolicy_ptr
PortableServer::LifespanPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_IdUniquenessPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_IdUniquenessPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::IdUniquenessPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_IdUniquenessPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::IdUniquenessPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_IdUniquenessPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_IdUniquenessPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::IdUniquenessPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_IdUniquenessPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_IdUniquenessPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_IdUniquenessPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_IdUniquenessPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_IdUniquenessPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_IdUniquenessPolicyValue::typecode()
{
  return PortableServer::_tc_IdUniquenessPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_IdUniquenessPolicyValue;


// Stub interface IdUniquenessPolicy
PortableServer::IdUniquenessPolicy::~IdUniquenessPolicy()
{
}

void *PortableServer::IdUniquenessPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/IdUniquenessPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::IdUniquenessPolicy_ptr PortableServer::IdUniquenessPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/IdUniquenessPolicy:1.0" )))
      return _duplicate( (PortableServer::IdUniquenessPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::IdUniquenessPolicy_ptr
PortableServer::IdUniquenessPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_IdAssignmentPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_IdAssignmentPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::IdAssignmentPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_IdAssignmentPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::IdAssignmentPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_IdAssignmentPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_IdAssignmentPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::IdAssignmentPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_IdAssignmentPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_IdAssignmentPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_IdAssignmentPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_IdAssignmentPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_IdAssignmentPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_IdAssignmentPolicyValue::typecode()
{
  return PortableServer::_tc_IdAssignmentPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_IdAssignmentPolicyValue;


// Stub interface IdAssignmentPolicy
PortableServer::IdAssignmentPolicy::~IdAssignmentPolicy()
{
}

void *PortableServer::IdAssignmentPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/IdAssignmentPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::IdAssignmentPolicy_ptr PortableServer::IdAssignmentPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/IdAssignmentPolicy:1.0" )))
      return _duplicate( (PortableServer::IdAssignmentPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::IdAssignmentPolicy_ptr
PortableServer::IdAssignmentPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_ImplicitActivationPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_ImplicitActivationPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::ImplicitActivationPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ImplicitActivationPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::ImplicitActivationPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ImplicitActivationPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_ImplicitActivationPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::ImplicitActivationPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_ImplicitActivationPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_ImplicitActivationPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_ImplicitActivationPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_ImplicitActivationPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_ImplicitActivationPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_ImplicitActivationPolicyValue::typecode()
{
  return PortableServer::_tc_ImplicitActivationPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_ImplicitActivationPolicyValue;


// Stub interface ImplicitActivationPolicy
PortableServer::ImplicitActivationPolicy::~ImplicitActivationPolicy()
{
}

void *PortableServer::ImplicitActivationPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ImplicitActivationPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::ImplicitActivationPolicy_ptr PortableServer::ImplicitActivationPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ImplicitActivationPolicy:1.0" )))
      return _duplicate( (PortableServer::ImplicitActivationPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::ImplicitActivationPolicy_ptr
PortableServer::ImplicitActivationPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_ServantRetentionPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_ServantRetentionPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::ServantRetentionPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ServantRetentionPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::ServantRetentionPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_ServantRetentionPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_ServantRetentionPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::ServantRetentionPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_ServantRetentionPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_ServantRetentionPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_ServantRetentionPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_ServantRetentionPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_ServantRetentionPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_ServantRetentionPolicyValue::typecode()
{
  return PortableServer::_tc_ServantRetentionPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_ServantRetentionPolicyValue;


// Stub interface ServantRetentionPolicy
PortableServer::ServantRetentionPolicy::~ServantRetentionPolicy()
{
}

void *PortableServer::ServantRetentionPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ServantRetentionPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::ServantRetentionPolicy_ptr PortableServer::ServantRetentionPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ServantRetentionPolicy:1.0" )))
      return _duplicate( (PortableServer::ServantRetentionPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::ServantRetentionPolicy_ptr
PortableServer::ServantRetentionPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst _tc_RequestProcessingPolicyValue; };
#else
CORBA::TypeCodeConst PortableServer::_tc_RequestProcessingPolicyValue;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::RequestProcessingPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_RequestProcessingPolicyValue, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::RequestProcessingPolicyValue &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_RequestProcessingPolicyValue, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_RequestProcessingPolicyValue : public CORBA::StaticTypeInfo {
    typedef PortableServer::RequestProcessingPolicyValue _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_RequestProcessingPolicyValue::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_RequestProcessingPolicyValue::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_RequestProcessingPolicyValue::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_RequestProcessingPolicyValue::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_RequestProcessingPolicyValue::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_RequestProcessingPolicyValue::typecode()
{
  return PortableServer::_tc_RequestProcessingPolicyValue;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_RequestProcessingPolicyValue;


// Stub interface RequestProcessingPolicy
PortableServer::RequestProcessingPolicy::~RequestProcessingPolicy()
{
}

void *PortableServer::RequestProcessingPolicy::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/RequestProcessingPolicy:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Policy)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::RequestProcessingPolicy_ptr PortableServer::RequestProcessingPolicy::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/RequestProcessingPolicy:1.0" )))
      return _duplicate( (PortableServer::RequestProcessingPolicy_ptr) _p );
  }
  return _nil();
}

PortableServer::RequestProcessingPolicy_ptr
PortableServer::RequestProcessingPolicy::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POAManager::_tc_AdapterInactive; };
#else
CORBA::TypeCodeConst PortableServer::POAManager::_tc_AdapterInactive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POAManager::AdapterInactive::AdapterInactive()
{
}

PortableServer::POAManager::AdapterInactive::AdapterInactive( const AdapterInactive& _s )
{
}

PortableServer::POAManager::AdapterInactive::~AdapterInactive()
{
}

PortableServer::POAManager::AdapterInactive&
PortableServer::POAManager::AdapterInactive::operator=( const AdapterInactive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POAManager_AdapterInactive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POAManager::AdapterInactive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POAManager_AdapterInactive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POAManager_AdapterInactive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POAManager_AdapterInactive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POAManager_AdapterInactive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POAManager_AdapterInactive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POAManager/AdapterInactive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POAManager_AdapterInactive::typecode()
{
  return PortableServer::POAManager::_tc_AdapterInactive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POAManager_AdapterInactive;

void operator<<=( CORBA::Any &_a, const PortableServer::POAManager::AdapterInactive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POAManager_AdapterInactive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POAManager::AdapterInactive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POAManager::AdapterInactive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POAManager_AdapterInactive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POAManager::AdapterInactive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POAManager_AdapterInactive, (void *&)_e);
}

void PortableServer::POAManager::AdapterInactive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw AdapterInactive_var( (PortableServer::POAManager::AdapterInactive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POAManager::AdapterInactive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POAManager/AdapterInactive:1.0";
}

void PortableServer::POAManager::AdapterInactive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POAManager::AdapterInactive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POAManager::AdapterInactive::_clone() const
{
  return new AdapterInactive( *this );
}

PortableServer::POAManager::AdapterInactive *PortableServer::POAManager::AdapterInactive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POAManager/AdapterInactive:1.0" ) )
    return (AdapterInactive *) _ex;
  return NULL;
}

const PortableServer::POAManager::AdapterInactive *PortableServer::POAManager::AdapterInactive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POAManager/AdapterInactive:1.0" ) )
    return (AdapterInactive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POAManager::_tc_State; };
#else
CORBA::TypeCodeConst PortableServer::POAManager::_tc_State;
#endif

void operator<<=( CORBA::Any &_a, const PortableServer::POAManager::State &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POAManager_State, &_e);
  _a.from_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POAManager::State &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POAManager_State, &_e);
  return _a.to_static_any (_sa);
}

class _Marshaller_PortableServer_POAManager_State : public CORBA::StaticTypeInfo {
    typedef PortableServer::POAManager::State _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POAManager_State::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POAManager_State::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POAManager_State::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POAManager_State::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::ULong ul;
  if( !dc.enumeration( ul ) )
    return FALSE;
  *(_MICO_T*) v = (_MICO_T) ul;
  return TRUE;
}

void _Marshaller_PortableServer_POAManager_State::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.enumeration( (CORBA::ULong) *(_MICO_T *) v );
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POAManager_State::typecode()
{
  return PortableServer::POAManager::_tc_State;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POAManager_State;


// Stub interface POAManager
PortableServer::POAManager::~POAManager()
{
}

void *PortableServer::POAManager::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/POAManager:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

PortableServer::POAManager_ptr PortableServer::POAManager::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/POAManager:1.0" )))
      return _duplicate( (PortableServer::POAManager_ptr) _p );
  }
  return _nil();
}

PortableServer::POAManager_ptr
PortableServer::POAManager::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface AdapterActivator
PortableServer::AdapterActivator::~AdapterActivator()
{
}

void *PortableServer::AdapterActivator::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/AdapterActivator:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

PortableServer::AdapterActivator_ptr PortableServer::AdapterActivator::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/AdapterActivator:1.0" )))
      return _duplicate( (PortableServer::AdapterActivator_ptr) _p );
  }
  return _nil();
}

PortableServer::AdapterActivator_ptr
PortableServer::AdapterActivator::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface ServantManager
PortableServer::ServantManager::~ServantManager()
{
}

void *PortableServer::ServantManager::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ServantManager:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

PortableServer::ServantManager_ptr PortableServer::ServantManager::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ServantManager:1.0" )))
      return _duplicate( (PortableServer::ServantManager_ptr) _p );
  }
  return _nil();
}

PortableServer::ServantManager_ptr
PortableServer::ServantManager::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface ServantActivator
PortableServer::ServantActivator::~ServantActivator()
{
}

void *PortableServer::ServantActivator::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ServantActivator:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = ServantManager::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::ServantActivator_ptr PortableServer::ServantActivator::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ServantActivator:1.0" )))
      return _duplicate( (PortableServer::ServantActivator_ptr) _p );
  }
  return _nil();
}

PortableServer::ServantActivator_ptr
PortableServer::ServantActivator::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}



// Stub interface ServantLocator
PortableServer::ServantLocator::~ServantLocator()
{
}

void *PortableServer::ServantLocator::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/ServantLocator:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = ServantManager::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::ServantLocator_ptr PortableServer::ServantLocator::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/ServantLocator:1.0" )))
      return _duplicate( (PortableServer::ServantLocator_ptr) _p );
  }
  return _nil();
}

PortableServer::ServantLocator_ptr
PortableServer::ServantLocator::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_AdapterAlreadyExists; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_AdapterAlreadyExists;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::AdapterAlreadyExists::AdapterAlreadyExists()
{
}

PortableServer::POA::AdapterAlreadyExists::AdapterAlreadyExists( const AdapterAlreadyExists& _s )
{
}

PortableServer::POA::AdapterAlreadyExists::~AdapterAlreadyExists()
{
}

PortableServer::POA::AdapterAlreadyExists&
PortableServer::POA::AdapterAlreadyExists::operator=( const AdapterAlreadyExists& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_AdapterAlreadyExists : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::AdapterAlreadyExists _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_AdapterAlreadyExists::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_AdapterAlreadyExists::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_AdapterAlreadyExists::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_AdapterAlreadyExists::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_AdapterAlreadyExists::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/AdapterAlreadyExists:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_AdapterAlreadyExists::typecode()
{
  return PortableServer::POA::_tc_AdapterAlreadyExists;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_AdapterAlreadyExists;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::AdapterAlreadyExists &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterAlreadyExists, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::AdapterAlreadyExists *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterAlreadyExists &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterAlreadyExists, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterAlreadyExists *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_AdapterAlreadyExists, (void *&)_e);
}

void PortableServer::POA::AdapterAlreadyExists::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw AdapterAlreadyExists_var( (PortableServer::POA::AdapterAlreadyExists*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::AdapterAlreadyExists::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/AdapterAlreadyExists:1.0";
}

void PortableServer::POA::AdapterAlreadyExists::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::AdapterAlreadyExists::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::AdapterAlreadyExists::_clone() const
{
  return new AdapterAlreadyExists( *this );
}

PortableServer::POA::AdapterAlreadyExists *PortableServer::POA::AdapterAlreadyExists::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterAlreadyExists:1.0" ) )
    return (AdapterAlreadyExists *) _ex;
  return NULL;
}

const PortableServer::POA::AdapterAlreadyExists *PortableServer::POA::AdapterAlreadyExists::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterAlreadyExists:1.0" ) )
    return (AdapterAlreadyExists *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_AdapterInactive; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_AdapterInactive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::AdapterInactive::AdapterInactive()
{
}

PortableServer::POA::AdapterInactive::AdapterInactive( const AdapterInactive& _s )
{
}

PortableServer::POA::AdapterInactive::~AdapterInactive()
{
}

PortableServer::POA::AdapterInactive&
PortableServer::POA::AdapterInactive::operator=( const AdapterInactive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_AdapterInactive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::AdapterInactive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_AdapterInactive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_AdapterInactive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_AdapterInactive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_AdapterInactive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_AdapterInactive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/AdapterInactive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_AdapterInactive::typecode()
{
  return PortableServer::POA::_tc_AdapterInactive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_AdapterInactive;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::AdapterInactive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterInactive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::AdapterInactive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterInactive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterInactive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterInactive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_AdapterInactive, (void *&)_e);
}

void PortableServer::POA::AdapterInactive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw AdapterInactive_var( (PortableServer::POA::AdapterInactive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::AdapterInactive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/AdapterInactive:1.0";
}

void PortableServer::POA::AdapterInactive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::AdapterInactive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::AdapterInactive::_clone() const
{
  return new AdapterInactive( *this );
}

PortableServer::POA::AdapterInactive *PortableServer::POA::AdapterInactive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterInactive:1.0" ) )
    return (AdapterInactive *) _ex;
  return NULL;
}

const PortableServer::POA::AdapterInactive *PortableServer::POA::AdapterInactive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterInactive:1.0" ) )
    return (AdapterInactive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_AdapterNonExistent; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_AdapterNonExistent;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::AdapterNonExistent::AdapterNonExistent()
{
}

PortableServer::POA::AdapterNonExistent::AdapterNonExistent( const AdapterNonExistent& _s )
{
}

PortableServer::POA::AdapterNonExistent::~AdapterNonExistent()
{
}

PortableServer::POA::AdapterNonExistent&
PortableServer::POA::AdapterNonExistent::operator=( const AdapterNonExistent& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_AdapterNonExistent : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::AdapterNonExistent _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_AdapterNonExistent::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_AdapterNonExistent::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_AdapterNonExistent::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_AdapterNonExistent::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_AdapterNonExistent::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/AdapterNonExistent:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_AdapterNonExistent::typecode()
{
  return PortableServer::POA::_tc_AdapterNonExistent;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_AdapterNonExistent;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::AdapterNonExistent &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterNonExistent, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::AdapterNonExistent *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterNonExistent &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_AdapterNonExistent, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::AdapterNonExistent *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_AdapterNonExistent, (void *&)_e);
}

void PortableServer::POA::AdapterNonExistent::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw AdapterNonExistent_var( (PortableServer::POA::AdapterNonExistent*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::AdapterNonExistent::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/AdapterNonExistent:1.0";
}

void PortableServer::POA::AdapterNonExistent::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::AdapterNonExistent::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::AdapterNonExistent::_clone() const
{
  return new AdapterNonExistent( *this );
}

PortableServer::POA::AdapterNonExistent *PortableServer::POA::AdapterNonExistent::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterNonExistent:1.0" ) )
    return (AdapterNonExistent *) _ex;
  return NULL;
}

const PortableServer::POA::AdapterNonExistent *PortableServer::POA::AdapterNonExistent::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/AdapterNonExistent:1.0" ) )
    return (AdapterNonExistent *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_InvalidPolicy; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_InvalidPolicy;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::InvalidPolicy::InvalidPolicy()
{
}

PortableServer::POA::InvalidPolicy::InvalidPolicy( const InvalidPolicy& _s )
{
  index = ((InvalidPolicy&)_s).index;
}

PortableServer::POA::InvalidPolicy::~InvalidPolicy()
{
}

PortableServer::POA::InvalidPolicy&
PortableServer::POA::InvalidPolicy::operator=( const InvalidPolicy& _s )
{
  index = ((InvalidPolicy&)_s).index;
  return *this;
}
#endif

#ifndef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::InvalidPolicy::InvalidPolicy()
{
}

#endif

PortableServer::POA::InvalidPolicy::InvalidPolicy( CORBA::UShort _m0 )
{
  index = _m0;
}

class _Marshaller_PortableServer_POA_InvalidPolicy : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::InvalidPolicy _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_InvalidPolicy::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_InvalidPolicy::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_InvalidPolicy::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_InvalidPolicy::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->index ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_InvalidPolicy::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/InvalidPolicy:1.0" );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->index );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_InvalidPolicy::typecode()
{
  return PortableServer::POA::_tc_InvalidPolicy;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_InvalidPolicy;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::InvalidPolicy &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_InvalidPolicy, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::InvalidPolicy *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::InvalidPolicy &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_InvalidPolicy, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::InvalidPolicy *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_InvalidPolicy, (void *&)_e);
}

void PortableServer::POA::InvalidPolicy::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw InvalidPolicy_var( (PortableServer::POA::InvalidPolicy*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::InvalidPolicy::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/InvalidPolicy:1.0";
}

void PortableServer::POA::InvalidPolicy::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::InvalidPolicy::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::InvalidPolicy::_clone() const
{
  return new InvalidPolicy( *this );
}

PortableServer::POA::InvalidPolicy *PortableServer::POA::InvalidPolicy::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/InvalidPolicy:1.0" ) )
    return (InvalidPolicy *) _ex;
  return NULL;
}

const PortableServer::POA::InvalidPolicy *PortableServer::POA::InvalidPolicy::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/InvalidPolicy:1.0" ) )
    return (InvalidPolicy *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_NoServant; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_NoServant;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::NoServant::NoServant()
{
}

PortableServer::POA::NoServant::NoServant( const NoServant& _s )
{
}

PortableServer::POA::NoServant::~NoServant()
{
}

PortableServer::POA::NoServant&
PortableServer::POA::NoServant::operator=( const NoServant& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_NoServant : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::NoServant _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_NoServant::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_NoServant::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_NoServant::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_NoServant::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_NoServant::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/NoServant:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_NoServant::typecode()
{
  return PortableServer::POA::_tc_NoServant;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_NoServant;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::NoServant &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_NoServant, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::NoServant *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::NoServant &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_NoServant, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::NoServant *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_NoServant, (void *&)_e);
}

void PortableServer::POA::NoServant::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw NoServant_var( (PortableServer::POA::NoServant*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::NoServant::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/NoServant:1.0";
}

void PortableServer::POA::NoServant::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::NoServant::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::NoServant::_clone() const
{
  return new NoServant( *this );
}

PortableServer::POA::NoServant *PortableServer::POA::NoServant::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/NoServant:1.0" ) )
    return (NoServant *) _ex;
  return NULL;
}

const PortableServer::POA::NoServant *PortableServer::POA::NoServant::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/NoServant:1.0" ) )
    return (NoServant *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_ObjectAlreadyActive; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_ObjectAlreadyActive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::ObjectAlreadyActive::ObjectAlreadyActive()
{
}

PortableServer::POA::ObjectAlreadyActive::ObjectAlreadyActive( const ObjectAlreadyActive& _s )
{
}

PortableServer::POA::ObjectAlreadyActive::~ObjectAlreadyActive()
{
}

PortableServer::POA::ObjectAlreadyActive&
PortableServer::POA::ObjectAlreadyActive::operator=( const ObjectAlreadyActive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_ObjectAlreadyActive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::ObjectAlreadyActive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_ObjectAlreadyActive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_ObjectAlreadyActive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_ObjectAlreadyActive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_ObjectAlreadyActive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_ObjectAlreadyActive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/ObjectAlreadyActive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_ObjectAlreadyActive::typecode()
{
  return PortableServer::POA::_tc_ObjectAlreadyActive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_ObjectAlreadyActive;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::ObjectAlreadyActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ObjectAlreadyActive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::ObjectAlreadyActive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ObjectAlreadyActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ObjectAlreadyActive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ObjectAlreadyActive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_ObjectAlreadyActive, (void *&)_e);
}

void PortableServer::POA::ObjectAlreadyActive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ObjectAlreadyActive_var( (PortableServer::POA::ObjectAlreadyActive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::ObjectAlreadyActive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/ObjectAlreadyActive:1.0";
}

void PortableServer::POA::ObjectAlreadyActive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::ObjectAlreadyActive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::ObjectAlreadyActive::_clone() const
{
  return new ObjectAlreadyActive( *this );
}

PortableServer::POA::ObjectAlreadyActive *PortableServer::POA::ObjectAlreadyActive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ObjectAlreadyActive:1.0" ) )
    return (ObjectAlreadyActive *) _ex;
  return NULL;
}

const PortableServer::POA::ObjectAlreadyActive *PortableServer::POA::ObjectAlreadyActive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ObjectAlreadyActive:1.0" ) )
    return (ObjectAlreadyActive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_ObjectNotActive; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_ObjectNotActive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::ObjectNotActive::ObjectNotActive()
{
}

PortableServer::POA::ObjectNotActive::ObjectNotActive( const ObjectNotActive& _s )
{
}

PortableServer::POA::ObjectNotActive::~ObjectNotActive()
{
}

PortableServer::POA::ObjectNotActive&
PortableServer::POA::ObjectNotActive::operator=( const ObjectNotActive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_ObjectNotActive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::ObjectNotActive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_ObjectNotActive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_ObjectNotActive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_ObjectNotActive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_ObjectNotActive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_ObjectNotActive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/ObjectNotActive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_ObjectNotActive::typecode()
{
  return PortableServer::POA::_tc_ObjectNotActive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_ObjectNotActive;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::ObjectNotActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ObjectNotActive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::ObjectNotActive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ObjectNotActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ObjectNotActive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ObjectNotActive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_ObjectNotActive, (void *&)_e);
}

void PortableServer::POA::ObjectNotActive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ObjectNotActive_var( (PortableServer::POA::ObjectNotActive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::ObjectNotActive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/ObjectNotActive:1.0";
}

void PortableServer::POA::ObjectNotActive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::ObjectNotActive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::ObjectNotActive::_clone() const
{
  return new ObjectNotActive( *this );
}

PortableServer::POA::ObjectNotActive *PortableServer::POA::ObjectNotActive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ObjectNotActive:1.0" ) )
    return (ObjectNotActive *) _ex;
  return NULL;
}

const PortableServer::POA::ObjectNotActive *PortableServer::POA::ObjectNotActive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ObjectNotActive:1.0" ) )
    return (ObjectNotActive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_ServantAlreadyActive; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_ServantAlreadyActive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::ServantAlreadyActive::ServantAlreadyActive()
{
}

PortableServer::POA::ServantAlreadyActive::ServantAlreadyActive( const ServantAlreadyActive& _s )
{
}

PortableServer::POA::ServantAlreadyActive::~ServantAlreadyActive()
{
}

PortableServer::POA::ServantAlreadyActive&
PortableServer::POA::ServantAlreadyActive::operator=( const ServantAlreadyActive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_ServantAlreadyActive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::ServantAlreadyActive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_ServantAlreadyActive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_ServantAlreadyActive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_ServantAlreadyActive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_ServantAlreadyActive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_ServantAlreadyActive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/ServantAlreadyActive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_ServantAlreadyActive::typecode()
{
  return PortableServer::POA::_tc_ServantAlreadyActive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_ServantAlreadyActive;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::ServantAlreadyActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ServantAlreadyActive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::ServantAlreadyActive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ServantAlreadyActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ServantAlreadyActive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ServantAlreadyActive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_ServantAlreadyActive, (void *&)_e);
}

void PortableServer::POA::ServantAlreadyActive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ServantAlreadyActive_var( (PortableServer::POA::ServantAlreadyActive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::ServantAlreadyActive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/ServantAlreadyActive:1.0";
}

void PortableServer::POA::ServantAlreadyActive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::ServantAlreadyActive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::ServantAlreadyActive::_clone() const
{
  return new ServantAlreadyActive( *this );
}

PortableServer::POA::ServantAlreadyActive *PortableServer::POA::ServantAlreadyActive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ServantAlreadyActive:1.0" ) )
    return (ServantAlreadyActive *) _ex;
  return NULL;
}

const PortableServer::POA::ServantAlreadyActive *PortableServer::POA::ServantAlreadyActive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ServantAlreadyActive:1.0" ) )
    return (ServantAlreadyActive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_ServantNotActive; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_ServantNotActive;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::ServantNotActive::ServantNotActive()
{
}

PortableServer::POA::ServantNotActive::ServantNotActive( const ServantNotActive& _s )
{
}

PortableServer::POA::ServantNotActive::~ServantNotActive()
{
}

PortableServer::POA::ServantNotActive&
PortableServer::POA::ServantNotActive::operator=( const ServantNotActive& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_ServantNotActive : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::ServantNotActive _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_ServantNotActive::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_ServantNotActive::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_ServantNotActive::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_ServantNotActive::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_ServantNotActive::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_ServantNotActive::typecode()
{
  return PortableServer::POA::_tc_ServantNotActive;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_ServantNotActive;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::ServantNotActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ServantNotActive, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::ServantNotActive *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ServantNotActive &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_ServantNotActive, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::ServantNotActive *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_ServantNotActive, (void *&)_e);
}

void PortableServer::POA::ServantNotActive::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw ServantNotActive_var( (PortableServer::POA::ServantNotActive*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::ServantNotActive::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0";
}

void PortableServer::POA::ServantNotActive::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::ServantNotActive::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::ServantNotActive::_clone() const
{
  return new ServantNotActive( *this );
}

PortableServer::POA::ServantNotActive *PortableServer::POA::ServantNotActive::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0" ) )
    return (ServantNotActive *) _ex;
  return NULL;
}

const PortableServer::POA::ServantNotActive *PortableServer::POA::ServantNotActive::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0" ) )
    return (ServantNotActive *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_WrongAdapter; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_WrongAdapter;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::WrongAdapter::WrongAdapter()
{
}

PortableServer::POA::WrongAdapter::WrongAdapter( const WrongAdapter& _s )
{
}

PortableServer::POA::WrongAdapter::~WrongAdapter()
{
}

PortableServer::POA::WrongAdapter&
PortableServer::POA::WrongAdapter::operator=( const WrongAdapter& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_WrongAdapter : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::WrongAdapter _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_WrongAdapter::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_WrongAdapter::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_WrongAdapter::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_WrongAdapter::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_WrongAdapter::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/WrongAdapter:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_WrongAdapter::typecode()
{
  return PortableServer::POA::_tc_WrongAdapter;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_WrongAdapter;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::WrongAdapter &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_WrongAdapter, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::WrongAdapter *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::WrongAdapter &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_WrongAdapter, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::WrongAdapter *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_WrongAdapter, (void *&)_e);
}

void PortableServer::POA::WrongAdapter::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw WrongAdapter_var( (PortableServer::POA::WrongAdapter*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::WrongAdapter::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/WrongAdapter:1.0";
}

void PortableServer::POA::WrongAdapter::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::WrongAdapter::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::WrongAdapter::_clone() const
{
  return new WrongAdapter( *this );
}

PortableServer::POA::WrongAdapter *PortableServer::POA::WrongAdapter::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/WrongAdapter:1.0" ) )
    return (WrongAdapter *) _ex;
  return NULL;
}

const PortableServer::POA::WrongAdapter *PortableServer::POA::WrongAdapter::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/WrongAdapter:1.0" ) )
    return (WrongAdapter *) _ex;
  return NULL;
}

#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst POA::_tc_WrongPolicy; };
#else
CORBA::TypeCodeConst PortableServer::POA::_tc_WrongPolicy;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::POA::WrongPolicy::WrongPolicy()
{
}

PortableServer::POA::WrongPolicy::WrongPolicy( const WrongPolicy& _s )
{
}

PortableServer::POA::WrongPolicy::~WrongPolicy()
{
}

PortableServer::POA::WrongPolicy&
PortableServer::POA::WrongPolicy::operator=( const WrongPolicy& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_POA_WrongPolicy : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::POA::WrongPolicy _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_POA_WrongPolicy::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_POA_WrongPolicy::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_POA_WrongPolicy::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_POA_WrongPolicy::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_POA_WrongPolicy::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/POA/WrongPolicy:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_POA_WrongPolicy::typecode()
{
  return PortableServer::POA::_tc_WrongPolicy;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_POA_WrongPolicy;

void operator<<=( CORBA::Any &_a, const PortableServer::POA::WrongPolicy &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_WrongPolicy, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::POA::WrongPolicy *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::WrongPolicy &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_POA_WrongPolicy, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::POA::WrongPolicy *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_POA_WrongPolicy, (void *&)_e);
}

void PortableServer::POA::WrongPolicy::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw WrongPolicy_var( (PortableServer::POA::WrongPolicy*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::POA::WrongPolicy::_repoid() const
{
  return "IDL:omg.org/PortableServer/POA/WrongPolicy:1.0";
}

void PortableServer::POA::WrongPolicy::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::POA::WrongPolicy::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::POA::WrongPolicy::_clone() const
{
  return new WrongPolicy( *this );
}

PortableServer::POA::WrongPolicy *PortableServer::POA::WrongPolicy::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/WrongPolicy:1.0" ) )
    return (WrongPolicy *) _ex;
  return NULL;
}

const PortableServer::POA::WrongPolicy *PortableServer::POA::WrongPolicy::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/POA/WrongPolicy:1.0" ) )
    return (WrongPolicy *) _ex;
  return NULL;
}


// Stub interface POA
PortableServer::POA::~POA()
{
}

void *PortableServer::POA::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/POA:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

PortableServer::POA_ptr PortableServer::POA::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/POA:1.0" )))
      return _duplicate( (PortableServer::POA_ptr) _p );
  }
  return _nil();
}

PortableServer::POA_ptr
PortableServer::POA::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


#ifdef HAVE_NAMESPACE
namespace PortableServer { CORBA::TypeCodeConst Current::_tc_NoContext; };
#else
CORBA::TypeCodeConst PortableServer::Current::_tc_NoContext;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
PortableServer::Current::NoContext::NoContext()
{
}

PortableServer::Current::NoContext::NoContext( const NoContext& _s )
{
}

PortableServer::Current::NoContext::~NoContext()
{
}

PortableServer::Current::NoContext&
PortableServer::Current::NoContext::operator=( const NoContext& _s )
{
  return *this;
}
#endif

class _Marshaller_PortableServer_Current_NoContext : public CORBA::StaticTypeInfo {
    typedef ::PortableServer::Current::NoContext _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller_PortableServer_Current_NoContext::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_PortableServer_Current_NoContext::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_PortableServer_Current_NoContext::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller_PortableServer_Current_NoContext::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  string repoid;
  return
    dc.except_begin( repoid ) &&
    dc.except_end();
}

void _Marshaller_PortableServer_Current_NoContext::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.except_begin( "IDL:omg.org/PortableServer/Current/NoContext:1.0" );
  ec.except_end();
}

CORBA::TypeCode_ptr _Marshaller_PortableServer_Current_NoContext::typecode()
{
  return PortableServer::Current::_tc_NoContext;
}

CORBA::StaticTypeInfo *_marshaller_PortableServer_Current_NoContext;

void operator<<=( CORBA::Any &_a, const PortableServer::Current::NoContext &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_Current_NoContext, &_e);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, PortableServer::Current::NoContext *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::Current::NoContext &_e )
{
  CORBA::StaticAny _sa (_marshaller_PortableServer_Current_NoContext, &_e);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, PortableServer::Current::NoContext *&_e )
{
  return _a.to_static_any (_marshaller_PortableServer_Current_NoContext, (void *&)_e);
}

void PortableServer::Current::NoContext::_throwit() const
{
  #ifdef HAVE_EXCEPTIONS
  #ifdef HAVE_STD_EH
  throw *this;
  #else
  throw NoContext_var( (PortableServer::Current::NoContext*)_clone() );
  #endif
  #else
  CORBA::Exception::_throw_failed( _clone() );
  #endif
}

const char *PortableServer::Current::NoContext::_repoid() const
{
  return "IDL:omg.org/PortableServer/Current/NoContext:1.0";
}

void PortableServer::Current::NoContext::_encode( CORBA::DataEncoder &_en ) const
{
  assert(0);
}

void PortableServer::Current::NoContext::_encode_any( CORBA::Any &_a ) const
{
  _a <<= *this;
}

CORBA::Exception *PortableServer::Current::NoContext::_clone() const
{
  return new NoContext( *this );
}

PortableServer::Current::NoContext *PortableServer::Current::NoContext::EXCEPTION_DOWNCAST( CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/Current/NoContext:1.0" ) )
    return (NoContext *) _ex;
  return NULL;
}

const PortableServer::Current::NoContext *PortableServer::Current::NoContext::EXCEPTION_DOWNCAST( const CORBA::Exception *_ex )
{
  if( _ex && !strcmp( _ex->_repoid(), "IDL:omg.org/PortableServer/Current/NoContext:1.0" ) )
    return (NoContext *) _ex;
  return NULL;
}


// Stub interface Current
PortableServer::Current::~Current()
{
}

void *PortableServer::Current::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:omg.org/PortableServer/Current:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if( (_p = MICO_SCOPE(CORBA,Current)::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

PortableServer::Current_ptr PortableServer::Current::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:omg.org/PortableServer/Current:1.0" )))
      return _duplicate( (PortableServer::Current_ptr) _p );
  }
  return _nil();
}

PortableServer::Current_ptr
PortableServer::Current::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}


class _Marshaller__seq_PortableServer_POA : public CORBA::StaticTypeInfo {
    typedef IfaceSequenceTmpl<PortableServer::POA_var,PortableServer::POA_ptr> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
    CORBA::TypeCode_ptr typecode ();
};


CORBA::StaticValueType _Marshaller__seq_PortableServer_POA::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_PortableServer_POA::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_PortableServer_POA::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

CORBA::Boolean _Marshaller__seq_PortableServer_POA::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  assert (0);
  return FALSE;
}

void _Marshaller__seq_PortableServer_POA::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  assert (0);
}

CORBA::TypeCode_ptr _Marshaller__seq_PortableServer_POA::typecode()
{
  if (!_tc)
    _tc = (new CORBA::TypeCode (
    "010000001300000044000000010000000e00000034000000010000002300"
    "000049444c3a6f6d672e6f72672f506f727461626c655365727665722f50"
    "4f413a312e30000004000000504f410000000000"))->mk_constant();
  return _tc;
}

CORBA::TypeCode_ptr _Marshaller__seq_PortableServer_POA::_tc = 0;
CORBA::StaticTypeInfo *_marshaller__seq_PortableServer_POA;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<PortableServer::POA_var,PortableServer::POA_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_PortableServer_POA, &_s);
  _a.from_static_any (_sa);
}

void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<PortableServer::POA_var,PortableServer::POA_ptr> *_s )
{
  _a <<= *_s;
  delete _s;
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<PortableServer::POA_var,PortableServer::POA_ptr> &_s )
{
  CORBA::StaticAny _sa (_marshaller__seq_PortableServer_POA, &_s);
  return _a.to_static_any (_sa);
}

CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<PortableServer::POA_var,PortableServer::POA_ptr> *&_s )
{
  return _a.to_static_any (_marshaller__seq_PortableServer_POA, (void *&)_s);
}


struct __tc_init_POA {
  __tc_init_POA()
  {
    PortableServer::_tc_POAList = 
    "010000001500000088000000010000002700000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f414c6973743a312e300000"
    "08000000504f414c697374001300000044000000010000000e0000003400"
    "0000010000002300000049444c3a6f6d672e6f72672f506f727461626c65"
    "5365727665722f504f413a312e30000004000000504f410000000000";
    PortableServer::_tc_ObjectId = 
    "010000001500000054000000010000002800000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f4f626a65637449643a312e3000"
    "090000004f626a656374496400000000130000000c000000010000000a00"
    "000000000000";
    PortableServer::_tc_ForwardRequest = 
    "0100000016000000a3000000010000002e00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f466f7277617264526571756573"
    "743a312e300000000f000000466f72776172645265717565737400000100"
    "000012000000666f72776172645f7265666572656e63650000000e000000"
    "33000000010000001d00000049444c3a6f6d672e6f72672f434f5242412f"
    "4f626a6563743a312e3000000000070000004f626a65637400";
    _marshaller_PortableServer_ForwardRequest = new _Marshaller_PortableServer_ForwardRequest;
    PortableServer::_tc_ThreadPolicyValue = 
    "010000001100000084000000010000003100000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f546872656164506f6c69637956"
    "616c75653a312e300000000012000000546872656164506f6c6963795661"
    "6c7565000000020000000f0000004f52425f4354524c5f4d4f44454c0000"
    "1400000053494e474c455f5448524541445f4d4f44454c00";
    _marshaller_PortableServer_ThreadPolicyValue = new _Marshaller_PortableServer_ThreadPolicyValue;
    PortableServer::_tc_LifespanPolicyValue = 
    "010000001100000077000000010000003300000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f4c6966657370616e506f6c6963"
    "7956616c75653a312e300000140000004c6966657370616e506f6c696379"
    "56616c756500020000000a0000005452414e5349454e540000000b000000"
    "50455253495354454e5400";
    _marshaller_PortableServer_LifespanPolicyValue = new _Marshaller_PortableServer_LifespanPolicyValue;
    PortableServer::_tc_IdUniquenessPolicyValue = 
    "010000001100000080000000010000003700000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f4964556e697175656e65737350"
    "6f6c69637956616c75653a312e300000180000004964556e697175656e65"
    "7373506f6c69637956616c756500020000000a000000554e495155455f49"
    "440000000c0000004d554c5449504c455f494400";
    _marshaller_PortableServer_IdUniquenessPolicyValue = new _Marshaller_PortableServer_IdUniquenessPolicyValue;
    PortableServer::_tc_IdAssignmentPolicyValue = 
    "01000000110000007a000000010000003700000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f496441737369676e6d656e7450"
    "6f6c69637956616c75653a312e30000018000000496441737369676e6d65"
    "6e74506f6c69637956616c7565000200000008000000555345525f494400"
    "0a00000053595354454d5f494400";
    _marshaller_PortableServer_IdAssignmentPolicyValue = new _Marshaller_PortableServer_IdAssignmentPolicyValue;
    PortableServer::_tc_ImplicitActivationPolicyValue = 
    "0100000011000000a3000000010000003d00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f496d706c696369744163746976"
    "6174696f6e506f6c69637956616c75653a312e30000000001e000000496d"
    "706c6963697441637469766174696f6e506f6c69637956616c7565000000"
    "0200000014000000494d504c494349545f41435449564154494f4e001700"
    "00004e4f5f494d504c494349545f41435449564154494f4e00";
    _marshaller_PortableServer_ImplicitActivationPolicyValue = new _Marshaller_PortableServer_ImplicitActivationPolicyValue;
    PortableServer::_tc_ServantRetentionPolicyValue = 
    "010000001100000083000000010000003b00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f53657276616e74526574656e74"
    "696f6e506f6c69637956616c75653a312e3000001c00000053657276616e"
    "74526574656e74696f6e506f6c69637956616c7565000200000007000000"
    "52455441494e00000b0000004e4f4e5f52455441494e00";
    _marshaller_PortableServer_ServantRetentionPolicyValue = new _Marshaller_PortableServer_ServantRetentionPolicyValue;
    PortableServer::_tc_RequestProcessingPolicyValue = 
    "0100000011000000bc000000010000003c00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f5265717565737450726f636573"
    "73696e67506f6c69637956616c75653a312e30001d000000526571756573"
    "7450726f63657373696e67506f6c69637956616c75650000000003000000"
    "1b0000005553455f4143544956455f4f424a4543545f4d41505f4f4e4c59"
    "0000140000005553455f44454641554c545f53455256414e540014000000"
    "5553455f53455256414e545f4d414e4147455200";
    _marshaller_PortableServer_RequestProcessingPolicyValue = new _Marshaller_PortableServer_RequestProcessingPolicyValue;
    PortableServer::POAManager::_tc_AdapterInactive = 
    "01000000160000005c000000010000003a00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f414d616e616765722f4164"
    "6170746572496e6163746976653a312e3000000010000000416461707465"
    "72496e6163746976650000000000";
    _marshaller_PortableServer_POAManager_AdapterInactive = new _Marshaller_PortableServer_POAManager_AdapterInactive;
    PortableServer::POAManager::_tc_State = 
    "01000000110000007d000000010000003000000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f414d616e616765722f5374"
    "6174653a312e30000600000053746174650000000400000008000000484f"
    "4c44494e47000700000041435449564500000b0000004449534341524449"
    "4e47000009000000494e41435449564500";
    _marshaller_PortableServer_POAManager_State = new _Marshaller_PortableServer_POAManager_State;
    PortableServer::POA::_tc_AdapterAlreadyExists = 
    "010000001600000060000000010000003800000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f41646170746572416c"
    "72656164794578697374733a312e30001500000041646170746572416c72"
    "656164794578697374730000000000000000";
    _marshaller_PortableServer_POA_AdapterAlreadyExists = new _Marshaller_PortableServer_POA_AdapterAlreadyExists;
    PortableServer::POA::_tc_AdapterInactive = 
    "010000001600000054000000010000003300000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f41646170746572496e"
    "6163746976653a312e3000001000000041646170746572496e6163746976"
    "650000000000";
    _marshaller_PortableServer_POA_AdapterInactive = new _Marshaller_PortableServer_POA_AdapterInactive;
    PortableServer::POA::_tc_AdapterNonExistent = 
    "01000000160000005c000000010000003600000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f416461707465724e6f"
    "6e4578697374656e743a312e3000000013000000416461707465724e6f6e"
    "4578697374656e74000000000000";
    _marshaller_PortableServer_POA_AdapterNonExistent = new _Marshaller_PortableServer_POA_AdapterNonExistent;
    PortableServer::POA::_tc_InvalidPolicy = 
    "010000001600000064000000010000003100000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f496e76616c6964506f"
    "6c6963793a312e30000000000e000000496e76616c6964506f6c69637900"
    "00000100000006000000696e64657800000004000000";
    _marshaller_PortableServer_POA_InvalidPolicy = new _Marshaller_PortableServer_POA_InvalidPolicy;
    PortableServer::POA::_tc_NoServant = 
    "01000000160000004c000000010000002d00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f4e6f53657276616e74"
    "3a312e30000000000a0000004e6f53657276616e7400000000000000";
    _marshaller_PortableServer_POA_NoServant = new _Marshaller_PortableServer_POA_NoServant;
    PortableServer::POA::_tc_ObjectAlreadyActive = 
    "01000000160000005c000000010000003700000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f4f626a656374416c72"
    "656164794163746976653a312e300000140000004f626a656374416c7265"
    "6164794163746976650000000000";
    _marshaller_PortableServer_POA_ObjectAlreadyActive = new _Marshaller_PortableServer_POA_ObjectAlreadyActive;
    PortableServer::POA::_tc_ObjectNotActive = 
    "010000001600000054000000010000003300000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f4f626a6563744e6f74"
    "4163746976653a312e300000100000004f626a6563744e6f744163746976"
    "650000000000";
    _marshaller_PortableServer_POA_ObjectNotActive = new _Marshaller_PortableServer_POA_ObjectNotActive;
    PortableServer::POA::_tc_ServantAlreadyActive = 
    "010000001600000060000000010000003800000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f53657276616e74416c"
    "72656164794163746976653a312e30001500000053657276616e74416c72"
    "656164794163746976650000000000000000";
    _marshaller_PortableServer_POA_ServantAlreadyActive = new _Marshaller_PortableServer_POA_ServantAlreadyActive;
    PortableServer::POA::_tc_ServantNotActive = 
    "010000001600000058000000010000003400000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f53657276616e744e6f"
    "744163746976653a312e30001100000053657276616e744e6f7441637469"
    "76650000000000000000";
    _marshaller_PortableServer_POA_ServantNotActive = new _Marshaller_PortableServer_POA_ServantNotActive;
    PortableServer::POA::_tc_WrongAdapter = 
    "010000001600000050000000010000003000000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f57726f6e6741646170"
    "7465723a312e30000d00000057726f6e6741646170746572000000000000"
    "0000";
    _marshaller_PortableServer_POA_WrongAdapter = new _Marshaller_PortableServer_POA_WrongAdapter;
    PortableServer::POA::_tc_WrongPolicy = 
    "01000000160000004c000000010000002f00000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f504f412f57726f6e67506f6c69"
    "63793a312e3000000c00000057726f6e67506f6c6963790000000000";
    _marshaller_PortableServer_POA_WrongPolicy = new _Marshaller_PortableServer_POA_WrongPolicy;
    PortableServer::Current::_tc_NoContext = 
    "010000001600000050000000010000003100000049444c3a6f6d672e6f72"
    "672f506f727461626c655365727665722f43757272656e742f4e6f436f6e"
    "746578743a312e30000000000a0000004e6f436f6e746578740000000000"
    "0000";
    _marshaller_PortableServer_Current_NoContext = new _Marshaller_PortableServer_Current_NoContext;
    _marshaller__seq_PortableServer_POA = new _Marshaller__seq_PortableServer_POA;
  }
};

static __tc_init_POA __init_POA;

