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
//  Implementation of skeletons
//--------------------------------------------------------

CORBA::Contained_skel::Contained_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Contained:1.0", "Contained" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/Contained:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Contained_skel>( this ) );
}

CORBA::Contained_skel::Contained_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Contained:1.0", "Contained" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Contained_skel>( this ) );
}

CORBA::Contained_skel::~Contained_skel()
{
}

bool CORBA::Contained_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 17)) {
    case 0:
      if( strcmp( _req->op_name(), "describe" ) == 0 ) {
        Description* _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained_Description );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = describe();
        __res.value( _marshaller_CORBA_Contained_Description, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( _req->op_name(), "_get_name" ) == 0 ) {
        Identifier _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = name();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_get_version" ) == 0 ) {
        VersionSpec _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = version();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 1:
      if( strcmp( _req->op_name(), "_get_absolute_name" ) == 0 ) {
        ScopedName _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = absolute_name();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "move" ) == 0 ) {
        Container_var new_container;
        CORBA::StaticAny _new_container( _marshaller_CORBA_Container, &new_container.inout() );
        Identifier_var new_name;
        CORBA::StaticAny _new_name( CORBA::_stc_string, &new_name.inout() );
        VersionSpec_var new_version;
        CORBA::StaticAny _new_version( CORBA::_stc_string, &new_version.inout() );

        _req->add_in_arg( &_new_container );
        _req->add_in_arg( &_new_name );
        _req->add_in_arg( &_new_version );

        if( !_req->read_args() )
          return true;

        move( new_container, new_name, new_version );
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_name" ) == 0 ) {
        Identifier_var _value;
        CORBA::StaticAny __value( CORBA::_stc_string, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        name( _value );
        _req->write_results();
        return true;
      }
      break;
    case 9:
      if( strcmp( _req->op_name(), "_get_defined_in" ) == 0 ) {
        Container_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Container, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = defined_in();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 11:
      if( strcmp( _req->op_name(), "_get_id" ) == 0 ) {
        RepositoryId _res;
        CORBA::StaticAny __res( CORBA::_stc_string, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = id();
        _req->write_results();
        CORBA::string_free( _res );
        return true;
      }
      break;
    case 12:
      if( strcmp( _req->op_name(), "_get_containing_repository" ) == 0 ) {
        Repository_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Repository, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = containing_repository();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_set_version" ) == 0 ) {
        VersionSpec_var _value;
        CORBA::StaticAny __value( CORBA::_stc_string, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        version( _value );
        _req->write_results();
        return true;
      }
      break;
    case 16:
      if( strcmp( _req->op_name(), "_set_id" ) == 0 ) {
        RepositoryId_var _value;
        CORBA::StaticAny __value( CORBA::_stc_string, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        id( _value );
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

CORBA::Contained_ptr CORBA::Contained_skel::_this()
{
  return CORBA::Contained::_duplicate( this );
}


CORBA::Container_skel::Container_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Container:1.0", "Container" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/Container:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Container_skel>( this ) );
}

CORBA::Container_skel::Container_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Container:1.0", "Container" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Container_skel>( this ) );
}

CORBA::Container_skel::~Container_skel()
{
}

bool CORBA::Container_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 31)) {
    case 0:
      if( strcmp( _req->op_name(), "remove_contained" ) == 0 ) {
        Contained_var con;
        CORBA::StaticAny _con( _marshaller_CORBA_Contained, &con.inout() );

        _req->add_in_arg( &_con );

        if( !_req->read_args() )
          return true;

        remove_contained( con );
        _req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "create_constant" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var type;
        CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type.inout() );
        CORBA::Any value;
        CORBA::StaticAny _value( CORBA::_stc_any, &value );

        ConstantDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ConstantDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_type );
        _req->add_in_arg( &_value );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_constant( id, name, version, type, value );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "lookup_name" ) == 0 ) {
        Identifier_var search_name;
        CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name.inout() );
        CORBA::Long levels_to_search;
        CORBA::StaticAny _levels_to_search( CORBA::_stc_long, &levels_to_search );
        DefinitionKind limit_type;
        CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
        CORBA::Boolean exclude_inherited;
        CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );

        ContainedSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );
        _req->add_in_arg( &_search_name );
        _req->add_in_arg( &_levels_to_search );
        _req->add_in_arg( &_limit_type );
        _req->add_in_arg( &_exclude_inherited );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = lookup_name( search_name, levels_to_search, limit_type, exclude_inherited );
        __res.value( _marshaller__seq_CORBA_Contained, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( _req->op_name(), "locate_id" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );

        Contained_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );
        _req->add_in_arg( &_id );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = locate_id( id );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 8:
      if( strcmp( _req->op_name(), "find" ) == 0 ) {
        ScopedName_var search_name;
        CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name.inout() );

        Contained_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );
        _req->add_in_arg( &_search_name );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find( search_name );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "create_alias" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var original_type;
        CORBA::StaticAny _original_type( _marshaller_CORBA_IDLType, &original_type.inout() );

        AliasDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_AliasDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_original_type );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_alias( id, name, version, original_type );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 12:
      if( strcmp( _req->op_name(), "create_struct" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        StructMemberSeq members;
        CORBA::StaticAny _members( _marshaller__seq_CORBA_StructMember, &members );

        StructDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_StructDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_members );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_struct( id, name, version, members );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 17:
      if( strcmp( _req->op_name(), "create_module" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );

        ModuleDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ModuleDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_module( id, name, version );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_exception" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        StructMemberSeq members;
        CORBA::StaticAny _members( _marshaller__seq_CORBA_StructMember, &members );

        ExceptionDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ExceptionDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_members );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_exception( id, name, version, members );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_union" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var discriminator_type;
        CORBA::StaticAny _discriminator_type( _marshaller_CORBA_IDLType, &discriminator_type.inout() );
        UnionMemberSeq members;
        CORBA::StaticAny _members( _marshaller__seq_CORBA_UnionMember, &members );

        UnionDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_UnionDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_discriminator_type );
        _req->add_in_arg( &_members );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_union( id, name, version, discriminator_type, members );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_value" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        CORBA::Boolean is_custom;
        CORBA::StaticAny _is_custom( CORBA::_stc_boolean, &is_custom );
        CORBA::Boolean is_abstract;
        CORBA::StaticAny _is_abstract( CORBA::_stc_boolean, &is_abstract );
        ValueDef_var base_value;
        CORBA::StaticAny _base_value( _marshaller_CORBA_ValueDef, &base_value.inout() );
        CORBA::Boolean is_truncatable;
        CORBA::StaticAny _is_truncatable( CORBA::_stc_boolean, &is_truncatable );
        ValueDefSeq abstract_base_values;
        CORBA::StaticAny _abstract_base_values( _marshaller__seq_CORBA_ValueDef, &abstract_base_values );
        InterfaceDefSeq supported_interfaces;
        CORBA::StaticAny _supported_interfaces( _marshaller__seq_CORBA_InterfaceDef, &supported_interfaces );
        InitializerSeq initializers;
        CORBA::StaticAny _initializers( _marshaller__seq_CORBA_Initializer, &initializers );

        ValueDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ValueDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_is_custom );
        _req->add_in_arg( &_is_abstract );
        _req->add_in_arg( &_base_value );
        _req->add_in_arg( &_is_truncatable );
        _req->add_in_arg( &_abstract_base_values );
        _req->add_in_arg( &_supported_interfaces );
        _req->add_in_arg( &_initializers );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_value( id, name, version, is_custom, is_abstract, base_value, is_truncatable, abstract_base_values, supported_interfaces, initializers );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 18:
      if( strcmp( _req->op_name(), "lookup" ) == 0 ) {
        ScopedName_var search_name;
        CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name.inout() );

        Contained_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );
        _req->add_in_arg( &_search_name );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = lookup( search_name );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_interface" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        InterfaceDefSeq base_interfaces;
        CORBA::StaticAny _base_interfaces( _marshaller__seq_CORBA_InterfaceDef, &base_interfaces );
        CORBA::Boolean is_abstract;
        CORBA::StaticAny _is_abstract( CORBA::_stc_boolean, &is_abstract );

        InterfaceDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_InterfaceDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_base_interfaces );
        _req->add_in_arg( &_is_abstract );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_interface( id, name, version, base_interfaces, is_abstract );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "find_name" ) == 0 ) {
        Identifier_var search_name;
        CORBA::StaticAny _search_name( CORBA::_stc_string, &search_name.inout() );
        DefinitionKind limit_type;
        CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );

        ContainedSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );
        _req->add_in_arg( &_search_name );
        _req->add_in_arg( &_limit_type );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = find_name( search_name, limit_type );
        __res.value( _marshaller__seq_CORBA_Contained, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 20:
      if( strcmp( _req->op_name(), "create_enum" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        EnumMemberSeq members;
        CORBA::StaticAny _members( CORBA::_stcseq_string, &members );

        EnumDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_EnumDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_members );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_enum( id, name, version, members );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 21:
      if( strcmp( _req->op_name(), "create_value_box" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var original_type_def;
        CORBA::StaticAny _original_type_def( _marshaller_CORBA_IDLType, &original_type_def.inout() );

        ValueBoxDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ValueBoxDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_original_type_def );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_value_box( id, name, version, original_type_def );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 23:
      if( strcmp( _req->op_name(), "create_native" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );

        NativeDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_NativeDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_native( id, name, version );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 24:
      if( strcmp( _req->op_name(), "add_contained" ) == 0 ) {
        Contained_var con;
        CORBA::StaticAny _con( _marshaller_CORBA_Contained, &con.inout() );

        _req->add_in_arg( &_con );

        if( !_req->read_args() )
          return true;

        add_contained( con );
        _req->write_results();
        return true;
      }
      break;
    case 26:
      if( strcmp( _req->op_name(), "contents" ) == 0 ) {
        DefinitionKind limit_type;
        CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
        CORBA::Boolean exclude_inherited;
        CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );

        ContainedSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_Contained );
        _req->add_in_arg( &_limit_type );
        _req->add_in_arg( &_exclude_inherited );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = contents( limit_type, exclude_inherited );
        __res.value( _marshaller__seq_CORBA_Contained, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 28:
      if( strcmp( _req->op_name(), "locate_name" ) == 0 ) {
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        CORBA::Boolean include_enclosing_scopes;
        CORBA::StaticAny _include_enclosing_scopes( CORBA::_stc_boolean, &include_enclosing_scopes );
        CORBA::Boolean is_first_level;
        CORBA::StaticAny _is_first_level( CORBA::_stc_boolean, &is_first_level );

        Contained_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_include_enclosing_scopes );
        _req->add_in_arg( &_is_first_level );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = locate_name( name, include_enclosing_scopes, is_first_level );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 30:
      if( strcmp( _req->op_name(), "describe_contents" ) == 0 ) {
        DefinitionKind limit_type;
        CORBA::StaticAny _limit_type( _marshaller_CORBA_DefinitionKind, &limit_type );
        CORBA::Boolean exclude_inherited;
        CORBA::StaticAny _exclude_inherited( CORBA::_stc_boolean, &exclude_inherited );
        CORBA::Long max_returned_objs;
        CORBA::StaticAny _max_returned_objs( CORBA::_stc_long, &max_returned_objs );

        DescriptionSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_Container_Description );
        _req->add_in_arg( &_limit_type );
        _req->add_in_arg( &_exclude_inherited );
        _req->add_in_arg( &_max_returned_objs );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = describe_contents( limit_type, exclude_inherited, max_returned_objs );
        __res.value( _marshaller__seq_CORBA_Container_Description, _res );
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

CORBA::Container_ptr CORBA::Container_skel::_this()
{
  return CORBA::Container::_duplicate( this );
}


CORBA::Repository_skel::Repository_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Repository:1.0", "Repository" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/Repository:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Repository_skel>( this ) );
}

CORBA::Repository_skel::Repository_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/Repository:1.0", "Repository" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<Repository_skel>( this ) );
}

CORBA::Repository_skel::~Repository_skel()
{
}

bool CORBA::Repository_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 11)) {
    case 0:
      if( strcmp( _req->op_name(), "get_primitive" ) == 0 ) {
        PrimitiveKind kind;
        CORBA::StaticAny _kind( _marshaller_CORBA_PrimitiveKind, &kind );

        PrimitiveDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_PrimitiveDef, &_res );
        _req->add_in_arg( &_kind );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = get_primitive( kind );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_string" ) == 0 ) {
        CORBA::ULong bound;
        CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );

        StringDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_StringDef, &_res );
        _req->add_in_arg( &_bound );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_string( bound );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 1:
      if( strcmp( _req->op_name(), "create_wstring" ) == 0 ) {
        CORBA::ULong bound;
        CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );

        WstringDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_WstringDef, &_res );
        _req->add_in_arg( &_bound );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_wstring( bound );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 8:
      if( strcmp( _req->op_name(), "create_array" ) == 0 ) {
        CORBA::ULong length;
        CORBA::StaticAny _length( CORBA::_stc_ulong, &length );
        IDLType_var element_type;
        CORBA::StaticAny _element_type( _marshaller_CORBA_IDLType, &element_type.inout() );

        ArrayDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ArrayDef, &_res );
        _req->add_in_arg( &_length );
        _req->add_in_arg( &_element_type );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_array( length, element_type );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 9:
      if( strcmp( _req->op_name(), "create_sequence" ) == 0 ) {
        CORBA::ULong bound;
        CORBA::StaticAny _bound( CORBA::_stc_ulong, &bound );
        IDLType_var element_type;
        CORBA::StaticAny _element_type( _marshaller_CORBA_IDLType, &element_type.inout() );

        SequenceDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_SequenceDef, &_res );
        _req->add_in_arg( &_bound );
        _req->add_in_arg( &_element_type );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_sequence( bound, element_type );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "create_fixed" ) == 0 ) {
        CORBA::UShort digits;
        CORBA::StaticAny _digits( CORBA::_stc_ushort, &digits );
        CORBA::Short scale;
        CORBA::StaticAny _scale( CORBA::_stc_short, &scale );

        FixedDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_FixedDef, &_res );
        _req->add_in_arg( &_digits );
        _req->add_in_arg( &_scale );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_fixed( digits, scale );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "lookup_id" ) == 0 ) {
        RepositoryId_var search_id;
        CORBA::StaticAny _search_id( CORBA::_stc_string, &search_id.inout() );

        Contained_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_Contained, &_res );
        _req->add_in_arg( &_search_id );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = lookup_id( search_id );
        _req->write_results();
        CORBA::release( _res );
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

CORBA::Repository_ptr CORBA::Repository_skel::_this()
{
  return CORBA::Repository::_duplicate( this );
}


CORBA::ModuleDef_skel::ModuleDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ModuleDef:1.0", "ModuleDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ModuleDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ModuleDef_skel>( this ) );
}

CORBA::ModuleDef_skel::ModuleDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ModuleDef:1.0", "ModuleDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ModuleDef_skel>( this ) );
}

CORBA::ModuleDef_skel::~ModuleDef_skel()
{
}

bool CORBA::ModuleDef_skel::dispatch( CORBA::StaticServerRequest_ptr /*_req*/, CORBA::Environment & /*_env*/ )
{
  return false;
}

CORBA::ModuleDef_ptr CORBA::ModuleDef_skel::_this()
{
  return CORBA::ModuleDef::_duplicate( this );
}


CORBA::ConstantDef_skel::ConstantDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ConstantDef:1.0", "ConstantDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ConstantDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ConstantDef_skel>( this ) );
}

CORBA::ConstantDef_skel::ConstantDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ConstantDef:1.0", "ConstantDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ConstantDef_skel>( this ) );
}

CORBA::ConstantDef_skel::~ConstantDef_skel()
{
}

bool CORBA::ConstantDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 2:
      if( strcmp( _req->op_name(), "_get_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = type_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_value" ) == 0 ) {
        CORBA::Any _value;
        CORBA::StaticAny __value( CORBA::_stc_any, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        value( _value );
        _req->write_results();
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "_set_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        type_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
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
      if( strcmp( _req->op_name(), "_get_value" ) == 0 ) {
        CORBA::Any* _res;
        CORBA::StaticAny __res( CORBA::_stc_any );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = value();
        __res.value( CORBA::_stc_any, _res );
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

CORBA::ConstantDef_ptr CORBA::ConstantDef_skel::_this()
{
  return CORBA::ConstantDef::_duplicate( this );
}


CORBA::TypedefDef_skel::TypedefDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/TypedefDef:1.0", "TypedefDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/TypedefDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<TypedefDef_skel>( this ) );
}

CORBA::TypedefDef_skel::TypedefDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/TypedefDef:1.0", "TypedefDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<TypedefDef_skel>( this ) );
}

CORBA::TypedefDef_skel::~TypedefDef_skel()
{
}

bool CORBA::TypedefDef_skel::dispatch( CORBA::StaticServerRequest_ptr /*_req*/, CORBA::Environment & /*_env*/ )
{
  return false;
}

CORBA::TypedefDef_ptr CORBA::TypedefDef_skel::_this()
{
  return CORBA::TypedefDef::_duplicate( this );
}


CORBA::StructDef_skel::StructDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/StructDef:1.0", "StructDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/StructDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<StructDef_skel>( this ) );
}

CORBA::StructDef_skel::StructDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/StructDef:1.0", "StructDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<StructDef_skel>( this ) );
}

CORBA::StructDef_skel::~StructDef_skel()
{
}

bool CORBA::StructDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_members" ) == 0 ) {
      StructMemberSeq* _res;
      CORBA::StaticAny __res( _marshaller__seq_CORBA_StructMember );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = members();
      __res.value( _marshaller__seq_CORBA_StructMember, _res );
      _req->write_results();
      delete _res;
      return true;
    }
    if( strcmp( _req->op_name(), "_set_members" ) == 0 ) {
      StructMemberSeq _value;
      CORBA::StaticAny __value( _marshaller__seq_CORBA_StructMember, &_value );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      members( _value );
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

CORBA::StructDef_ptr CORBA::StructDef_skel::_this()
{
  return CORBA::StructDef::_duplicate( this );
}


CORBA::UnionDef_skel::UnionDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/UnionDef:1.0", "UnionDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/UnionDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<UnionDef_skel>( this ) );
}

CORBA::UnionDef_skel::UnionDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/UnionDef:1.0", "UnionDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<UnionDef_skel>( this ) );
}

CORBA::UnionDef_skel::~UnionDef_skel()
{
}

bool CORBA::UnionDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 0:
      if( strcmp( _req->op_name(), "_get_discriminator_type" ) == 0 ) {
        CORBA::TypeCode_ptr _res;
        CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = discriminator_type();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_get_members" ) == 0 ) {
        UnionMemberSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_UnionMember );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = members();
        __res.value( _marshaller__seq_CORBA_UnionMember, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( _req->op_name(), "_set_discriminator_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        discriminator_type_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_set_members" ) == 0 ) {
        UnionMemberSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_UnionMember, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        members( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "_get_discriminator_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = discriminator_type_def();
        _req->write_results();
        CORBA::release( _res );
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

CORBA::UnionDef_ptr CORBA::UnionDef_skel::_this()
{
  return CORBA::UnionDef::_duplicate( this );
}


CORBA::EnumDef_skel::EnumDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/EnumDef:1.0", "EnumDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/EnumDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<EnumDef_skel>( this ) );
}

CORBA::EnumDef_skel::EnumDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/EnumDef:1.0", "EnumDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<EnumDef_skel>( this ) );
}

CORBA::EnumDef_skel::~EnumDef_skel()
{
}

bool CORBA::EnumDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_members" ) == 0 ) {
      EnumMemberSeq* _res;
      CORBA::StaticAny __res( CORBA::_stcseq_string );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = members();
      __res.value( CORBA::_stcseq_string, _res );
      _req->write_results();
      delete _res;
      return true;
    }
    if( strcmp( _req->op_name(), "_set_members" ) == 0 ) {
      EnumMemberSeq _value;
      CORBA::StaticAny __value( CORBA::_stcseq_string, &_value );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      members( _value );
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

CORBA::EnumDef_ptr CORBA::EnumDef_skel::_this()
{
  return CORBA::EnumDef::_duplicate( this );
}


CORBA::AliasDef_skel::AliasDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/AliasDef:1.0", "AliasDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/AliasDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<AliasDef_skel>( this ) );
}

CORBA::AliasDef_skel::AliasDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/AliasDef:1.0", "AliasDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<AliasDef_skel>( this ) );
}

CORBA::AliasDef_skel::~AliasDef_skel()
{
}

bool CORBA::AliasDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_original_type_def" ) == 0 ) {
      IDLType_ptr _res;
      CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = original_type_def();
      _req->write_results();
      CORBA::release( _res );
      return true;
    }
    if( strcmp( _req->op_name(), "_set_original_type_def" ) == 0 ) {
      IDLType_var _value;
      CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      original_type_def( _value );
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

CORBA::AliasDef_ptr CORBA::AliasDef_skel::_this()
{
  return CORBA::AliasDef::_duplicate( this );
}


CORBA::NativeDef_skel::NativeDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/NativeDef:1.0", "NativeDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/NativeDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<NativeDef_skel>( this ) );
}

CORBA::NativeDef_skel::NativeDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/NativeDef:1.0", "NativeDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<NativeDef_skel>( this ) );
}

CORBA::NativeDef_skel::~NativeDef_skel()
{
}

bool CORBA::NativeDef_skel::dispatch( CORBA::StaticServerRequest_ptr /*_req*/, CORBA::Environment & /*_env*/ )
{
  return false;
}

CORBA::NativeDef_ptr CORBA::NativeDef_skel::_this()
{
  return CORBA::NativeDef::_duplicate( this );
}


CORBA::PrimitiveDef_skel::PrimitiveDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/PrimitiveDef:1.0", "PrimitiveDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/PrimitiveDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<PrimitiveDef_skel>( this ) );
}

CORBA::PrimitiveDef_skel::PrimitiveDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/PrimitiveDef:1.0", "PrimitiveDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<PrimitiveDef_skel>( this ) );
}

CORBA::PrimitiveDef_skel::~PrimitiveDef_skel()
{
}

bool CORBA::PrimitiveDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_kind" ) == 0 ) {
      PrimitiveKind _res;
      CORBA::StaticAny __res( _marshaller_CORBA_PrimitiveKind, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = kind();
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

CORBA::PrimitiveDef_ptr CORBA::PrimitiveDef_skel::_this()
{
  return CORBA::PrimitiveDef::_duplicate( this );
}


CORBA::StringDef_skel::StringDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/StringDef:1.0", "StringDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/StringDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<StringDef_skel>( this ) );
}

CORBA::StringDef_skel::StringDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/StringDef:1.0", "StringDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<StringDef_skel>( this ) );
}

CORBA::StringDef_skel::~StringDef_skel()
{
}

bool CORBA::StringDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_bound" ) == 0 ) {
      CORBA::ULong _res;
      CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = bound();
      _req->write_results();
      return true;
    }
    if( strcmp( _req->op_name(), "_set_bound" ) == 0 ) {
      CORBA::ULong _value;
      CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      bound( _value );
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

CORBA::StringDef_ptr CORBA::StringDef_skel::_this()
{
  return CORBA::StringDef::_duplicate( this );
}


CORBA::WstringDef_skel::WstringDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/WstringDef:1.0", "WstringDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/WstringDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<WstringDef_skel>( this ) );
}

CORBA::WstringDef_skel::WstringDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/WstringDef:1.0", "WstringDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<WstringDef_skel>( this ) );
}

CORBA::WstringDef_skel::~WstringDef_skel()
{
}

bool CORBA::WstringDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_bound" ) == 0 ) {
      CORBA::ULong _res;
      CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = bound();
      _req->write_results();
      return true;
    }
    if( strcmp( _req->op_name(), "_set_bound" ) == 0 ) {
      CORBA::ULong _value;
      CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      bound( _value );
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

CORBA::WstringDef_ptr CORBA::WstringDef_skel::_this()
{
  return CORBA::WstringDef::_duplicate( this );
}


CORBA::FixedDef_skel::FixedDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/FixedDef:1.0", "FixedDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/FixedDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<FixedDef_skel>( this ) );
}

CORBA::FixedDef_skel::FixedDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/FixedDef:1.0", "FixedDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<FixedDef_skel>( this ) );
}

CORBA::FixedDef_skel::~FixedDef_skel()
{
}

bool CORBA::FixedDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 1:
      if( strcmp( _req->op_name(), "_get_digits" ) == 0 ) {
        CORBA::UShort _res;
        CORBA::StaticAny __res( CORBA::_stc_ushort, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = digits();
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_digits" ) == 0 ) {
        CORBA::UShort _value;
        CORBA::StaticAny __value( CORBA::_stc_ushort, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        digits( _value );
        _req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "_set_scale" ) == 0 ) {
        CORBA::Short _value;
        CORBA::StaticAny __value( CORBA::_stc_short, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        scale( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "_get_scale" ) == 0 ) {
        CORBA::Short _res;
        CORBA::StaticAny __res( CORBA::_stc_short, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = scale();
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

CORBA::FixedDef_ptr CORBA::FixedDef_skel::_this()
{
  return CORBA::FixedDef::_duplicate( this );
}


CORBA::SequenceDef_skel::SequenceDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/SequenceDef:1.0", "SequenceDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/SequenceDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<SequenceDef_skel>( this ) );
}

CORBA::SequenceDef_skel::SequenceDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/SequenceDef:1.0", "SequenceDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<SequenceDef_skel>( this ) );
}

CORBA::SequenceDef_skel::~SequenceDef_skel()
{
}

bool CORBA::SequenceDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 1:
      if( strcmp( _req->op_name(), "_get_element_type" ) == 0 ) {
        CORBA::TypeCode_ptr _res;
        CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = element_type();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_set_bound" ) == 0 ) {
        CORBA::ULong _value;
        CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        bound( _value );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_get_element_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = element_type_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_element_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        element_type_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "_get_bound" ) == 0 ) {
        CORBA::ULong _res;
        CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = bound();
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

CORBA::SequenceDef_ptr CORBA::SequenceDef_skel::_this()
{
  return CORBA::SequenceDef::_duplicate( this );
}


CORBA::ArrayDef_skel::ArrayDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ArrayDef:1.0", "ArrayDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ArrayDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ArrayDef_skel>( this ) );
}

CORBA::ArrayDef_skel::ArrayDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ArrayDef:1.0", "ArrayDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ArrayDef_skel>( this ) );
}

CORBA::ArrayDef_skel::~ArrayDef_skel()
{
}

bool CORBA::ArrayDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 0:
      if( strcmp( _req->op_name(), "_get_length" ) == 0 ) {
        CORBA::ULong _res;
        CORBA::StaticAny __res( CORBA::_stc_ulong, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = length();
        _req->write_results();
        return true;
      }
      break;
    case 1:
      if( strcmp( _req->op_name(), "_get_element_type" ) == 0 ) {
        CORBA::TypeCode_ptr _res;
        CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = element_type();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_get_element_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = element_type_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_set_length" ) == 0 ) {
        CORBA::ULong _value;
        CORBA::StaticAny __value( CORBA::_stc_ulong, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        length( _value );
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_element_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        element_type_def( _value );
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

CORBA::ArrayDef_ptr CORBA::ArrayDef_skel::_this()
{
  return CORBA::ArrayDef::_duplicate( this );
}


CORBA::ExceptionDef_skel::ExceptionDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ExceptionDef:1.0", "ExceptionDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ExceptionDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ExceptionDef_skel>( this ) );
}

CORBA::ExceptionDef_skel::ExceptionDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ExceptionDef:1.0", "ExceptionDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ExceptionDef_skel>( this ) );
}

CORBA::ExceptionDef_skel::~ExceptionDef_skel()
{
}

bool CORBA::ExceptionDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
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
    if( strcmp( _req->op_name(), "_get_members" ) == 0 ) {
      StructMemberSeq* _res;
      CORBA::StaticAny __res( _marshaller__seq_CORBA_StructMember );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = members();
      __res.value( _marshaller__seq_CORBA_StructMember, _res );
      _req->write_results();
      delete _res;
      return true;
    }
    if( strcmp( _req->op_name(), "_set_members" ) == 0 ) {
      StructMemberSeq _value;
      CORBA::StaticAny __value( _marshaller__seq_CORBA_StructMember, &_value );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      members( _value );
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

CORBA::ExceptionDef_ptr CORBA::ExceptionDef_skel::_this()
{
  return CORBA::ExceptionDef::_duplicate( this );
}


CORBA::AttributeDef_skel::AttributeDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/AttributeDef:1.0", "AttributeDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/AttributeDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<AttributeDef_skel>( this ) );
}

CORBA::AttributeDef_skel::AttributeDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/AttributeDef:1.0", "AttributeDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<AttributeDef_skel>( this ) );
}

CORBA::AttributeDef_skel::~AttributeDef_skel()
{
}

bool CORBA::AttributeDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 2:
      if( strcmp( _req->op_name(), "_get_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = type_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      if( strcmp( _req->op_name(), "_set_mode" ) == 0 ) {
        AttributeMode _value;
        CORBA::StaticAny __value( _marshaller_CORBA_AttributeMode, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        mode( _value );
        _req->write_results();
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "_get_mode" ) == 0 ) {
        AttributeMode _res;
        CORBA::StaticAny __res( _marshaller_CORBA_AttributeMode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = mode();
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        type_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
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

CORBA::AttributeDef_ptr CORBA::AttributeDef_skel::_this()
{
  return CORBA::AttributeDef::_duplicate( this );
}


CORBA::OperationDef_skel::OperationDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OperationDef:1.0", "OperationDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/OperationDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OperationDef_skel>( this ) );
}

CORBA::OperationDef_skel::OperationDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/OperationDef:1.0", "OperationDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<OperationDef_skel>( this ) );
}

CORBA::OperationDef_skel::~OperationDef_skel()
{
}

bool CORBA::OperationDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 17)) {
    case 0:
      if( strcmp( _req->op_name(), "_get_mode" ) == 0 ) {
        OperationMode _res;
        CORBA::StaticAny __res( _marshaller_CORBA_OperationMode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = mode();
        _req->write_results();
        return true;
      }
      break;
    case 1:
      if( strcmp( _req->op_name(), "_get_result_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = result_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_set_result_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        result_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_params" ) == 0 ) {
        ParDescriptionSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_ParameterDescription, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        params( _value );
        _req->write_results();
        return true;
      }
      break;
    case 7:
      if( strcmp( _req->op_name(), "_set_mode" ) == 0 ) {
        OperationMode _value;
        CORBA::StaticAny __value( _marshaller_CORBA_OperationMode, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        mode( _value );
        _req->write_results();
        return true;
      }
      break;
    case 8:
      if( strcmp( _req->op_name(), "_set_exceptions" ) == 0 ) {
        ExceptionDefSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_ExceptionDef, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        exceptions( _value );
        _req->write_results();
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "_set_contexts" ) == 0 ) {
        ContextIdSeq _value;
        CORBA::StaticAny __value( CORBA::_stcseq_string, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        contexts( _value );
        _req->write_results();
        return true;
      }
      break;
    case 11:
      if( strcmp( _req->op_name(), "_get_contexts" ) == 0 ) {
        ContextIdSeq* _res;
        CORBA::StaticAny __res( CORBA::_stcseq_string );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = contexts();
        __res.value( CORBA::_stcseq_string, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 13:
      if( strcmp( _req->op_name(), "_get_exceptions" ) == 0 ) {
        ExceptionDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ExceptionDef );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = exceptions();
        __res.value( _marshaller__seq_CORBA_ExceptionDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 14:
      if( strcmp( _req->op_name(), "_get_result" ) == 0 ) {
        CORBA::TypeCode_ptr _res;
        CORBA::StaticAny __res( CORBA::_stc_TypeCode, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = result();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 15:
      if( strcmp( _req->op_name(), "_get_params" ) == 0 ) {
        ParDescriptionSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ParameterDescription );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = params();
        __res.value( _marshaller__seq_CORBA_ParameterDescription, _res );
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

CORBA::OperationDef_ptr CORBA::OperationDef_skel::_this()
{
  return CORBA::OperationDef::_duplicate( this );
}


CORBA::InterfaceDef_skel::InterfaceDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/InterfaceDef:1.0", "InterfaceDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/InterfaceDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<InterfaceDef_skel>( this ) );
}

CORBA::InterfaceDef_skel::InterfaceDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/InterfaceDef:1.0", "InterfaceDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<InterfaceDef_skel>( this ) );
}

CORBA::InterfaceDef_skel::~InterfaceDef_skel()
{
}

bool CORBA::InterfaceDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 13)) {
    case 1:
      if( strcmp( _req->op_name(), "is_a" ) == 0 ) {
        RepositoryId_var interface_id;
        CORBA::StaticAny _interface_id( CORBA::_stc_string, &interface_id.inout() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->add_in_arg( &_interface_id );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_a( interface_id );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "create_operation" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var result;
        CORBA::StaticAny _result( _marshaller_CORBA_IDLType, &result.inout() );
        OperationMode mode;
        CORBA::StaticAny _mode( _marshaller_CORBA_OperationMode, &mode );
        ParDescriptionSeq params;
        CORBA::StaticAny _params( _marshaller__seq_CORBA_ParameterDescription, &params );
        ExceptionDefSeq exceptions;
        CORBA::StaticAny _exceptions( _marshaller__seq_CORBA_ExceptionDef, &exceptions );
        ContextIdSeq contexts;
        CORBA::StaticAny _contexts( CORBA::_stcseq_string, &contexts );

        OperationDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_OperationDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_result );
        _req->add_in_arg( &_mode );
        _req->add_in_arg( &_params );
        _req->add_in_arg( &_exceptions );
        _req->add_in_arg( &_contexts );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_operation( id, name, version, result, mode, params, exceptions, contexts );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 3:
      if( strcmp( _req->op_name(), "_set_is_abstract" ) == 0 ) {
        CORBA::Boolean _value;
        CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        is_abstract( _value );
        _req->write_results();
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "describe_interface" ) == 0 ) {
        FullInterfaceDescription* _res;
        CORBA::StaticAny __res( _marshaller_CORBA_InterfaceDef_FullInterfaceDescription );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = describe_interface();
        __res.value( _marshaller_CORBA_InterfaceDef_FullInterfaceDescription, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      if( strcmp( _req->op_name(), "_set_base_interfaces" ) == 0 ) {
        InterfaceDefSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_InterfaceDef, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        base_interfaces( _value );
        _req->write_results();
        return true;
      }
      break;
    case 7:
      if( strcmp( _req->op_name(), "create_attribute" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var type;
        CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type.inout() );
        AttributeMode mode;
        CORBA::StaticAny _mode( _marshaller_CORBA_AttributeMode, &mode );

        AttributeDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_AttributeDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_type );
        _req->add_in_arg( &_mode );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_attribute( id, name, version, type, mode );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "_get_base_interfaces" ) == 0 ) {
        InterfaceDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_InterfaceDef );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = base_interfaces();
        __res.value( _marshaller__seq_CORBA_InterfaceDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 12:
      if( strcmp( _req->op_name(), "_get_is_abstract" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_abstract();
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

CORBA::InterfaceDef_ptr CORBA::InterfaceDef_skel::_this()
{
  return CORBA::InterfaceDef::_duplicate( this );
}


CORBA::ValueMemberDef_skel::ValueMemberDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueMemberDef:1.0", "ValueMemberDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ValueMemberDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueMemberDef_skel>( this ) );
}

CORBA::ValueMemberDef_skel::ValueMemberDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueMemberDef:1.0", "ValueMemberDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueMemberDef_skel>( this ) );
}

CORBA::ValueMemberDef_skel::~ValueMemberDef_skel()
{
}

bool CORBA::ValueMemberDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 7)) {
    case 0:
      if( strcmp( _req->op_name(), "_set_access" ) == 0 ) {
        Visibility _value;
        CORBA::StaticAny __value( CORBA::_stc_short, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        access( _value );
        _req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( _req->op_name(), "_get_type_def" ) == 0 ) {
        IDLType_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = type_def();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "_get_access" ) == 0 ) {
        Visibility _res;
        CORBA::StaticAny __res( CORBA::_stc_short, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = access();
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_type_def" ) == 0 ) {
        IDLType_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        type_def( _value );
        _req->write_results();
        return true;
      }
      break;
    case 6:
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

CORBA::ValueMemberDef_ptr CORBA::ValueMemberDef_skel::_this()
{
  return CORBA::ValueMemberDef::_duplicate( this );
}


CORBA::ValueDef_skel::ValueDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueDef:1.0", "ValueDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ValueDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueDef_skel>( this ) );
}

CORBA::ValueDef_skel::ValueDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueDef:1.0", "ValueDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueDef_skel>( this ) );
}

CORBA::ValueDef_skel::~ValueDef_skel()
{
}

bool CORBA::ValueDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    
#ifndef __MINGW32__
extern CORBA::ULong mico_string_hash (const char *, CORBA::ULong);
#endif

    switch (mico_string_hash (_req->op_name(), 29)) {
    case 0:
      if( strcmp( _req->op_name(), "_set_supported_interfaces" ) == 0 ) {
        InterfaceDefSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_InterfaceDef, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        supported_interfaces( _value );
        _req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( _req->op_name(), "create_value_member" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var type;
        CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type.inout() );
        Visibility access;
        CORBA::StaticAny _access( CORBA::_stc_short, &access );

        ValueMemberDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ValueMemberDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_type );
        _req->add_in_arg( &_access );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_value_member( id, name, version, type, access );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 5:
      if( strcmp( _req->op_name(), "describe_value" ) == 0 ) {
        FullValueDescription* _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ValueDef_FullValueDescription );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = describe_value();
        __res.value( _marshaller_CORBA_ValueDef_FullValueDescription, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 6:
      if( strcmp( _req->op_name(), "_get_supported_interfaces" ) == 0 ) {
        InterfaceDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_InterfaceDef );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = supported_interfaces();
        __res.value( _marshaller__seq_CORBA_InterfaceDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 8:
      if( strcmp( _req->op_name(), "is_a" ) == 0 ) {
        RepositoryId_var value_id;
        CORBA::StaticAny _value_id( CORBA::_stc_string, &value_id.inout() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->add_in_arg( &_value_id );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_a( value_id );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_is_abstract" ) == 0 ) {
        CORBA::Boolean _value;
        CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        is_abstract( _value );
        _req->write_results();
        return true;
      }
      break;
    case 10:
      if( strcmp( _req->op_name(), "_get_is_abstract" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_abstract();
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_get_is_truncatable" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_truncatable();
        _req->write_results();
        return true;
      }
      break;
    case 11:
      if( strcmp( _req->op_name(), "_set_abstract_base_values" ) == 0 ) {
        ValueDefSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_ValueDef, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        abstract_base_values( _value );
        _req->write_results();
        return true;
      }
      break;
    case 13:
      if( strcmp( _req->op_name(), "create_attribute" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var type;
        CORBA::StaticAny _type( _marshaller_CORBA_IDLType, &type.inout() );
        AttributeMode mode;
        CORBA::StaticAny _mode( _marshaller_CORBA_AttributeMode, &mode );

        AttributeDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_AttributeDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_type );
        _req->add_in_arg( &_mode );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_attribute( id, name, version, type, mode );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 14:
      if( strcmp( _req->op_name(), "create_operation" ) == 0 ) {
        RepositoryId_var id;
        CORBA::StaticAny _id( CORBA::_stc_string, &id.inout() );
        Identifier_var name;
        CORBA::StaticAny _name( CORBA::_stc_string, &name.inout() );
        VersionSpec_var version;
        CORBA::StaticAny _version( CORBA::_stc_string, &version.inout() );
        IDLType_var result;
        CORBA::StaticAny _result( _marshaller_CORBA_IDLType, &result.inout() );
        OperationMode mode;
        CORBA::StaticAny _mode( _marshaller_CORBA_OperationMode, &mode );
        ParDescriptionSeq params;
        CORBA::StaticAny _params( _marshaller__seq_CORBA_ParameterDescription, &params );
        ExceptionDefSeq exceptions;
        CORBA::StaticAny _exceptions( _marshaller__seq_CORBA_ExceptionDef, &exceptions );
        ContextIdSeq contexts;
        CORBA::StaticAny _contexts( CORBA::_stcseq_string, &contexts );

        OperationDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_OperationDef, &_res );
        _req->add_in_arg( &_id );
        _req->add_in_arg( &_name );
        _req->add_in_arg( &_version );
        _req->add_in_arg( &_result );
        _req->add_in_arg( &_mode );
        _req->add_in_arg( &_params );
        _req->add_in_arg( &_exceptions );
        _req->add_in_arg( &_contexts );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = create_operation( id, name, version, result, mode, params, exceptions, contexts );
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 15:
      if( strcmp( _req->op_name(), "_set_base_value" ) == 0 ) {
        ValueDef_var _value;
        CORBA::StaticAny __value( _marshaller_CORBA_ValueDef, &_value.inout() );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        base_value( _value );
        _req->write_results();
        return true;
      }
      break;
    case 16:
      if( strcmp( _req->op_name(), "_get_base_value" ) == 0 ) {
        ValueDef_ptr _res;
        CORBA::StaticAny __res( _marshaller_CORBA_ValueDef, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = base_value();
        _req->write_results();
        CORBA::release( _res );
        return true;
      }
      break;
    case 18:
      if( strcmp( _req->op_name(), "_get_is_custom" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = is_custom();
        _req->write_results();
        return true;
      }
      break;
    case 24:
      if( strcmp( _req->op_name(), "_set_initializers" ) == 0 ) {
        InitializerSeq _value;
        CORBA::StaticAny __value( _marshaller__seq_CORBA_Initializer, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        initializers( _value );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_is_custom" ) == 0 ) {
        CORBA::Boolean _value;
        CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        is_custom( _value );
        _req->write_results();
        return true;
      }
      if( strcmp( _req->op_name(), "_set_is_truncatable" ) == 0 ) {
        CORBA::Boolean _value;
        CORBA::StaticAny __value( CORBA::_stc_boolean, &_value );

        _req->add_in_arg( &__value );

        if( !_req->read_args() )
          return true;

        is_truncatable( _value );
        _req->write_results();
        return true;
      }
      break;
    case 25:
      if( strcmp( _req->op_name(), "_get_abstract_base_values" ) == 0 ) {
        ValueDefSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_ValueDef );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = abstract_base_values();
        __res.value( _marshaller__seq_CORBA_ValueDef, _res );
        _req->write_results();
        delete _res;
        return true;
      }
      break;
    case 27:
      if( strcmp( _req->op_name(), "_get_initializers" ) == 0 ) {
        InitializerSeq* _res;
        CORBA::StaticAny __res( _marshaller__seq_CORBA_Initializer );
        _req->set_result( &__res );

        if( !_req->read_args() )
          return true;

        _res = initializers();
        __res.value( _marshaller__seq_CORBA_Initializer, _res );
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

CORBA::ValueDef_ptr CORBA::ValueDef_skel::_this()
{
  return CORBA::ValueDef::_duplicate( this );
}


CORBA::ValueBoxDef_skel::ValueBoxDef_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueBoxDef:1.0", "ValueBoxDef" );
  assert( !CORBA::is_nil( _impl ) );
  _create_ref( _id,
    0,
    _impl,
    "IDL:omg.org/CORBA/ValueBoxDef:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueBoxDef_skel>( this ) );
}

CORBA::ValueBoxDef_skel::ValueBoxDef_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:omg.org/CORBA/ValueBoxDef:1.0", "ValueBoxDef" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper<ValueBoxDef_skel>( this ) );
}

CORBA::ValueBoxDef_skel::~ValueBoxDef_skel()
{
}

bool CORBA::ValueBoxDef_skel::dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( _req->op_name(), "_get_original_type_def" ) == 0 ) {
      IDLType_ptr _res;
      CORBA::StaticAny __res( _marshaller_CORBA_IDLType, &_res );
      _req->set_result( &__res );

      if( !_req->read_args() )
        return true;

      _res = original_type_def();
      _req->write_results();
      CORBA::release( _res );
      return true;
    }
    if( strcmp( _req->op_name(), "_set_original_type_def" ) == 0 ) {
      IDLType_var _value;
      CORBA::StaticAny __value( _marshaller_CORBA_IDLType, &_value.inout() );

      _req->add_in_arg( &__value );

      if( !_req->read_args() )
        return true;

      original_type_def( _value );
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

CORBA::ValueBoxDef_ptr CORBA::ValueBoxDef_skel::_this()
{
  return CORBA::ValueBoxDef::_duplicate( this );
}

