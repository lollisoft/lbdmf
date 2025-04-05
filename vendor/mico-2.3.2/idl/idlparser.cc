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
#include <mico/throw.h>
#include <mico/ir_impl.h>
#include <mico/template_impl.h>
#include "idlparser.h"
#include "error.h"



//-- IDLParser ----------------------------------------------------------

IDLParser::IDLParser( DB& db, bool feed_included_defs )
{
  _root               = db.get_parse_tree();
  _current_parse_node = NULL;
  _feed_included_defs = feed_included_defs;
  _repo               = CORBA::Repository::_narrow( db.get_idl_container() );
  assert( !CORBA::is_nil( _repo ) );
  _db                 = &db;
  _version            = "1.0";
}

IDLParser::~IDLParser()
{
  if( !_forward_dcl.empty() ) {
    cerr << IDLError( 1 )  << endl;
    exit( 1 );
  }
}

void IDLParser::collect()
{
  //  _root->print ();
#ifdef HAVE_EXCEPTIONS
  try {
#endif
    scan( _repo, _root );
#ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &ex ) {
    ParseNode *node = current_parse_node();
    assert( node != NULL );
    char *ident = node->getIdent();
    assert( ident != NULL );
    switch( ex->minor() ) {
    case MICO_IR_EXC_DUPLICATE_NAME:
      cerr << IDLError( 12, node, ident ) << endl;
      break;
    case MICO_IR_EXC_DUPLICATE_REPOID:
      cerr << IDLError( 13, node, ident ) << endl;
      break;
    case MICO_IR_EXC_DUPLICATE_LABEL:
      cerr << IDLError( 14, node, ident ) << endl;
      break;
    case MICO_IR_EXC_AMBIGUOUS_NAME:
      cerr << IDLError( 15, node, ident ) << endl;
      break;
    case MICO_IR_EXC_OVERLOADING:
      cerr << IDLError( 16, node, ident ) << endl;
      break;
    case MICO_IR_EXC_BAD_RECURSION:
      cerr << IDLError( 17, node, ident ) << endl;
      break;
    case MICO_IR_EXC_BAD_ONEWAY:
      cerr << IDLError( 18, node, ident ) << endl;
      break;
    case MICO_IR_EXC_DUPLICATE_MEMBER:
      cerr << IDLError( 19, node, ident ) << endl;
      break;
    case MICO_IR_EXC_BAD_UNION:
      cerr << IDLError( 21, node ) << endl;
      break;
    case MICO_IR_EXC_BAD_TYPE:
      // This error indicates that we tried to create an interface within
      // an interface. This error can not occur when the IR is fed via
      // the IDL compiler (because the IDL grammar already inhibits this).
      assert( 0 );
    default:
      cerr << IDLError( 31, node ) << endl;
      break;
    }
    exit( 1 );
  }
#endif
  
  _db->set_repoids( _repo );
}

void IDLParser::add_forward_dcl( char* id )
{
  _forward_dcl.insert( id );
}

void IDLParser::remove_forward_dcl( char* id )
{
  _forward_dcl.erase( id );
  _seen_iface.insert( id );
}

bool IDLParser::is_in_forward_dcl( char* id )
{
  return _forward_dcl.find( id ) != _forward_dcl.end();
}

bool IDLParser::is_iface_defined( char* id )
{
  return _seen_iface.find( id ) != _seen_iface.end();
}

void IDLParser::current_parse_node( ParseNode* node )
{
  _current_parse_node = node;
}

ParseNode* IDLParser::current_parse_node()
{
  return _current_parse_node;
}

char *IDLParser::gen_repo_id( ParseNode *node )
{
  string id;

  current_parse_node( node );

  id = "IDL:" + _db->get_current_prefix();
  id += node->getIdent();
  id += ":";
  id += _version;

  _db->register_repoid( node, id );

  return CORBA::string_dup( id.c_str() );
}


void IDLParser::scan( CORBA::Container_ptr con, ParseNode *node )
{
  if( node == NULL )
    return;

  ParseNodeType t = node->getType();
  
  if( t != exports && t != definitions && t != t_module &&
      t != interface_dcl && t != abstract_forward_dcl && t != forward_dcl &&
      t != value_forward_dcl && t != abstract_value_forward_dcl &&
      t != value_dcl && t != abstract_value_dcl && t != t_include &&
      !(node->is_toplevel()) && !_feed_included_defs )
    return;
  
  switch( node->getType() ) {
  case t_pragma:
    collectPragma( con, node );
    break;
  case t_include:
    collectInclude( con, node );
    break;
  case exports:
  case definitions:
    scan( con, node->getBranch( 1 ) );
    scan( con, node->getBranch( 2 ) );
    break;
  case t_module:
    collectModule( con, node );
    break;
  case struct_type:
    {
      CORBA::StructDef_var s = collectStruct( con, node );
      break;
    }
  case union_type:
    {
      CORBA::UnionDef_var u = collectUnion( con, node );
      break;
    }
  case const_dcl:
    collectConstDcl( con, node );
    break;
  case except_dcl:
    collectException( con, node );
    break;
  case forward_dcl:
    collectForwardDcl( con, node, FALSE );
    break;
  case abstract_forward_dcl:
    collectForwardDcl( con, node, TRUE );
    break;
  case interface_dcl:
    collectInterface( con, node );
    break;
  case t_typedef:
    collectTypedef( con, node );
    break;
  case t_native:
    collectNative( con, node );
    break;
  case op_dcl:
    collectMethod( con, node );
    break;
  case t_attribute:
    collectAttribute( con, node, CORBA::ATTR_NORMAL );
    break;
  case t_readonly_attribute:
    collectAttribute( con, node, CORBA::ATTR_READONLY );
    break;
  case enum_type:
    {
      CORBA::EnumDef_var e = collectEnum( con, node );
      break;
    }
  case value_forward_dcl:
    collectValueForwardDcl( con, node, FALSE );
    break;
  case abstract_value_forward_dcl:
    collectValueForwardDcl( con, node, TRUE );
    break;
  case value_box_dcl:
    collectValueBoxDcl( con, node );
    break;
  case value_dcl:
    collectValueDcl( con, node, FALSE );
    break;
  case abstract_value_dcl:
    collectValueDcl( con, node, TRUE );
    break;
  case public_state_member:
    collectStateMember (con, node, CORBA::PUBLIC_MEMBER);
    break;
  case private_state_member:
    collectStateMember (con, node, CORBA::PRIVATE_MEMBER);
    break;
  default:
    node->print();
    assert( 0 );
  }
}


void IDLParser::collectPragma( CORBA::Container_ptr con, ParseNode *node )
{
  string s;
  s = node->getIdent();
  
  // Strip off "#pragma"
  s = s.substr( 7 );
  
  int i = s.find_first_not_of( " " );
  if( !(i > 0) )
    return;
  int j = s.find_first_of( " ", i );
  if( !(j > i) )
    return;

  // Get pragma directive
  string dir;
  dir = s.substr( i, j - i );
  i = s.find_first_not_of( " ", j );
  check_pragma_syntax( i > 0, node );
  if( dir == "prefix" ) {
    check_pragma_syntax( s[ i ] == '"', node );
    j = s.find( '"', i + 1 );
    check_pragma_syntax( j > i, node );
   
    // Get prefix
    string prefix;
    prefix = s.substr( i + 1, j - i - 1 );
    _db->switch_prefix( prefix );
    return;
  }
  j = s.find( ' ', i );
  check_pragma_syntax( j > i, node );
  
  // Get name
  string name;
  name = s.substr( i, j - i );
  if( name[ 0 ] != ':' ) {
    // Name is relative, make it absolute
    CORBA::String_var tmp;
    switch( con->def_kind() ) {
    case CORBA::dk_Repository:
      tmp = (const char*) "";
      break;
    case CORBA::dk_Module:
    case CORBA::dk_Interface:
    case CORBA::dk_Struct:
    case CORBA::dk_Union:
    case CORBA::dk_Exception:
    case CORBA::dk_Value:
      {
	CORBA::Contained_var c = CORBA::Contained::_narrow( con );
	assert( !CORBA::is_nil( c ) );
	tmp = c->absolute_name();
	break;
      }
    default:
      assert( 0 );
    }
    name = tmp.in() + string("::") + name;
  }
  
  i = s.find_first_not_of( " ", j );
  if( dir == "version" ) {
    j = s.find_first_not_of( "0123456789.", i );
    if( j < 0 )
      j = s.length();
    string version;
    version = s.substr( i, j - i );
    _db->set_repo_version( name, version );
  } else if( dir == "ID" ){
    check_pragma_syntax( s[ i ] == '"', node );
    j = s.find( '"', i + 1 );
    check_pragma_syntax( j > i, node );
    string id;
    id = s.substr( i + 1, j - i - 1 );
    _db->set_repo_id( name, id );
  } else
    // On special request of Reza, unknown #pragma directives
    // do not result in an error
    return;
}

void IDLParser::check_pragma_syntax( bool condition, ParseNode *node )
{
  if( condition )
    return;
  cerr << IDLError( 22, node ) << endl;
  exit( 1 );
}

void IDLParser::collectInclude( CORBA::Container_ptr con, ParseNode *node )
{
  string s = node->getIdent();
  string num;
  string name;
  int i, j;

  assert( s[0] == '#' );
 
  if (s.find ("#line ") == 0)
    s = s.substr (6);
  else if (s[1] == ' ') 
    s = s.substr( 2 );
  else
    assert (0);

  // Get line number
  i = s.find_first_of( "0123456789" );
  assert( i >= 0 );
  j = s.find_first_not_of( "0123456789", i );
  assert( j > i );

  // strip off line number
  s = s.substr( j );

  // Get file name
  i = s.find( '"' );
  assert (i >= 0);

  j = s.find( '"', ++i );
  assert( j >= i );

  if (s.length() > j+2) {
    if (s[j+2] == '1')
      _db->enter_include_file();

    if (s[j+2] == '2')
      _db->leave_include_file();
  }
}

void IDLParser::collectModule( CORBA::Container_ptr con, ParseNode *node )
{
  CORBA::ModuleDef_var m;
  
  assert( node->getType() == t_module );

  CORBA::String_var repo_id = gen_repo_id( node );

  string name;
  name = node->getIdent();
  _db->enter_scope( name );

  if( node->is_toplevel() || _feed_included_defs ) {
    CORBA::Contained_var c = _repo->lookup_id( repo_id );
    if( !CORBA::is_nil( c ) ) {
      // We re-open an existing module
      m = CORBA::ModuleDef::_narrow( c );
      assert( !CORBA::is_nil( m ) );
    } else {
      // We create a new module
      m = con->create_module( repo_id, node->getIdent(), _version );
    }
    scan( m, node->getBranch( 1 ) );
  }
  
  _db->leave_scope();
}

void IDLParser::collectTypedef( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == t_typedef );
  CORBA::IDLType_var orig = collectType( con, node->getBranch( 1 ) );
  node = node->getBranch( 2 );
  while( node != NULL ) {
    assert( node->getType() == declarators );
    ParseNode *dcl = node->getBranch( 1 );
    if( dcl->getType() == simple_declarator ) {
      CORBA::String_var repo_id = gen_repo_id( dcl );
      CORBA::AliasDef_var a = con->create_alias( repo_id,
						 dcl->getIdent(),
						 _version,
						 orig );
    } else if( dcl->getType() == array_declarator ) {
      CORBA::ArrayDef_var arr = collectArray( con, orig, dcl->getBranch( 1 ) );
      CORBA::String_var repo_id = gen_repo_id( dcl );
      CORBA::AliasDef_var a = con->create_alias( repo_id,
						 dcl->getIdent(),
						 _version,
						 arr );
    } else
      assert( 0 );
    node = node->getBranch( 2 );
  }
}

void
IDLParser::collectNative( CORBA::Container_ptr con, ParseNode *node)
{
  assert( node->getType() == t_native );
  ParseNode *dcl = node->getBranch( 1 );
  assert( dcl->getType() == simple_declarator );
  CORBA::String_var repo_id = gen_repo_id( dcl );
  CORBA::NativeDef_var n = con->create_native( repo_id,
					       dcl->getIdent(),
					       _version );
}

CORBA::ArrayDef_ptr
IDLParser::collectArray( CORBA::Container_ptr con,
			 CORBA::IDLType_ptr orig, ParseNode *node )
{
  assert( node->getType() == fixed_array_sizes );
  Const c = collectConst( con, node->getBranch( 1 ) );
  CORBA::ULong length = c.get_int();
  CORBA::IDLType_var elem;
  if( node->getBranch( 2 ) != NULL ) {
    elem = collectArray( con, orig, node->getBranch( 2 ) );
  } else {
    elem = CORBA::IDLType::_duplicate( orig );
  }
  CORBA::ArrayDef_ptr arr = _repo->create_array( length, elem );
  _db->register_anonym_type( node, arr );
  return arr;
}

void IDLParser::collectConstDcl( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == const_dcl );

  CORBA::IDLType_var type;
  ParseNode* t = node->getBranch( 1 );

  if( t->getType() == fixed_pt_type ) {
    collectConstFixedDcl( con, node );
    return;
  }
  
  if( t->getType() == scoped_name ) {
    // Type decl is a scoped name. Must refer to another const
    CORBA::Contained_var contained;
    contained = con->find( collectScopedName( t ) );
    if( CORBA::is_nil( contained ) ) {
      cerr << IDLError( 2, t, t->getIdent() ) << endl;
      exit( 1 );
    }
    CORBA::AliasDef_var alias = CORBA::AliasDef::_narrow( contained );
    if( CORBA::is_nil( alias ) ) {
      cerr << IDLError( 3, t, t->getIdent() ) << endl;
      exit( 1 );
    }
    do {
      type = alias->original_type_def();
      alias = CORBA::AliasDef::_narrow( type );
    } while( !CORBA::is_nil( alias ) );
  } else {
    type = collectType( con, t );
  }
  
  CORBA::TypeCode_var tc = type->type();
  switch( tc->kind() ) {
  case CORBA::tk_float:
  case CORBA::tk_double:
  case CORBA::tk_long:
  case CORBA::tk_short:
  case CORBA::tk_ulong:
  case CORBA::tk_ushort:
  case CORBA::tk_boolean:
  case CORBA::tk_string:
  case CORBA::tk_wstring:
  case CORBA::tk_char:
  case CORBA::tk_octet:
  case CORBA::tk_wchar:
  case CORBA::tk_longlong:
  case CORBA::tk_ulonglong:
  case CORBA::tk_longdouble:
    break;
  default:
    cerr << IDLError( 4, t, t->getIdent() ) << endl;
    exit( 1 );
  }

  Const const_value = collectConst( con, node->getBranch( 2 ) );
  CORBA::Any val = const_value.get_value( tc );
  
  CORBA::String_var repo_id = gen_repo_id( node );
  CORBA::ConstantDef_var c = con->create_constant( repo_id,
						   node->getIdent(),
						   _version,
						   type,
						   val );
}

/*
 * Const dcl of a fixed has to be handled differently. Consider:
 *   const fixed f = 123.45D;
 * here, the type dcl is incomplete. The consequence is, that
 * for fixed const dcl we have to collect the value first
 * and then create a type in the IR.
 */
void IDLParser::collectConstFixedDcl( CORBA::Container_ptr con,
				      ParseNode *node )
{
  assert( node->getType() == const_dcl );

  CORBA::IDLType_var type;
  ParseNode* t = node->getBranch( 1 );

  Const const_value = collectConst( con, node->getBranch( 2 ) );

  CORBA::LongDouble ld;
  CORBA::Boolean r = ( const_value.get_any() >>= ld );
  assert (r);

  FixedBase f (ld);
  
  type = _repo->create_fixed( f.fixed_digits(), f.fixed_scale() );
  _db->register_anonym_type( t, type );
  
  CORBA::TypeCode_var tc = type->type();

  CORBA::Any val = const_value.get_value( tc );
  
  CORBA::String_var repo_id = gen_repo_id( node );
  CORBA::ConstantDef_var c = con->create_constant( repo_id,
						   node->getIdent(),
						   _version,
						   type,
						   val );
}

void IDLParser::collectException( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == except_dcl );

  CORBA::String_var repo_id = gen_repo_id( node );

  string name;
  name = node->getIdent();
  _db->enter_scope( name );
  
  CORBA::StructMemberSeq members;
  CORBA::ExceptionDef_var e = con->create_exception( repo_id,
						     node->getIdent(),
						     _version,
						     members );
  collectStructMembers( e, node->getBranch( 1 ), members );
  e->members( members );
  current_parse_node( node );
  _db->leave_scope();
}

CORBA::StructDef_ptr
IDLParser::collectStruct( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == struct_type );

  CORBA::String_var repo_id = gen_repo_id( node );

  string name;
  name = node->getIdent();
  _db->enter_scope( name );

  CORBA::StructMemberSeq members;
  CORBA::StructDef_ptr s = con->create_struct( repo_id,
					       node->getIdent(),
					       _version,
					       members );
  collectStructMembers( s, node->getBranch( 1 ), members );
  s->members( members );
  current_parse_node( node );
  _db->leave_scope();
  return s;
}

void IDLParser::collectStructMembers( CORBA::Container_ptr con,
				      ParseNode *n, CORBA::StructMemberSeq &m )
{
  if( n == NULL )
    return;
  assert( n->getType() == member_list );
  collectStructMember( con, n->getBranch( 1 ), m );
  n = n->getBranch( 2 );
  if( n != NULL )
    collectStructMembers( con, n, m );
}

void IDLParser::collectStructMember( CORBA::Container_ptr con,
				     ParseNode *n, CORBA::StructMemberSeq &m )
{
  if (n->getType() == t_pragma) {
    collectPragma (con, n);
    return;
  }
  if (n->getType() == t_include) {
    collectInclude (con, n);
    return;
  }
  assert( n->getType() == member );
  CORBA::IDLType_var t = collectType( con, n->getBranch( 1 ) );
  collectStructMemberDeclarators( con, n->getBranch( 2 ), t, m );
}

void IDLParser::collectStructMemberDeclarators( CORBA::Container_ptr con,
						ParseNode *n,
						CORBA::IDLType_ptr t,
						CORBA::StructMemberSeq &m )
{
  assert( n->getType() == declarators );
  collectStructMemberDeclarator( con, n->getBranch( 1 ), t, m );
  n = n->getBranch( 2 );
  if( n != NULL )
    collectStructMemberDeclarators( con, n, t, m );
}

void IDLParser::collectStructMemberDeclarator( CORBA::Container_ptr con,
					       ParseNode *n,
					       CORBA::IDLType_ptr t,
					       CORBA::StructMemberSeq &m )
{
  CORBA::StructMember member;
  int i = m.length();
  m.length( i + 1 );

  switch( n->getType() ) {
  case simple_declarator:
    member.name     = CORBA::string_dup( n->getIdent() );
    member.type     = CORBA::_tc_void;   //[6.5.10]
    member.type_def = CORBA::IDLType::_duplicate( t );
    m[ i ] = member;
    break;
  case array_declarator:
    member.name     = CORBA::string_dup( n->getIdent() );
    member.type     = CORBA::_tc_void;   //[6.5.10]
    member.type_def = collectArray( con, t, n->getBranch( 1 ) );
    m[ i ] = member;
    break;
  default:
    assert( 0 );
  }
}

CORBA::UnionDef_ptr
IDLParser::collectUnion( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == union_type );

  CORBA::String_var repo_id = gen_repo_id( node );

  string name;
  name = node->getIdent();
  _db->enter_scope( name );

  CORBA::IDLType_var switch_type = CORBA::IDLType::_nil();

  CORBA::UnionMemberSeq members;
  CORBA::UnionDef_ptr u = con->create_union( repo_id,
					     node->getIdent(),
					     _version,
					     switch_type,
					     members );

#if 1
  switch_type = collectUnionSwitchTypeSpec( u, node->getBranch( 1 ) );
  u->discriminator_type_def( switch_type );
#endif
  
  collectUnionMembers( u, node->getBranch( 2 ), switch_type, members );
  current_parse_node( node );
  u->members( members );
  _db->leave_scope();
  return u;
}

CORBA::IDLType_ptr
IDLParser::collectUnionSwitchTypeSpec( CORBA::Container_ptr con,
				       ParseNode *node )
{
  CORBA::IDLType_ptr switch_type = collectType( con, node );
  CORBA::IDLType_var resolv_type = CORBA::IDLType::_duplicate( switch_type );
  while( resolv_type->def_kind() == CORBA::dk_Alias ) {
    CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( resolv_type );
    assert( !CORBA::is_nil( a ) );
    resolv_type = a->original_type_def();
  }
  switch( resolv_type->def_kind() ) {
  case CORBA::dk_Enum:
    break;
  case CORBA::dk_Primitive:
    {
      CORBA::PrimitiveDef_var p = CORBA::PrimitiveDef::_narrow( resolv_type );
      assert( !CORBA::is_nil( p ) );
      switch( p->kind() ) {
      case CORBA::pk_long:
      case CORBA::pk_ulong:
      case CORBA::pk_longlong:
      case CORBA::pk_ulonglong:
      case CORBA::pk_short:
      case CORBA::pk_ushort:
      case CORBA::pk_char:
      case CORBA::pk_wchar:
      case CORBA::pk_boolean:
	break;
      default:
	cerr << IDLError( 5, node ) << endl;
	exit( 1 );
      }
      break;
    }
  default:
    cerr << IDLError( 5, node ) << endl;
    exit( 1 );
  }
  return switch_type;
}

void
IDLParser::collectUnionElementSpec( CORBA::Container_ptr con,
				    ParseNode *node,
				    CORBA::UnionMember& member )
{
  assert( node->getType() == _case );
  while( node->getBranch( 3 ) == NULL ) {
    node = node->getBranch( 2 );
    assert( node->getType() == _case );
  }
  node = node->getBranch( 3 );
  assert( node->getType() == element_spec );
  CORBA::IDLType_var type_spec = collectType( con, node->getBranch( 1 ) );
  node = node->getBranch( 2 );
  switch( node->getType() ) {
  case simple_declarator:
    member.name     = CORBA::string_dup( node->getIdent() );
    member.type     = CORBA::_tc_void;   //[6.5.11]
    member.type_def = CORBA::IDLType::_duplicate( type_spec );
    break;
  case array_declarator:
    member.name     = CORBA::string_dup( node->getIdent() );
    member.type     = CORBA::_tc_void;   //[6.5.11]
    member.type_def = collectArray( con, type_spec, node->getBranch( 1 ) );
    break;
  default:
    assert( 0 );
  }
}

void
IDLParser::collectUnionCaseLabel( CORBA::Container_ptr con,
				  ParseNode *node,
				  CORBA::IDLType_ptr switch_type,
				  CORBA::UnionMember& member ) 
{
  if( node->getType() == t_default ) {
    member.label <<= CORBA::Any::from_octet( 0 );
  } else {
    CORBA::IDLType_var resolv_type = CORBA::IDLType::_duplicate( switch_type );
    while( resolv_type->def_kind() == CORBA::dk_Alias ) {
      CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( resolv_type );
      assert( !CORBA::is_nil( a ) );
      resolv_type = a->original_type_def();
    }
    switch( resolv_type->def_kind() ) {
    case CORBA::dk_Enum:
      {
	if( node->getType() != scoped_name ) {
	  cerr << IDLError( 20, node ) << endl;
	  exit( 1 );
	}
	CORBA::TypeCode_var enum_tc = resolv_type->type();
	enum_tc = CORBA::TypeCode::_duplicate( enum_tc->unalias() );

	string label;
	string scoped_name = node->getIdent();
	if( (int) scoped_name.find( "::" ) >= 0 ) {
	  // We have a scoped name. Check that the discriminator
	  // type is defined in the scope that is defined through
	  // this scoped name
	  string scoped_enum = scoped_name;
	  int i = scoped_enum.find_last_of( ":" );
	  scoped_enum = scoped_enum.substr( 0, i+1 );
	  CORBA::EnumDef_var enum_switch_type =
	    CORBA::EnumDef::_narrow( resolv_type );
	  assert( !CORBA::is_nil( enum_switch_type ) );
	  CORBA::String_var enum_name = enum_switch_type->name();
	  scoped_enum += enum_name;
	  CORBA::Contained_var e = con->find( scoped_enum.c_str() );
	  if( CORBA::is_nil( e ) || !e->_is_equivalent( resolv_type ) ) {
	    cout << IDLError( 11, node, scoped_name.c_str(),
  			                scoped_enum.c_str() ) << endl;
	    exit( 1 );
	  }
	  label = scoped_name.substr( i+1 );
	} else {
	  label = scoped_name;
	}

	CORBA::ULong j;
	for( j = 0; j < enum_tc->member_count(); j++ ) {
	  if( !strcmp( enum_tc->member_name( j ), label.c_str() ) ) {
	    member.label.set_type( enum_tc );
	    CORBA::Boolean r = member.label.enum_put( j );
	    assert (r);
	    break;
	  }
	}
	if( j >= enum_tc->member_count() ) {
	  CORBA::Contained_var c = CORBA::Contained::_narrow( switch_type );
	  assert( !CORBA::is_nil( c ) );
	  CORBA::String_var name = c->absolute_name();
	  cerr << IDLError( 11, node, label.c_str(), (char*) name ) << endl;
	  exit( 1 );
	}
      }
      break;
    case CORBA::dk_Primitive:
      {
	Const c = collectConst( con, node );
	CORBA::TypeCode_var tc = resolv_type->type();
	CORBA::Any a = c.get_value( tc );
	member.label = a;
      }
      break;
    default:
      break;
    }
  }
}
  
void
IDLParser::collectUnionCases( CORBA::Container_ptr con,
			      ParseNode *node,
			      CORBA::IDLType_ptr switch_type,
			      CORBA::UnionMemberSeq& members )
{
  if (node->getBranch( 4 ) != NULL) {
    collectPragma (con, node->getBranch( 4 ));
  }

  assert( node->getType() == _case );

  CORBA::UnionMember member;
  collectUnionElementSpec( con, node, member );
  collectUnionCaseLabel( con, node->getBranch( 1 ), switch_type, member );

  int i = members.length();
  members.length( i + 1 );
  members[ i ] = member;
  
  if( node->getBranch( 2 ) != NULL )
    collectUnionCases( con, node->getBranch( 2 ), switch_type, members );
}

void
IDLParser::collectUnionMembers( CORBA::Container_ptr con,
				ParseNode *node,
				CORBA::IDLType_ptr switch_type,
				CORBA::UnionMemberSeq& members )
{
  assert( node->getType() == switch_body );
  collectUnionCases( con, node->getBranch( 1 ), switch_type, members );
  if( node->getBranch( 2 ) != NULL )
    collectUnionMembers( con, node->getBranch( 2 ), switch_type, members );
}

void
IDLParser::collectForwardDcl( CORBA::Container_ptr con, ParseNode *node,
			      CORBA::Boolean is_abstract )
{
  assert( node->getType() == forward_dcl ||
	  node->getType() == abstract_forward_dcl );
  
  CORBA::String_var repo_id = gen_repo_id( node );

  if( is_iface_defined( repo_id ) )
    return;

  if( !is_in_forward_dcl( repo_id ) ) {
    CORBA::InterfaceDef_var in;
 
    if( node->is_toplevel() || _feed_included_defs ) {
      CORBA::InterfaceDefSeq base_interfaces; // Leave empty for now
  
      in = con->create_interface( repo_id,
				  node->getIdent(),
				  _version,
				  base_interfaces,
				  is_abstract );
    } else {
      /*
       * Since we don't feed included defs, we only have to make
       * sure that no other IDL type with the same identifier
       * exists (the only exception being that there is another
       * interface with the same name).
       */
      CORBA::ContainedSeq_var c = con->find_name( node->getIdent(),
						  CORBA::dk_all );
      // there can be at most one IDL type with that name in the
      // current scope
      assert( c->length() <= 1 );
      if (c->length() == 1) {
	in = CORBA::InterfaceDef::_narrow( c[ (MICO_ULong) 0 ] );
	if( CORBA::is_nil( in ) ) {
	  cerr << IDLError( 23, node, node->getIdent() ) << endl;
	  exit( 1 );
	}
      }
      else {
	return;
      }
    }

    CORBA::String_var id = in->id();
    add_forward_dcl( id );
  }
}

void IDLParser::collectInterface( CORBA::Container_ptr con, ParseNode *node )
{
  CORBA::InterfaceDef_var in;
 
  ParseNode *header = node->getBranch( 1 );

  CORBA::String_var repo_id = gen_repo_id( header );

  string name;
  name = header->getIdent();
  _db->enter_scope( name );
  
  CORBA::String_var id;

  CORBA::InterfaceDefSeq base_interfaces; // Leave empty for now
  CORBA::Boolean is_abstract;

  if (header->getType() == abstract_interface_header) {
    is_abstract = TRUE;
  }
  else {
    is_abstract = FALSE;
  }

  if( node->is_toplevel() || _feed_included_defs ) {
    CORBA::ContainedSeq_var c = con->find_name( header->getIdent(),
					   CORBA::dk_Interface );
    if( c->length() > 0 ) {
      id = c[ (MICO_ULong)0 ]->id();
      if( !is_in_forward_dcl( id ) ) {
	cerr << IDLError( 12, header, header->getIdent() ) << endl;
	exit( 1 );
      }
    }

    in = con->create_interface( repo_id,
				header->getIdent(),
				_version,
				base_interfaces,
				is_abstract );
  } else {
    /*
     * Since we don't feed included defs, we only have to make
     * sure that no other IDL type with the same identifier
     * exists (the only exception being that there is another
     * interface with the same name).
     */
    CORBA::ContainedSeq_var c = con->find_name( header->getIdent(),
						CORBA::dk_all );
    // there can be at most one IDL type with that name in the
    // current scope
    assert( c->length() <= 1 );
    if( c->length() > 0 ) {
      in = CORBA::InterfaceDef::_narrow( c[ (MICO_ULong) 0 ] );
      if( CORBA::is_nil( in ) ) {
	cerr << IDLError( 23, header, header->getIdent() ) << endl;
	exit( 1 );
      }
    }
    else {
      _db->leave_scope();
      return;
    }
  }

  id = in->id();
  remove_forward_dcl( id );

  header = header->getBranch( 1 );
  
  while( header != NULL ) {
    ParseNode* node_base = header->getBranch( 1 );
    CORBA::IDLType_var t = collectType( con, node_base );
    CORBA::InterfaceDef_ptr base =
      CORBA::InterfaceDef::_narrow( t );
    if( CORBA::is_nil( base ) ) {
      cerr << IDLError( 8, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    CORBA::String_var id = base->id();
    if( is_in_forward_dcl( id ) ) {
      cerr << IDLError( 9, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    if( in->_is_equivalent( base ) ) {
      cerr << IDLError( 25, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    if( in->is_abstract() && !base->is_abstract() ) {
      cerr << IDLError( 30, node_base, node_base->getIdent(), id.in() )
	   << endl;
      exit( 1 );
    }
    int i = base_interfaces.length();
    base_interfaces.length( i + 1 );
    base_interfaces[ i ] = base;
    header = header->getBranch( 2 );
  }
  
  if( node->is_toplevel() || _feed_included_defs ) {
    in->base_interfaces( base_interfaces );
    scan( in, node->getBranch( 2 ) );
  }

  _db->leave_scope();
}

void
IDLParser::collectRaisesExpr( CORBA::Container_ptr con, ParseNode *node,
			      CORBA::ExceptionDefSeq &exs )
{
  if( node == NULL )
    return;
  
  assert( node->getType() == raises_expr );
  node = node->getBranch( 1 );
  while( node != NULL ) {
    CORBA::Contained_var c;
    c = con->find( collectScopedName( node->getBranch( 1 ) ) );
    if( CORBA::is_nil( c ) ) {
      cerr << IDLError( 2, node->getBranch( 1 ),
			node->getBranch( 1 )->getIdent() ) << endl;
      exit( 1 );
    }
    CORBA::ExceptionDef_ptr ex = CORBA::ExceptionDef::_narrow( c );
    if( CORBA::is_nil( ex ) ) {
      cerr << IDLError( 6, node->getBranch( 1 ),
			node->getBranch( 1 )->getIdent() ) << endl;
      exit( 1 );
    }
    int i = exs.length();
    exs.length( i + 1 );
    exs[ i ] = ex;
    node = node->getBranch( 2 );
  }
}

void
IDLParser::collectContextExpr( ParseNode *node, CORBA::ContextIdSeq &ctx )
{
  while( node != NULL ) {
    assert( node->getType() == string_literals );
    int i = ctx.length();
    ctx.length( i + 1 );
    ctx[ i ] = (const char *) node->getIdent();
    node = node->getBranch( 1 );
  }
}

void
IDLParser::collectMethod( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == op_dcl );
  // con must be an InterfaceDef or a ValueDef
  CORBA::InterfaceDef_var interf = CORBA::InterfaceDef::_narrow( con );
  CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( con );
  assert( !CORBA::is_nil( interf ) || !CORBA::is_nil( val ) );

  // Get operation attribute
  CORBA::OperationMode op_mode;
  if( node->getBranch( 1 ) == NULL )
    op_mode = CORBA::OP_NORMAL;
  else
    op_mode = CORBA::OP_ONEWAY;
  
  CORBA::ParDescriptionSeq params;
  ParseNode *p = node->getBranch( 3 );
  if( p != NULL ) {
    // This method has parameters
    int i = 0;
    
    while( p != NULL ) {
      assert( p->getType() == param_dcls );
      ParseNode *q;
      CORBA::ParameterMode mode;    // in, out, inout attribute
      CORBA::IDLType_ptr idl_type;  // type specification
      
      q = p->getBranch( 1 );
      assert( q->getType() == param_dcl );
      switch( q->getBranch( 1 )->getType() ) {
      case t_in:
	mode = CORBA::PARAM_IN;
	break;
      case t_out:
	mode = CORBA::PARAM_OUT;
	break;
      case t_inout:
	mode = CORBA::PARAM_INOUT;
	break;
      default:
	assert( 0 );
      }
      idl_type = collectType( con, q->getBranch( 2 ) );
      CORBA::ParameterDescription param;
      param.name = CORBA::string_dup( q->getBranch( 3 )->getIdent() );
      param.mode = mode;
      param.type = idl_type->type();
      param.type_def = idl_type;

      params.length( i + 1 );
      params[ i++ ] = param;
      p = p->getBranch( 2 );
    }
  }

  // Look for return value
  CORBA::TypeCode_var op_result_type;
  CORBA::IDLType_var op_result;
  
  p = node->getBranch( 2 );
  assert( p != NULL );
  if( p->getType() == t_void ) {
    op_result = _repo->get_primitive( CORBA::pk_void );
  } else {
    assert( p->getType() == op_type_spec );
    op_result = collectType( con, p->getBranch( 1 ) );
  }

  CORBA::ExceptionDefSeq exceptions;
  if( node->getBranch( 4 ) ) {
    collectRaisesExpr( con, node->getBranch( 4 ), exceptions );
  }
    
  CORBA::ContextIdSeq contexts;
  if( node->getBranch( 5 ) )
    collectContextExpr( node->getBranch( 5 ), contexts );
  
  CORBA::String_var repo_id = gen_repo_id( node );;
  CORBA::OperationDef_var op;
  
  if (!CORBA::is_nil (interf)) {
    op = interf->create_operation( repo_id,
				   node->getIdent(),
				   _version,
				   op_result,
				   op_mode,
				   params,
				   exceptions,
				   contexts );
  }
  else {
    op = val->create_operation( repo_id,
				node->getIdent(),
				_version,
				op_result,
				op_mode,
				params,
				exceptions,
				contexts );
  }
}

void
IDLParser::collectAttribute( CORBA::Container_ptr con, ParseNode *node,
			     CORBA::AttributeMode mode )
{
  assert( node->getType() == t_attribute ||
	  node->getType() == t_readonly_attribute );
  
  // con must be an InterfaceDef or a ValueDef
  CORBA::InterfaceDef_var interf = CORBA::InterfaceDef::_narrow( con );
  CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( con );
  assert( !CORBA::is_nil( interf ) || !CORBA::is_nil( val ) );
  
  CORBA::IDLType_var idl_type;
  
  idl_type = collectType( con, node->getBranch( 1 ) );

  ParseNode *p;
  p = node->getBranch( 2 );
  do {
    assert( p->getType() == simple_declarators );
    char *name = p->getBranch( 1 )->getIdent();
    CORBA::String_var repo_id = gen_repo_id( p->getBranch( 1 ) );
    CORBA::AttributeDef_var attr;

    if (!CORBA::is_nil (interf)) {
      interf->create_attribute( repo_id,
				name,
				_version,
				idl_type,
				mode );
    }
    else {
      val->create_attribute( repo_id,
			     name,
			     _version,
			     idl_type,
			     mode );
    }

    p = p->getBranch( 2 );
  } while( p != NULL );
}

void
IDLParser::collectValueForwardDcl( CORBA::Container_ptr con, ParseNode *node,
				   CORBA::Boolean is_abstract )
{
  assert( node->getType() == value_forward_dcl ||
	  node->getType() == abstract_value_forward_dcl );
  
  CORBA::String_var repo_id = gen_repo_id( node );

  if( is_iface_defined( repo_id ) )
    return;

  if( !is_in_forward_dcl( repo_id ) ) {
    CORBA::ValueDef_var in;
 
    if( node->is_toplevel() || _feed_included_defs ) {
      CORBA::ValueDefSeq abstract_base_values; // Leave empty for now
      CORBA::InterfaceDefSeq supported_interfaces; // dito
      CORBA::InitializerSeq initializers;
  
      in = con->create_value( repo_id,
			      node->getIdent(),
			      _version,
			      FALSE,
			      is_abstract,
			      CORBA::ValueDef::_nil(),
			      FALSE,
			      abstract_base_values,
			      supported_interfaces,
			      initializers );
    } else {
      /*
       * Since we don't feed included defs, we only have to make
       * sure that no other IDL type with the same identifier
       * exists (the only exception being that there is another
       * interface with the same name).
       */
      CORBA::ContainedSeq_var c = con->find_name( node->getIdent(),
						  CORBA::dk_all );
      // there can be at most one IDL type with that name in the
      // current scope
      assert( c->length() <= 1 );
      if( c->length() > 0 ) {
	in = CORBA::ValueDef::_narrow( c[ (MICO_ULong) 0 ] );
	if( CORBA::is_nil( in ) ) {
	  cerr << IDLError( 23, node, node->getIdent() ) << endl;
	  exit( 1 );
	}
      }
      else {
	return;
      }
    }
    
    CORBA::String_var id = in->id();
    add_forward_dcl( id );
  }
}

void
IDLParser::collectValueBoxDcl( CORBA::Container_ptr con, ParseNode *node )
{
  assert( node->getType() == value_box_dcl );
  CORBA::IDLType_var orig = collectType( con, node->getBranch( 1 ) );

  if( node->is_toplevel() || _feed_included_defs ) {
    CORBA::String_var repo_id = gen_repo_id( node );
    CORBA::ValueBoxDef_var v = con->create_value_box ( repo_id,
						       node->getIdent(),
						       _version,
						       orig );
  }
}

void
IDLParser::collectValueDcl( CORBA::Container_ptr con, ParseNode *node,
			    CORBA::Boolean is_abstract )
{
  assert( node->getType() == value_dcl ||
	  node->getType() == abstract_value_dcl );

  ParseNode * header = node->getBranch (1);

  assert (header->getType() == value_header ||
	  header->getType() == custom_value_header);

  CORBA::String_var repo_id = gen_repo_id( header );

  string name;
  name = header->getIdent();
  _db->enter_scope (name);

  CORBA::ValueDef_var val;
  CORBA::InterfaceDefSeq supported_interfaces;
  CORBA::ValueDef_var base_value;
  CORBA::ValueDefSeq abstract_base_values;
  CORBA::InitializerSeq initializers;
  CORBA::Boolean is_custom;
  CORBA::Boolean is_truncatable;

  if (header->getType() == custom_value_header) {
    is_custom = TRUE;
  }
  else {
    is_custom = FALSE;
  }

  if( node->is_toplevel() || _feed_included_defs ) {
    CORBA::ContainedSeq_var c = con->find_name( name.c_str(),
						CORBA::dk_Value );

    if( c->length() > 0 ) {
      CORBA::String_var id;
      id = c[ (MICO_ULong)0 ]->id();
      if( !is_in_forward_dcl( id ) ) {
	cerr << IDLError( 12, header, header->getIdent() ) << endl;
	exit( 1 );
      }
    }

    val = con->create_value( repo_id,
			     header->getIdent(),
			     _version,
			     FALSE,
			     is_abstract,
			     CORBA::ValueDef::_nil(),
			     FALSE,
			     abstract_base_values,
			     supported_interfaces,
			     initializers );
  } else {
    /*
     * Since we don't feed included defs, we only have to make
     * sure that no other IDL type with the same identifier
     * exists (the only exception being that there is another
     * interface with the same name).
     */
    CORBA::ContainedSeq_var c = con->find_name( header->getIdent(),
						CORBA::dk_all );
    // there can be at most one IDL type with that name in the
    // current scope
    assert( c->length() <= 1 );
    if( c->length() > 0 ) {
      val = CORBA::ValueDef::_narrow( c[ (MICO_ULong) 0 ] );
      if( CORBA::is_nil( val ) ) {
	cerr << IDLError( 23, header, header->getIdent() ) << endl;
	exit( 1 );
      }
    }
    else {
      _db->leave_scope();
      return;
    }
  }

  CORBA::String_var id = val->id();
  remove_forward_dcl( id );

  header = header->getBranch (1);
  // first element may contain supported interfaces
  if (header != NULL) {
    assert (header->getType() == value_inheritance_spec);
    ParseNode * sins = header->getBranch (4);
    bool have_concrete_if = false;

    while (sins != NULL) {
      assert (sins->getType() == scoped_names);
      ParseNode * sin = sins->getBranch (1);
      CORBA::IDLType_var t = collectType (con, sin);
      CORBA::InterfaceDef_ptr sif = CORBA::InterfaceDef::_narrow (t);

      if (!sif->is_abstract()) {
	if (have_concrete_if) {
	  cerr << IDLError( 31 ) << endl;
	  exit( 1 );
	}
	have_concrete_if = true;
      }

      CORBA::String_var bid = sif->id();
      if( is_in_forward_dcl( bid ) ) {
	cerr << IDLError( 9, sin, sin->getIdent() ) << endl;
	exit( 1 );
      }

      CORBA::ULong i = supported_interfaces.length();
      supported_interfaces.length (i+1);
      supported_interfaces[i] = sif;
      sins = sins->getBranch (2);
    }
  }

  // first element may be a concrete (non-abstract) value

  if (header != NULL) {
    ParseNode * cvt;
    if ((cvt = header->getBranch (1)) == NULL) {
      if ((cvt = header->getBranch (2)) != NULL) {
	is_truncatable = TRUE;
      }
      else {
	is_truncatable = FALSE;
      }
    }
    else {
      is_truncatable = FALSE;
    }
    
    if (cvt != NULL) {
      if (is_custom && is_truncatable) {
	cerr << IDLError(26, cvt, name.c_str()) << endl;
	exit (1);
      }
    
      if (is_abstract && is_truncatable) {
	cerr << IDLError(27, cvt, name.c_str()) << endl;
	exit (1);
      }

      if (cvt->getType() == scoped_names) {
	cvt = cvt->getBranch (1);
      }
    
      assert (cvt->getType() == scoped_name ||
	      cvt->getType() == t_valuebase);
    
      if (cvt->getType() == scoped_name) {
	CORBA::IDLType_var t = collectType (con, cvt);
	base_value = CORBA::ValueDef::_narrow (t);
	if (CORBA::is_nil (base_value)) {
	  cerr << IDLError (8, cvt, cvt->getIdent()) << endl;
	  exit (1);
	}
	CORBA::String_var bid = base_value->id();
	if (is_in_forward_dcl (bid)) {
	  cerr << IDLError (9, cvt, cvt->getIdent()) << endl;
	  exit (1);
	}
	if (base_value->_is_equivalent (val)) {
	  cerr << IDLError (25, cvt, cvt->getIdent()) << endl;
	  exit (1);
	}
	if (is_abstract && !base_value->is_abstract()) {
	  cerr << IDLError (28, cvt, name.c_str(), cvt->getIdent()) << endl;
	  exit (1);
	}
	if (is_truncatable && base_value->is_abstract()) {
	  cerr << IDLError (29, cvt, name.c_str(), cvt->getIdent()) << endl;
	  exit (1);
	}
	if (base_value->is_abstract()) {
	  // not a concrete base
	  abstract_base_values.length (1);
	  abstract_base_values[0] = CORBA::ValueDef::_duplicate (base_value);
	  base_value = CORBA::ValueDef::_nil ();
	}
      }
      else {
	// inherits from ValueBase
	base_value = CORBA::ValueDef::_nil ();
      }
    }
    header = header->getBranch (3);
  }
  else {
    // does not inherit anything
    base_value = CORBA::ValueDef::_nil ();
    is_truncatable = FALSE;
  }

  // scan abstract base values
  while (header != NULL) {
    assert (header->getType() == scoped_names);
    ParseNode * node_base = header->getBranch (1);
    CORBA::IDLType_var t = collectType (con, node_base);
    CORBA::ValueDef_ptr base =
      CORBA::ValueDef::_narrow (t);

    if (CORBA::is_nil (base)) {
      cerr << IDLError( 8, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    CORBA::String_var bid = base->id();
    if (is_in_forward_dcl (bid)) {
      cerr << IDLError( 9, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    if (val->_is_equivalent (base)) {
      cerr << IDLError( 25, node_base, node_base->getIdent() ) << endl;
      exit( 1 );
    }
    CORBA::ULong i = abstract_base_values.length();
    abstract_base_values.length (i+1);
    abstract_base_values[i] = base;
    header = header->getBranch (2);
  }

  /*
   * Done with header
   *
   * We can't call scan() recursively, because we must collect
   * initializers separately.
   */

  if (node->is_toplevel() || _feed_included_defs) {
    // scan members
    ParseNode * elements = node->getBranch (2);
    while (elements != NULL) {
      assert (elements->getType() == value_elements ||
	      elements->getType() == exports);

      ParseNode * element = elements->getBranch (1);

      if (element->getType() == init_dcl) {
	CORBA::Initializer initializer;
	CORBA::ULong icount;

	initializer.name = (const char *) element->getIdent();
	ParseNode * idcl = element->getBranch (1);
	assert (idcl->getType() == init_param_decls);

	while (idcl != NULL) {
	  ParseNode * ipd = idcl->getBranch (1);
	  CORBA::IDLType_var t = collectType (val, ipd->getBranch (1));
	  assert (ipd->getBranch(2)->getType() == simple_declarator);
	  const char * name = ipd->getBranch(2)->getIdent();
	  icount = initializer.members.length();
	  initializer.members.length (icount+1);
	  CORBA::StructMember inelem;
	  inelem.name = CORBA::string_dup (name);
	  inelem.type = CORBA::_tc_void;
	  inelem.type_def = CORBA::IDLType::_duplicate (t);
	  initializer.members[icount] = inelem;
	  idcl = idcl->getBranch (2);
	}
	icount = initializers.length();
	initializers.length (icount + 1);
	initializers[icount] = initializer;
      }
      else {
	scan (val, element);
      }

      elements = elements->getBranch (2);
    }

    // set attributes
    val->supported_interfaces (supported_interfaces);
    val->initializers (initializers);
    val->base_value (base_value);
    val->abstract_base_values (abstract_base_values);
    val->is_abstract (is_abstract);
    val->is_custom (is_custom);
    val->is_truncatable (is_truncatable);
  }

  _db->leave_scope();
}

void
IDLParser::collectStateMember (CORBA::Container_ptr con, ParseNode *node,
			       CORBA::Visibility vis)
{
  assert (node->getType() == public_state_member ||
	  node->getType() == private_state_member);

  // con must be a ValueDef
  CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( con );
  assert( !CORBA::is_nil( val ) );

  CORBA::IDLType_var idl_type = collectType (con, node->getBranch (1));
  node = node->getBranch (2);

  while (node != NULL) {
    assert (node->getType() == declarators);
    ParseNode * dcl = node->getBranch (1);
    if (dcl->getType() == simple_declarator) {
      CORBA::String_var repo_id = gen_repo_id (dcl);
      CORBA::ValueMemberDef_var vm =
	val->create_value_member (repo_id,
				  dcl->getIdent(),
				  _version,
				  idl_type,
				  vis);
    }
    else if (dcl->getType() == array_declarator) {
      CORBA::ArrayDef_var arr = collectArray (con, idl_type,
					      dcl->getBranch(1));
      CORBA::String_var repo_id = gen_repo_id (dcl);
      CORBA::ValueMemberDef_var vm =
	val->create_value_member (repo_id,
				  dcl->getIdent(),
				  _version,
				  arr,
				  vis);
    }
    else {
      assert (0);
    }
    node = node->getBranch (2);
  }
}

CORBA::EnumDef_ptr
IDLParser::collectEnum( CORBA::Container_ptr con, ParseNode *p )
{
  assert( p->getType() == enum_type );
  CORBA::EnumMemberSeq members;
  collectEnumMembers( members, p->getBranch( 1 ) );
  char *name = p->getIdent();
  
  CORBA::String_var repo_id = gen_repo_id( p );
  return con->create_enum( repo_id, name, _version, members );
}

void IDLParser::collectEnumMembers( CORBA::EnumMemberSeq& m, ParseNode *n )
{
  int i;
  
  switch( n->getType() ) {
  case enumerator:
    i = m.length();
    m.length( i + 1 );
    m[ i ] = CORBA::string_dup( n->getIdent() );
    break;
  case enumerators:
    collectEnumMembers( m, n->getBranch( 1 ) );
    collectEnumMembers( m, n->getBranch( 2 ) );
    break;
  default:
    assert( 0 );
  }
}

CORBA::IDLType_ptr IDLParser::collectType( CORBA::Container_ptr con,
					   ParseNode *p )
{
  switch( p->getType() ) {
  case t_void:
    return _repo->get_primitive( CORBA::pk_void );
  case t_float:
    return _repo->get_primitive( CORBA::pk_float );
  case t_double:
    return _repo->get_primitive( CORBA::pk_double );
  case t_long:
    return _repo->get_primitive( CORBA::pk_long );
  case t_short:
    return _repo->get_primitive( CORBA::pk_short );
  case t_unsigned_long:
    return _repo->get_primitive( CORBA::pk_ulong );
  case t_unsigned_short:
    return _repo->get_primitive( CORBA::pk_ushort );
  case t_char:
    return _repo->get_primitive( CORBA::pk_char );
  case t_boolean:
    return _repo->get_primitive( CORBA::pk_boolean );
  case t_octet:
    return _repo->get_primitive( CORBA::pk_octet );
  case t_any:
    return _repo->get_primitive( CORBA::pk_any );
  case t_object:
    return _repo->get_primitive( CORBA::pk_objref );
  case t_longlong:
    return _repo->get_primitive( CORBA::pk_longlong );
  case t_unsigned_longlong:
    return _repo->get_primitive( CORBA::pk_ulonglong );
  case t_long_double:
    return _repo->get_primitive( CORBA::pk_longdouble );
  case t_wide_char:
    return _repo->get_primitive( CORBA::pk_wchar );
  case t_valuebase:
    return _repo->get_primitive( CORBA::pk_value_base );
  case t_string:
    if( p->getBranch( 1 ) == NULL )
      // Unbounded string
      return _repo->get_primitive( CORBA::pk_string );
    else {
      // Bounded string
      Const c = collectConst( con, p->getBranch( 1 ) );
      CORBA::ULong bound = c.get_int();
      CORBA::StringDef_ptr str = _repo->create_string( bound );
      _db->register_anonym_type( p, str );
      return str;
    }
    break;
  case t_wide_string:
    if( p->getBranch( 1 ) == NULL )
      // Unbounded wstring
      return _repo->get_primitive( CORBA::pk_wstring );
    else {
      // Bounded wstring
      Const c = collectConst( con, p->getBranch( 1 ) );
      CORBA::ULong bound = c.get_int();
      CORBA::WstringDef_ptr wstr = _repo->create_wstring( bound );
      _db->register_anonym_type( p, wstr );
      return wstr;
    }
    break;
  case t_sequence:
    {
      CORBA::IDLType_var element_type = collectType( con, p->getBranch( 1 ) );
      CORBA::ULong bound = 0;
      if( p->getBranch( 2 ) != NULL ) {
	// Bounded sequence
	Const c = collectConst( con, p->getBranch( 2 ) );
	bound = c.get_int();
      }
      CORBA::SequenceDef_ptr seq = _repo->create_sequence( bound, element_type );
      _db->register_anonym_type( p, seq );
      return seq;
    }
  case fixed_pt_type:
    {
      CORBA::FixedDef_ptr f;
      /*
       * A fixed type dcl without digits and scale can only occur
       * in const dcl. This is handled in IDLParser::collectConstFixedDcl()
       */
      assert( p->getBranch( 1 ) != NULL );
      Const c = collectConst( con, p->getBranch( 1 ) );
      CORBA::ULong digits = c.get_int();
      f = _repo->create_fixed( digits, p->getIntegerLiteral() );
      _db->register_anonym_type( p, f );
      return f;
    }
  case scoped_name:
    {
      CORBA::Contained_var c;
      c = con->find( collectScopedName( p ) );
      if( CORBA::is_nil( c ) ) {
	if( is_TypeCode( p ) )
	  return _repo->get_primitive( CORBA::pk_TypeCode );
	if( is_Principal( p ) )
	  return _repo->get_primitive( CORBA::pk_Principal );
	cerr << IDLError( 2, p, p->getIdent() ) << endl;
	exit( 1 );
      }
      CORBA::IDLType_ptr t = CORBA::IDLType::_narrow( c );
      if( CORBA::is_nil( t ) ) {
	cerr << IDLError( 7, p, p->getIdent() ) << endl;
	exit( 1 );
      }
      return t;
    }
  case struct_type:
    {
      return collectStruct( con, p );
    }
  case union_type:
    {
      return collectUnion( con, p );
    }
  case enum_type:
    {
      return collectEnum( con, p );
    }

  default:
    p->print();
    assert( 0 );
  }
  return 0;
}

CORBA::ScopedName IDLParser::collectScopedName( ParseNode *n )
{
  assert( n->getType() == scoped_name );
  
  current_parse_node( n );
  return n->getIdent();
}

bool IDLParser::is_TypeCode( ParseNode *n )
{
  assert( n->getType() == scoped_name );
  return strcmp( n->getIdent(), "TypeCode" ) == 0 ||
    strcmp( n->getIdent(), "CORBA::TypeCode" ) == 0;
}

bool IDLParser::is_Principal( ParseNode *n )
{
  assert( n->getType() == scoped_name );
  return strcmp( n->getIdent(), "CORBA::Principal" ) == 0;
}

Const IDLParser::collectConst( CORBA::Container_ptr con, ParseNode *p )
{
  if( p == NULL )
    return Const();

  Const c1( collectConst( con, p->getBranch( 1 ) ) );
  Const c2( collectConst( con, p->getBranch( 2 ) ) );
  
  switch( p->getType() ) {
  case t_floating_pt_literal:
    return Const( CORBA::_tc_longdouble, p->getFloatingPtLiteral(), p );
  case t_fixed_pt_literal:
    return Const( CORBA::_tc_longdouble, p->getFixedPtLiteral(), p );
  case t_integer_literal:
    return Const( CORBA::_tc_longlong, p->getIntegerLiteral(), p );
  case t_string_literal:
    return Const( CORBA::_tc_string, p->getStringLiteral(), p );
  case t_character_literal:
    return Const( CORBA::_tc_char,
		  CORBA::Any::from_char ( p->getCharacterLiteral() ), p );
  case t_boolean_literal:
    return Const( CORBA::_tc_boolean,
		  CORBA::Any::from_boolean ( p->getBooleanLiteral() ), p );
  case t_vertical_line:
    return c1 | c2;
  case t_circumflex:
    return c1 ^ c2;
  case t_ampersand:
    return c1 & c2;
  case t_shiftright:
    return c1 >> c2;
  case t_shiftleft:
    return c1 << c2;
  case t_plus_sign:
    if( p->getBranch( 2 ) == NULL )
      return c1;
    else
      return c1 + c2;
  case t_minus_sign:
    if( p->getBranch( 2 ) == NULL )
      return Const( CORBA::_tc_longlong, (CORBA::LongLong) 0, p ) - c1;
    else
      return c1 - c2;
  case t_asterik:
    return c1 * c2;
  case t_solidus:
    return c1 / c2;
  case t_percent_sign:
    return c1 % c2;
  case t_tilde:
    return ~c1;
  case scoped_name:
    {
      CORBA::Contained_var contained;
      contained = con->find( collectScopedName( p ) );
      if( CORBA::is_nil( contained ) ) {
	cerr << IDLError( 2, p, p->getIdent() ) << endl;
	exit( 1 );
      }
      CORBA::ConstantDef_var c = CORBA::ConstantDef::_narrow( contained );
      if( CORBA::is_nil( c ) ) {
	cerr << IDLError( 24, p, p->getIdent() ) << endl;
	exit( 1 );
      }
      return Const( c->value(), p );
    }
  default:
    p->print();
    assert( 0 );
  }
  return Const();
}
