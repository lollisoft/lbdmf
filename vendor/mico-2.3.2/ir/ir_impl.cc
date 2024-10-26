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

#define MICO_CONF_IR

#ifdef __MINGW32__
#include <cstring>
#endif
#include <CORBA-SMALL.h>
#include <mico/throw.h>
#include <mico/ir_impl.h>
#include <mico/template_impl.h>


//-- IRObject -----------------------------------------------------------

IRObject_impl::SetIRObj IRObject_impl::_visited;

IRObject_impl::IRObject_impl()
{
  _dk = CORBA::dk_none;
  // we keep one reference for ourselves (released in destroy())
  (void) CORBA::IRObject::_duplicate (this);
}

CORBA::DefinitionKind IRObject_impl::def_kind()
{
  return _dk;
}

void IRObject_impl::destroy()
{
  if( _dk == CORBA::dk_Repository || _dk == CORBA::dk_Primitive )
    mico_throw (CORBA::NO_PERMISSION());

  CORBA::Contained_var con = CORBA::Contained::_narrow( this );
  if( !CORBA::is_nil( con ) ) {
    // We are a Contained. Tell our Container to remove us
    CORBA::Container_var container = con->defined_in();
    container->remove_contained( con );
  }
  
  CORBA::release( this );
}

//-- Contained ----------------------------------------------------------

Contained_impl::Contained_impl( CORBA::Container_ptr defined_in )
{
  _id = (const char *) "";
  _name = (const char *) "";
  _version = (const char *) "";
  _defined_in = CORBA::Container::_duplicate( defined_in );
}

CORBA::RepositoryId Contained_impl::id()
{
  return CORBA::string_dup( _id );
}

void Contained_impl::id( const char* _value )
{
  CORBA::Repository_var repo = this->containing_repository();
  CORBA::Contained_var con = repo->lookup_id( _value );
  if( !CORBA::is_nil( con ) && !this->_is_equivalent( con ) )
    mico_throw ( CORBA::INTF_REPOS (MICO_IR_EXC_DUPLICATE_REPOID,
                                    CORBA::COMPLETED_NO) );

  _id = _value;
  string id;
  id = _value;
  int i = id.find_last_of( ":" );
  if( i >= 0 ) {
    string version;
    version = id.substr( i + 1, id.length() - i - 1 );
    _version = version.c_str();
  }
}

char* Contained_impl::name()
{
  return CORBA::string_dup( _name );
}

void Contained_impl::name( const char* _value )
{
  _name = _value;
}

char* Contained_impl::version()
{
  return CORBA::string_dup( _version );
}

void Contained_impl::version( const char* _value )
{
  _version = _value;
  string id;
  id = _id;
  int i = id.find_last_of( ":" );
  if( i >= 0 ) {
    id = id.substr( 0, i + 1 );
    id += _value;
    _id = id.c_str();
  }
}

CORBA::Container_ptr Contained_impl::defined_in()
{
  return CORBA::Container::_duplicate( _defined_in );
}

char* Contained_impl::absolute_name()
{
  string s;
  CORBA::String_var name;
  
  CORBA::Container_var def_in = this->defined_in();
  assert( !CORBA::is_nil( def_in ) );
  name = this->name();
  switch( def_in->def_kind() ) {
  case CORBA::dk_Repository:
    s = string( "::" ) + (const char *)name;
    break;
  case CORBA::dk_Value:
  case CORBA::dk_Interface:
  case CORBA::dk_Module:
  case CORBA::dk_Struct:
  case CORBA::dk_Union:
  case CORBA::dk_Exception:
    {
      CORBA::Contained_var con = CORBA::Contained::_narrow( def_in );
      assert( !CORBA::is_nil( con ) );
      s = con->absolute_name();
      s += string( "::" ) + (const char *)name;
      break;
    }
  default:
    assert( 0 );
  }
  return CORBA::string_dup( s.c_str() );
}

CORBA::Repository_ptr Contained_impl::containing_repository()
{
  CORBA::Container_var def_in = this->defined_in();
  assert( !CORBA::is_nil( def_in ) );
  CORBA::Repository_ptr r = CORBA::Repository::_narrow( def_in );
  if( !CORBA::is_nil( r ) )
    return r;
  CORBA::release( r );
  CORBA::Contained_var c = CORBA::Contained::_narrow( def_in );
  assert( !CORBA::is_nil( c ) );
  return c->containing_repository();
}

CORBA::Contained::Description* Contained_impl::describe()
{
  CORBA::Contained::Description *desc = new CORBA::Contained::Description;
  
  desc->kind = _dk;

  CORBA::String_var def_in_id;
  CORBA::Contained_var def_in = CORBA::Contained::_narrow( _defined_in );
  if( !CORBA::is_nil( def_in ) )
    def_in_id = def_in->id();
  else
    // The Repository doesn't have a RepoID, because it is not a
    // Contained. This seems to be a loop-hole in the standard.
    def_in_id = (const char *) "";

  switch( _dk ) {
  case CORBA::dk_Module:
    {
      CORBA::ModuleDescription d;
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Constant:
    {
      CORBA::ConstantDescription d;
      CORBA::ConstantDef_var c = CORBA::ConstantDef::_narrow( this );
      assert( !CORBA::is_nil( c ) );
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      d.type       = c->type();
      CORBA::Any *a = c->value();
      d.value = *a;
      delete a;
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Struct:
  case CORBA::dk_Union:
  case CORBA::dk_Enum:
  case CORBA::dk_Alias:
  case CORBA::dk_ValueBox:
  case CORBA::dk_Native:
    {
      CORBA::TypeDescription d;
      CORBA::TypedefDef_var t = CORBA::TypedefDef::_narrow( this );
      assert( !CORBA::is_nil( t ) );
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      d.type       = t->type();
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Exception:
    {
      CORBA::ExceptionDescription d;
      CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( this );
      assert( !CORBA::is_nil( e ) );
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      d.type       = e->type();
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Attribute:
    {
      CORBA::AttributeDescription d;
      CORBA::AttributeDef_var a = CORBA::AttributeDef::_narrow( this );
      assert( !CORBA::is_nil( a ) );
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      d.type       = a->type();
      d.mode       = a->mode();
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Operation:
    {
      CORBA::OperationDescription d;
      CORBA::OperationDef_var o = CORBA::OperationDef::_narrow( this );
      assert( !CORBA::is_nil( o ) );
      d.name       = _name;
      d.id         = _id;
      d.defined_in = def_in_id;
      d.version    = _version;
      d.result     = o->result();
      d.mode       = o->mode();
      CORBA::ContextIdSeq_var ctx = o->contexts();
      d.contexts   = ctx.in();
      CORBA::ParDescriptionSeq_var params = o->params();
      d.parameters = params.in();
      CORBA::ExceptionDefSeq_var exc = o->exceptions();
      d.exceptions.length( exc->length() );
      for( CORBA::ULong j = 0; j < exc->length(); j++ ) {
	CORBA::Contained::Description_var des = exc[ j ]->describe();
	CORBA::ExceptionDescription ex;
	CORBA::Boolean r = ( des->value >>= ex );
	assert (r);
	d.exceptions[ j ] = ex;
      }
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Interface:
    {
      CORBA::InterfaceDescription d;
      CORBA::InterfaceDef_var i = CORBA::InterfaceDef::_narrow( this );
      assert( !CORBA::is_nil( i ) );
      d.name            = _name;
      d.id              = _id;
      d.defined_in      = def_in_id;
      d.version         = _version;
      CORBA::InterfaceDefSeq_var bases = i->base_interfaces();
      d.base_interfaces.length( bases->length() );
      for( CORBA::ULong j = 0; j < bases->length(); j++ )
	d.base_interfaces[ j ] = bases[ j ]->id();
      desc->value <<= d;
      break;
    }
  case CORBA::dk_Value:
    {
      CORBA::ValueDescription d;
      CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( this );
      assert( !CORBA::is_nil( v ) );
      d.name           = _name;
      d.id             = _id;
      d.defined_in     = def_in_id;
      d.version        = _version;
      d.is_abstract    = v->is_abstract();
      d.is_custom      = v->is_custom();
      d.is_truncatable = v->is_truncatable();
      CORBA::InterfaceDefSeq_var supported = v->supported_interfaces();
      d.supported_interfaces.length( supported->length() );
      for (CORBA::ULong j0 = 0; j0 < supported->length(); j0++)
	d.supported_interfaces[ j0 ] = supported[ j0 ]->id();
      CORBA::ValueDef_var base = v->base_value();
      if (CORBA::is_nil (base))
	d.base_value = (const char *)"";
      else
	d.base_value = base->id();
      CORBA::ValueDefSeq_var bases = v->abstract_base_values();
      d.abstract_base_values.length (bases->length());
      for( CORBA::ULong j1 = 0; j1 < bases->length(); j1++ )
	d.abstract_base_values[j1] = bases[j1]->id();
      desc->value <<= d;
      break;
    }
  default:
    assert( 0 );
  }
  return desc;
}

void Contained_impl::move( CORBA::Container_ptr new_container,
			   const char* new_name,
			   const char* new_version )
{
  // Make sure that we don't get delete during the transaction by
  // creating a reference to ourselfs (i.e. this)
  CORBA::Contained_var __this = CORBA::Contained::_duplicate( this );

  _defined_in->remove_contained( this );
  _name = CORBA::string_dup( new_name );
  _version = CORBA::string_dup( new_version );
  new_container->add_contained( this );
}


//-- Container ----------------------------------------------------------

Container_impl::Container_impl()
{
}

/*
 * Check if we have any duplicate names or ids in this scope.
 */
void Container_impl::check_for_duplicates( const char* name,
					   const char* id )
{
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::Contained_var con = _contents[ i ];

    CORBA::String_var con_name = con->name();
    if( strcmp( con_name, name ) == 0 )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_NAME,
                                     CORBA::COMPLETED_NO ) );
  }
  
  CORBA::Repository_var repo;
  
  if( _dk == CORBA::dk_Repository ) {
    repo = CORBA::Repository::_narrow( this );
  } else {
    CORBA::Contained_var c = CORBA::Contained::_narrow( this );
    assert( !CORBA::is_nil( c ) );
    repo = c->containing_repository();
  }
  
  CORBA::Contained_var con = repo->lookup_id( id );
  if( !CORBA::is_nil( con ) )
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_REPOID,
                                   CORBA::COMPLETED_NO ) );
}

/*
 * Returns true iff name is a scoped name (i.e. it contains
 * "::" as a substring.
 */
bool Container_impl::is_scoped_name( string& name )
{
  return (int)name.find( "::", 0 ) >= 0;
}

bool Container_impl::is_relative_scoped_name( string& name )
{
  return name[ 0 ] != ':';
}

string Container_impl::first_of_scoped_name( string& name )
{
  int i, j;
  
  i = is_relative_scoped_name( name ) ? 0 : 2;
  j = name.find( "::", i ) - i;
  if( j < 0 )
    return name.substr( i );
  else
    return name.substr( i, j );
}

void Container_impl::strip_first_scope( string& name )
{
  int i, j;

  i = is_relative_scoped_name( name ) ? 0 : 2;
  j = name.find( "::", i );
  if( j < 0 )
    name = "";
  else
    name = name.substr( j + 2 );
}

CORBA::Contained_ptr
Container_impl::locate_id( const char* id )
{
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::Contained_var con = _contents[ i ];

    CORBA::String_var con_id = con->id();
    if( strcmp( con_id, id ) == 0 ) {
      return CORBA::Contained::_duplicate( con );
    }

    CORBA::Container_var c = CORBA::Container::_narrow( con );
    if( !CORBA::is_nil( c ) ) {
      CORBA::Contained_var contained = c->locate_id( id );
      if( !CORBA::is_nil( contained ) )
	return CORBA::Contained::_duplicate( contained );
    }
  }
  return CORBA::Contained::_nil();
}

CORBA::Contained_ptr
Container_impl::locate_name( const char* name,
			     CORBA::Boolean include_enclosing_scopes,
			     CORBA::Boolean is_first_level )
{
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::String_var n = _contents[ i ]->name();
    if( strcmp( n, name ) == 0 ) {
      return CORBA::Contained::_duplicate( _contents[ i ] );
    }
  }
  
  // Object not found in this level. Extend search to higher levels
  // If this is an InterfaceDef, then first look through all
  // base interfaces
  CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( this );
  if( !CORBA::is_nil( in ) ) {
    CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
    if( bases->length() > 0 ) {
      // This interface has base interfaces
      CORBA::Contained_var hit = CORBA::Contained::_nil();
      for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
	CORBA::Contained_var contained =
	  bases[ i ]->locate_name( name, include_enclosing_scopes, FALSE );
	if( !CORBA::is_nil( contained ) ) {
	  if( CORBA::is_nil( hit ) ) {
	    // First time we found the name along an inheritance path.
	    // Save it and search other inheritance paths.
	    hit = CORBA::Contained::_duplicate( contained );
	    continue;
	  }
	  if( !hit->_is_equivalent( contained ) ) {
	    // We have found the same name along two inheritance paths denoting
	    // different types. This means we have an ambiguity.
	    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_AMBIGUOUS_NAME,
                                           CORBA::COMPLETED_NO ) );
	  }
	}
      }
      if( !CORBA::is_nil( hit ) )
	return CORBA::Contained::_duplicate( hit );
    }
  }
  
  if( !include_enclosing_scopes )
    return CORBA::Contained::_nil();
  
  // Now search the enclosing container, but not if we are currently
  // searching an inherited interface
  CORBA::Contained_var c = CORBA::Contained::_narrow( this );
  if( CORBA::is_nil( c ) || !is_first_level ) {
    return CORBA::Contained::_nil();
  }
  CORBA::Container_var def_in = c->defined_in();
  if( !CORBA::is_nil( def_in ) ) {
    return def_in->locate_name( name, include_enclosing_scopes, TRUE );
  }
  return CORBA::Contained::_nil();
}

CORBA::Contained_ptr Container_impl::lookup( const char* search_name )
{
  string name = search_name;

  if( !is_relative_scoped_name( name ) ) {
    // We have to start our search from the toplevel repository
    if( _dk != CORBA::dk_Repository ) {
      CORBA::Contained_var con = CORBA::Contained::_narrow( this );
      assert( !CORBA::is_nil( con ) );
      name = name.substr( 2 );
      CORBA::Container_var repo = con->containing_repository();
      return repo->lookup( name.c_str() );
    }
  }

  string first = first_of_scoped_name( name );
  strip_first_scope( name );
    
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::String_var n = _contents[i]->name();
    if( strcmp( n, first.c_str() ) == 0 ) {
      if( name == "" )
	// Found it
	return CORBA::Contained::_duplicate( _contents[i] );

      CORBA::Container_var con = CORBA::Container::_narrow( _contents[i] );
      if( CORBA::is_nil( con ) )
	return CORBA::Contained::_nil();
      return con->lookup( name.c_str() );
    }
  }

  return CORBA::Contained::_nil();
}

CORBA::ContainedSeq*
Container_impl::contents( CORBA::DefinitionKind limit_type,
			  CORBA::Boolean exclude_inherited )
{
  CORBA::ContainedSeq *s = new CORBA::ContainedSeq;

  CORBA::ULong j = 0;
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    if( limit_type == CORBA::dk_all ||
	_contents[ i ]->def_kind() == limit_type ) {
      s->length( j + 1 );
      (*s)[ j++ ] = _contents[ i ];
    }
  }

  if( !exclude_inherited && _dk == CORBA::dk_Interface ) {
    CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( this );
    assert( !CORBA::is_nil( in ) );
    CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
    for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
      CORBA::ContainedSeq_var inherited =
	bases[ i ]->contents( limit_type, exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
  }
  if( !exclude_inherited && _dk == CORBA::dk_Value ) {
    CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( this );
    assert( !CORBA::is_nil( val ) );
    CORBA::ValueDefSeq_var bases = val->abstract_base_values();
    for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
      CORBA::ContainedSeq_var inherited =
	bases[ i ]->contents( limit_type, exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
    CORBA::InterfaceDefSeq_var supported = val->supported_interfaces();
    for (CORBA::ULong i1 = 0; i1 < supported->length(); i1++) {
      CORBA::ContainedSeq_var inherited =
	supported[i1]->contents( limit_type, exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
    CORBA::ValueDef_var base = val->base_value();
    if (!CORBA::is_nil (base)) {
      CORBA::ContainedSeq_var inherited =
	base->contents( limit_type, exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
  }
  
  return s;
}

CORBA::ContainedSeq*
Container_impl::lookup_name( const char* search_name,
			     CORBA::Long levels_to_search,
			     CORBA::DefinitionKind limit_type,
			     CORBA::Boolean exclude_inherited )
{
  CORBA::ContainedSeq *s = new CORBA::ContainedSeq;

  if( levels_to_search == 0 )
    return s;
  
  levels_to_search--;
  
  CORBA::ULong j = 0;
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    if( limit_type == CORBA::dk_all ||
	_contents[ i ]->def_kind() == limit_type ) {
      CORBA::String_var name = _contents[ i ]->name();
      if( strcmp( name, search_name ) == 0 ) {
	s->length( j + 1 );
	(*s)[ j++ ] = _contents[ i ];
      }
    }
    CORBA::Container_var con = CORBA::Container::_narrow( _contents[i] );
    if( !CORBA::is_nil( con ) ) {
      // Descend for the contents of this container
      CORBA::ContainedSeq_var nested = con->lookup_name( search_name,
							 levels_to_search,
							 limit_type,
							 exclude_inherited );
      s->length( s->length() + nested->length() );
      for( CORBA::ULong k = 0; k < nested->length(); k++ )
	(*s)[ j++ ] = nested[ k ];
    }
  }

  if( !exclude_inherited && _dk == CORBA::dk_Interface ) {
    CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( this );
    assert( !CORBA::is_nil( in ) );
    CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
    for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
      CORBA::String_var my = in->absolute_name();
      CORBA::String_var other = bases[i]->absolute_name();
      CORBA::ContainedSeq_var inherited =
	bases[ i ]->lookup_name( search_name,
				 levels_to_search,
				 limit_type,
				 exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
  }
  if( !exclude_inherited && _dk == CORBA::dk_Value ) {
    CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( this );
    assert( !CORBA::is_nil( val ) );
    CORBA::ValueDefSeq_var bases = val->abstract_base_values();
    for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
      CORBA::ContainedSeq_var inherited =
	bases[ i ]->lookup_name( search_name,
				 levels_to_search,
				 limit_type,
				 exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
    CORBA::InterfaceDefSeq_var supported = val->supported_interfaces();
    for( CORBA::ULong i1 = 0; i1 < supported->length(); i1++) {
      CORBA::ContainedSeq_var inherited =
	supported[ i1 ]->lookup_name( search_name,
				      levels_to_search,
				      limit_type,
				      exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
    CORBA::ValueDef_var base = val->base_value();
    if (!CORBA::is_nil (base)) {
      CORBA::ContainedSeq_var inherited =
	base->lookup_name( search_name,
			   levels_to_search,
			   limit_type,
			   exclude_inherited );
      s->length( s->length() + inherited->length() );
      for( CORBA::ULong k = 0; k < inherited->length(); k++ )
	(*s)[ j++ ] = inherited[ k ];
    }
  }

  return s;
}

CORBA::Container::DescriptionSeq*
Container_impl::describe_contents( CORBA::DefinitionKind limit_type,
				   CORBA::Boolean exclude_inherited,
				   CORBA::Long max_returned_objs )
{
  CORBA::ContainedSeq_var cont =
    this->contents( limit_type, exclude_inherited );
  
  CORBA::Long limit = cont->length();
  if( limit > max_returned_objs && max_returned_objs != -1 )
    limit = max_returned_objs;
  
  CORBA::Container::DescriptionSeq* s = new CORBA::Container::DescriptionSeq;
  s->length( limit );
  
  for( CORBA::ULong i = 0; (CORBA::Long)i < limit; i++ ) {
    CORBA::Container::Description d;
    d.contained_object = cont[ i ];
    CORBA::Contained::Description_var cont_desc = cont[ i ]->describe();
    d.kind = cont_desc->kind;
    d.value = cont_desc->value;
    (*s)[ i ] = d;
  }
  return s;
}

CORBA::ModuleDef_ptr
Container_impl::create_module( const char* id,
			       const char* name,
			       const char* version )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module ) {
    // Can only create a module in the repository or in a module
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }

  check_for_duplicates( name, id );
  
  CORBA::ModuleDef_ptr m =
    new ModuleDef_impl( this, id, name, version );
  insert_contained( m );
  return m;
}

CORBA::ConstantDef_ptr
Container_impl::create_constant( const char* id,
				 const char* name,
				 const char* version,
				 CORBA::IDLType_ptr type,
				 const CORBA::Any& value )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module     &&
      this->def_kind() != CORBA::dk_Value      &&
      this->def_kind() != CORBA::dk_Interface ) {
    // Can only create a constant in the repository, in a module
    // or in an interface
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }

  check_for_duplicates( name, id );
  
  CORBA::ConstantDef_ptr c =
    new ConstantDef_impl( this, id, name, version, type, value );
  insert_contained( c );
  return c;
}

CORBA::StructDef_ptr
Container_impl::create_struct( const char* id,
			       const char* name,
			       const char* version,
			       const CORBA::StructMemberSeq& members )
{
  check_for_duplicates( name, id );
  
  CORBA::StructDef_ptr s =
    new StructDef_impl( this, id, name, version, members );
  insert_contained( s );
  return s;
}

CORBA::ExceptionDef_ptr
Container_impl::create_exception( const char* id,
				  const char* name,
				  const char* version,
				  const CORBA::StructMemberSeq& members )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module     &&
      this->def_kind() != CORBA::dk_Value      &&
      this->def_kind() != CORBA::dk_Interface ) {
    // Can only create an exception in the repository, in a module
    // or in an interface
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }

  check_for_duplicates( name, id );
  
  CORBA::ExceptionDef_ptr e =
    new ExceptionDef_impl( this, id, name, version, members );
  insert_contained( e );
  return e;
}

CORBA::UnionDef_ptr
Container_impl::create_union( const char* id,
			      const char* name,
			      const char* version,
			      CORBA::IDLType_ptr discr,
			      const CORBA::UnionMemberSeq& members )
{
  check_for_duplicates( name, id );
  
  CORBA::UnionDef_ptr u =
    new UnionDef_impl( this, id, name, version, discr, members );
  insert_contained( u );
  return u;
}

CORBA::EnumDef_ptr
Container_impl::create_enum( const char* id,
			     const char* name,
			     const char* version,
			     const CORBA::EnumMemberSeq& members )
{
  check_for_duplicates( name, id );
  
  CORBA::EnumDef_ptr e =
    new EnumDef_impl( this, id, name, version );
  e->members( members );
  insert_contained( e );
  return e;
}

CORBA::AliasDef_ptr
Container_impl::create_alias( const char* id,
			      const char* name,
			      const char* version,
			      CORBA::IDLType_ptr original_type )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module     &&
      this->def_kind() != CORBA::dk_Value     &&
      this->def_kind() != CORBA::dk_Interface ) {
    // Can only create an alias in the repository, in a module
    // or in an interface
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }

  check_for_duplicates( name, id );
  
  CORBA::AliasDef_ptr a =
    new AliasDef_impl( this, id, name, version );
  a->original_type_def( original_type );
  insert_contained( a );
  return a;
}

CORBA::InterfaceDef_ptr
Container_impl::create_interface( const char* id,
				  const char* name,
				  const char* version,
				  const CORBA::InterfaceDefSeq& base_interfaces,
				  CORBA::Boolean is_abstract )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module ) {
    // Can only create an interface in the repository or in a module
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }
  
  CORBA::Contained_var in_probe = this->locate_id( id );
  if( !CORBA::is_nil( in_probe ) ) {
    if( in_probe->def_kind() != CORBA::dk_Interface ) {
      // A different IDL construct exists which is not an
      // interface => duplicate symbol error
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_NAME,
                                     CORBA::COMPLETED_NO ) );
    }
    
    // Interface has already been defined via a forward
    // declaration. Now we only have to move this definition
    // to the end to reflect the correct declaration ordering
    // and set the base interfaces
    int len = _contents.length();
    for( int i = 0; i < len; i++ ) {
      CORBA::String_var con_id = _contents[ i ]->id();
      CORBA::String_var in_probe_id = in_probe->id();
      if( strcmp( con_id, in_probe_id ) == 0 ) {
	if( i + 1 == len )
	  break;
	for( int j = i; j < len - 1; j++ )
	  _contents[ j ] = _contents[ j + 1 ];
	_contents[ len - 1 ] = in_probe;
	break;
      }
    }
    CORBA::InterfaceDef_ptr iface = CORBA::InterfaceDef::_narrow( in_probe );
    iface->base_interfaces( base_interfaces );
    iface->is_abstract( is_abstract );
    return iface;
  }

  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::InterfaceDef_ptr in =
    new InterfaceDef_impl( this, id, name, version, base_interfaces, is_abstract );
  _contents[ i ] = CORBA::InterfaceDef::_duplicate( in );
  return in;
}

CORBA::ValueDef_ptr
Container_impl::create_value( const char* id,
			      const char* name,
			      const char* version,
			      CORBA::Boolean is_custom,
			      CORBA::Boolean is_abstract,
			      CORBA::ValueDef_ptr base_value,
			      CORBA::Boolean is_truncatable,
			      const CORBA::ValueDefSeq& abstract_base_values,
			      const CORBA::InterfaceDefSeq& supported_interfaces,
			      const CORBA::InitializerSeq& initializers )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module ) {
    // Can only create a value in the repository or in a module
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }
  
  CORBA::Contained_var val_probe = this->locate_id( id );
  if( !CORBA::is_nil( val_probe ) ) {
    if( val_probe->def_kind() != CORBA::dk_Value ) {
      // A different IDL construct exists which is not a
      // value => duplicate symbol error
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_NAME,
                                     CORBA::COMPLETED_NO ) );
    }
    
    // Value has already been defined via a forward
    // declaration. Now we only have to move this definition
    // to the end to reflect the correct declaration ordering
    // and set the base interfaces
    int len = _contents.length();
    for( int i = 0; i < len; i++ ) {
      CORBA::String_var con_id = _contents[ i ]->id();
      CORBA::String_var val_probe_id = val_probe->id();
      if( strcmp( con_id, val_probe_id ) == 0 ) {
	if( i + 1 == len )
	  break;
	for( int j = i; j < len - 1; j++ )
	  _contents[ j ] = _contents[ j + 1 ];
	_contents[ len - 1 ] = val_probe;
	break;
      }
    }
    CORBA::ValueDef_ptr val = CORBA::ValueDef::_narrow( val_probe );
    val->is_abstract (is_abstract);
    val->base_value (base_value);
    val->is_truncatable (is_truncatable);
    val->abstract_base_values (abstract_base_values);
    val->supported_interfaces (supported_interfaces);
    val->initializers (initializers);
    return val;
  }

  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::ValueDef_ptr val =
    new ValueDef_impl( this, id, name, version, is_custom,
		       is_abstract,
		       base_value,
		       is_truncatable,
		       abstract_base_values,
		       supported_interfaces,
		       initializers );
  _contents[ i ] = CORBA::ValueDef::_duplicate( val );
  return val;
}

CORBA::ValueBoxDef_ptr
Container_impl::create_value_box( const char* id,
				  const char* name,
				  const char* version,
				  CORBA::IDLType_ptr original_type_def )
{
  if( this->def_kind() != CORBA::dk_Repository &&
      this->def_kind() != CORBA::dk_Module ) {
    // Can only create a value box in the repository or in a module
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_TYPE,
                                   CORBA::COMPLETED_NO ) );
  }

  check_for_duplicates( name, id );
  
  CORBA::ValueBoxDef_ptr val =
    new ValueBoxDef_impl( this, id, name, version, original_type_def );
  insert_contained( val );
  return val;
}

CORBA::NativeDef_ptr
Container_impl::create_native( const char* id,
			       const char* name,
			       const char* version )
{
  check_for_duplicates( name, id );
  
  CORBA::NativeDef_ptr n =
    new NativeDef_impl( this, id, name, version );
  insert_contained( n );
  return n;
}

void
Container_impl::remove_contained( CORBA::Contained_ptr con )
{
  CORBA::String_var con_id = con->id();
  
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::String_var id = _contents[ i ]->id();
    if( strcmp( id, con_id ) == 0 ) {
      if( i < _contents.length() - 1 ) {
	for( CORBA::ULong j = i; j < _contents.length() - 1; j++ ) {
	  _contents[ j ] = _contents[ j + 1 ];
	}
      }
      _contents.length( _contents.length() - 1 );
      break;
    }
  }
}


CORBA::Contained_ptr
Container_impl::find( const char* search_name )
{
  string name = search_name;

  if( is_scoped_name( name ) ) {
    // search_name is a scoped name.
    CORBA::Contained_var con;
    string first = first_of_scoped_name( name );
    
    if( is_relative_scoped_name( name ) )
      con = locate_name( (char *) first.c_str(), TRUE, TRUE );
    else {
      CORBA::Repository_var repo;
      
      switch( this->def_kind() ) {
      case CORBA::dk_Repository:
	repo = CORBA::Repository::_narrow( this );
	break;
      case CORBA::dk_Module:
      case CORBA::dk_Interface:
      case CORBA::dk_Value:
      case CORBA::dk_Struct:
      case CORBA::dk_Union:
      case CORBA::dk_Exception:
	{
	  CORBA::Contained_var c = CORBA::Contained::_narrow( this );
	  assert( !CORBA::is_nil( c ) );
	  repo = c->containing_repository();
	  break;
	}
      default:
	assert( 0 );
      }
      con = repo->locate_name( (char *) first.c_str(), TRUE, TRUE );
    }
    while( 1 ) {
      if( CORBA::is_nil( con ) )
	return CORBA::Contained::_nil();
      strip_first_scope( name );
      if( name == "" )
	return CORBA::Contained::_duplicate( con );
      
      // con should be a container
      first = first_of_scoped_name( name );
      CORBA::Container_var container = CORBA::Container::_narrow( con );
      if( CORBA::is_nil( container ) )
	return CORBA::Contained::_nil();
      con = container->locate_name( (char *) first.c_str(), FALSE, TRUE );
    }
  } else {
    // search_name is a simple name. It must be located in this scope
    // or an enclosing scope.
    return locate_name( (char *) name.c_str(), TRUE, TRUE );
  }
  return CORBA::Contained::_nil();
}

CORBA::ContainedSeq*
Container_impl::find_name( const char* search_name,
			   CORBA::DefinitionKind limit_type )
{
  CORBA::ContainedSeq *s = new CORBA::ContainedSeq;

  CORBA::ULong j = 0;
  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    if( limit_type == CORBA::dk_all ||
	_contents[ i ]->def_kind() == limit_type ) {
      CORBA::String_var name = _contents[ i ]->name();
      if( strcmp( name, search_name ) == 0 ) {
	s->length( j + 1 );
	(*s)[ j++ ] = _contents[ i ];
      }
    }
  }

  return s;
}

void
Container_impl::add_contained( CORBA::Contained_ptr con )
{
  int i = _contents.length();
  _contents.length( i + 1 );
  _contents[ i ] = CORBA::Contained::_duplicate( con );
}

void
Container_impl::insert_contained( CORBA::Contained_ptr type )
{
  /*
   * We don't need to insert structs and unions before anything else any
   * longer. Rather, we preserve the correct order. When adding nested
   * structures, there is at most one incomplete struct/union at any
   * level, so we have no problem tracing them.
   */

  _contents.length( _contents.length() + 1 );
  _contents[_contents.length()-1] = CORBA::Contained::_duplicate (type);
}


//-- IDLType ------------------------------------------------------------

IDLType_impl::IDLType_impl()
{
  _type = CORBA::TypeCode::_nil();
}

IDLType_impl::IDLType_impl( CORBA::TypeCode_ptr type )
{
  _type = CORBA::TypeCode::_duplicate( type );
}

CORBA::TypeCode_ptr IDLType_impl::type()
{
  assert( !CORBA::is_nil( _type ) );
  return CORBA::TypeCode::_duplicate( _type );
}


//-- Repository ---------------------------------------------------------

Repository_impl::Repository_impl()
{
  _dk = CORBA::dk_Repository;

  // Make all possible primitive kinds
  _pk_void       = new PrimitiveDef_impl( CORBA::pk_void );
  _pk_float      = new PrimitiveDef_impl( CORBA::pk_float );
  _pk_double     = new PrimitiveDef_impl( CORBA::pk_double );
  _pk_long       = new PrimitiveDef_impl( CORBA::pk_long );
  _pk_short      = new PrimitiveDef_impl( CORBA::pk_short );
  _pk_ulong      = new PrimitiveDef_impl( CORBA::pk_ulong );
  _pk_ushort     = new PrimitiveDef_impl( CORBA::pk_ushort );
  _pk_char       = new PrimitiveDef_impl( CORBA::pk_char );
  _pk_boolean    = new PrimitiveDef_impl( CORBA::pk_boolean );
  _pk_octet      = new PrimitiveDef_impl( CORBA::pk_octet );
  _pk_string     = new PrimitiveDef_impl( CORBA::pk_string );
  _pk_any        = new PrimitiveDef_impl( CORBA::pk_any );
  _pk_objref     = new PrimitiveDef_impl( CORBA::pk_objref );
  _pk_typecode   = new PrimitiveDef_impl( CORBA::pk_TypeCode );
  _pk_principal  = new PrimitiveDef_impl( CORBA::pk_Principal );
  _pk_longlong   = new PrimitiveDef_impl( CORBA::pk_longlong );
  _pk_ulonglong  = new PrimitiveDef_impl( CORBA::pk_ulonglong );
  _pk_longdouble = new PrimitiveDef_impl( CORBA::pk_longdouble );
  _pk_wchar      = new PrimitiveDef_impl( CORBA::pk_wchar );
  _pk_wstring    = new PrimitiveDef_impl( CORBA::pk_wstring );
  _pk_valuebase  = new PrimitiveDef_impl( CORBA::pk_value_base );
}

CORBA::Contained_ptr
Repository_impl::lookup_id( const char* search_id )
{
  return locate_id( search_id );
}

CORBA::PrimitiveDef_ptr
Repository_impl::get_primitive( CORBA::PrimitiveKind kind )
{
  switch( kind ) {
  case CORBA::pk_void:
    return CORBA::PrimitiveDef::_duplicate( _pk_void );
  case CORBA::pk_float:
    return CORBA::PrimitiveDef::_duplicate( _pk_float );
  case CORBA::pk_double:
    return CORBA::PrimitiveDef::_duplicate( _pk_double );
  case CORBA::pk_long:
    return CORBA::PrimitiveDef::_duplicate( _pk_long );
  case CORBA::pk_short:
    return CORBA::PrimitiveDef::_duplicate( _pk_short );
  case CORBA::pk_ulong:
    return CORBA::PrimitiveDef::_duplicate( _pk_ulong );
  case CORBA::pk_ushort:
    return CORBA::PrimitiveDef::_duplicate( _pk_ushort );
  case CORBA::pk_char:
    return CORBA::PrimitiveDef::_duplicate( _pk_char );
  case CORBA::pk_boolean:
    return CORBA::PrimitiveDef::_duplicate( _pk_boolean );
  case CORBA::pk_octet:
    return CORBA::PrimitiveDef::_duplicate( _pk_octet );
  case CORBA::pk_string:
    return CORBA::PrimitiveDef::_duplicate( _pk_string );
  case CORBA::pk_any:
    return CORBA::PrimitiveDef::_duplicate( _pk_any );
  case CORBA::pk_objref:
    return CORBA::PrimitiveDef::_duplicate( _pk_objref );
  case CORBA::pk_TypeCode:
    return CORBA::PrimitiveDef::_duplicate( _pk_typecode );
  case CORBA::pk_Principal:
    return CORBA::PrimitiveDef::_duplicate( _pk_principal );
  case CORBA::pk_longlong:
    return CORBA::PrimitiveDef::_duplicate( _pk_longlong );
  case CORBA::pk_ulonglong:
    return CORBA::PrimitiveDef::_duplicate( _pk_ulonglong );
  case CORBA::pk_longdouble:
    return CORBA::PrimitiveDef::_duplicate( _pk_longdouble );
  case CORBA::pk_wchar:
    return CORBA::PrimitiveDef::_duplicate( _pk_wchar );
  case CORBA::pk_wstring:
    return CORBA::PrimitiveDef::_duplicate( _pk_wstring );
  case CORBA::pk_value_base:
    return CORBA::PrimitiveDef::_duplicate( _pk_valuebase );
  default:
    assert( 0 );
  }
  return CORBA::PrimitiveDef::_nil();
}

CORBA::IDLType_ptr
Repository_impl::add_anonymous_type( CORBA::IDLType_ptr type )
{
  int i;

  i = _anonymous_types.length();
  CORBA::TypeCode_var type_tc = type->type();

  // We can *not* check for duplicate definitions
  // of recursive sequences: the TypeCode of their element_type_def
  // is incomplete at this time!
  // TypeCode::equal() does now handle the case of incomplete recursive
  // types (and returns FALSE), so we can check for sequences, too.

  for( int j = 0; j < i; j++ ) {
    CORBA::TypeCode_var current_tc = _anonymous_types[ j ]->type();
    if( current_tc->equal( type_tc ) )
      // We already have a definition of this type
      return CORBA::IDLType::_duplicate( _anonymous_types[ j ] );
  }

  _anonymous_types.length( i + 1 );
  _anonymous_types[ i ] = CORBA::IDLType::_duplicate( type );
  return CORBA::IDLType::_duplicate( type );
}

CORBA::StringDef_ptr Repository_impl::create_string( CORBA::ULong bound )
{
  CORBA::StringDef_var s = new StringDef_impl;
  s->bound( bound );
  CORBA::IDLType_var t = add_anonymous_type( s );
  return CORBA::StringDef::_narrow( t );
}

CORBA::WstringDef_ptr Repository_impl::create_wstring( CORBA::ULong bound )
{
  CORBA::WstringDef_var s = new WstringDef_impl;
  s->bound( bound );
  CORBA::IDLType_var t = add_anonymous_type( s );
  return CORBA::WstringDef::_narrow( t );
}

CORBA::SequenceDef_ptr
Repository_impl::create_sequence( CORBA::ULong bound,
				  CORBA::IDLType_ptr element_type )
{
  CORBA::SequenceDef_var s = new SequenceDef_impl;
  s->element_type_def( element_type );
  s->bound( bound );
  CORBA::IDLType_var t = add_anonymous_type( s );
  return CORBA::SequenceDef::_narrow( t );
}

CORBA::ArrayDef_ptr
Repository_impl::create_array( CORBA::ULong length,
			       CORBA::IDLType_ptr element_type )
{
  CORBA::ArrayDef_var a = new ArrayDef_impl;
  a->element_type_def( element_type );
  a->length( length );
  CORBA::IDLType_var t = add_anonymous_type( a );
  return CORBA::ArrayDef::_narrow( t );
}

CORBA::FixedDef_ptr
Repository_impl::create_fixed( CORBA::UShort digits,
			       CORBA::Short scale )
{
  CORBA::FixedDef_var f = new FixedDef_impl;
  f->digits( digits );
  f->scale( scale );
  CORBA::IDLType_var t = add_anonymous_type( f );
  return CORBA::FixedDef::_narrow( t );
}


//-- ModuleDef ----------------------------------------------------------

ModuleDef_impl::ModuleDef_impl( CORBA::Container_ptr defined_in,
				const char* id,
				const char* name,
				const char* version )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Module;
  _id = id;
  _name = name;
  _version = version;
}


//-- ConstantDef --------------------------------------------------------

ConstantDef_impl::ConstantDef_impl( CORBA::Container_ptr defined_in,
				    const char* id,
				    const char* name,
				    const char* version,
				    CORBA::IDLType_ptr type,
				    const CORBA::Any& a )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Constant;
  _id = id;
  _name = name;
  _version = version;
  _type_def = CORBA::IDLType::_duplicate( type );
  _value = a;
  assert( !CORBA::is_nil( _type_def ) );
  CORBA::TypeCode_var tc1 = _type_def->type();
  CORBA::TypeCode_var tc2 = _value.type();
  assert( tc1->equal( tc2 ) );
}

CORBA::TypeCode_ptr ConstantDef_impl::type()
{
  assert( !CORBA::is_nil( _type_def ) );
  return _type_def->type();
}

CORBA::IDLType_ptr ConstantDef_impl::type_def()
{
  return CORBA::IDLType::_duplicate( _type_def );
}

void ConstantDef_impl::type_def( CORBA::IDLType_ptr value )
{
  _type_def = CORBA::IDLType::_duplicate( value );
}


CORBA::Any* ConstantDef_impl::value()
{
  CORBA::Any *a = new CORBA::Any;
  *a = _value;
  return a;
}

void ConstantDef_impl::value( const CORBA::Any& a )
{
  assert( !CORBA::is_nil( _type_def ) );
  CORBA::TypeCode_var tc1 = _type_def->type();
  CORBA::TypeCode_var tc2 = ((CORBA::Any&) a).type();
  if( !tc1->equal( tc2 ) ) {
    mico_throw (CORBA::NO_PERMISSION());
  }
  _value = a;
}


//-- TypedefDef ---------------------------------------------------------

TypedefDef_impl::TypedefDef_impl( CORBA::Container_ptr defined_in)
  : Contained_impl( defined_in )
{
}


//-- StructDef ----------------------------------------------------------

StructDef_impl::StructDef_impl( CORBA::Container_ptr defined_in,
				const char* id,
				const char* name,
				const char* version,
				const CORBA::StructMemberSeq& members )
  : Contained_impl( defined_in ), TypedefDef_impl( defined_in )
{
  check_for_duplicates (members);
  check_for_bad_recursion (members);

  _dk = CORBA::dk_Struct;
  _id = id;
  _name = name;
  _version = version;
  _members = members;
}

CORBA::StructMemberSeq* StructDef_impl::members()
{
  for (CORBA::ULong i = 0; i < _members.length(); ++i)
    _members[i].type = _members[i].type_def->type();
  return new CORBA::StructMemberSeq (_members);
}

void StructDef_impl::members( const CORBA::StructMemberSeq& _value )
{
  check_for_duplicates (_value);
  check_for_bad_recursion (_value);

  _members = _value;
}


CORBA::TypeCode_ptr
StructDef_impl::type()
{
  CORBA::Boolean visited = _visited.count (this);

  if (!visited)
    _visited.insert (this);

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::ULong i;
  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _old_member_types.length() != _members.length();

  for (i = 0; i < _members.length(); ++i) {
    CORBA::TypeCode_var tc = _members[i].type_def->type();
    if (CORBA::is_nil (tc)) {
      if (!visited)
	_visited.erase (this);
      return CORBA::TypeCode::_nil();
    }
    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done) {
      if (!visited)
	_visited.erase (this);
      return CORBA::TypeCode::_duplicate (_type);
    }
    _members[i].type = tc;
    if (modified)
      continue;
    if (_old_member_types[i].in() != _members[i].type.in() ||
	strcmp (_type->member_name(i), _members[i].name))
      modified = TRUE;
  }

  if (modified) {
    // disconnect member typecodes so they get properly embedded into
    // the newly created typecode
    _old_member_types.length (_members.length());
    for (i = 0; i < _members.length(); ++i) {
      _old_member_types[i] = _members[i].type;
      _members[i].type->disconnect (_type);
    }
    _type = CORBA::TypeCode::create_struct_tc (_id, _name, _members);
  }

  _done = TRUE;

  if (!visited)
    _visited.erase (this);

  return CORBA::TypeCode::_duplicate (_type);
}

void
StructDef_impl::check_for_duplicates (const CORBA::StructMemberSeq &mems)
{
  CORBA::ULong i, j;

  // See if we have any duplicate names in the member list
  for( i = 0; i < mems.length(); i++ ) {
    for( j = i + 1; j < mems.length(); j++ ) {
      if( strcmp( mems[ i ].name, mems[ j ].name ) == 0 )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_MEMBER,
                                       CORBA::COMPLETED_NO ) );
    }
  }
}

void
StructDef_impl::check_for_bad_recursion( const CORBA::StructMemberSeq& mem )
{
  // Check for bad form of recursion
  for( CORBA::ULong i = 0; i < mem.length(); i++ ) {
    CORBA::StructDef_var s = CORBA::StructDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( s ) ) {
      if( s->_is_equivalent( this ) )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_RECURSION,
                                       CORBA::COMPLETED_NO ) );
      CORBA::StructMemberSeq_var nested_mem = s->members();
      check_for_bad_recursion( nested_mem.in() );
    }
    CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( u ) ) {
      CORBA::UnionMemberSeq_var nested_mem = u->members();
      check_for_bad_recursion( nested_mem.in() );
    }
  }
}

void
StructDef_impl::check_for_bad_recursion( const CORBA::UnionMemberSeq& mem )
{
  // Check for bad form of recursion
  for( CORBA::ULong i = 0; i < mem.length(); i++ ) {
    CORBA::StructDef_var s = CORBA::StructDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( s ) ) {
      if( s->_is_equivalent( this ) )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_RECURSION,
                                       CORBA::COMPLETED_NO ) );
      CORBA::StructMemberSeq_var nested_mem = s->members();
      check_for_bad_recursion( nested_mem.in() );
    }
    CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( u ) ) {
      CORBA::UnionMemberSeq_var nested_mem = u->members();
      check_for_bad_recursion( nested_mem.in() );
    }
  }
}


//-- UnionDef -----------------------------------------------------------

UnionDef_impl::UnionDef_impl( CORBA::Container_ptr defined_in,
			      const char* id,
			      const char* name,
			      const char* version,
			      CORBA::IDLType_ptr discr,
			      const CORBA::UnionMemberSeq& members )
  : Contained_impl( defined_in ), TypedefDef_impl( defined_in )
{
  check_for_duplicates (members);
  check_for_bad_recursion (members);

  _dk = CORBA::dk_Union;
  _id = id;
  _name = name;
  _version = version;
  _discr = CORBA::IDLType::_duplicate( discr );
  _members = members;
}

CORBA::TypeCode_ptr UnionDef_impl::discriminator_type()
{
  return _discr->type();
}

CORBA::IDLType_ptr UnionDef_impl::discriminator_type_def()
{
  return CORBA::IDLType::_duplicate( _discr );
}

void UnionDef_impl::discriminator_type_def( CORBA::IDLType_ptr value )
{
  _discr = CORBA::IDLType::_duplicate( value );
}

CORBA::UnionMemberSeq* UnionDef_impl::members()
{
  for (CORBA::ULong i = 0; i < _members.length(); ++i)
    _members[i].type = _members[i].type_def->type();
  return new CORBA::UnionMemberSeq (_members);
}

void UnionDef_impl::members( const CORBA::UnionMemberSeq& _value )
{
  check_for_duplicates (_value);
  check_for_bad_recursion (_value);
  check_explicit_default_case (_value);

  _members = _value;
}

CORBA::TypeCode_ptr
UnionDef_impl::type()
{
  if (CORBA::is_nil (_discr))
    return CORBA::TypeCode::_nil();

  CORBA::Boolean visited = _visited.count (this);
  if (!visited)
    _visited.insert (this);

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::TypeCode_var discr_type = _discr->type();
  if (CORBA::is_nil (discr_type)) {
    if (!visited)
      _visited.erase (this);
    return CORBA::TypeCode::_nil();
  }

  CORBA::ULong i;
  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _old_member_types.length() != _members.length() ||
    _old_discr_type.in() != discr_type.in();

  for (i = 0; i < _members.length(); ++i) {
    CORBA::TypeCode_var tc = _members[i].type_def->type();
    if (CORBA::is_nil (tc)) {
      if (!visited)
        _visited.erase (this);
      return CORBA::TypeCode::_nil();
    }
    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done) {
      if (!visited)
        _visited.erase (this);
      return CORBA::TypeCode::_duplicate (_type);
    }
    _members[i].type = tc;
    if (modified)
      continue;
    if (_old_member_types[i].in() != _members[i].type.in() ||
	strcmp (_type->member_name(i), _members[i].name) ||
	!(*_type->member_label(i) == _members[i].label))
      modified = TRUE;
  }

  if (modified) {
    // disconnect member typecodes so they get properly embedded into
    // the newly created typecode
    _old_discr_type = discr_type;
    _old_member_types.length (_members.length());
    for (i = 0; i < _members.length(); ++i) {
      _old_member_types[i] = _members[i].type;
      _members[i].type->disconnect (_type);
    }
    _type = CORBA::TypeCode::create_union_tc(_id, _name, discr_type, _members);
  }

  _done = TRUE;

  if (!visited)
    _visited.erase (this);

  return CORBA::TypeCode::_duplicate (_type);
}

void
UnionDef_impl::check_for_duplicates( const CORBA::UnionMemberSeq &mems )
{
  CORBA::ULong i, j;

  // See if we have any duplicate names or labels in the member list
  for( i = 0; i < mems.length(); i++ ) {
    for( j = i + 1; j < mems.length(); j++ ) {
      if( strcmp( mems[ i ].name, mems[ j ].name ) == 0 ) {
	// Only raise error if member types are different
	if( !mems[ i ].type_def->_is_equivalent( mems[ j ].type_def ) )
	  mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_MEMBER,
                                         CORBA::COMPLETED_NO ) );
      }
      if( mems[ i ].label == mems[ j ].label )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_LABEL,
                                       CORBA::COMPLETED_NO ) );
    }
  }
}

void
UnionDef_impl::check_for_bad_recursion( const CORBA::StructMemberSeq& mem )
{
  // Check for bad form of recursion
  for( CORBA::ULong i = 0; i < mem.length(); i++ ) {
    CORBA::StructDef_var s = CORBA::StructDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( s ) ) {
      CORBA::StructMemberSeq_var nested_mem = s->members();
      check_for_bad_recursion( nested_mem.in() );
    }
    CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( u ) ) {
      if( u->_is_equivalent( this ) )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_RECURSION,
                                       CORBA::COMPLETED_NO ) );
      CORBA::UnionMemberSeq_var nested_mem = u->members();
      check_for_bad_recursion( nested_mem.in() );
    }
  }
}

void
UnionDef_impl::check_for_bad_recursion( const CORBA::UnionMemberSeq& mem )
{
  // Check for bad form of recursion
  for( CORBA::ULong i = 0; i < mem.length(); i++ ) {
    CORBA::StructDef_var s = CORBA::StructDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( s ) ) {
      CORBA::StructMemberSeq_var nested_mem = s->members();
      check_for_bad_recursion( nested_mem.in() );
    }
    CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( mem[ i ].type_def );
    if( !CORBA::is_nil( u ) ) {
      if( u->_is_equivalent( this ) )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_RECURSION,
                                       CORBA::COMPLETED_NO ) );
      CORBA::UnionMemberSeq_var nested_mem = u->members();
      check_for_bad_recursion( nested_mem.in() );
    }
  }
}

void
UnionDef_impl::check_explicit_default_case (const CORBA::UnionMemberSeq &mems)
{
  // If we have an explicit default case, make sure that we have
  // value of the discriminator type for the default value left
  CORBA::ULong i;
  
  for( i = 0; i < mems.length(); i++ ) {
    CORBA::TypeCode_var tc = mems[ i ].label.type();
    if( tc->kind() == CORBA::tk_octet )
      break;
  }
  if( i == mems.length() )
    // There was no explicit default case. So there is nothing to check
    return;

  // Determine the number of possible values for the discriminator type
  CORBA::ULongLong num_discr_vals;
  CORBA::TypeCode_var discr_tc = _discr->type();
  switch( discr_tc->kind() ) {
  case CORBA::tk_boolean:
    num_discr_vals = 2;
    break;
  case CORBA::tk_char:
    num_discr_vals = 256;
    break;
  case CORBA::tk_enum:
    num_discr_vals = discr_tc->member_count();
    break;
  default:
    // For all other discriminator types we just assume a
    // ridiciously high value. Its highly unlikely that
    // there exisits a IDL-union specification with >> 1000 cases.
    num_discr_vals = 0xffffffff;
    break;
  }
  
  if( num_discr_vals == mems.length() - 1 )
    mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_UNION,
                                   CORBA::COMPLETED_NO ) );
}

//-- EnumDef ------------------------------------------------------------

EnumDef_impl::EnumDef_impl( CORBA::Container_ptr defined_in,
			    const char* id,
			    const char* name,
			    const char* version )
  : Contained_impl( defined_in ), TypedefDef_impl( defined_in )
{
  _dk = CORBA::dk_Enum;
  _id = id;
  _name = name;
  _version = version;
}

CORBA::EnumMemberSeq* EnumDef_impl::members()
{
  CORBA::EnumMemberSeq *m = new CORBA::EnumMemberSeq;
  *m = _members;
  return m;
}

void EnumDef_impl::members( const CORBA::EnumMemberSeq& _value )
{
  _members = _value;
  _type = CORBA::TypeCode::create_enum_tc( _id, _name, _members );

  // See if we have any duplicate names in the member list
  for( CORBA::ULong i = 0; i < _members.length(); i++ ) {
    for( CORBA::ULong j = i + 1; j < _members.length(); j++ ) {
      if( strcmp( _members[ i ], _members[ j ] ) == 0 )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_MEMBER,
                                       CORBA::COMPLETED_NO ) );
    }
  }
}


//-- AliasDef -----------------------------------------------------------

AliasDef_impl::AliasDef_impl( CORBA::Container_ptr defined_in,
			      const char* id,
			      const char* name,
			      const char* version )
  : Contained_impl( defined_in ), TypedefDef_impl( defined_in )
{
  _dk = CORBA::dk_Alias;
  _id = id;
  _name = name;
  _version = version;
}

CORBA::IDLType_ptr AliasDef_impl::original_type_def()
{
  return CORBA::IDLType::_duplicate( _original );
}

void AliasDef_impl::original_type_def( CORBA::IDLType_ptr _value )
{
  _original = CORBA::IDLType::_duplicate( _value );
}

CORBA::TypeCode_ptr
AliasDef_impl::type()
{
  if (CORBA::is_nil (_original))
    return CORBA::TypeCode::_nil();

  _done = FALSE;

  // check whether we need to recreate the typecode ...

  CORBA::TypeCode_var original_type = _original->type();
  if (CORBA::is_nil (original_type))
    return CORBA::TypeCode::_nil();

  // if _done then a nested invocation to this->type()
  // has already calculated the typecode ...
  if (_done)
    return CORBA::TypeCode::_duplicate (_type);

  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _old_original_type.in() != original_type.in();

  if (modified) {
    // disconnect content type code so it gets properly embedded into
    // the newly created typecode
    _old_original_type = original_type;
    original_type->disconnect (_type);

    _type = CORBA::TypeCode::create_alias_tc (_id, _name, original_type);
  }

  _done = TRUE;

  return CORBA::TypeCode::_duplicate (_type);
}

//-- NativeDef -----------------------------------------------------------

NativeDef_impl::NativeDef_impl ( CORBA::Container_ptr defined_in,
				 const char* id,
				 const char* name,
				 const char* version )
  : Contained_impl( defined_in ), TypedefDef_impl( defined_in )
{
  _dk = CORBA::dk_Native;
  _id = id;
  _name = name;
  _version = version;
  _type = CORBA::TypeCode::create_native_tc( _id, _name );
}

//-- PrimitiveDef -------------------------------------------------------

PrimitiveDef_impl::PrimitiveDef_impl( CORBA::PrimitiveKind kind )
{
  _dk = CORBA::dk_Primitive;
  _kind = kind;
  switch( kind ) {
  case CORBA::pk_void:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_void );
    break;
  case CORBA::pk_float:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_float );
    break;
  case CORBA::pk_double:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_double );
    break;
  case CORBA::pk_long:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_long );
    break;
  case CORBA::pk_short:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_short );
    break;
  case CORBA::pk_ulong:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_ulong );
    break;
  case CORBA::pk_ushort:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_ushort );
    break;
  case CORBA::pk_char:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_char );
    break;
  case CORBA::pk_boolean:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_boolean );
    break;
  case CORBA::pk_octet:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_octet );
    break;
  case CORBA::pk_string:
    _type = CORBA::TypeCode::create_string_tc( 0 );
    break;
  case CORBA::pk_any:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_any );
    break;
  case CORBA::pk_objref:
    _type = CORBA::TypeCode::create_interface_tc( 
                      (const char *) "IDL:omg.org/CORBA/Object:1.0",
		      "Object" );
    break;
  case CORBA::pk_TypeCode:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_TypeCode );
    break;
  case CORBA::pk_Principal:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_Principal );
    break;
  case CORBA::pk_longlong:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_longlong );
    break;
  case CORBA::pk_ulonglong:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_ulonglong );
    break;
  case CORBA::pk_longdouble:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_longdouble );
    break;
  case CORBA::pk_wchar:
    _type = CORBA::TypeCode::create_basic_tc( CORBA::tk_wchar );
    break;
  case CORBA::pk_wstring:
    _type = CORBA::TypeCode::create_wstring_tc( 0 );
    break;
  case CORBA::pk_value_base:
    _type = CORBA::TypeCode::create_value_tc(
                      "IDL:omg.org/CORBA/ValueBase:1.0",
		      "ValueBase",
		      CORBA::VM_NONE,
		      CORBA::TypeCode::_nil(),
		      CORBA::ValueMemberSeq());
    break;
  default:
    assert( 0 );
  }
}

CORBA::PrimitiveKind PrimitiveDef_impl::kind()
{
  return _kind;
}


//-- StringDef ----------------------------------------------------------

StringDef_impl::StringDef_impl()
{
  _dk = CORBA::dk_String;
  _type = CORBA::TypeCode::create_string_tc( 0 );
  _bound = 0;
}

CORBA::ULong StringDef_impl::bound()
{
  return _bound;
}

void StringDef_impl::bound( CORBA::ULong _value )
{
  if( _value == 0 )
    mico_throw (CORBA::BAD_PARAM());

  _bound = _value;
  _type = CORBA::TypeCode::create_string_tc( _value );
}


//-- WstringDef ---------------------------------------------------------

WstringDef_impl::WstringDef_impl()
{
  _dk = CORBA::dk_Wstring;
  _type = CORBA::TypeCode::create_wstring_tc( 0 );
  _bound = 0;
}

CORBA::ULong WstringDef_impl::bound()
{
  return _bound;
}

void WstringDef_impl::bound( CORBA::ULong _value )
{
  if( _value == 0 )
    mico_throw (CORBA::BAD_PARAM());

  _bound = _value;
  _type = CORBA::TypeCode::create_wstring_tc( _value );
}


//-- FixedDef -----------------------------------------------------------

FixedDef_impl::FixedDef_impl()
{
  _dk = CORBA::dk_Fixed;
  _type = CORBA::TypeCode::create_fixed_tc( 0, 0 );
  _digits = 0;
  _scale = 0;
}

CORBA::UShort FixedDef_impl::digits()
{
  return _digits;
}

void FixedDef_impl::digits( CORBA::UShort _value )
{
  _digits = _value;
  _type = CORBA::TypeCode::create_fixed_tc( _digits, _scale );
}

CORBA::Short FixedDef_impl::scale()
{
  return _scale;
}

void FixedDef_impl::scale( CORBA::Short _value )
{
  _scale = _value;
  _type = CORBA::TypeCode::create_fixed_tc( _digits, _scale );
}


//-- SequenceDef --------------------------------------------------------

SequenceDef_impl::SequenceDef_impl()
{
  _dk = CORBA::dk_Sequence;
  _bound = 0;
  _element_type_def = CORBA::IDLType::_nil();
}

CORBA::TypeCode_ptr
SequenceDef_impl::type()
{
  if (CORBA::is_nil (_element_type_def))
    return CORBA::TypeCode::_nil();

  CORBA::TypeCode_var element_type;

  _done = FALSE;
    
  if (_visited.count (_element_type_def.in())) {
    // create "forward decl" for element type ...
    CORBA::Contained_var cont =
      CORBA::Contained::_narrow (_element_type_def);
    assert (!CORBA::is_nil (cont));
    CORBA::String_var repoid = cont->id();
    if (CORBA::is_nil (_rec_type) || strcmp (_rec_type->id(), repoid))
      _rec_type = CORBA::TypeCode::create_recursive_tc (repoid);
    element_type = _rec_type;
  } else {
    element_type = _element_type_def->type();
    if (CORBA::is_nil (element_type))
      return CORBA::TypeCode::_nil();

    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done)
      return CORBA::TypeCode::_duplicate (_type);
  }

  // check whether we need to recreate the typecode ...

  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _type->length() != _bound ||
    _old_element_type.in() != element_type.in();

  if (modified) {
    // disconnect content type code so it gets properly embedded into
    // the newly created typecode
    _old_element_type = element_type;
    element_type->disconnect (_type);

    _type = CORBA::TypeCode::create_sequence_tc (_bound, element_type);
  }

  _done = TRUE;

  return CORBA::TypeCode::_duplicate (_type);
}

CORBA::ULong SequenceDef_impl::bound()
{
  return _bound;
}

void SequenceDef_impl::bound( CORBA::ULong _value )
{
  _bound = _value;
}

CORBA::TypeCode_ptr SequenceDef_impl::element_type()
{
  assert( !CORBA::is_nil( _element_type_def ) );
  return _element_type_def->type();
}

CORBA::IDLType_ptr SequenceDef_impl::element_type_def()
{
  return CORBA::IDLType::_duplicate( _element_type_def );
}

void SequenceDef_impl::element_type_def( CORBA::IDLType_ptr _value )
{
  _element_type_def = CORBA::IDLType::_duplicate( _value );
}


//-- ArrayDef -----------------------------------------------------------

ArrayDef_impl::ArrayDef_impl()
{
  _dk = CORBA::dk_Array;
  _length = 0;
  _element_type_def = CORBA::IDLType::_nil();
}

CORBA::TypeCode_ptr
ArrayDef_impl::type()
{
  if (CORBA::is_nil (_element_type_def))
    return CORBA::TypeCode::_nil();

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::TypeCode_var element_type = _element_type_def->type();
  if (CORBA::is_nil (element_type))
    return CORBA::TypeCode::_nil();

  // if _done then a nested invocation to this->type()
  // has already calculated the typecode ...
  if (_done)
    return CORBA::TypeCode::_duplicate (_type);

  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _type->length() != _length ||
    _old_element_type.in() != element_type.in();

  if (modified) {
    // disconnect content type code so it gets properly embedded into
    // the newly created typecode
    _old_element_type = element_type;
    element_type->disconnect (_type);

    _type = CORBA::TypeCode::create_array_tc (_length, element_type);
  }

  _done = TRUE;

  return CORBA::TypeCode::_duplicate (_type);
}

CORBA::ULong ArrayDef_impl::length()
{
  return _length;
}

void ArrayDef_impl::length( CORBA::ULong _value )
{
  _length = _value;
}

CORBA::TypeCode_ptr ArrayDef_impl::element_type()
{
  assert( !CORBA::is_nil( _element_type_def ) );
  return _element_type_def->type();
}

CORBA::IDLType_ptr ArrayDef_impl::element_type_def()
{
  return CORBA::IDLType::_duplicate( _element_type_def );
}

void ArrayDef_impl::element_type_def( CORBA::IDLType_ptr _value )
{
  _element_type_def = CORBA::IDLType::_duplicate( _value );
}

//-- ExceptionDef -------------------------------------------------------

ExceptionDef_impl::ExceptionDef_impl( CORBA::Container_ptr defined_in,
				      const char* id,
				      const char* name,
				      const char* version,
				      const CORBA::StructMemberSeq& members )
  : Contained_impl( defined_in )
{
  check_for_duplicates (members);

  _dk = CORBA::dk_Exception;
  _id = id;
  _name = name;
  _version = version;
  _members = members;
}

CORBA::StructMemberSeq* ExceptionDef_impl::members()
{
  CORBA::StructMemberSeq *m = new CORBA::StructMemberSeq;
  *m = _members;
  return m;
}

void ExceptionDef_impl::members( const CORBA::StructMemberSeq& _value )
{
  check_for_duplicates (_value);
  _members = _value;
}

void
ExceptionDef_impl::check_for_duplicates (const CORBA::StructMemberSeq &mems)
{
  CORBA::ULong i, j;

  // See if we have any duplicate names in the member list
  for( i = 0; i < mems.length(); i++ ) {
    for( j = i + 1; j < mems.length(); j++ ) {
      if( strcmp( mems[ i ].name, mems[ j ].name ) == 0 )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_MEMBER,
                                       CORBA::COMPLETED_NO ) );
    }
  }
}

CORBA::TypeCode_ptr
ExceptionDef_impl::type()
{
  CORBA::Boolean visited = _visited.count (this);
  if (!visited)
    _visited.insert (this);

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::ULong i;
  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _old_member_types.length() != _members.length();

  for (i = 0; i < _members.length(); ++i) {
    _members[i].type = _members[i].type_def->type();
    if (CORBA::is_nil (_members[i].type)) {
      if (!visited)
	_visited.erase (this);
      return CORBA::TypeCode::_nil();
    }
    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done) {
      if (!visited)
	_visited.erase (this);
      return CORBA::TypeCode::_duplicate (_type);
    }
    if (modified)
      continue;
    if (_old_member_types[i].in() != _members[i].type.in() ||
	strcmp (_type->member_name(i), _members[i].name))
      modified = TRUE;
  }

  if (modified) {
    // disconnect member typecodes so they get properly embedded into
    // the newly created typecode
    _old_member_types.length (_members.length());
    for (i = 0; i < _members.length(); ++i) {
      _old_member_types[i] = _members[i].type;
      _members[i].type->disconnect (_type);
    }

    _type = CORBA::TypeCode::create_exception_tc (_id, _name, _members);
  }

  _done = TRUE;

  if (!visited)
    _visited.erase (this);

  return CORBA::TypeCode::_duplicate (_type);
}


//-- AttributeDef -------------------------------------------------------

AttributeDef_impl::AttributeDef_impl( CORBA::Container_ptr defined_in,
				      const char* id,
				      const char* name,
				      const char* version,
				      CORBA::IDLType_ptr type_def,
				      CORBA::AttributeMode mode )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Attribute;
  _id = id;
  _name = name;
  _version = version;
  _type_def = CORBA::IDLType::_duplicate( type_def );
  _mode = mode;
}

CORBA::TypeCode_ptr AttributeDef_impl::type()
{
  return _type_def->type();
}

CORBA::IDLType_ptr AttributeDef_impl::type_def()
{
  return CORBA::IDLType::_duplicate( _type_def );
}

void AttributeDef_impl::type_def( CORBA::IDLType_ptr _value )
{
  _type_def = CORBA::IDLType::_duplicate( _value );
}

CORBA::AttributeMode AttributeDef_impl::mode()
{
  return _mode;
}

void AttributeDef_impl::mode( CORBA::AttributeMode _value )
{
  _mode = _value;
}


//-- OperationDef -------------------------------------------------------

OperationDef_impl::OperationDef_impl( CORBA::Container_ptr defined_in,
				      const char* id,
				      const char* name,
				      const char* version,
				      CORBA::IDLType_ptr result,
				      CORBA::OperationMode mode,
				      const CORBA::ParDescriptionSeq& params,
				      const CORBA::ExceptionDefSeq& exs,
				      const CORBA::ContextIdSeq& ctx )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Operation;
  _id = id;
  _name = name;
  _version = version;
  _result_def = CORBA::IDLType::_duplicate( result );
  _mode = mode;
  _params = params;
  _exceptions = exs;
  _contexts = ctx;
}

CORBA::TypeCode_ptr OperationDef_impl::result()
{
  return _result_def->type();
}

CORBA::IDLType_ptr OperationDef_impl::result_def()
{
  return CORBA::IDLType::_duplicate( _result_def );
}

void OperationDef_impl::result_def( CORBA::IDLType_ptr _value )
{
  _result_def = CORBA::IDLType::_duplicate( _value );
}

CORBA::ParDescriptionSeq* OperationDef_impl::params()
{
  CORBA::ParDescriptionSeq* p = new CORBA::ParDescriptionSeq;
  *p = _params;
  return p;
}

void OperationDef_impl::params( const CORBA::ParDescriptionSeq& _value )
{
  _params = _value;
}

CORBA::OperationMode OperationDef_impl::mode()
{
  return _mode;
}

void OperationDef_impl::mode( CORBA::OperationMode _value )
{
  _mode = _value;
}

CORBA::ContextIdSeq* OperationDef_impl::contexts()
{
  CORBA::ContextIdSeq *ctx = new CORBA::ContextIdSeq;
  *ctx = _contexts;
  return ctx;
}

void OperationDef_impl::contexts( const CORBA::ContextIdSeq& _value )
{
  _contexts = _value;
}

CORBA::ExceptionDefSeq* OperationDef_impl::exceptions()
{
  CORBA::ExceptionDefSeq *exs = new CORBA::ExceptionDefSeq;
  *exs = _exceptions;
  return exs;
}

void OperationDef_impl::exceptions( const CORBA::ExceptionDefSeq& _value )
{
  _exceptions = _value;
}


//-- InterfaceDef -------------------------------------------------------

InterfaceDef_impl::InterfaceDef_impl()
  : Contained_impl( CORBA::Container::_nil())
{
}

InterfaceDef_impl::InterfaceDef_impl( CORBA::Container_ptr defined_in,
				      const char* id,
				      const char* name,
				      const char* version,
				      const CORBA::InterfaceDefSeq& base_itf,
				      CORBA::Boolean is_abstract )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Interface;
  _id = id;
  _name = name;
  _version = version;
  _base_interfaces = base_itf;
  _is_abstract = is_abstract;

  if (is_abstract) {
    _type = CORBA::TypeCode::create_abstract_interface_tc( id, name );
  }
  else {
    _type = CORBA::TypeCode::create_interface_tc( id, name );
  }
}

void InterfaceDef_impl::check_for_overloaded_ops( const char* name,
						  const char* id )
{
  CORBA::ContainedSeq_var contents = this->contents( CORBA::dk_all, FALSE );
  
  for( CORBA::ULong i = 0; i < contents->length(); i++ ) {
    CORBA::Contained_ptr con = contents[ i ];

    if( con->def_kind() == CORBA::dk_Operation ||
	con->def_kind() == CORBA::dk_Attribute ) {

      CORBA::String_var con_name = con->name();
      if( strcmp( con_name, name ) == 0 )
        mico_throw (CORBA::BAD_PARAM( MICO_IR_EXC_OVERLOADING,
                                      CORBA::COMPLETED_NO ) );
    }
  }
  
  CORBA::Repository_var repo = this->containing_repository();

  CORBA::Contained_var con = repo->lookup_id( id );
  if( !CORBA::is_nil( con ) )
    mico_throw (CORBA::BAD_PARAM( MICO_IR_EXC_DUPLICATE_REPOID,
                                  CORBA::COMPLETED_NO ) );
}

CORBA::InterfaceDefSeq* InterfaceDef_impl::base_interfaces()
{
  CORBA::InterfaceDefSeq* b = new CORBA::InterfaceDefSeq;
  *b = _base_interfaces;
  return b;
}

void
InterfaceDef_impl::base_interfaces( const CORBA::InterfaceDefSeq& _value )
{
  _base_interfaces = _value;
}

CORBA::Boolean
InterfaceDef_impl::is_abstract()
{
  return _is_abstract;
}

void
InterfaceDef_impl::is_abstract( CORBA::Boolean _value )
{
  _is_abstract = _value;
}

CORBA::Boolean
InterfaceDef_impl::is_a( const char* interface_id )
{
  if( strcmp( _id, interface_id ) == 0 )
    return TRUE;

  if( strcmp( "IDL:omg.org/CORBA/Object:1.0", interface_id ) == 0 &&
      !_is_abstract )
    return TRUE;

  if( strcmp( "IDL:omg.org/CORBA/AbstractBase:1.0", interface_id ) == 0 &&
      _is_abstract )
    return TRUE;
   
  for( CORBA::ULong i = 0; i < _base_interfaces.length(); i++ ) {
    if( _base_interfaces[ i ]->is_a( interface_id ) )
      return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef::FullInterfaceDescription*
InterfaceDef_impl::describe_interface()
{
  CORBA::InterfaceDef::FullInterfaceDescription *desc =
    new CORBA::InterfaceDef::FullInterfaceDescription;
  
  desc->name = _name;
  desc->id = _id;

  CORBA::Contained_var def_in = CORBA::Contained::_narrow( _defined_in );
  if( !CORBA::is_nil( def_in ) )
    desc->defined_in = def_in->id();
  else
    desc->defined_in = (const char *) "";
  
  desc->version = _version;

  desc->base_interfaces.length( _base_interfaces.length() );
  for( CORBA::ULong j0 = 0; j0 < _base_interfaces.length(); j0++ )
	desc->base_interfaces[ j0 ] = _base_interfaces[ j0 ]->id();

  desc->type = type();
  desc->is_abstract = _is_abstract;
  
  CORBA::ContainedSeq_var csv = contents (CORBA::dk_Operation, FALSE);
  desc->operations.length (csv->length());
  for (CORBA::ULong i0=0; i0<csv->length(); i0++) {
    CORBA::Contained::Description_var d = csv[i0]->describe ();
    CORBA::OperationDescription * od;
    assert (d->kind == CORBA::dk_Operation);
    CORBA::Boolean r = (d->value >>= od);
    assert (r);
    desc->operations[i0] = *od;
  }

  csv = contents (CORBA::dk_Attribute, FALSE);
  desc->attributes.length (csv->length());
  for (CORBA::ULong i1=0; i1<csv->length(); i1++) {
    CORBA::Contained::Description_var d = csv[i1]->describe ();
    CORBA::AttributeDescription * ad;
    assert (d->kind == CORBA::dk_Attribute);
    CORBA::Boolean r = (d->value >>= ad);
    assert (r);
    desc->attributes[i1] = *ad;
  }

  return desc;
}

CORBA::AttributeDef_ptr
InterfaceDef_impl::create_attribute( const char* id,
				     const char* name,
				     const char* version,
				     CORBA::IDLType_ptr type,
				     CORBA::AttributeMode mode )
{
  check_for_overloaded_ops( name, id );
  
  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::AttributeDef_ptr op =
    new AttributeDef_impl( this, id, name, version, type, mode );
  _contents[ i ] = CORBA::AttributeDef::_duplicate( op );
  return op;
}

CORBA::OperationDef_ptr
InterfaceDef_impl::create_operation( const char* id,
				     const char* name,
				     const char* version,
				     CORBA::IDLType_ptr result,
				     CORBA::OperationMode mode,
				     const CORBA::ParDescriptionSeq& params,
				     const CORBA::ExceptionDefSeq& exceptions,
				     const CORBA::ContextIdSeq& contexts )
{
  check_for_overloaded_ops( name, id );

  if( mode == CORBA::OP_ONEWAY ) {
    // Check that oneway operations have no result, no out, inout parameters
    // and no raises expressions
    CORBA::TypeCode_var result_tc = result->type();
    if( result_tc->kind() != CORBA::tk_void )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                     CORBA::COMPLETED_NO ) );
    if( exceptions.length() != 0 )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                     CORBA::COMPLETED_NO ) );
    for( CORBA::ULong i = 0; i < params.length(); i++ )
      if( params[ i ].mode != CORBA::PARAM_IN )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                       CORBA::COMPLETED_NO ) );
  }

  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::OperationDef_ptr op =
    new OperationDef_impl( this, id, name, version, result, mode, params,
			   exceptions, contexts );
  _contents[ i ] = CORBA::OperationDef::_duplicate( op );
  return op;
}

//-- ValueMemberDef -------------------------------------------------------

ValueMemberDef_impl::ValueMemberDef_impl ( CORBA::Container_ptr defined_in,
					   const char* id,
					   const char* name,
					   const char* version,
					   CORBA::IDLType_ptr type,
					   CORBA::Visibility access )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_ValueMember;
  _id = id;
  _name = name;
  _version = version;
  _type_def = CORBA::IDLType::_duplicate (type);
  _access = access;
}

CORBA::TypeCode_ptr
ValueMemberDef_impl::type()
{
  return _type_def->type();
}

CORBA::IDLType_ptr
ValueMemberDef_impl::type_def()
{
  return CORBA::IDLType::_duplicate (_type_def);
}

void
ValueMemberDef_impl::type_def( CORBA::IDLType_ptr _new_value )
{
  _type_def = CORBA::IDLType::_duplicate (_new_value);
}

CORBA::Visibility
ValueMemberDef_impl::access()
{
  return _access;
}

void
ValueMemberDef_impl::access( CORBA::Visibility _new_value )
{
  _access = _new_value;
}

//-- ValueDef -------------------------------------------------------

ValueDef_impl::ValueDef_impl ( CORBA::Container_ptr defined_in,
			       const char* id,
			       const char* name,
			       const char* version,
			       CORBA::Boolean is_custom,
			       CORBA::Boolean is_abstract,
			       CORBA::ValueDef_ptr base_value,
			       CORBA::Boolean is_truncatable,
			       const CORBA::ValueDefSeq& abstract_base_values,
			       const CORBA::InterfaceDefSeq& supported_interfaces,
			       const CORBA::InitializerSeq& inits )
  : Contained_impl( defined_in )
{
  _dk = CORBA::dk_Value;
  _id = id;
  _name = name;
  _version = version;
  _is_custom = is_custom;
  _is_abstract = is_abstract;
  _base_value = CORBA::ValueDef::_duplicate (base_value);
  _is_truncatable = is_truncatable;
  _abstract_base_values = abstract_base_values;
  _supported_interfaces = supported_interfaces;
  initializers (inits);
}

CORBA::InterfaceDefSeq*
ValueDef_impl::supported_interfaces()
{
  return new CORBA::InterfaceDefSeq (_supported_interfaces);
}

void
ValueDef_impl::supported_interfaces( const CORBA::InterfaceDefSeq& _new_value )
{
  _supported_interfaces = _new_value;
}

CORBA::InitializerSeq*
ValueDef_impl::initializers()
{
  return new CORBA::InitializerSeq (_initializers);
}

void
ValueDef_impl::initializers( const CORBA::InitializerSeq& _new_value )
{
  _initializers = _new_value;
  for (CORBA::ULong i = 0; i < _initializers.length(); ++i) {
    for (CORBA::ULong j = 0; j < _initializers[i].members.length(); ++j) {
      _initializers[i].members[j].type =
	_initializers[i].members[j].type_def->type();
    }
  }
}

CORBA::ValueDef_ptr
ValueDef_impl::base_value()
{
  return CORBA::ValueDef::_duplicate (_base_value);
}

void
ValueDef_impl::base_value( CORBA::ValueDef_ptr _new_value )
{
  _base_value = CORBA::ValueDef::_duplicate (_new_value);
}

CORBA::ValueDefSeq*
ValueDef_impl::abstract_base_values()
{
  return new CORBA::ValueDefSeq (_abstract_base_values);
}

void
ValueDef_impl::abstract_base_values( const CORBA::ValueDefSeq& _new_value )
{
  _abstract_base_values = _new_value;
}

CORBA::Boolean
ValueDef_impl::is_abstract()
{
  return _is_abstract;
}

void
ValueDef_impl::is_abstract( CORBA::Boolean _new_value )
{
  _is_abstract = _new_value;
}

CORBA::Boolean
ValueDef_impl::is_custom()
{
  return _is_custom;
}

void
ValueDef_impl::is_custom( CORBA::Boolean _new_value )
{
  _is_custom = _new_value;
}

CORBA::Boolean
ValueDef_impl::is_truncatable()
{
  return _is_truncatable;
}

void
ValueDef_impl::is_truncatable( CORBA::Boolean _new_value )
{
  _is_truncatable = _new_value;
}

CORBA::Boolean
ValueDef_impl::is_a( const char* value_id )
{
  if( strcmp( _id, value_id ) == 0 )
    return TRUE;

  if( strcmp( "IDL:omg.org/CORBA/ValueBase:1.0", value_id ) == 0 )
    return TRUE;
   
  for( CORBA::ULong i = 0; i < _abstract_base_values.length(); i++ ) {
    if( _abstract_base_values[i]->is_a( value_id ) )
      return TRUE;
  }
  for( CORBA::ULong j = 0; j < _supported_interfaces.length(); j++ ) {
    if( _supported_interfaces[j]->is_a( value_id ) )
      return TRUE;
  }
  if( !CORBA::is_nil( _base_value ) &&
      _base_value->is_a( value_id ) )
    return TRUE;

  return FALSE;
}

CORBA::ValueDef::FullValueDescription*
ValueDef_impl::describe_value()
{
  CORBA::ValueDef::FullValueDescription *desc =
    new CORBA::ValueDef::FullValueDescription;
  
  desc->name = _name;
  desc->id = _id;

  CORBA::Contained_var def_in = CORBA::Contained::_narrow( _defined_in );
  if( !CORBA::is_nil( def_in ) )
    desc->defined_in = def_in->id();
  else
    desc->defined_in = (const char *) "";
  
  desc->version = _version;
  desc->is_abstract = _is_abstract;
  desc->is_custom = _is_custom;
  desc->is_truncatable = _is_truncatable;

  desc->abstract_base_values.length( _abstract_base_values.length() );
  for( CORBA::ULong j0 = 0; j0 < _abstract_base_values.length(); j0++ )
    desc->abstract_base_values[j0] = _abstract_base_values[j0]->id();

  desc->supported_interfaces.length( _supported_interfaces.length() );
  for( CORBA::ULong j1 = 0; j1 < _supported_interfaces.length(); j1++ )
    desc->supported_interfaces[j1] = _supported_interfaces[j1]->id();

  if (CORBA::is_nil (_base_value))
    desc->base_value = (const char *)"";
  else
    desc->base_value = _base_value->id();

  desc->type = type();

  desc->initializers = _initializers;

  // operations, attributes, members

  CORBA::ULong j = 0;

  for( CORBA::ULong i = 0; i < _contents.length(); i++ ) {
    CORBA::OperationDef_var op =
      CORBA::OperationDef::_narrow( _contents[ i ] );
    if( !CORBA::is_nil( op ) ) {
      desc->operations.length( j + 1 );
      CORBA::OperationDescription op_desc;
      op_desc.id = op->id();
      op_desc.defined_in = this->id();
      op_desc.name = op->name();
      op_desc.mode = op->mode();
      op_desc.result = op->result();
      CORBA::ParDescriptionSeq_var params = op->params();
      op_desc.parameters = params.in();
      CORBA::ContextIdSeq_var ctx = op->contexts();
      op_desc.contexts = ctx.in();
      
      // Get all exceptions
      CORBA::ExceptionDefSeq_var exs = op->exceptions();
      op_desc.exceptions.length( exs->length() );
      for( CORBA::ULong k = 0; k < exs->length(); k++ ) {
	op_desc.exceptions[ k ].name = exs[ k ]->name();
	op_desc.exceptions[ k ].id   = exs[ k ]->id();
	CORBA::Container_var def_in = exs[ k ]->defined_in();
	CORBA::Contained_var contained = CORBA::Contained::_narrow( def_in );
	if( !CORBA::is_nil( contained ) )
	  op_desc.exceptions[ k ].defined_in = contained->id();
	else
	  op_desc.exceptions[ k ].defined_in = (const char *)"";
	op_desc.exceptions[ k ].version = exs[ k ]->version();
	op_desc.exceptions[ k ].type    = exs[ k ]->type();
      }
      
      desc->operations[ j++ ] = op_desc;
    }
  }

  j = 0;
  for( CORBA::ULong i0 = 0; i0 < _contents.length(); i0++ ) {
    CORBA::AttributeDef_var a =
      CORBA::AttributeDef::_narrow( _contents[ i0 ] );
    if( !CORBA::is_nil( a ) ) {
      desc->attributes.length( j + 1 );

      CORBA::Contained::Description_var d = a->describe();
      CORBA::Boolean r = (d->value >>= desc->attributes[j++]);
      assert (r);
    }
  }

  j = 0;
  for (CORBA::ULong i1 = 0; i1 < _contents.length(); ++i1) {
    CORBA::ValueMemberDef_var m =
      CORBA::ValueMemberDef::_narrow (_contents[i1]);
    if (!CORBA::is_nil (m)) {
      desc->members.length (j+1);

      desc->members[j].name       = m->name();
      desc->members[j].id         = m->id();
      desc->members[j].version    = m->version();
      desc->members[j].access     = m->access();
      desc->members[j].type       = m->type();
      desc->members[j].type_def   = m->type_def();
      desc->members[j].defined_in = this->id();
      j++;
    }
  }
  return desc;
}


void
ValueDef_impl::check_for_overloaded_ops( const char* name,
					 const char* id )
{
  CORBA::ContainedSeq_var contents = this->contents( CORBA::dk_all, FALSE );
  
  for( CORBA::ULong i = 0; i < contents->length(); i++ ) {
    CORBA::Contained_ptr con = contents[ i ];

    CORBA::String_var con_name = con->name();
    if( strcmp( con_name, name ) == 0 )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_OVERLOADING,
                                     CORBA::COMPLETED_NO ) );

    CORBA::String_var con_id = con->id();
    if( strcmp( con_id, id ) == 0 )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_DUPLICATE_REPOID,
                                     CORBA::COMPLETED_NO ) );
  }
}

CORBA::ValueMemberDef_ptr
ValueDef_impl::create_value_member( const char* id,
				    const char* name,
				    const char* version,
				    CORBA::IDLType_ptr type,
				    CORBA::Visibility access )
{
  check_for_overloaded_ops( name, id );
  
  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::ValueMemberDef_ptr mem =
    new ValueMemberDef_impl( this, id, name, version, type, access );
  _contents[ i ] = CORBA::ValueMemberDef::_duplicate( mem );
  return mem;
}


CORBA::AttributeDef_ptr
ValueDef_impl::create_attribute( const char* id,
				 const char* name,
				 const char* version,
				 CORBA::IDLType_ptr type,
				 CORBA::AttributeMode mode )
{
  check_for_overloaded_ops( name, id );
  
  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::AttributeDef_ptr op =
    new AttributeDef_impl( this, id, name, version, type, mode );
  _contents[ i ] = CORBA::AttributeDef::_duplicate( op );
  return op;
}


CORBA::OperationDef_ptr
ValueDef_impl::create_operation( const char* id,
				 const char* name,
				 const char* version,
				 CORBA::IDLType_ptr result,
				 CORBA::OperationMode mode,
				 const CORBA::ParDescriptionSeq& params,
				 const CORBA::ExceptionDefSeq& exceptions,
				 const CORBA::ContextIdSeq& contexts )
{
  check_for_overloaded_ops( name, id );

  if( mode == CORBA::OP_ONEWAY ) {
    // Check that oneway operations have no result, no out, inout parameters
    // and no raises expressions
    CORBA::TypeCode_var result_tc = result->type();
    if( result_tc->kind() != CORBA::tk_void )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                     CORBA::COMPLETED_NO ) );
    if( exceptions.length() != 0 )
      mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                     CORBA::COMPLETED_NO ) );
    for( CORBA::ULong i = 0; i < params.length(); i++ )
      if( params[ i ].mode != CORBA::PARAM_IN )
	mico_throw( CORBA::INTF_REPOS( MICO_IR_EXC_BAD_ONEWAY,
                                       CORBA::COMPLETED_NO ) );
  }

  int i = _contents.length();
  _contents.length( i + 1 );
  CORBA::OperationDef_ptr op =
    new OperationDef_impl( this, id, name, version, result, mode, params,
			   exceptions, contexts );
  _contents[ i ] = CORBA::OperationDef::_duplicate( op );
  return op;
}

CORBA::TypeCode_ptr
ValueDef_impl::type()
{
  if (_visited.count (this)) {
    // create "forward decl" ...
    if (CORBA::is_nil (_rec_type) || strcmp (_rec_type->id(), _id))
      _rec_type = CORBA::TypeCode::create_recursive_tc (_id);
    return CORBA::TypeCode::_duplicate (_rec_type);
  }

  _visited.insert (this);

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::ULong i, j;

  CORBA::TypeCode_var base_type;
  if (!CORBA::is_nil (_base_value)) {
    base_type = _base_value->type();

    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done) {
      _visited.erase (this);
      return CORBA::TypeCode::_duplicate (_type);
    }
  }

  CORBA::ValueModifier modifier = CORBA::VM_NONE;
  // only one modifier allowed
  assert (!!_is_abstract + !!_is_custom + !!_is_truncatable <= 1);
  if (_is_abstract)
    modifier = CORBA::VM_ABSTRACT;
  if (_is_custom)
    modifier = CORBA::VM_CUSTOM;
  if (_is_truncatable)
    modifier = CORBA::VM_TRUNCATABLE;

  CORBA::ValueMemberSeq members;

  for (i = j = 0; i < _contents.length(); ++i) {
    CORBA::ValueMemberDef_var mdef =
      CORBA::ValueMemberDef::_narrow (_contents[i]);
    if (CORBA::is_nil (mdef))
      continue;
    members.length (j+1);
    members[j].type = mdef->type();
    if (CORBA::is_nil (members[j].type)) {
      _visited.erase (this);
      return CORBA::TypeCode::_nil();
    }
    // if _done then a nested invocation to this->type()
    // has already calculated the typecode ...
    if (_done) {
      _visited.erase (this);
      return CORBA::TypeCode::_duplicate (_type);
    }
    members[j].name = mdef->name();
    members[j].id = mdef->id();
    members[j].access = mdef->access();
    j++;
  }

  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _type->type_modifier() != modifier ||
    _old_member_types.length() != members.length() ||
    _old_base_type.in() != base_type.in();

  if (!modified) {
    for (i = 0; i < members.length(); ++i) {
      if (_old_member_types[i].in() != members[i].type.in() ||
	  strcmp (_type->member_name(i), members[i].name) ||
	  _type->member_visibility(i) != members[i].access) {
	modified = TRUE;
	break;
      }
    }
  }

  if (modified) {
    // disconnect member typecodes so they get properly embedded into
    // the newly created typecode
    _old_base_type = base_type;
    _old_member_types.length (members.length());
    for (i = 0; i < members.length(); ++i) {
      _old_member_types[i] = members[i].type;
      members[i].type->disconnect (_type);
    }

    if (!CORBA::is_nil (base_type))
      base_type->disconnect (_type);

    _type = CORBA::TypeCode::create_value_tc (_id, _name, modifier,
					      base_type, members);
  }

  _done = TRUE;

  _visited.erase (this);

  return CORBA::TypeCode::_duplicate (_type);
}

//-- ValueBoxDef -------------------------------------------------------

ValueBoxDef_impl::ValueBoxDef_impl ( CORBA::Container_ptr defined_in,
				     const char* id,
				     const char* name,
				     const char* version,
				     CORBA::IDLType_ptr original_type_def )
  : Contained_impl (defined_in), TypedefDef_impl (defined_in)
{
  _dk = CORBA::dk_ValueBox;
  _id = id;
  _name = name;
  _version = version;
  _original_type_def = CORBA::IDLType::_duplicate (original_type_def);
}

CORBA::IDLType_ptr
ValueBoxDef_impl::original_type_def()
{
  return CORBA::IDLType::_duplicate (_original_type_def);
}

void
ValueBoxDef_impl::original_type_def( CORBA::IDLType_ptr _new_value )
{
  _original_type_def = CORBA::IDLType::_duplicate (_new_value);
}

CORBA::TypeCode_ptr
ValueBoxDef_impl::type()
{
  if (CORBA::is_nil (_original_type_def))
    return CORBA::TypeCode::_nil();

  // check whether we need to recreate the typecode ...

  _done = FALSE;

  CORBA::TypeCode_var original_type = _original_type_def->type();
  if (CORBA::is_nil (original_type))
    return CORBA::TypeCode::_nil();

  // if _done then a nested invocation to this->type()
  // has already calculated the typecode ...
  if (_done)
    return CORBA::TypeCode::_duplicate (_type);

  CORBA::Boolean modified =
    CORBA::is_nil (_type) ||
    _old_original_type.in() != original_type.in();

  if (modified) {
    // disconnect content type code so it gets properly embedded into
    // the newly created typecode
    _old_original_type = original_type;
    original_type->disconnect (_type);

    _type = CORBA::TypeCode::create_value_box_tc (_id, _name, original_type);
  }

  _done = TRUE;

  return CORBA::TypeCode::_duplicate (_type);
}

