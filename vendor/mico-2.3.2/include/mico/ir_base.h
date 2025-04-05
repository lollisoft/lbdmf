/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__IR_BASE_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __IR_BASE_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


typedef char* Identifier;
typedef CORBA::String_var Identifier_var;
typedef CORBA::String_out Identifier_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Identifier;

typedef char* VersionSpec;
typedef CORBA::String_var VersionSpec_var;
typedef CORBA::String_out VersionSpec_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_VersionSpec;

typedef char* RepositoryId;
typedef CORBA::String_var RepositoryId_var;
typedef CORBA::String_out RepositoryId_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_RepositoryId;

enum DefinitionKind {
  dk_none = 0,
  dk_all,
  dk_Attribute,
  dk_Constant,
  dk_Exception,
  dk_Interface,
  dk_Module,
  dk_Operation,
  dk_Typedef,
  dk_Alias,
  dk_Struct,
  dk_Union,
  dk_Enum,
  dk_Primitive,
  dk_String,
  dk_Sequence,
  dk_Array,
  dk_Repository,
  dk_Wstring,
  dk_Fixed,
  dk_Value,
  dk_ValueBox,
  dk_ValueMember,
  dk_Native
};

typedef DefinitionKind& DefinitionKind_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_DefinitionKind;

class IRObject;
typedef IRObject *IRObject_ptr;
typedef IRObject_ptr IRObjectRef;
typedef ObjVar<IRObject> IRObject_var;
typedef IRObject_var IRObject_out;


// Common definitions for interface IRObject
class IRObject : 
  virtual public CORBA::Object
{
  public:
    virtual ~IRObject();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef IRObject_ptr _ptr_type;
    typedef IRObject_var _var_type;
    #endif

    static IRObject_ptr _narrow( CORBA::Object_ptr obj );
    static IRObject_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static IRObject_ptr _duplicate( IRObject_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static IRObject_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual DefinitionKind def_kind() = 0;

    virtual void destroy() = 0;

  protected:
    IRObject() {};
  private:
    IRObject( const IRObject& );
    void operator=( const IRObject& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_IRObject;

// Stub for interface IRObject
class IRObject_stub:
  virtual public IRObject
{
  public:
    virtual ~IRObject_stub();
    DefinitionKind def_kind();

    void destroy();

  private:
    void operator=( const IRObject_stub& );
};

class IRObject_skel :
  virtual public StaticMethodDispatcher,
  virtual public IRObject
{
  public:
    IRObject_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~IRObject_skel();
    IRObject_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    IRObject_ptr _this();

};

class IDLType;
typedef IDLType *IDLType_ptr;
typedef IDLType_ptr IDLTypeRef;
typedef ObjVar<IDLType> IDLType_var;
typedef IDLType_var IDLType_out;


// Common definitions for interface IDLType
class IDLType : 
  virtual public ::CORBA::IRObject
{
  public:
    virtual ~IDLType();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef IDLType_ptr _ptr_type;
    typedef IDLType_var _var_type;
    #endif

    static IDLType_ptr _narrow( CORBA::Object_ptr obj );
    static IDLType_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static IDLType_ptr _duplicate( IDLType_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static IDLType_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr type() = 0;

  protected:
    IDLType() {};
  private:
    IDLType( const IDLType& );
    void operator=( const IDLType& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_IDLType;

// Stub for interface IDLType
class IDLType_stub:
  virtual public IDLType,
  virtual public ::CORBA::IRObject_stub
{
  public:
    virtual ~IDLType_stub();
    CORBA::TypeCode_ptr type();

  private:
    void operator=( const IDLType_stub& );
};

class IDLType_skel :
  virtual public StaticMethodDispatcher,
  virtual public IDLType
{
  public:
    IDLType_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~IDLType_skel();
    IDLType_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    IDLType_ptr _this();

};

struct StructMember;
typedef TVarVar<StructMember> StructMember_var;
typedef StructMember_var StructMember_out;

struct StructMember {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef StructMember_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  StructMember();
  ~StructMember();
  StructMember( const StructMember& s );
  StructMember& operator=( const StructMember& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  CORBA::TypeCode_var type;
  IDLType_var type_def;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_StructMember;

typedef SequenceTmpl<StructMember,MICO_TID_DEF> StructMemberSeq;
#ifdef _WINDOWS
static StructMemberSeq _dummy_StructMemberSeq;
#endif
typedef TSeqVar<SequenceTmpl<StructMember,MICO_TID_DEF> > StructMemberSeq_var;
typedef StructMemberSeq_var StructMemberSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_StructMemberSeq;

struct UnionMember;
typedef TVarVar<UnionMember> UnionMember_var;
typedef UnionMember_var UnionMember_out;

struct UnionMember {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef UnionMember_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  UnionMember();
  ~UnionMember();
  UnionMember( const UnionMember& s );
  UnionMember& operator=( const UnionMember& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  CORBA::Any label;
  CORBA::TypeCode_var type;
  IDLType_var type_def;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_UnionMember;

typedef SequenceTmpl<UnionMember,MICO_TID_DEF> UnionMemberSeq;
#ifdef _WINDOWS
static UnionMemberSeq _dummy_UnionMemberSeq;
#endif
typedef TSeqVar<SequenceTmpl<UnionMember,MICO_TID_DEF> > UnionMemberSeq_var;
typedef UnionMemberSeq_var UnionMemberSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_UnionMemberSeq;

typedef StringSequenceTmpl<CORBA::String_var> EnumMemberSeq;
#ifdef _WINDOWS
static EnumMemberSeq _dummy_EnumMemberSeq;
#endif
typedef TSeqVar<StringSequenceTmpl<CORBA::String_var> > EnumMemberSeq_var;
typedef EnumMemberSeq_var EnumMemberSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_EnumMemberSeq;

typedef CORBA::Short Visibility;
MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Visibility;

MICO_EXPORT_CONST_DECL const CORBA::Short PRIVATE_MEMBER;
MICO_EXPORT_CONST_DECL const CORBA::Short PUBLIC_MEMBER;
typedef CORBA::Short ValueModifier;
MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueModifier;

MICO_EXPORT_CONST_DECL const CORBA::Short VM_NONE;
MICO_EXPORT_CONST_DECL const CORBA::Short VM_CUSTOM;
MICO_EXPORT_CONST_DECL const CORBA::Short VM_ABSTRACT;
MICO_EXPORT_CONST_DECL const CORBA::Short VM_TRUNCATABLE;
struct ValueMember;
typedef TVarVar<ValueMember> ValueMember_var;
typedef ValueMember_var ValueMember_out;

struct ValueMember {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ValueMember_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ValueMember();
  ~ValueMember();
  ValueMember( const ValueMember& s );
  ValueMember& operator=( const ValueMember& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var type;
  IDLType_var type_def;
  Visibility access;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueMember;

typedef SequenceTmpl<ValueMember,MICO_TID_DEF> ValueMemberSeq;
#ifdef _WINDOWS
static ValueMemberSeq _dummy_ValueMemberSeq;
#endif
typedef TSeqVar<SequenceTmpl<ValueMember,MICO_TID_DEF> > ValueMemberSeq_var;
typedef ValueMemberSeq_var ValueMemberSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueMemberSeq;

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &a, const ::CORBA::DefinitionKind &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::DefinitionKind &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_DefinitionKind;

void operator<<=( CORBA::Any &a, const CORBA::IRObject_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::IRObject_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::IRObject_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_IRObject;

void operator<<=( CORBA::Any &a, const CORBA::IDLType_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::IDLType_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::IDLType_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_IDLType;

void operator<<=( CORBA::Any &_a, const ::CORBA::StructMember &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::StructMember *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::StructMember &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::StructMember *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_StructMember;

void operator<<=( CORBA::Any &_a, const ::CORBA::UnionMember &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::UnionMember *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::UnionMember &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::UnionMember *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_UnionMember;

void operator<<=( CORBA::Any &_a, const ::CORBA::ValueMember &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ValueMember *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueMember &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueMember *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueMember;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::StructMember,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_StructMember;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::UnionMember,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_UnionMember;

void operator<<=( CORBA::Any &_a, const StringSequenceTmpl<CORBA::String_var> &_s );
void operator<<=( CORBA::Any &_a, StringSequenceTmpl<CORBA::String_var> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, StringSequenceTmpl<CORBA::String_var> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, StringSequenceTmpl<CORBA::String_var> *&_s );

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ValueMember,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ValueMember;

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
