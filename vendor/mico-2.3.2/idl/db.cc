/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#include <CORBA.h>
#include <mico/util.h>
#include <mico/ir_impl.h>
#include <mico/template_impl.h>
#include "db.h"


DB::DB()
{
  _parse_tree = NULL;

  vector<string> empty_scope;
  _current_scope.push_back (empty_scope);

  string empty;
  _current_prefix.push_back( empty );
}

DB::~DB()
{
  if( _parse_tree != NULL )
    delete _parse_tree;
}

void DB::set_parse_tree( ParseNode* node )
{
  if( _parse_tree != NULL )
    delete _parse_tree;
  _parse_tree = node;
}

ParseNode* DB::get_parse_tree()
{
  return _parse_tree;
}

void DB::set_idl_container( CORBA::Container_ptr con )
{
  _con = CORBA::Container::_duplicate( con );
}

CORBA::Container_ptr DB::get_idl_container()
{
  return CORBA::Container::_duplicate( _con );
}

/*
 * Generate a pseudo repoid for an IRObject that is not a
 * Contained (like SequenceDef)
 */
string DB::gen_pseudo_repoid( CORBA::IDLType_ptr t )
{
  string name;

  CORBA::Contained_var con = CORBA::Contained::_narrow( t );
  if( !CORBA::is_nil( con ) ) {
    CORBA::String_var tmp = con->id();
    name = tmp;
    return name;
  }
  
  CORBA::StringDef_var str = CORBA::StringDef::_narrow( t );
  if( !CORBA::is_nil( str ) ) {
    name = "string_";
    name += xdec( str->bound() );
    return name;
  }

  CORBA::WstringDef_var wstr = CORBA::WstringDef::_narrow( t );
  if( !CORBA::is_nil( wstr ) ) {
    name = "wstring_";
    name += xdec( wstr->bound() );
    return name;
  }

  CORBA::SequenceDef_var seq = CORBA::SequenceDef::_narrow( t );
  if( !CORBA::is_nil( seq ) ) {
    name = "sequence_";
    CORBA::IDLType_var elem = seq->element_type_def();
    name += gen_pseudo_repoid( elem );
    name += "_";
    name += xdec( seq->bound() );
    return name;
  }

  CORBA::FixedDef_var fix = CORBA::FixedDef::_narrow( t );
  if( !CORBA::is_nil( fix ) ) {
    name = "fixed_";
    CORBA::TypeCode_var tc = t->type();
    name += xdec( tc->fixed_digits() );
    name += '_';
    name += xdec( tc->fixed_scale() );
    return name;
  }
  
  CORBA::ArrayDef_var arr = CORBA::ArrayDef::_narrow( t );
  if( !CORBA::is_nil( arr ) ) {
    name = "array_";
    CORBA::IDLType_var elem = arr->element_type_def();
    name += gen_pseudo_repoid( elem );
    name += xdec( arr->length() );
    return name;
  }
  
  CORBA::PrimitiveDef_var prim = CORBA::PrimitiveDef::_narrow( t );
  assert( !CORBA::is_nil( prim ) );
  name = "primitive_";
  name += xdec( (long) prim->kind() );
  return name;
}

void DB::register_repoid( ParseNode* node, string &id )
{
  if( !(node->is_toplevel()) )
    _repoid_fname_map[ id ] = node->getFname();
}

void DB::register_anonym_type( ParseNode* node, CORBA::IDLType_ptr t )
{
  if( node->is_toplevel() )
    return;

  string pseudo_id;
  
  pseudo_id = gen_pseudo_repoid( t );

  _repoid_fname_map[ pseudo_id ] = node->getFname();
}

bool DB::repoid_defined( string& id )
{
  return _repoid_fname_map.count( id ) != 0;
}

string DB::get_fname_for_repoid( string &id )
{
  return _repoid_fname_map[ id ];
}

void DB::enter_scope( string& name )
{
  _current_scope.back().push_back( name );
  string last_prefix;
  last_prefix = _current_prefix.back();
  _current_prefix.push_back( last_prefix );
}

void DB::leave_scope()
{
  assert( _current_scope.back().size() > 0 );
  assert( _current_prefix.size() > 0 );
  _current_scope.back().pop_back();
  _current_prefix.pop_back();
}

void DB::enter_include_file ()
{
  string empty_prefix;
  _current_prefix.push_back( empty_prefix );

  vector<string> empty_scope;
  _current_scope.push_back (empty_scope);
}

void DB::leave_include_file ()
{
  assert (_current_scope.size() > 0);
  assert (_current_prefix.size() > 0);
  _current_scope.pop_back();
  _current_prefix.pop_back();
}

void DB::switch_prefix( string& name )
{
  _current_prefix.pop_back();
  _current_prefix.push_back( name );
}

string DB::get_current_prefix()
{
  string prefix;

  prefix = _current_prefix.back();
  
  for (VecVecString::size_type i=0; i < _current_scope.back().size(); i++) {
    if (prefix != "")
      prefix += "/";
    prefix += (_current_scope.back())[i];
  }

  if (prefix != "")
    prefix += "/";
  
  return prefix;
}

void DB::set_repo_version( string& name, string& version )
{
  _version_name.push_back( name );
  _version.push_back( version );
}

void DB::set_repo_id( string& name, string& id )
{
  _id_name.push_back( name );
  _id.push_back( id );
}

void DB::set_repoids( CORBA::Repository_ptr repo )
{
  for( vector<string>::size_type i = 0; i < _version.size(); i++ ) {
    CORBA::Contained_var c =
      repo->lookup( (char *) _version_name[ i ].c_str() );
    assert( !CORBA::is_nil( c ) );
    c->version( (char *) _version[ i ].c_str() );
  }
  for( vector<string>::size_type i0 = 0; i0 < _id.size(); i0++ ) {
    CORBA::Contained_var c = repo->lookup( (char *) _id_name[ i0 ].c_str() );
    assert( !CORBA::is_nil( c ) );
    c->id( (char *) _id[ i0 ].c_str() );
  }
}
