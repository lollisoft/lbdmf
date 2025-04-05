/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__IR_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __IR_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


typedef char* ScopedName;
typedef CORBA::String_var ScopedName_var;
typedef CORBA::String_out ScopedName_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ScopedName;

class Container;
typedef Container *Container_ptr;
typedef Container_ptr ContainerRef;
typedef ObjVar<Container> Container_var;
typedef Container_var Container_out;

class Repository;
typedef Repository *Repository_ptr;
typedef Repository_ptr RepositoryRef;
typedef ObjVar<Repository> Repository_var;
typedef Repository_var Repository_out;

class Contained;
typedef Contained *Contained_ptr;
typedef Contained_ptr ContainedRef;
typedef ObjVar<Contained> Contained_var;
typedef Contained_var Contained_out;


// Common definitions for interface Contained
class Contained : 
  virtual public ::CORBA::IRObject
{
  public:
    virtual ~Contained();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Contained_ptr _ptr_type;
    typedef Contained_var _var_type;
    #endif

    static Contained_ptr _narrow( CORBA::Object_ptr obj );
    static Contained_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Contained_ptr _duplicate( Contained_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Contained_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    struct Description;
    typedef TVarVar<Description> Description_var;
    typedef Description_var Description_out;

    struct Description {
      #ifdef HAVE_TYPEDEF_OVERLOAD
      typedef Description_var _var_type;
      #endif
      #ifdef HAVE_EXPLICIT_STRUCT_OPS
      Description();
      ~Description();
      Description( const Description& s );
      Description& operator=( const Description& s );
      #endif //HAVE_EXPLICIT_STRUCT_OPS

      DefinitionKind kind;
      CORBA::Any value;
    };

    static CORBA::TypeCodeConst _tc_Description;

    virtual char* id() = 0;
    virtual void id( const char* value ) = 0;
    virtual char* name() = 0;
    virtual void name( const char* value ) = 0;
    virtual char* version() = 0;
    virtual void version( const char* value ) = 0;
    virtual Container_ptr defined_in() = 0;
    virtual char* absolute_name() = 0;
    virtual Repository_ptr containing_repository() = 0;

    virtual Description* describe() = 0;
    virtual void move( Container_ptr new_container, const char* new_name, const char* new_version ) = 0;

  protected:
    Contained() {};
  private:
    Contained( const Contained& );
    void operator=( const Contained& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Contained;

// Stub for interface Contained
class Contained_stub:
  virtual public Contained,
  virtual public ::CORBA::IRObject_stub
{
  public:
    virtual ~Contained_stub();
    char* id();
    void id( const char* value );
    char* name();
    void name( const char* value );
    char* version();
    void version( const char* value );
    Container_ptr defined_in();
    char* absolute_name();
    Repository_ptr containing_repository();

    Description* describe();
    void move( Container_ptr new_container, const char* new_name, const char* new_version );

  private:
    void operator=( const Contained_stub& );
};

class Contained_skel :
  virtual public StaticMethodDispatcher,
  virtual public Contained
{
  public:
    Contained_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~Contained_skel();
    Contained_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    Contained_ptr _this();

};

class ValueDef;
//typedef ValueDef *ValueDef_ptr;
typedef ValueDef_ptr ValueDefRef;
typedef ObjVar<ValueDef> ValueDef_var;
typedef ValueDef_var ValueDef_out;

typedef IfaceSequenceTmpl<ValueDef_var,ValueDef_ptr> ValueDefSeq;
#ifdef _WINDOWS
static ValueDefSeq _dummy_ValueDefSeq;
#endif
typedef TSeqVar<IfaceSequenceTmpl<ValueDef_var,ValueDef_ptr> > ValueDefSeq_var;
typedef ValueDefSeq_var ValueDefSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueDefSeq;

class InterfaceDef;
//typedef InterfaceDef *InterfaceDef_ptr;
typedef InterfaceDef_ptr InterfaceDefRef;
typedef ObjVar<InterfaceDef> InterfaceDef_var;
typedef InterfaceDef_var InterfaceDef_out;

typedef IfaceSequenceTmpl<InterfaceDef_var,InterfaceDef_ptr> InterfaceDefSeq;
#ifdef _WINDOWS
static InterfaceDefSeq _dummy_InterfaceDefSeq;
#endif
typedef TSeqVar<IfaceSequenceTmpl<InterfaceDef_var,InterfaceDef_ptr> > InterfaceDefSeq_var;
typedef InterfaceDefSeq_var InterfaceDefSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_InterfaceDefSeq;

typedef IfaceSequenceTmpl<Contained_var,Contained_ptr> ContainedSeq;
#ifdef _WINDOWS
static ContainedSeq _dummy_ContainedSeq;
#endif
typedef TSeqVar<IfaceSequenceTmpl<Contained_var,Contained_ptr> > ContainedSeq_var;
typedef ContainedSeq_var ContainedSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ContainedSeq;

struct Initializer;
typedef TVarVar<Initializer> Initializer_var;
typedef Initializer_var Initializer_out;

struct Initializer {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef Initializer_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  Initializer();
  ~Initializer();
  Initializer( const Initializer& s );
  Initializer& operator=( const Initializer& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  StructMemberSeq members;
  Identifier_var name;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Initializer;

typedef SequenceTmpl<Initializer,MICO_TID_DEF> InitializerSeq;
#ifdef _WINDOWS
static InitializerSeq _dummy_InitializerSeq;
#endif
typedef TSeqVar<SequenceTmpl<Initializer,MICO_TID_DEF> > InitializerSeq_var;
typedef InitializerSeq_var InitializerSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_InitializerSeq;

class ModuleDef;
typedef ModuleDef *ModuleDef_ptr;
typedef ModuleDef_ptr ModuleDefRef;
typedef ObjVar<ModuleDef> ModuleDef_var;
typedef ModuleDef_var ModuleDef_out;

class ConstantDef;
typedef ConstantDef *ConstantDef_ptr;
typedef ConstantDef_ptr ConstantDefRef;
typedef ObjVar<ConstantDef> ConstantDef_var;
typedef ConstantDef_var ConstantDef_out;

class StructDef;
typedef StructDef *StructDef_ptr;
typedef StructDef_ptr StructDefRef;
typedef ObjVar<StructDef> StructDef_var;
typedef StructDef_var StructDef_out;

class ExceptionDef;
typedef ExceptionDef *ExceptionDef_ptr;
typedef ExceptionDef_ptr ExceptionDefRef;
typedef ObjVar<ExceptionDef> ExceptionDef_var;
typedef ExceptionDef_var ExceptionDef_out;

class UnionDef;
typedef UnionDef *UnionDef_ptr;
typedef UnionDef_ptr UnionDefRef;
typedef ObjVar<UnionDef> UnionDef_var;
typedef UnionDef_var UnionDef_out;

class EnumDef;
typedef EnumDef *EnumDef_ptr;
typedef EnumDef_ptr EnumDefRef;
typedef ObjVar<EnumDef> EnumDef_var;
typedef EnumDef_var EnumDef_out;

class AliasDef;
typedef AliasDef *AliasDef_ptr;
typedef AliasDef_ptr AliasDefRef;
typedef ObjVar<AliasDef> AliasDef_var;
typedef AliasDef_var AliasDef_out;

class ValueBoxDef;
typedef ValueBoxDef *ValueBoxDef_ptr;
typedef ValueBoxDef_ptr ValueBoxDefRef;
typedef ObjVar<ValueBoxDef> ValueBoxDef_var;
typedef ValueBoxDef_var ValueBoxDef_out;

class NativeDef;
typedef NativeDef *NativeDef_ptr;
typedef NativeDef_ptr NativeDefRef;
typedef ObjVar<NativeDef> NativeDef_var;
typedef NativeDef_var NativeDef_out;


// Common definitions for interface Container
class Container : 
  virtual public ::CORBA::IRObject
{
  public:
    virtual ~Container();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Container_ptr _ptr_type;
    typedef Container_var _var_type;
    #endif

    static Container_ptr _narrow( CORBA::Object_ptr obj );
    static Container_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Container_ptr _duplicate( Container_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Container_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    struct Description;
    typedef TVarVar<Description> Description_var;
    typedef Description_var Description_out;

    struct Description {
      #ifdef HAVE_TYPEDEF_OVERLOAD
      typedef Description_var _var_type;
      #endif
      #ifdef HAVE_EXPLICIT_STRUCT_OPS
      Description();
      ~Description();
      Description( const Description& s );
      Description& operator=( const Description& s );
      #endif //HAVE_EXPLICIT_STRUCT_OPS

      Contained_var contained_object;
      DefinitionKind kind;
      CORBA::Any value;
    };

    static CORBA::TypeCodeConst _tc_Description;

    typedef SequenceTmpl<Description,MICO_TID_DEF> DescriptionSeq;
    #ifdef _WINDOWS
    static DescriptionSeq _dummy_DescriptionSeq;
    #endif
    typedef TSeqVar<SequenceTmpl<Description,MICO_TID_DEF> > DescriptionSeq_var;
    typedef DescriptionSeq_var DescriptionSeq_out;

    static CORBA::TypeCodeConst _tc_DescriptionSeq;

    virtual Contained_ptr lookup( const char* search_name ) = 0;
    virtual ContainedSeq* contents( DefinitionKind limit_type, CORBA::Boolean exclude_inherited ) = 0;
    virtual ContainedSeq* lookup_name( const char* search_name, CORBA::Long levels_to_search, DefinitionKind limit_type, CORBA::Boolean exclude_inherited ) = 0;
    virtual DescriptionSeq* describe_contents( DefinitionKind limit_type, CORBA::Boolean exclude_inherited, CORBA::Long max_returned_objs ) = 0;
    virtual ModuleDef_ptr create_module( const char* id, const char* name, const char* version ) = 0;
    virtual ConstantDef_ptr create_constant( const char* id, const char* name, const char* version, IDLType_ptr type, const CORBA::Any& value ) = 0;
    virtual StructDef_ptr create_struct( const char* id, const char* name, const char* version, const StructMemberSeq& members ) = 0;
    virtual ExceptionDef_ptr create_exception( const char* id, const char* name, const char* version, const StructMemberSeq& members ) = 0;
    virtual UnionDef_ptr create_union( const char* id, const char* name, const char* version, IDLType_ptr discriminator_type, const UnionMemberSeq& members ) = 0;
    virtual EnumDef_ptr create_enum( const char* id, const char* name, const char* version, const EnumMemberSeq& members ) = 0;
    virtual AliasDef_ptr create_alias( const char* id, const char* name, const char* version, IDLType_ptr original_type ) = 0;
    virtual InterfaceDef_ptr create_interface( const char* id, const char* name, const char* version, const InterfaceDefSeq& base_interfaces, CORBA::Boolean is_abstract
#ifdef HAVE_CORBA_2_1
  = FALSE
#endif
     ) = 0;
    virtual ValueDef_ptr create_value( const char* id, const char* name, const char* version, CORBA::Boolean is_custom, CORBA::Boolean is_abstract, ValueDef_ptr base_value, CORBA::Boolean is_truncatable, const ValueDefSeq& abstract_base_values, const InterfaceDefSeq& supported_interfaces, const InitializerSeq& initializers ) = 0;
    virtual ValueBoxDef_ptr create_value_box( const char* id, const char* name, const char* version, IDLType_ptr original_type_def ) = 0;
    virtual NativeDef_ptr create_native( const char* id, const char* name, const char* version ) = 0;
    virtual Contained_ptr find( const char* search_name ) = 0;
    virtual ContainedSeq* find_name( const char* search_name, DefinitionKind limit_type ) = 0;
    virtual Contained_ptr locate_id( const char* id ) = 0;
    virtual Contained_ptr locate_name( const char* name, CORBA::Boolean include_enclosing_scopes, CORBA::Boolean is_first_level ) = 0;
    virtual void remove_contained( Contained_ptr con ) = 0;
    virtual void add_contained( Contained_ptr con ) = 0;

  protected:
    Container() {};
  private:
    Container( const Container& );
    void operator=( const Container& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Container;

// Stub for interface Container
class Container_stub:
  virtual public Container,
  virtual public ::CORBA::IRObject_stub
{
  public:
    virtual ~Container_stub();
    Contained_ptr lookup( const char* search_name );
    ContainedSeq* contents( DefinitionKind limit_type, CORBA::Boolean exclude_inherited );
    ContainedSeq* lookup_name( const char* search_name, CORBA::Long levels_to_search, DefinitionKind limit_type, CORBA::Boolean exclude_inherited );
    DescriptionSeq* describe_contents( DefinitionKind limit_type, CORBA::Boolean exclude_inherited, CORBA::Long max_returned_objs );
    ModuleDef_ptr create_module( const char* id, const char* name, const char* version );
    ConstantDef_ptr create_constant( const char* id, const char* name, const char* version, IDLType_ptr type, const CORBA::Any& value );
    StructDef_ptr create_struct( const char* id, const char* name, const char* version, const StructMemberSeq& members );
    ExceptionDef_ptr create_exception( const char* id, const char* name, const char* version, const StructMemberSeq& members );
    UnionDef_ptr create_union( const char* id, const char* name, const char* version, IDLType_ptr discriminator_type, const UnionMemberSeq& members );
    EnumDef_ptr create_enum( const char* id, const char* name, const char* version, const EnumMemberSeq& members );
    AliasDef_ptr create_alias( const char* id, const char* name, const char* version, IDLType_ptr original_type );
    InterfaceDef_ptr create_interface( const char* id, const char* name, const char* version, const InterfaceDefSeq& base_interfaces, CORBA::Boolean is_abstract
#ifdef HAVE_CORBA_2_1
  = FALSE
#endif
      );
    ValueDef_ptr create_value( const char* id, const char* name, const char* version, CORBA::Boolean is_custom, CORBA::Boolean is_abstract, ValueDef_ptr base_value, CORBA::Boolean is_truncatable, const ValueDefSeq& abstract_base_values, const InterfaceDefSeq& supported_interfaces, const InitializerSeq& initializers );
    ValueBoxDef_ptr create_value_box( const char* id, const char* name, const char* version, IDLType_ptr original_type_def );
    NativeDef_ptr create_native( const char* id, const char* name, const char* version );
    Contained_ptr find( const char* search_name );
    ContainedSeq* find_name( const char* search_name, DefinitionKind limit_type );
    Contained_ptr locate_id( const char* id );
    Contained_ptr locate_name( const char* name, CORBA::Boolean include_enclosing_scopes, CORBA::Boolean is_first_level );
    void remove_contained( Contained_ptr con );
    void add_contained( Contained_ptr con );

  private:
    void operator=( const Container_stub& );
};

class Container_skel :
  virtual public StaticMethodDispatcher,
  virtual public Container
{
  public:
    Container_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~Container_skel();
    Container_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    Container_ptr _this();

};

enum PrimitiveKind {
  pk_null = 0,
  pk_void,
  pk_short,
  pk_long,
  pk_ushort,
  pk_ulong,
  pk_float,
  pk_double,
  pk_boolean,
  pk_char,
  pk_octet,
  pk_any,
  pk_TypeCode,
  pk_Principal,
  pk_string,
  pk_objref,
  pk_longlong,
  pk_ulonglong,
  pk_longdouble,
  pk_wchar,
  pk_wstring,
  pk_value_base
};

typedef PrimitiveKind& PrimitiveKind_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_PrimitiveKind;

class PrimitiveDef;
typedef PrimitiveDef *PrimitiveDef_ptr;
typedef PrimitiveDef_ptr PrimitiveDefRef;
typedef ObjVar<PrimitiveDef> PrimitiveDef_var;
typedef PrimitiveDef_var PrimitiveDef_out;

class StringDef;
typedef StringDef *StringDef_ptr;
typedef StringDef_ptr StringDefRef;
typedef ObjVar<StringDef> StringDef_var;
typedef StringDef_var StringDef_out;

class WstringDef;
typedef WstringDef *WstringDef_ptr;
typedef WstringDef_ptr WstringDefRef;
typedef ObjVar<WstringDef> WstringDef_var;
typedef WstringDef_var WstringDef_out;

class SequenceDef;
typedef SequenceDef *SequenceDef_ptr;
typedef SequenceDef_ptr SequenceDefRef;
typedef ObjVar<SequenceDef> SequenceDef_var;
typedef SequenceDef_var SequenceDef_out;

class ArrayDef;
typedef ArrayDef *ArrayDef_ptr;
typedef ArrayDef_ptr ArrayDefRef;
typedef ObjVar<ArrayDef> ArrayDef_var;
typedef ArrayDef_var ArrayDef_out;

class FixedDef;
typedef FixedDef *FixedDef_ptr;
typedef FixedDef_ptr FixedDefRef;
typedef ObjVar<FixedDef> FixedDef_var;
typedef FixedDef_var FixedDef_out;


// Common definitions for interface Repository
class Repository : 
  virtual public ::CORBA::Container
{
  public:
    virtual ~Repository();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Repository_ptr _ptr_type;
    typedef Repository_var _var_type;
    #endif

    static Repository_ptr _narrow( CORBA::Object_ptr obj );
    static Repository_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Repository_ptr _duplicate( Repository_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Repository_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual Contained_ptr lookup_id( const char* search_id ) = 0;
    virtual PrimitiveDef_ptr get_primitive( PrimitiveKind kind ) = 0;
    virtual StringDef_ptr create_string( CORBA::ULong bound ) = 0;
    virtual WstringDef_ptr create_wstring( CORBA::ULong bound ) = 0;
    virtual SequenceDef_ptr create_sequence( CORBA::ULong bound, IDLType_ptr element_type ) = 0;
    virtual ArrayDef_ptr create_array( CORBA::ULong length, IDLType_ptr element_type ) = 0;
    virtual FixedDef_ptr create_fixed( CORBA::UShort digits, CORBA::Short scale ) = 0;

  protected:
    Repository() {};
  private:
    Repository( const Repository& );
    void operator=( const Repository& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_Repository;

// Stub for interface Repository
class Repository_stub:
  virtual public Repository,
  virtual public ::CORBA::Container_stub
{
  public:
    virtual ~Repository_stub();
    Contained_ptr lookup_id( const char* search_id );
    PrimitiveDef_ptr get_primitive( PrimitiveKind kind );
    StringDef_ptr create_string( CORBA::ULong bound );
    WstringDef_ptr create_wstring( CORBA::ULong bound );
    SequenceDef_ptr create_sequence( CORBA::ULong bound, IDLType_ptr element_type );
    ArrayDef_ptr create_array( CORBA::ULong length, IDLType_ptr element_type );
    FixedDef_ptr create_fixed( CORBA::UShort digits, CORBA::Short scale );

  private:
    void operator=( const Repository_stub& );
};

class Repository_skel :
  virtual public StaticMethodDispatcher,
  virtual public Repository
{
  public:
    Repository_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~Repository_skel();
    Repository_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    Repository_ptr _this();

};


// Common definitions for interface ModuleDef
class ModuleDef : 
  virtual public ::CORBA::Container,
  virtual public ::CORBA::Contained
{
  public:
    virtual ~ModuleDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ModuleDef_ptr _ptr_type;
    typedef ModuleDef_var _var_type;
    #endif

    static ModuleDef_ptr _narrow( CORBA::Object_ptr obj );
    static ModuleDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ModuleDef_ptr _duplicate( ModuleDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ModuleDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

  protected:
    ModuleDef() {};
  private:
    ModuleDef( const ModuleDef& );
    void operator=( const ModuleDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ModuleDef;

// Stub for interface ModuleDef
class ModuleDef_stub:
  virtual public ModuleDef,
  virtual public ::CORBA::Container_stub,
  virtual public ::CORBA::Contained_stub
{
  public:
    virtual ~ModuleDef_stub();
  private:
    void operator=( const ModuleDef_stub& );
};

class ModuleDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ModuleDef
{
  public:
    ModuleDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ModuleDef_skel();
    ModuleDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ModuleDef_ptr _this();

};

struct ModuleDescription;
typedef TVarVar<ModuleDescription> ModuleDescription_var;
typedef ModuleDescription_var ModuleDescription_out;

struct ModuleDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ModuleDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ModuleDescription();
  ~ModuleDescription();
  ModuleDescription( const ModuleDescription& s );
  ModuleDescription& operator=( const ModuleDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ModuleDescription;


// Common definitions for interface ConstantDef
class ConstantDef : 
  virtual public ::CORBA::Contained
{
  public:
    virtual ~ConstantDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ConstantDef_ptr _ptr_type;
    typedef ConstantDef_var _var_type;
    #endif

    static ConstantDef_ptr _narrow( CORBA::Object_ptr obj );
    static ConstantDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ConstantDef_ptr _duplicate( ConstantDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ConstantDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr type() = 0;
    virtual IDLType_ptr type_def() = 0;
    virtual void type_def( IDLType_ptr value ) = 0;
    virtual CORBA::Any* value() = 0;
    virtual void value( const CORBA::Any& value ) = 0;

  protected:
    ConstantDef() {};
  private:
    ConstantDef( const ConstantDef& );
    void operator=( const ConstantDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ConstantDef;

// Stub for interface ConstantDef
class ConstantDef_stub:
  virtual public ConstantDef,
  virtual public ::CORBA::Contained_stub
{
  public:
    virtual ~ConstantDef_stub();
    CORBA::TypeCode_ptr type();
    IDLType_ptr type_def();
    void type_def( IDLType_ptr value );
    CORBA::Any* value();
    void value( const CORBA::Any& value );

  private:
    void operator=( const ConstantDef_stub& );
};

class ConstantDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ConstantDef
{
  public:
    ConstantDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ConstantDef_skel();
    ConstantDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ConstantDef_ptr _this();

};

struct ConstantDescription;
typedef TVarVar<ConstantDescription> ConstantDescription_var;
typedef ConstantDescription_var ConstantDescription_out;

struct ConstantDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ConstantDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ConstantDescription();
  ~ConstantDescription();
  ConstantDescription( const ConstantDescription& s );
  ConstantDescription& operator=( const ConstantDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var type;
  CORBA::Any value;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ConstantDescription;

class TypedefDef;
typedef TypedefDef *TypedefDef_ptr;
typedef TypedefDef_ptr TypedefDefRef;
typedef ObjVar<TypedefDef> TypedefDef_var;
typedef TypedefDef_var TypedefDef_out;


// Common definitions for interface TypedefDef
class TypedefDef : 
  virtual public ::CORBA::Contained,
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~TypedefDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef TypedefDef_ptr _ptr_type;
    typedef TypedefDef_var _var_type;
    #endif

    static TypedefDef_ptr _narrow( CORBA::Object_ptr obj );
    static TypedefDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static TypedefDef_ptr _duplicate( TypedefDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static TypedefDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

  protected:
    TypedefDef() {};
  private:
    TypedefDef( const TypedefDef& );
    void operator=( const TypedefDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_TypedefDef;

// Stub for interface TypedefDef
class TypedefDef_stub:
  virtual public TypedefDef,
  virtual public ::CORBA::Contained_stub,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~TypedefDef_stub();
  private:
    void operator=( const TypedefDef_stub& );
};

class TypedefDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public TypedefDef
{
  public:
    TypedefDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~TypedefDef_skel();
    TypedefDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    TypedefDef_ptr _this();

};

struct TypeDescription;
typedef TVarVar<TypeDescription> TypeDescription_var;
typedef TypeDescription_var TypeDescription_out;

struct TypeDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef TypeDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  TypeDescription();
  ~TypeDescription();
  TypeDescription( const TypeDescription& s );
  TypeDescription& operator=( const TypeDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var type;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_TypeDescription;


// Common definitions for interface StructDef
class StructDef : 
  virtual public ::CORBA::TypedefDef,
  virtual public ::CORBA::Container
{
  public:
    virtual ~StructDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef StructDef_ptr _ptr_type;
    typedef StructDef_var _var_type;
    #endif

    static StructDef_ptr _narrow( CORBA::Object_ptr obj );
    static StructDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static StructDef_ptr _duplicate( StructDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static StructDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual StructMemberSeq* members() = 0;
    virtual void members( const StructMemberSeq& value ) = 0;

  protected:
    StructDef() {};
  private:
    StructDef( const StructDef& );
    void operator=( const StructDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_StructDef;

// Stub for interface StructDef
class StructDef_stub:
  virtual public StructDef,
  virtual public ::CORBA::TypedefDef_stub,
  virtual public ::CORBA::Container_stub
{
  public:
    virtual ~StructDef_stub();
    StructMemberSeq* members();
    void members( const StructMemberSeq& value );

  private:
    void operator=( const StructDef_stub& );
};

class StructDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public StructDef
{
  public:
    StructDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~StructDef_skel();
    StructDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    StructDef_ptr _this();

};


// Common definitions for interface UnionDef
class UnionDef : 
  virtual public ::CORBA::TypedefDef,
  virtual public ::CORBA::Container
{
  public:
    virtual ~UnionDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef UnionDef_ptr _ptr_type;
    typedef UnionDef_var _var_type;
    #endif

    static UnionDef_ptr _narrow( CORBA::Object_ptr obj );
    static UnionDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static UnionDef_ptr _duplicate( UnionDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static UnionDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr discriminator_type() = 0;
    virtual IDLType_ptr discriminator_type_def() = 0;
    virtual void discriminator_type_def( IDLType_ptr value ) = 0;
    virtual UnionMemberSeq* members() = 0;
    virtual void members( const UnionMemberSeq& value ) = 0;

  protected:
    UnionDef() {};
  private:
    UnionDef( const UnionDef& );
    void operator=( const UnionDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_UnionDef;

// Stub for interface UnionDef
class UnionDef_stub:
  virtual public UnionDef,
  virtual public ::CORBA::TypedefDef_stub,
  virtual public ::CORBA::Container_stub
{
  public:
    virtual ~UnionDef_stub();
    CORBA::TypeCode_ptr discriminator_type();
    IDLType_ptr discriminator_type_def();
    void discriminator_type_def( IDLType_ptr value );
    UnionMemberSeq* members();
    void members( const UnionMemberSeq& value );

  private:
    void operator=( const UnionDef_stub& );
};

class UnionDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public UnionDef
{
  public:
    UnionDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~UnionDef_skel();
    UnionDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    UnionDef_ptr _this();

};


// Common definitions for interface EnumDef
class EnumDef : 
  virtual public ::CORBA::TypedefDef
{
  public:
    virtual ~EnumDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef EnumDef_ptr _ptr_type;
    typedef EnumDef_var _var_type;
    #endif

    static EnumDef_ptr _narrow( CORBA::Object_ptr obj );
    static EnumDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static EnumDef_ptr _duplicate( EnumDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static EnumDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual EnumMemberSeq* members() = 0;
    virtual void members( const EnumMemberSeq& value ) = 0;

  protected:
    EnumDef() {};
  private:
    EnumDef( const EnumDef& );
    void operator=( const EnumDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_EnumDef;

// Stub for interface EnumDef
class EnumDef_stub:
  virtual public EnumDef,
  virtual public ::CORBA::TypedefDef_stub
{
  public:
    virtual ~EnumDef_stub();
    EnumMemberSeq* members();
    void members( const EnumMemberSeq& value );

  private:
    void operator=( const EnumDef_stub& );
};

class EnumDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public EnumDef
{
  public:
    EnumDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~EnumDef_skel();
    EnumDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    EnumDef_ptr _this();

};


// Common definitions for interface AliasDef
class AliasDef : 
  virtual public ::CORBA::TypedefDef
{
  public:
    virtual ~AliasDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef AliasDef_ptr _ptr_type;
    typedef AliasDef_var _var_type;
    #endif

    static AliasDef_ptr _narrow( CORBA::Object_ptr obj );
    static AliasDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static AliasDef_ptr _duplicate( AliasDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static AliasDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual IDLType_ptr original_type_def() = 0;
    virtual void original_type_def( IDLType_ptr value ) = 0;

  protected:
    AliasDef() {};
  private:
    AliasDef( const AliasDef& );
    void operator=( const AliasDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_AliasDef;

// Stub for interface AliasDef
class AliasDef_stub:
  virtual public AliasDef,
  virtual public ::CORBA::TypedefDef_stub
{
  public:
    virtual ~AliasDef_stub();
    IDLType_ptr original_type_def();
    void original_type_def( IDLType_ptr value );

  private:
    void operator=( const AliasDef_stub& );
};

class AliasDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public AliasDef
{
  public:
    AliasDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~AliasDef_skel();
    AliasDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    AliasDef_ptr _this();

};


// Common definitions for interface NativeDef
class NativeDef : 
  virtual public ::CORBA::TypedefDef
{
  public:
    virtual ~NativeDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef NativeDef_ptr _ptr_type;
    typedef NativeDef_var _var_type;
    #endif

    static NativeDef_ptr _narrow( CORBA::Object_ptr obj );
    static NativeDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static NativeDef_ptr _duplicate( NativeDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static NativeDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

  protected:
    NativeDef() {};
  private:
    NativeDef( const NativeDef& );
    void operator=( const NativeDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_NativeDef;

// Stub for interface NativeDef
class NativeDef_stub:
  virtual public NativeDef,
  virtual public ::CORBA::TypedefDef_stub
{
  public:
    virtual ~NativeDef_stub();
  private:
    void operator=( const NativeDef_stub& );
};

class NativeDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public NativeDef
{
  public:
    NativeDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~NativeDef_skel();
    NativeDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    NativeDef_ptr _this();

};


// Common definitions for interface PrimitiveDef
class PrimitiveDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~PrimitiveDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef PrimitiveDef_ptr _ptr_type;
    typedef PrimitiveDef_var _var_type;
    #endif

    static PrimitiveDef_ptr _narrow( CORBA::Object_ptr obj );
    static PrimitiveDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static PrimitiveDef_ptr _duplicate( PrimitiveDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static PrimitiveDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual PrimitiveKind kind() = 0;

  protected:
    PrimitiveDef() {};
  private:
    PrimitiveDef( const PrimitiveDef& );
    void operator=( const PrimitiveDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_PrimitiveDef;

// Stub for interface PrimitiveDef
class PrimitiveDef_stub:
  virtual public PrimitiveDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~PrimitiveDef_stub();
    PrimitiveKind kind();

  private:
    void operator=( const PrimitiveDef_stub& );
};

class PrimitiveDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public PrimitiveDef
{
  public:
    PrimitiveDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~PrimitiveDef_skel();
    PrimitiveDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    PrimitiveDef_ptr _this();

};


// Common definitions for interface StringDef
class StringDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~StringDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef StringDef_ptr _ptr_type;
    typedef StringDef_var _var_type;
    #endif

    static StringDef_ptr _narrow( CORBA::Object_ptr obj );
    static StringDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static StringDef_ptr _duplicate( StringDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static StringDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::ULong bound() = 0;
    virtual void bound( CORBA::ULong value ) = 0;

  protected:
    StringDef() {};
  private:
    StringDef( const StringDef& );
    void operator=( const StringDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_StringDef;

// Stub for interface StringDef
class StringDef_stub:
  virtual public StringDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~StringDef_stub();
    CORBA::ULong bound();
    void bound( CORBA::ULong value );

  private:
    void operator=( const StringDef_stub& );
};

class StringDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public StringDef
{
  public:
    StringDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~StringDef_skel();
    StringDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    StringDef_ptr _this();

};


// Common definitions for interface WstringDef
class WstringDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~WstringDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef WstringDef_ptr _ptr_type;
    typedef WstringDef_var _var_type;
    #endif

    static WstringDef_ptr _narrow( CORBA::Object_ptr obj );
    static WstringDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static WstringDef_ptr _duplicate( WstringDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static WstringDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::ULong bound() = 0;
    virtual void bound( CORBA::ULong value ) = 0;

  protected:
    WstringDef() {};
  private:
    WstringDef( const WstringDef& );
    void operator=( const WstringDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_WstringDef;

// Stub for interface WstringDef
class WstringDef_stub:
  virtual public WstringDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~WstringDef_stub();
    CORBA::ULong bound();
    void bound( CORBA::ULong value );

  private:
    void operator=( const WstringDef_stub& );
};

class WstringDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public WstringDef
{
  public:
    WstringDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~WstringDef_skel();
    WstringDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    WstringDef_ptr _this();

};


// Common definitions for interface FixedDef
class FixedDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~FixedDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef FixedDef_ptr _ptr_type;
    typedef FixedDef_var _var_type;
    #endif

    static FixedDef_ptr _narrow( CORBA::Object_ptr obj );
    static FixedDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static FixedDef_ptr _duplicate( FixedDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static FixedDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::UShort digits() = 0;
    virtual void digits( CORBA::UShort value ) = 0;
    virtual CORBA::Short scale() = 0;
    virtual void scale( CORBA::Short value ) = 0;

  protected:
    FixedDef() {};
  private:
    FixedDef( const FixedDef& );
    void operator=( const FixedDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_FixedDef;

// Stub for interface FixedDef
class FixedDef_stub:
  virtual public FixedDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~FixedDef_stub();
    CORBA::UShort digits();
    void digits( CORBA::UShort value );
    CORBA::Short scale();
    void scale( CORBA::Short value );

  private:
    void operator=( const FixedDef_stub& );
};

class FixedDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public FixedDef
{
  public:
    FixedDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~FixedDef_skel();
    FixedDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    FixedDef_ptr _this();

};


// Common definitions for interface SequenceDef
class SequenceDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~SequenceDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef SequenceDef_ptr _ptr_type;
    typedef SequenceDef_var _var_type;
    #endif

    static SequenceDef_ptr _narrow( CORBA::Object_ptr obj );
    static SequenceDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static SequenceDef_ptr _duplicate( SequenceDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static SequenceDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::ULong bound() = 0;
    virtual void bound( CORBA::ULong value ) = 0;
    virtual CORBA::TypeCode_ptr element_type() = 0;
    virtual IDLType_ptr element_type_def() = 0;
    virtual void element_type_def( IDLType_ptr value ) = 0;

  protected:
    SequenceDef() {};
  private:
    SequenceDef( const SequenceDef& );
    void operator=( const SequenceDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_SequenceDef;

// Stub for interface SequenceDef
class SequenceDef_stub:
  virtual public SequenceDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~SequenceDef_stub();
    CORBA::ULong bound();
    void bound( CORBA::ULong value );
    CORBA::TypeCode_ptr element_type();
    IDLType_ptr element_type_def();
    void element_type_def( IDLType_ptr value );

  private:
    void operator=( const SequenceDef_stub& );
};

class SequenceDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public SequenceDef
{
  public:
    SequenceDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~SequenceDef_skel();
    SequenceDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    SequenceDef_ptr _this();

};


// Common definitions for interface ArrayDef
class ArrayDef : 
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~ArrayDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ArrayDef_ptr _ptr_type;
    typedef ArrayDef_var _var_type;
    #endif

    static ArrayDef_ptr _narrow( CORBA::Object_ptr obj );
    static ArrayDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ArrayDef_ptr _duplicate( ArrayDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ArrayDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::ULong length() = 0;
    virtual void length( CORBA::ULong value ) = 0;
    virtual CORBA::TypeCode_ptr element_type() = 0;
    virtual IDLType_ptr element_type_def() = 0;
    virtual void element_type_def( IDLType_ptr value ) = 0;

  protected:
    ArrayDef() {};
  private:
    ArrayDef( const ArrayDef& );
    void operator=( const ArrayDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ArrayDef;

// Stub for interface ArrayDef
class ArrayDef_stub:
  virtual public ArrayDef,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~ArrayDef_stub();
    CORBA::ULong length();
    void length( CORBA::ULong value );
    CORBA::TypeCode_ptr element_type();
    IDLType_ptr element_type_def();
    void element_type_def( IDLType_ptr value );

  private:
    void operator=( const ArrayDef_stub& );
};

class ArrayDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ArrayDef
{
  public:
    ArrayDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ArrayDef_skel();
    ArrayDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ArrayDef_ptr _this();

};


// Common definitions for interface ExceptionDef
class ExceptionDef : 
  virtual public ::CORBA::Contained,
  virtual public ::CORBA::Container
{
  public:
    virtual ~ExceptionDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ExceptionDef_ptr _ptr_type;
    typedef ExceptionDef_var _var_type;
    #endif

    static ExceptionDef_ptr _narrow( CORBA::Object_ptr obj );
    static ExceptionDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ExceptionDef_ptr _duplicate( ExceptionDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ExceptionDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr type() = 0;
    virtual StructMemberSeq* members() = 0;
    virtual void members( const StructMemberSeq& value ) = 0;

  protected:
    ExceptionDef() {};
  private:
    ExceptionDef( const ExceptionDef& );
    void operator=( const ExceptionDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ExceptionDef;

// Stub for interface ExceptionDef
class ExceptionDef_stub:
  virtual public ExceptionDef,
  virtual public ::CORBA::Contained_stub,
  virtual public ::CORBA::Container_stub
{
  public:
    virtual ~ExceptionDef_stub();
    CORBA::TypeCode_ptr type();
    StructMemberSeq* members();
    void members( const StructMemberSeq& value );

  private:
    void operator=( const ExceptionDef_stub& );
};

class ExceptionDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ExceptionDef
{
  public:
    ExceptionDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ExceptionDef_skel();
    ExceptionDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ExceptionDef_ptr _this();

};

struct ExceptionDescription;
typedef TVarVar<ExceptionDescription> ExceptionDescription_var;
typedef ExceptionDescription_var ExceptionDescription_out;

struct ExceptionDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ExceptionDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ExceptionDescription();
  ~ExceptionDescription();
  ExceptionDescription( const ExceptionDescription& s );
  ExceptionDescription& operator=( const ExceptionDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var type;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ExceptionDescription;

enum AttributeMode {
  ATTR_NORMAL = 0,
  ATTR_READONLY
};

typedef AttributeMode& AttributeMode_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_AttributeMode;

class AttributeDef;
typedef AttributeDef *AttributeDef_ptr;
typedef AttributeDef_ptr AttributeDefRef;
typedef ObjVar<AttributeDef> AttributeDef_var;
typedef AttributeDef_var AttributeDef_out;


// Common definitions for interface AttributeDef
class AttributeDef : 
  virtual public ::CORBA::Contained
{
  public:
    virtual ~AttributeDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef AttributeDef_ptr _ptr_type;
    typedef AttributeDef_var _var_type;
    #endif

    static AttributeDef_ptr _narrow( CORBA::Object_ptr obj );
    static AttributeDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static AttributeDef_ptr _duplicate( AttributeDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static AttributeDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr type() = 0;
    virtual IDLType_ptr type_def() = 0;
    virtual void type_def( IDLType_ptr value ) = 0;
    virtual AttributeMode mode() = 0;
    virtual void mode( AttributeMode value ) = 0;

  protected:
    AttributeDef() {};
  private:
    AttributeDef( const AttributeDef& );
    void operator=( const AttributeDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_AttributeDef;

// Stub for interface AttributeDef
class AttributeDef_stub:
  virtual public AttributeDef,
  virtual public ::CORBA::Contained_stub
{
  public:
    virtual ~AttributeDef_stub();
    CORBA::TypeCode_ptr type();
    IDLType_ptr type_def();
    void type_def( IDLType_ptr value );
    AttributeMode mode();
    void mode( AttributeMode value );

  private:
    void operator=( const AttributeDef_stub& );
};

class AttributeDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public AttributeDef
{
  public:
    AttributeDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~AttributeDef_skel();
    AttributeDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    AttributeDef_ptr _this();

};

struct AttributeDescription;
typedef TVarVar<AttributeDescription> AttributeDescription_var;
typedef AttributeDescription_var AttributeDescription_out;

struct AttributeDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef AttributeDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  AttributeDescription();
  ~AttributeDescription();
  AttributeDescription( const AttributeDescription& s );
  AttributeDescription& operator=( const AttributeDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var type;
  AttributeMode mode;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_AttributeDescription;

enum OperationMode {
  OP_NORMAL = 0,
  OP_ONEWAY
};

typedef OperationMode& OperationMode_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OperationMode;

enum ParameterMode {
  PARAM_IN = 0,
  PARAM_OUT,
  PARAM_INOUT
};

typedef ParameterMode& ParameterMode_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ParameterMode;

struct ParameterDescription;
typedef TVarVar<ParameterDescription> ParameterDescription_var;
typedef ParameterDescription_var ParameterDescription_out;

struct ParameterDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ParameterDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ParameterDescription();
  ~ParameterDescription();
  ParameterDescription( const ParameterDescription& s );
  ParameterDescription& operator=( const ParameterDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  CORBA::TypeCode_var type;
  IDLType_var type_def;
  ParameterMode mode;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ParameterDescription;

typedef SequenceTmpl<ParameterDescription,MICO_TID_DEF> ParDescriptionSeq;
#ifdef _WINDOWS
static ParDescriptionSeq _dummy_ParDescriptionSeq;
#endif
typedef TSeqVar<SequenceTmpl<ParameterDescription,MICO_TID_DEF> > ParDescriptionSeq_var;
typedef ParDescriptionSeq_var ParDescriptionSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ParDescriptionSeq;

typedef char* ContextIdentifier;
typedef CORBA::String_var ContextIdentifier_var;
typedef CORBA::String_out ContextIdentifier_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ContextIdentifier;

typedef StringSequenceTmpl<CORBA::String_var> ContextIdSeq;
#ifdef _WINDOWS
static ContextIdSeq _dummy_ContextIdSeq;
#endif
typedef TSeqVar<StringSequenceTmpl<CORBA::String_var> > ContextIdSeq_var;
typedef ContextIdSeq_var ContextIdSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ContextIdSeq;

typedef IfaceSequenceTmpl<ExceptionDef_var,ExceptionDef_ptr> ExceptionDefSeq;
#ifdef _WINDOWS
static ExceptionDefSeq _dummy_ExceptionDefSeq;
#endif
typedef TSeqVar<IfaceSequenceTmpl<ExceptionDef_var,ExceptionDef_ptr> > ExceptionDefSeq_var;
typedef ExceptionDefSeq_var ExceptionDefSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ExceptionDefSeq;

typedef SequenceTmpl<ExceptionDescription,MICO_TID_DEF> ExcDescriptionSeq;
#ifdef _WINDOWS
static ExcDescriptionSeq _dummy_ExcDescriptionSeq;
#endif
typedef TSeqVar<SequenceTmpl<ExceptionDescription,MICO_TID_DEF> > ExcDescriptionSeq_var;
typedef ExcDescriptionSeq_var ExcDescriptionSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ExcDescriptionSeq;

class OperationDef;
//typedef OperationDef *OperationDef_ptr;
typedef OperationDef_ptr OperationDefRef;
typedef ObjVar<OperationDef> OperationDef_var;
typedef OperationDef_var OperationDef_out;


// Common definitions for interface OperationDef
class OperationDef : 
  virtual public ::CORBA::Contained
{
  public:
    virtual ~OperationDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef OperationDef_ptr _ptr_type;
    typedef OperationDef_var _var_type;
    #endif

    static OperationDef_ptr _narrow( CORBA::Object_ptr obj );
    static OperationDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static OperationDef_ptr _duplicate( OperationDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static OperationDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr result() = 0;
    virtual IDLType_ptr result_def() = 0;
    virtual void result_def( IDLType_ptr value ) = 0;
    virtual ParDescriptionSeq* params() = 0;
    virtual void params( const ParDescriptionSeq& value ) = 0;
    virtual OperationMode mode() = 0;
    virtual void mode( OperationMode value ) = 0;
    virtual ContextIdSeq* contexts() = 0;
    virtual void contexts( const ContextIdSeq& value ) = 0;
    virtual ExceptionDefSeq* exceptions() = 0;
    virtual void exceptions( const ExceptionDefSeq& value ) = 0;

  protected:
    OperationDef() {};
  private:
    OperationDef( const OperationDef& );
    void operator=( const OperationDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OperationDef;

// Stub for interface OperationDef
class OperationDef_stub:
  virtual public OperationDef,
  virtual public ::CORBA::Contained_stub
{
  public:
    virtual ~OperationDef_stub();
    CORBA::TypeCode_ptr result();
    IDLType_ptr result_def();
    void result_def( IDLType_ptr value );
    ParDescriptionSeq* params();
    void params( const ParDescriptionSeq& value );
    OperationMode mode();
    void mode( OperationMode value );
    ContextIdSeq* contexts();
    void contexts( const ContextIdSeq& value );
    ExceptionDefSeq* exceptions();
    void exceptions( const ExceptionDefSeq& value );

  private:
    void operator=( const OperationDef_stub& );
};

class OperationDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public OperationDef
{
  public:
    OperationDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~OperationDef_skel();
    OperationDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    OperationDef_ptr _this();

};

struct OperationDescription;
typedef TVarVar<OperationDescription> OperationDescription_var;
typedef OperationDescription_var OperationDescription_out;

struct OperationDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef OperationDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  OperationDescription();
  ~OperationDescription();
  OperationDescription( const OperationDescription& s );
  OperationDescription& operator=( const OperationDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  CORBA::TypeCode_var result;
  OperationMode mode;
  ContextIdSeq contexts;
  ParDescriptionSeq parameters;
  ExcDescriptionSeq exceptions;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OperationDescription;

typedef StringSequenceTmpl<CORBA::String_var> RepositoryIdSeq;
#ifdef _WINDOWS
static RepositoryIdSeq _dummy_RepositoryIdSeq;
#endif
typedef TSeqVar<StringSequenceTmpl<CORBA::String_var> > RepositoryIdSeq_var;
typedef RepositoryIdSeq_var RepositoryIdSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_RepositoryIdSeq;

typedef SequenceTmpl<OperationDescription,MICO_TID_DEF> OpDescriptionSeq;
#ifdef _WINDOWS
static OpDescriptionSeq _dummy_OpDescriptionSeq;
#endif
typedef TSeqVar<SequenceTmpl<OperationDescription,MICO_TID_DEF> > OpDescriptionSeq_var;
typedef OpDescriptionSeq_var OpDescriptionSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OpDescriptionSeq;

typedef SequenceTmpl<AttributeDescription,MICO_TID_DEF> AttrDescriptionSeq;
#ifdef _WINDOWS
static AttrDescriptionSeq _dummy_AttrDescriptionSeq;
#endif
typedef TSeqVar<SequenceTmpl<AttributeDescription,MICO_TID_DEF> > AttrDescriptionSeq_var;
typedef AttrDescriptionSeq_var AttrDescriptionSeq_out;

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_AttrDescriptionSeq;


// Common definitions for interface InterfaceDef
class InterfaceDef : 
  virtual public ::CORBA::Container,
  virtual public ::CORBA::Contained,
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~InterfaceDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef InterfaceDef_ptr _ptr_type;
    typedef InterfaceDef_var _var_type;
    #endif

    static InterfaceDef_ptr _narrow( CORBA::Object_ptr obj );
    static InterfaceDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static InterfaceDef_ptr _duplicate( InterfaceDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static InterfaceDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    struct FullInterfaceDescription;
    typedef TVarVar<FullInterfaceDescription> FullInterfaceDescription_var;
    typedef FullInterfaceDescription_var FullInterfaceDescription_out;

    struct FullInterfaceDescription {
      #ifdef HAVE_TYPEDEF_OVERLOAD
      typedef FullInterfaceDescription_var _var_type;
      #endif
      #ifdef HAVE_EXPLICIT_STRUCT_OPS
      FullInterfaceDescription();
      ~FullInterfaceDescription();
      FullInterfaceDescription( const FullInterfaceDescription& s );
      FullInterfaceDescription& operator=( const FullInterfaceDescription& s );
      #endif //HAVE_EXPLICIT_STRUCT_OPS

      Identifier_var name;
      RepositoryId_var id;
      RepositoryId_var defined_in;
      VersionSpec_var version;
      OpDescriptionSeq operations;
      AttrDescriptionSeq attributes;
      RepositoryIdSeq base_interfaces;
      CORBA::TypeCode_var type;
      CORBA::Boolean is_abstract;
    };

    static CORBA::TypeCodeConst _tc_FullInterfaceDescription;

    virtual InterfaceDefSeq* base_interfaces() = 0;
    virtual void base_interfaces( const InterfaceDefSeq& value ) = 0;
    virtual CORBA::Boolean is_abstract() = 0;
    virtual void is_abstract( CORBA::Boolean value ) = 0;

    virtual CORBA::Boolean is_a( const char* interface_id ) = 0;
    virtual FullInterfaceDescription* describe_interface() = 0;
    virtual AttributeDef_ptr create_attribute( const char* id, const char* name, const char* version, IDLType_ptr type, AttributeMode mode ) = 0;
    virtual OperationDef_ptr create_operation( const char* id, const char* name, const char* version, IDLType_ptr result, OperationMode mode, const ParDescriptionSeq& params, const ExceptionDefSeq& exceptions, const ContextIdSeq& contexts ) = 0;

  protected:
    InterfaceDef() {};
  private:
    InterfaceDef( const InterfaceDef& );
    void operator=( const InterfaceDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_InterfaceDef;

// Stub for interface InterfaceDef
class InterfaceDef_stub:
  virtual public InterfaceDef,
  virtual public ::CORBA::Container_stub,
  virtual public ::CORBA::Contained_stub,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~InterfaceDef_stub();
    InterfaceDefSeq* base_interfaces();
    void base_interfaces( const InterfaceDefSeq& value );
    CORBA::Boolean is_abstract();
    void is_abstract( CORBA::Boolean value );

    CORBA::Boolean is_a( const char* interface_id );
    FullInterfaceDescription* describe_interface();
    AttributeDef_ptr create_attribute( const char* id, const char* name, const char* version, IDLType_ptr type, AttributeMode mode );
    OperationDef_ptr create_operation( const char* id, const char* name, const char* version, IDLType_ptr result, OperationMode mode, const ParDescriptionSeq& params, const ExceptionDefSeq& exceptions, const ContextIdSeq& contexts );

  private:
    void operator=( const InterfaceDef_stub& );
};

class InterfaceDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public InterfaceDef
{
  public:
    InterfaceDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~InterfaceDef_skel();
    InterfaceDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    InterfaceDef_ptr _this();

};

struct InterfaceDescription;
typedef TVarVar<InterfaceDescription> InterfaceDescription_var;
typedef InterfaceDescription_var InterfaceDescription_out;

struct InterfaceDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef InterfaceDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  InterfaceDescription();
  ~InterfaceDescription();
  InterfaceDescription( const InterfaceDescription& s );
  InterfaceDescription& operator=( const InterfaceDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  RepositoryIdSeq base_interfaces;
  CORBA::Boolean is_abstract;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_InterfaceDescription;

class ValueMemberDef;
typedef ValueMemberDef *ValueMemberDef_ptr;
typedef ValueMemberDef_ptr ValueMemberDefRef;
typedef ObjVar<ValueMemberDef> ValueMemberDef_var;
typedef ValueMemberDef_var ValueMemberDef_out;


// Common definitions for interface ValueMemberDef
class ValueMemberDef : 
  virtual public ::CORBA::Contained
{
  public:
    virtual ~ValueMemberDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ValueMemberDef_ptr _ptr_type;
    typedef ValueMemberDef_var _var_type;
    #endif

    static ValueMemberDef_ptr _narrow( CORBA::Object_ptr obj );
    static ValueMemberDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ValueMemberDef_ptr _duplicate( ValueMemberDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ValueMemberDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual CORBA::TypeCode_ptr type() = 0;
    virtual IDLType_ptr type_def() = 0;
    virtual void type_def( IDLType_ptr value ) = 0;
    virtual Visibility access() = 0;
    virtual void access( Visibility value ) = 0;

  protected:
    ValueMemberDef() {};
  private:
    ValueMemberDef( const ValueMemberDef& );
    void operator=( const ValueMemberDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueMemberDef;

// Stub for interface ValueMemberDef
class ValueMemberDef_stub:
  virtual public ValueMemberDef,
  virtual public ::CORBA::Contained_stub
{
  public:
    virtual ~ValueMemberDef_stub();
    CORBA::TypeCode_ptr type();
    IDLType_ptr type_def();
    void type_def( IDLType_ptr value );
    Visibility access();
    void access( Visibility value );

  private:
    void operator=( const ValueMemberDef_stub& );
};

class ValueMemberDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ValueMemberDef
{
  public:
    ValueMemberDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ValueMemberDef_skel();
    ValueMemberDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ValueMemberDef_ptr _this();

};


// Common definitions for interface ValueDef
class ValueDef : 
  virtual public ::CORBA::Container,
  virtual public ::CORBA::Contained,
  virtual public ::CORBA::IDLType
{
  public:
    virtual ~ValueDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ValueDef_ptr _ptr_type;
    typedef ValueDef_var _var_type;
    #endif

    static ValueDef_ptr _narrow( CORBA::Object_ptr obj );
    static ValueDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ValueDef_ptr _duplicate( ValueDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ValueDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    struct FullValueDescription;
    typedef TVarVar<FullValueDescription> FullValueDescription_var;
    typedef FullValueDescription_var FullValueDescription_out;

    struct FullValueDescription {
      #ifdef HAVE_TYPEDEF_OVERLOAD
      typedef FullValueDescription_var _var_type;
      #endif
      #ifdef HAVE_EXPLICIT_STRUCT_OPS
      FullValueDescription();
      ~FullValueDescription();
      FullValueDescription( const FullValueDescription& s );
      FullValueDescription& operator=( const FullValueDescription& s );
      #endif //HAVE_EXPLICIT_STRUCT_OPS

      Identifier_var name;
      RepositoryId_var id;
      CORBA::Boolean is_abstract;
      CORBA::Boolean is_custom;
      RepositoryId_var defined_in;
      VersionSpec_var version;
      OpDescriptionSeq operations;
      AttrDescriptionSeq attributes;
      ValueMemberSeq members;
      InitializerSeq initializers;
      RepositoryIdSeq supported_interfaces;
      RepositoryIdSeq abstract_base_values;
      CORBA::Boolean is_truncatable;
      RepositoryId_var base_value;
      CORBA::TypeCode_var type;
    };

    static CORBA::TypeCodeConst _tc_FullValueDescription;

    virtual InterfaceDefSeq* supported_interfaces() = 0;
    virtual void supported_interfaces( const InterfaceDefSeq& value ) = 0;
    virtual InitializerSeq* initializers() = 0;
    virtual void initializers( const InitializerSeq& value ) = 0;
    virtual ValueDef_ptr base_value() = 0;
    virtual void base_value( ValueDef_ptr value ) = 0;
    virtual ValueDefSeq* abstract_base_values() = 0;
    virtual void abstract_base_values( const ValueDefSeq& value ) = 0;
    virtual CORBA::Boolean is_abstract() = 0;
    virtual void is_abstract( CORBA::Boolean value ) = 0;
    virtual CORBA::Boolean is_custom() = 0;
    virtual void is_custom( CORBA::Boolean value ) = 0;
    virtual CORBA::Boolean is_truncatable() = 0;
    virtual void is_truncatable( CORBA::Boolean value ) = 0;

    virtual CORBA::Boolean is_a( const char* value_id ) = 0;
    virtual FullValueDescription* describe_value() = 0;
    virtual ValueMemberDef_ptr create_value_member( const char* id, const char* name, const char* version, IDLType_ptr type, Visibility access ) = 0;
    virtual AttributeDef_ptr create_attribute( const char* id, const char* name, const char* version, IDLType_ptr type, AttributeMode mode ) = 0;
    virtual OperationDef_ptr create_operation( const char* id, const char* name, const char* version, IDLType_ptr result, OperationMode mode, const ParDescriptionSeq& params, const ExceptionDefSeq& exceptions, const ContextIdSeq& contexts ) = 0;

  protected:
    ValueDef() {};
  private:
    ValueDef( const ValueDef& );
    void operator=( const ValueDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueDef;

// Stub for interface ValueDef
class ValueDef_stub:
  virtual public ValueDef,
  virtual public ::CORBA::Container_stub,
  virtual public ::CORBA::Contained_stub,
  virtual public ::CORBA::IDLType_stub
{
  public:
    virtual ~ValueDef_stub();
    InterfaceDefSeq* supported_interfaces();
    void supported_interfaces( const InterfaceDefSeq& value );
    InitializerSeq* initializers();
    void initializers( const InitializerSeq& value );
    ValueDef_ptr base_value();
    void base_value( ValueDef_ptr value );
    ValueDefSeq* abstract_base_values();
    void abstract_base_values( const ValueDefSeq& value );
    CORBA::Boolean is_abstract();
    void is_abstract( CORBA::Boolean value );
    CORBA::Boolean is_custom();
    void is_custom( CORBA::Boolean value );
    CORBA::Boolean is_truncatable();
    void is_truncatable( CORBA::Boolean value );

    CORBA::Boolean is_a( const char* value_id );
    FullValueDescription* describe_value();
    ValueMemberDef_ptr create_value_member( const char* id, const char* name, const char* version, IDLType_ptr type, Visibility access );
    AttributeDef_ptr create_attribute( const char* id, const char* name, const char* version, IDLType_ptr type, AttributeMode mode );
    OperationDef_ptr create_operation( const char* id, const char* name, const char* version, IDLType_ptr result, OperationMode mode, const ParDescriptionSeq& params, const ExceptionDefSeq& exceptions, const ContextIdSeq& contexts );

  private:
    void operator=( const ValueDef_stub& );
};

class ValueDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ValueDef
{
  public:
    ValueDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ValueDef_skel();
    ValueDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ValueDef_ptr _this();

};

struct ValueDescription;
typedef TVarVar<ValueDescription> ValueDescription_var;
typedef ValueDescription_var ValueDescription_out;

struct ValueDescription {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ValueDescription_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ValueDescription();
  ~ValueDescription();
  ValueDescription( const ValueDescription& s );
  ValueDescription& operator=( const ValueDescription& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Identifier_var name;
  RepositoryId_var id;
  CORBA::Boolean is_abstract;
  CORBA::Boolean is_custom;
  RepositoryId_var defined_in;
  VersionSpec_var version;
  RepositoryIdSeq supported_interfaces;
  RepositoryIdSeq abstract_base_values;
  CORBA::Boolean is_truncatable;
  RepositoryId_var base_value;
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueDescription;


// Common definitions for interface ValueBoxDef
class ValueBoxDef : 
  virtual public ::CORBA::TypedefDef
{
  public:
    virtual ~ValueBoxDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ValueBoxDef_ptr _ptr_type;
    typedef ValueBoxDef_var _var_type;
    #endif

    static ValueBoxDef_ptr _narrow( CORBA::Object_ptr obj );
    static ValueBoxDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ValueBoxDef_ptr _duplicate( ValueBoxDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ValueBoxDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual IDLType_ptr original_type_def() = 0;
    virtual void original_type_def( IDLType_ptr value ) = 0;

  protected:
    ValueBoxDef() {};
  private:
    ValueBoxDef( const ValueBoxDef& );
    void operator=( const ValueBoxDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ValueBoxDef;

// Stub for interface ValueBoxDef
class ValueBoxDef_stub:
  virtual public ValueBoxDef,
  virtual public ::CORBA::TypedefDef_stub
{
  public:
    virtual ~ValueBoxDef_stub();
    IDLType_ptr original_type_def();
    void original_type_def( IDLType_ptr value );

  private:
    void operator=( const ValueBoxDef_stub& );
};

class ValueBoxDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ValueBoxDef
{
  public:
    ValueBoxDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ValueBoxDef_skel();
    ValueBoxDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ValueBoxDef_ptr _this();

};

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &_a, const ::CORBA::Contained::Description &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::Contained::Description *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Contained::Description &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Contained::Description *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Contained_Description;

void operator<<=( CORBA::Any &a, const CORBA::Contained_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::Contained_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::Contained_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Contained;

void operator<<=( CORBA::Any &_a, const ::CORBA::Initializer &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::Initializer *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Initializer &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Initializer *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Initializer;

void operator<<=( CORBA::Any &_a, const ::CORBA::Container::Description &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::Container::Description *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Container::Description &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::Container::Description *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Container_Description;

void operator<<=( CORBA::Any &a, const CORBA::Container_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::Container_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::Container_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Container;

void operator<<=( CORBA::Any &a, const ::CORBA::PrimitiveKind &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::PrimitiveKind &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_PrimitiveKind;

void operator<<=( CORBA::Any &a, const CORBA::Repository_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::Repository_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::Repository_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_Repository;

void operator<<=( CORBA::Any &a, const CORBA::ModuleDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ModuleDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ModuleDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ModuleDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::ModuleDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ModuleDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ModuleDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ModuleDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ModuleDescription;

void operator<<=( CORBA::Any &a, const CORBA::ConstantDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ConstantDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ConstantDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ConstantDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::ConstantDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ConstantDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ConstantDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ConstantDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ConstantDescription;

void operator<<=( CORBA::Any &a, const CORBA::TypedefDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::TypedefDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::TypedefDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_TypedefDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::TypeDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::TypeDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::TypeDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::TypeDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_TypeDescription;

void operator<<=( CORBA::Any &a, const CORBA::StructDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::StructDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::StructDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_StructDef;

void operator<<=( CORBA::Any &a, const CORBA::UnionDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::UnionDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::UnionDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_UnionDef;

void operator<<=( CORBA::Any &a, const CORBA::EnumDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::EnumDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::EnumDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_EnumDef;

void operator<<=( CORBA::Any &a, const CORBA::AliasDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::AliasDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::AliasDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_AliasDef;

void operator<<=( CORBA::Any &a, const CORBA::NativeDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::NativeDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::NativeDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_NativeDef;

void operator<<=( CORBA::Any &a, const CORBA::PrimitiveDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::PrimitiveDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::PrimitiveDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_PrimitiveDef;

void operator<<=( CORBA::Any &a, const CORBA::StringDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::StringDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::StringDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_StringDef;

void operator<<=( CORBA::Any &a, const CORBA::WstringDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::WstringDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::WstringDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_WstringDef;

void operator<<=( CORBA::Any &a, const CORBA::FixedDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::FixedDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::FixedDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_FixedDef;

void operator<<=( CORBA::Any &a, const CORBA::SequenceDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::SequenceDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::SequenceDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_SequenceDef;

void operator<<=( CORBA::Any &a, const CORBA::ArrayDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ArrayDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ArrayDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ArrayDef;

void operator<<=( CORBA::Any &a, const CORBA::ExceptionDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ExceptionDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ExceptionDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ExceptionDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::ExceptionDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ExceptionDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ExceptionDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ExceptionDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ExceptionDescription;

void operator<<=( CORBA::Any &a, const ::CORBA::AttributeMode &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::AttributeMode &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeMode;

void operator<<=( CORBA::Any &a, const CORBA::AttributeDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::AttributeDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::AttributeDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::AttributeDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::AttributeDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::AttributeDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::AttributeDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_AttributeDescription;

void operator<<=( CORBA::Any &a, const ::CORBA::OperationMode &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::OperationMode &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_OperationMode;

void operator<<=( CORBA::Any &a, const ::CORBA::ParameterMode &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::ParameterMode &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ParameterMode;

void operator<<=( CORBA::Any &_a, const ::CORBA::ParameterDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ParameterDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ParameterDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ParameterDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ParameterDescription;

void operator<<=( CORBA::Any &a, const CORBA::OperationDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::OperationDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::OperationDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_OperationDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::OperationDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::OperationDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::OperationDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::OperationDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_OperationDescription;

void operator<<=( CORBA::Any &_a, const ::CORBA::InterfaceDef::FullInterfaceDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::InterfaceDef::FullInterfaceDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::InterfaceDef::FullInterfaceDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::InterfaceDef::FullInterfaceDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDef_FullInterfaceDescription;

void operator<<=( CORBA::Any &a, const CORBA::InterfaceDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::InterfaceDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::InterfaceDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::InterfaceDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::InterfaceDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::InterfaceDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::InterfaceDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_InterfaceDescription;

void operator<<=( CORBA::Any &a, const CORBA::ValueMemberDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ValueMemberDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ValueMemberDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueMemberDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::ValueDef::FullValueDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ValueDef::FullValueDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueDef::FullValueDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueDef::FullValueDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDef_FullValueDescription;

void operator<<=( CORBA::Any &a, const CORBA::ValueDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ValueDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ValueDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDef;

void operator<<=( CORBA::Any &_a, const ::CORBA::ValueDescription &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ValueDescription *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueDescription &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ValueDescription *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueDescription;

void operator<<=( CORBA::Any &a, const CORBA::ValueBoxDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ValueBoxDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ValueBoxDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ValueBoxDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ValueDef_var,CORBA::ValueDef_ptr> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ValueDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::InterfaceDef_var,CORBA::InterfaceDef_ptr> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_InterfaceDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Contained_var,CORBA::Contained_ptr> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Contained;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Initializer,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Initializer;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Container::Description,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_Container_Description;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ParameterDescription,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ParameterDescription;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ExceptionDef_var,CORBA::ExceptionDef_ptr> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ExceptionDef;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ExceptionDescription,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ExceptionDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::OperationDescription,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_OperationDescription;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::AttributeDescription,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_AttributeDescription;

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
