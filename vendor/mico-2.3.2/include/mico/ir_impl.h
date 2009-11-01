/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#ifndef __IR_IMPL_H__
#define __IR_IMPL_H__


#define MICO_IR_EXC_DUPLICATE_NAME   100
#define MICO_IR_EXC_DUPLICATE_REPOID 101
#define MICO_IR_EXC_DUPLICATE_LABEL  102
#define MICO_IR_EXC_AMBIGUOUS_NAME   103
#define MICO_IR_EXC_OVERLOADING      104
#define MICO_IR_EXC_BAD_RECURSION    105
#define MICO_IR_EXC_BAD_ONEWAY       106
#define MICO_IR_EXC_DUPLICATE_MEMBER 107
#define MICO_IR_EXC_BAD_UNION        108
#define MICO_IR_EXC_BAD_TYPE         109



class IRObject_impl : virtual public CORBA::IRObject_skel
{
protected:
  CORBA::DefinitionKind _dk;

  typedef set<CORBA::IRObject_ptr, less<CORBA::IRObject_ptr> > SetIRObj;
  static SetIRObj _visited;

public:
  IRObject_impl();
  CORBA::DefinitionKind def_kind();
  void destroy();
};


class Contained_impl :
  virtual public IRObject_impl,
  virtual public CORBA::Contained_skel
{
protected:
  CORBA::RepositoryId_var _id;
  CORBA::Identifier_var   _name;
  CORBA::VersionSpec_var  _version;
  CORBA::Container_var    _defined_in;

  CORBA::RepositoryId container_id ();
public:
  Contained_impl( CORBA::Container_ptr defined_in );
  CORBA::RepositoryId id();
  void id( const char* value );
  char* name();
  void name( const char* value );
  char* version();
  void version( const char* value );
  CORBA::Container_ptr defined_in();
  char* absolute_name();
  CORBA::Repository_ptr containing_repository();
  CORBA::Contained::Description* describe();
  void move( CORBA::Container_ptr new_container,
	     const char* new_name,
	     const char* new_version );
};


class Container_impl : 
  virtual public IRObject_impl,
  virtual public CORBA::Container_skel
{
protected:
  CORBA::ContainedSeq _contents;

  void check_for_duplicates( const char* name,
			     const char* id );
  bool is_scoped_name( string& name );
  bool is_relative_scoped_name( string& name );
  string first_of_scoped_name( string& name );
  void strip_first_scope( string& name );
  CORBA::Contained_ptr locate_id( const char* id );
  CORBA::Contained_ptr locate_name( const char* name,
				    CORBA::Boolean include_enclosing_scopes,
				    CORBA::Boolean is_first_level );
  
public:
  Container_impl();

  virtual CORBA::Contained_ptr lookup( const char* search_name );
  virtual CORBA::ContainedSeq* contents( CORBA::DefinitionKind limit_type,
					 CORBA::Boolean exclude_inherited );
  virtual CORBA::ContainedSeq* lookup_name( const char* search_name,
					    CORBA::Long levels_to_search,
					    CORBA::DefinitionKind limit_type,
					    CORBA::Boolean exclude_inherited );
  CORBA::Container::DescriptionSeq* 
                     describe_contents( CORBA::DefinitionKind limit_type,
					CORBA::Boolean exclude_inherited,
					CORBA::Long max_returned_objs );
  CORBA::ModuleDef_ptr create_module( const char* id,
				      const char* name,
				      const char* version );
  CORBA::ConstantDef_ptr create_constant( const char* id,
					  const char* name,
					  const char* version,
					  CORBA::IDLType_ptr type,
					  const CORBA::Any& value );
  CORBA::ExceptionDef_ptr create_exception( const char* id,
					    const char* name,
					    const char* version,
					    const CORBA::StructMemberSeq& members );
  CORBA::StructDef_ptr create_struct( const char* id,
				      const char* name,
				      const char* version,
				      const CORBA::StructMemberSeq& members );
  CORBA::UnionDef_ptr create_union( const char* id,
				    const char* name,
				    const char* version,
				    CORBA::IDLType_ptr discriminator_type,
				    const CORBA::UnionMemberSeq& members );
  CORBA::EnumDef_ptr create_enum( const char* id,
				  const char* name,
				  const char* version,
				  const CORBA::EnumMemberSeq& members );
  CORBA::AliasDef_ptr create_alias( const char* id,
				    const char* name,
				    const char* version,
				    CORBA::IDLType_ptr original_type );
  CORBA::InterfaceDef_ptr create_interface( const char* id,
					    const char* name,
					    const char* version,
					    const CORBA::InterfaceDefSeq& base_interfaces,
					    CORBA::Boolean is_abstract
#ifdef USE_CORBA_2_1
  = FALSE
#endif
      );

  CORBA::ValueDef_ptr create_value( const char* id,
				    const char* name,
				    const char* version,
				    CORBA::Boolean is_custom,
				    CORBA::Boolean is_abstract,
				    CORBA::ValueDef_ptr base_value,
				    CORBA::Boolean is_truncatable,
				    const CORBA::ValueDefSeq& abstract_base_values,
				    const CORBA::InterfaceDefSeq& supported_interfaces,
				    const CORBA::InitializerSeq& initializers );

  CORBA::ValueBoxDef_ptr create_value_box( const char* id,
					   const char* name,
					   const char* version,
					   CORBA::IDLType_ptr original_type_def );

  CORBA::NativeDef_ptr create_native( const char* id,
				      const char* name,
				      const char* version );

  // MICO extension
  CORBA::Contained_ptr find( const char* search_name );
  CORBA::ContainedSeq* find_name( const char* search_name,
				  CORBA::DefinitionKind limit_type );
  void remove_contained( CORBA::Contained_ptr con );
  void add_contained( CORBA::Contained_ptr con );
  void insert_contained( CORBA::Contained_ptr type );
};



class IDLType_impl : 
  virtual public IRObject_impl,
  virtual public CORBA::IDLType_skel
{
protected:
  CORBA::TypeCode_var _type;
  
public:
  IDLType_impl();
  IDLType_impl( CORBA::TypeCode_ptr type );
  CORBA::TypeCode_ptr type();
};


class Repository_impl : 
  virtual public Container_impl,
  virtual public CORBA::Repository_skel
{
protected:
  CORBA::PrimitiveDef_var _pk_void;
  CORBA::PrimitiveDef_var _pk_float;
  CORBA::PrimitiveDef_var _pk_double;
  CORBA::PrimitiveDef_var _pk_long;
  CORBA::PrimitiveDef_var _pk_short;
  CORBA::PrimitiveDef_var _pk_ulong;
  CORBA::PrimitiveDef_var _pk_ushort;
  CORBA::PrimitiveDef_var _pk_char;
  CORBA::PrimitiveDef_var _pk_boolean;
  CORBA::PrimitiveDef_var _pk_octet;
  CORBA::PrimitiveDef_var _pk_string;
  CORBA::PrimitiveDef_var _pk_any;
  CORBA::PrimitiveDef_var _pk_objref;
  CORBA::PrimitiveDef_var _pk_typecode;
  CORBA::PrimitiveDef_var _pk_principal;
  CORBA::PrimitiveDef_var _pk_longlong;
  CORBA::PrimitiveDef_var _pk_ulonglong;
  CORBA::PrimitiveDef_var _pk_longdouble;
  CORBA::PrimitiveDef_var _pk_wchar;
  CORBA::PrimitiveDef_var _pk_wstring;
  CORBA::PrimitiveDef_var _pk_valuebase;

  typedef SequenceTmpl<CORBA::IDLType_var,MICO_TID_DEF> IDLTypeSeq;

  IDLTypeSeq _anonymous_types;
  
  CORBA::IDLType_ptr add_anonymous_type( CORBA::IDLType_ptr type );

public:
  Repository_impl();
  CORBA::Contained_ptr lookup_id( const char* search_id );
  CORBA::PrimitiveDef_ptr get_primitive( CORBA::PrimitiveKind kind );
  CORBA::StringDef_ptr create_string( CORBA::ULong bound );
  CORBA::WstringDef_ptr create_wstring( CORBA::ULong bound );
  CORBA::SequenceDef_ptr create_sequence( CORBA::ULong bound,
  					  CORBA::IDLType_ptr element_type );
  CORBA::ArrayDef_ptr create_array( CORBA::ULong length,
  				    CORBA::IDLType_ptr element_type );
  CORBA::FixedDef_ptr create_fixed( CORBA::UShort digits,
  				    CORBA::Short scale );
};


class ModuleDef_impl : 
  virtual public Container_impl,
  virtual public Contained_impl,
  virtual public CORBA::ModuleDef_skel
{
public:
  ModuleDef_impl( CORBA::Container_ptr defined_in,
		  const char* id,
		  const char* name,
		  const char* version );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,ModuleDef::_narrow_helper)( repoid );
  }
#endif
};


class ConstantDef_impl : 
  virtual public Contained_impl,
  virtual public CORBA::ConstantDef_skel
{
protected:
  CORBA::IDLType_var _type_def;
  CORBA::Any         _value;
public:
  ConstantDef_impl( CORBA::Container_ptr defined_in,
		    const char* id,
		    const char* name,
		    const char* version,
		    CORBA::IDLType_ptr type,
		    const CORBA::Any &value );
  CORBA::TypeCode_ptr type();
  CORBA::IDLType_ptr type_def();
  void type_def( CORBA::IDLType_ptr value );
  CORBA::Any* value();
  void value( const CORBA::Any& value );
};



class TypedefDef_impl : 
  virtual public Contained_impl,
  virtual public IDLType_impl,
  virtual public CORBA::TypedefDef_skel
{
public:
  TypedefDef_impl( CORBA::Container_ptr defined_in );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,TypedefDef::_narrow_helper)( repoid );
  }
#endif
};



class StructDef_impl : 
  virtual public TypedefDef_impl,
  virtual public Container_impl,
  virtual public CORBA::StructDef_skel
{
protected:
  CORBA::StructMemberSeq _members;

  SequenceTmpl<CORBA::TypeCode_var,MICO_TID_DEF> _old_member_types;
  CORBA::Boolean _done;

private:
  void check_for_bad_recursion( const CORBA::UnionMemberSeq& mem );
  void check_for_bad_recursion( const CORBA::StructMemberSeq& mem );
  void check_for_duplicates ( const CORBA::StructMemberSeq &mem );
  
public:
  StructDef_impl( CORBA::Container_ptr defined_in,
		  const char* id,
		  const char* name,
		  const char* version,
		  const CORBA::StructMemberSeq& members );
  CORBA::StructMemberSeq* members();
  void members( const CORBA::StructMemberSeq& value );
  CORBA::TypeCode_ptr type();
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,StructDef::_narrow_helper)( repoid );
  }
#endif
};



class UnionDef_impl : 
  virtual public TypedefDef_impl,
  virtual public Container_impl,
  virtual public CORBA::UnionDef_skel
{
protected:
  CORBA::IDLType_var    _discr;
  CORBA::UnionMemberSeq _members;

  SequenceTmpl<CORBA::TypeCode_var,MICO_TID_DEF> _old_member_types;
  CORBA::TypeCode_var _old_discr_type;
  CORBA::Boolean _done;

private:
  void check_for_bad_recursion( const CORBA::UnionMemberSeq& mem );
  void check_for_bad_recursion( const CORBA::StructMemberSeq& mem );
  void check_for_duplicates ( const CORBA::UnionMemberSeq& mem );
  void check_explicit_default_case( const CORBA::UnionMemberSeq &mem );
  
public:
  UnionDef_impl( CORBA::Container_ptr defined_in,
		 const char* id,
		 const char* name,
		 const char* version,
		 CORBA::IDLType_ptr discr,
		 const CORBA::UnionMemberSeq& members );
  CORBA::TypeCode_ptr discriminator_type();
  CORBA::IDLType_ptr discriminator_type_def();
  void discriminator_type_def( CORBA::IDLType_ptr value );
  CORBA::UnionMemberSeq* members();
  void members( const CORBA::UnionMemberSeq& value );
  CORBA::TypeCode_ptr type();
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,UnionDef::_narrow_helper)( repoid );
  }
#endif
};



class EnumDef_impl : 
  virtual public TypedefDef_impl,
  virtual public CORBA::EnumDef_skel
{
protected:
  CORBA::EnumMemberSeq _members;
public:
  EnumDef_impl( CORBA::Container_ptr defined_in,
		const char* id,
		const char* name,
		const char* version );
  CORBA::EnumMemberSeq* members();
  void members( const CORBA::EnumMemberSeq& value );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,EnumDef::_narrow_helper)( repoid );
  }
#endif
};



class AliasDef_impl : 
  virtual public TypedefDef_impl,
  virtual public CORBA::AliasDef_skel
{
protected:
  CORBA::IDLType_var _original;

  CORBA::TypeCode_var _old_original_type;
  CORBA::Boolean _done;

public:
  AliasDef_impl( CORBA::Container_ptr defined_in,
		 const char* id,
		 const char* name,
		 const char* version );
  CORBA::IDLType_ptr original_type_def();
  void original_type_def( CORBA::IDLType_ptr value );
  CORBA::TypeCode_ptr type();
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,AliasDef::_narrow_helper)( repoid );
  }
#endif
};



class NativeDef_impl : 
  virtual public TypedefDef_impl,
  virtual public CORBA::NativeDef_skel
{
public:
  NativeDef_impl( CORBA::Container_ptr defined_in,
		  const char* id,
		  const char* name,
		  const char* version );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,NativeDef::_narrow_helper)( repoid );
  }
#endif
};



class PrimitiveDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::PrimitiveDef_skel
{
protected:
  CORBA::PrimitiveKind _kind;
public:
  PrimitiveDef_impl( CORBA::PrimitiveKind kind );
  CORBA::PrimitiveKind kind();
};



class StringDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::StringDef_skel
{
protected:
  CORBA::ULong _bound;
public:
  StringDef_impl();
  CORBA::ULong bound();
  void bound( CORBA::ULong value );
};



class WstringDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::WstringDef_skel
{
protected:
  CORBA::ULong _bound;
public:
  WstringDef_impl();
  CORBA::ULong bound();
  void bound( CORBA::ULong value );
};



class FixedDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::FixedDef_skel
{
protected:
  CORBA::UShort _digits;
  CORBA::Short  _scale;
public:
  FixedDef_impl();
  CORBA::UShort digits();
  void digits( CORBA::UShort value );
  CORBA::Short scale();
  void scale( CORBA::Short value );
};



class SequenceDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::SequenceDef_skel
{
protected:
  CORBA::ULong        _bound;
  CORBA::IDLType_var  _element_type_def;
  CORBA::TypeCode_var _rec_type;

  CORBA::TypeCode_var _old_element_type;
  CORBA::Boolean _done;

public:
  SequenceDef_impl();
  CORBA::TypeCode_ptr type();
  CORBA::ULong bound();
  void bound( CORBA::ULong value );
  CORBA::TypeCode_ptr element_type();
  CORBA::IDLType_ptr element_type_def();
  void element_type_def( CORBA::IDLType_ptr value );
};



class ArrayDef_impl : 
  virtual public IDLType_impl,
  virtual public CORBA::ArrayDef_skel
{
protected:
  CORBA::ULong        _length;
  CORBA::IDLType_var  _element_type_def;

  CORBA::TypeCode_var _old_element_type;
  CORBA::Boolean _done;
  
public:
  ArrayDef_impl();
  CORBA::ULong length();
  void length( CORBA::ULong value );
  CORBA::TypeCode_ptr element_type();
  CORBA::IDLType_ptr element_type_def();
  void element_type_def( CORBA::IDLType_ptr value );
  CORBA::TypeCode_ptr type();
};



class ExceptionDef_impl : 
  virtual public Contained_impl,
  virtual public Container_impl,
  virtual public CORBA::ExceptionDef_skel
{
protected:
  CORBA::StructMemberSeq            _members;
  CORBA::TypeCode_var               _type;

  SequenceTmpl<CORBA::TypeCode_var,MICO_TID_DEF> _old_member_types;
  CORBA::Boolean _done;

private:
  void check_for_duplicates (const CORBA::StructMemberSeq &mems);
public:
  ExceptionDef_impl( CORBA::Container_ptr defined_in,
		     const char* id,
		     const char* name,
		     const char* version,
		     const CORBA::StructMemberSeq& members );
  CORBA::TypeCode_ptr type();
  CORBA::StructMemberSeq* members();
  void members( const CORBA::StructMemberSeq& value );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,ExceptionDef::_narrow_helper)( repoid );
  }
#endif
};



class AttributeDef_impl : 
  virtual public Contained_impl,
  virtual public CORBA::AttributeDef_skel
{
protected:
  CORBA::IDLType_var   _type_def;
  CORBA::AttributeMode _mode;
  
public:
  AttributeDef_impl( CORBA::Container_ptr defined_in,
		     const char* id,
		     const char* name,
		     const char* version,
		     CORBA::IDLType_ptr type_def,
		     CORBA::AttributeMode mode );
  CORBA::TypeCode_ptr type();
  CORBA::IDLType_ptr type_def();
  void type_def( CORBA::IDLType_ptr value );
  CORBA::AttributeMode mode();
  void mode( CORBA::AttributeMode value );
};


class OperationDef_impl : 
  virtual public Contained_impl,
  virtual public CORBA::OperationDef_skel
{
protected:
  CORBA::IDLType_var       _result_def;
  CORBA::ParDescriptionSeq _params;
  CORBA::OperationMode     _mode;
  CORBA::ExceptionDefSeq   _exceptions;
  CORBA::ContextIdSeq      _contexts;
  
public:
  OperationDef_impl( CORBA::Container_ptr defined_in,
		     const char* id,
		     const char* name,
		     const char* version,
		     CORBA::IDLType_ptr result,
		     CORBA::OperationMode mode,
		     const CORBA::ParDescriptionSeq& params,
		     const CORBA::ExceptionDefSeq& exs,
		     const CORBA::ContextIdSeq& ctx );
  CORBA::TypeCode_ptr result();
  CORBA::IDLType_ptr result_def();
  void result_def( CORBA::IDLType_ptr value );
  CORBA::ParDescriptionSeq* params();
  void params( const CORBA::ParDescriptionSeq& value );
  CORBA::OperationMode mode();
  void mode( CORBA::OperationMode value );
  CORBA::ContextIdSeq* contexts();
  void contexts( const CORBA::ContextIdSeq& value );
  CORBA::ExceptionDefSeq* exceptions();
  void exceptions( const CORBA::ExceptionDefSeq& value );
};



class InterfaceDef_impl : 
  virtual public Container_impl,
  virtual public Contained_impl,
  virtual public IDLType_impl,
  virtual public CORBA::InterfaceDef_skel
{
protected:
  CORBA::InterfaceDefSeq _base_interfaces;
  CORBA::Boolean _is_abstract;
  
  void check_for_overloaded_ops( const char* name,
				 const char* id );
public:
  InterfaceDef_impl();
  InterfaceDef_impl( CORBA::Container_ptr defined_in,
		     const char* id,
		     const char* name,
		     const char* version,
		     const CORBA::InterfaceDefSeq& base_interfaces,
		     CORBA::Boolean is_abstract );
  CORBA::InterfaceDefSeq* base_interfaces();
  void base_interfaces( const CORBA::InterfaceDefSeq& value );
  CORBA::Boolean is_abstract();
  void is_abstract( CORBA::Boolean value );
  CORBA::Boolean is_a( const char* interface_id );
  CORBA::InterfaceDef::FullInterfaceDescription* describe_interface();
  CORBA::AttributeDef_ptr create_attribute( const char* id,
					    const char* name,
					    const char* version,
					    CORBA::IDLType_ptr type,
					    CORBA::AttributeMode mode );
  CORBA::OperationDef_ptr create_operation( const char* id,
					    const char* name,
					    const char* version,
					    CORBA::IDLType_ptr result,
					    CORBA::OperationMode mode,
					    const CORBA::ParDescriptionSeq& params,
					    const CORBA::ExceptionDefSeq& exceptions,
					    const CORBA::ContextIdSeq& contexts );
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,InterfaceDef::_narrow_helper)( repoid );
  }
#endif
};


class ValueMemberDef_impl : 
  virtual public Contained_impl,
  virtual public CORBA::ValueMemberDef_skel
{
protected:
  CORBA::IDLType_var _type_def;
  CORBA::Visibility _access;
public:
  ValueMemberDef_impl ( CORBA::Container_ptr defined_in,
			const char* id,
			const char* name,
			const char* version,
			CORBA::IDLType_ptr type,
			CORBA::Visibility access );
  CORBA::TypeCode_ptr type();
  CORBA::IDLType_ptr type_def();
  void type_def( CORBA::IDLType_ptr _new_value );
  CORBA::Visibility access();
  void access( CORBA::Visibility _new_value );

#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,ValueMemberDef::_narrow_helper)( repoid );
  }
#endif
};


class ValueDef_impl : 
  virtual public Container_impl,
  virtual public Contained_impl,
  virtual public IDLType_impl,
  virtual public CORBA::ValueDef_skel
{
protected:
  CORBA::Boolean _is_custom;
  CORBA::Boolean _is_abstract;
  CORBA::ValueDef_var _base_value;
  CORBA::Boolean _is_truncatable;
  CORBA::ValueDefSeq _abstract_base_values;
  CORBA::InterfaceDefSeq _supported_interfaces;
  CORBA::InitializerSeq _initializers;
  CORBA::TypeCode_var _rec_type;

  CORBA::TypeCode_var _old_base_type;
  SequenceTmpl<CORBA::TypeCode_var,MICO_TID_DEF> _old_member_types;
  CORBA::Boolean _done;

  void check_for_overloaded_ops( const char* name,
				 const char* id );
public:
  ValueDef_impl ( CORBA::Container_ptr defined_in,
		  const char* id,
		  const char* name,
		  const char* version,
		  CORBA::Boolean is_custom,
		  CORBA::Boolean is_abstract,
		  CORBA::ValueDef_ptr base_value,
		  CORBA::Boolean is_truncatable,
		  const CORBA::ValueDefSeq& abstract_base_values,
		  const CORBA::InterfaceDefSeq& supported_interfaces,
		  const CORBA::InitializerSeq& initializers );
  CORBA::InterfaceDefSeq* supported_interfaces();
  void supported_interfaces( const CORBA::InterfaceDefSeq& _new_value );
  CORBA::InitializerSeq* initializers();
  void initializers( const CORBA::InitializerSeq& _new_value );
  CORBA::ValueDef_ptr base_value();
  void base_value( CORBA::ValueDef_ptr _new_value );
  CORBA::ValueDefSeq* abstract_base_values();
  void abstract_base_values( const CORBA::ValueDefSeq& _new_value );
  CORBA::Boolean is_abstract();
  void is_abstract( CORBA::Boolean _new_value );
  CORBA::Boolean is_custom();
  void is_custom( CORBA::Boolean _new_value );
  CORBA::Boolean is_truncatable();
  void is_truncatable( CORBA::Boolean _new_value );

  CORBA::Boolean is_a( const char* value_id );

  CORBA::ValueDef::FullValueDescription* describe_value();

  CORBA::ValueMemberDef_ptr create_value_member( const char* id,
						 const char* name,
						 const char* version,
						 CORBA::IDLType_ptr type,
						 CORBA::Visibility access );

  CORBA::AttributeDef_ptr create_attribute( const char* id,
					    const char* name,
					    const char* version,
					    CORBA::IDLType_ptr type,
					    CORBA::AttributeMode mode );

  CORBA::OperationDef_ptr create_operation( const char* id,
					    const char* name,
					    const char* version,
					    CORBA::IDLType_ptr result,
					    CORBA::OperationMode mode,
					    const CORBA::ParDescriptionSeq& params,
					    const CORBA::ExceptionDefSeq& exceptions,
					    const CORBA::ContextIdSeq& contexts );
  CORBA::TypeCode_ptr type();
#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,ValueDef::_narrow_helper)( repoid );
  }
#endif
};


class ValueBoxDef_impl : 
  virtual public TypedefDef_impl,
  virtual public CORBA::ValueBoxDef_skel
{
protected:
  CORBA::IDLType_var _original_type_def;

  CORBA::TypeCode_var _old_original_type;
  CORBA::Boolean _done;

public:
  ValueBoxDef_impl ( CORBA::Container_ptr defined_in,
		     const char* id,
		     const char* name,
		     const char* version,
		     CORBA::IDLType_ptr original_type_def );
  CORBA::IDLType_ptr original_type_def();
  void original_type_def( CORBA::IDLType_ptr _new_value );
  CORBA::TypeCode_ptr type();

#ifdef HAVE_EXPLICIT_METHOD_OVERRIDE
  virtual void *_narrow_helper( const char *repoid )
  {
      return this->MICO_SCOPE(CORBA,ValueBoxDef::_narrow_helper)( repoid );
  }
#endif
};

#endif
