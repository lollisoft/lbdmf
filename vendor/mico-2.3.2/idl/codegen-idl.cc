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
#include <fstream.h>
#include <ctype.h>
#include <stdio.h>
#include "codegen-idl.h"


static char *copyright[] = {
  "/*",
  " *  MICO --- a free CORBA implementation",
  " *  Copyright (C) 1997-98 Kay Roemer & Arno Puder",
  " *",
  " *  This file was automatically generated. DO NOT EDIT!",
  " */"
};

const int copyright_size = sizeof( copyright ) / sizeof( char * );



CodeGenIDL::CodeGenIDL( DB &db, bool emit_repoids )
  : CodeGen( db.get_idl_container() )
{
  _emit_repoids = emit_repoids;
}


void CodeGenIDL::emit( string &fnbase )
{
  string fn = fnbase + ".idl";
  
  ofstream file( fn.c_str() );

  for( int i = 0; i < copyright_size; i++ )
    file << copyright[ i ] << endl;
  
  file << endl;
  o.start_output( file );
  emitIDL();
  o.stop_output();
}

string CodeGenIDL::emit( CORBA::IRObject_ptr obj )
{
  ostrstream idl;

  CORBA::Contained_var contained = CORBA::Contained::_narrow( obj );
  if( !CORBA::is_nil( contained ) ) {
    CORBA::String_var id = contained->id();
    idl << "/*" << endl;
    idl << " * " << id.in() << endl;
    idl << " */" << endl << endl;
  }
  
  o.start_output( idl );
    
  switch( obj->def_kind() ) {
  case CORBA::dk_Module:
    {
      assert( 0 );
#if 0
      CORBA::ModuleDef_var m = CORBA::ModuleDef::_narrow( obj );
      emitIDLModule( m );
#endif
      break;
    }
  case CORBA::dk_Interface:
    {
      CORBA::InterfaceDef_var in =
	CORBA::InterfaceDef::_narrow( obj );
      emitIDLInterface( in );
      break;
    }
  case CORBA::dk_Operation:
    {
      CORBA::OperationDef_var op = CORBA::OperationDef::_narrow (obj);
      emitOperation( op );
      break;
    }
  case CORBA::dk_Attribute:
    {
      CORBA::AttributeDef_var attr = CORBA::AttributeDef::_narrow (obj);
      emitAttribute( attr );
      break;
    }
  case CORBA::dk_Struct:
    {
      CORBA::StructDef_var s = CORBA::StructDef::_narrow( obj );
      emitIDLStruct( s );
      break;
    }
  case CORBA::dk_Union:
    {
      CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( obj );
      emitIDLUnion( u );
      break;
    }
  case CORBA::dk_Constant:
    {
      CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( obj );
      emitIDLConstant( co );
      break;
    }
  case CORBA::dk_Exception:
    {
      CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( obj );
      emitIDLException( e );
      break;
    }
  case CORBA::dk_Enum:
    {
      CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( obj );
      emitIDLEnum( e );
      break;
    }
  case CORBA::dk_Alias:
    {
      CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( obj );
      emitIDLAlias( a );
      break;
    }
  case CORBA::dk_Native:
    {
      CORBA::NativeDef_var n = CORBA::NativeDef::_narrow( obj );
      emitIDLNative( n );
      break;
    }
  case CORBA::dk_Value:
    {
      CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( obj );
      emitIDLValue( v );
      break;
    }
  case CORBA::dk_ValueBox:
    {
      CORBA::ValueBoxDef_var v = CORBA::ValueBoxDef::_narrow( obj );
      emitIDLValueBox( v );
      break;
    }
  case CORBA::dk_ValueMember:
    {
      CORBA::ValueMemberDef_var v = CORBA::ValueMemberDef::_narrow( obj );
      emitValueMember( v );
      break;
    }

  default:
    assert( 0 );
  }
  o.stop_output();
  idl << ends;
  string result = idl.str();
  idl.rdbuf()->freeze( 0 );
  return result;
}

void CodeGenIDL::enter_scope( CORBA::Container_ptr c )
{
  vector<CORBA::Contained_var> trace_current_scope;
  vector<CORBA::Contained_var> trace_new_scope;
  CORBA::Container_var         scope;
  bool                         nl;
  
  scope = _current_scope;
  while( scope->def_kind() != CORBA::dk_Repository ) {
    CORBA::Contained_ptr scope_contained = CORBA::Contained::_narrow( scope );
    assert( !CORBA::is_nil( scope_contained ) );
    trace_current_scope.insert( trace_current_scope.begin(), scope_contained );
    scope = scope_contained->defined_in();
  }
  
  scope = CORBA::Container::_duplicate( c );
  while( scope->def_kind() != CORBA::dk_Repository ) {
    CORBA::Contained_ptr scope_contained = CORBA::Contained::_narrow( scope );
    assert( !CORBA::is_nil( scope_contained ) );
    trace_new_scope.insert( trace_new_scope.begin(), scope_contained );
    scope = scope_contained->defined_in();
  }
  
  vector<CORBA::Contained_var>::iterator i, j;
  for( i = trace_current_scope.begin(), j = trace_new_scope.begin();
       i != trace_current_scope.end() && j != trace_new_scope.end() &&
	 (*i)->_is_equivalent( *j );
       i++, j++ ) ;
  
  nl = false;
  while( i != trace_current_scope.end() ) {
    o << BL_CLOSE_SEMI;
    nl = true;
    i++;
  }
  if( nl )
    o << endl << endl;

  nl = false;
  while( j != trace_new_scope.end() ) {
    emit_repoid( *j );
    o << "module ";
    CORBA::Identifier_var name = (*j)->name();
    o << name << " " << BL_OPEN;
    nl = true;
    j++;
  }
  if( nl )
    o << endl;
  
  _current_scope = CORBA::Container::_duplicate( c );
}

void CodeGenIDL::emit_repoid( CORBA::Contained_ptr c )
{
  if( !_emit_repoids )
    return;
  CORBA::String_var name = c->name();
  CORBA::String_var repoid = c->id();
  o << "#pragma ID " << name << " \"" << repoid << "\"" << endl;
}

void CodeGenIDL::emitAttribute( CORBA::AttributeDef_ptr attr )
{
  if( attr->mode() == CORBA::ATTR_READONLY )
    o << "readonly ";
  o << "attribute ";
  CORBA::IDLType_var type_id = attr->type_def();
  emit_idl_type( type_id );
  CORBA::String_var n = attr->name();
  o << " " << n << ";" << endl;
}

void CodeGenIDL::emitOperation( CORBA::OperationDef_ptr op )
{
  if( op->mode() == CORBA::OP_ONEWAY )
    o << "oneway ";
  CORBA::IDLType_var type_id = op->result_def();
  emit_idl_type( type_id );
  CORBA::String_var n = op->name();
  o << " " << n << "(";
  CORBA::ParDescriptionSeq_var p = op->params();
  CORBA::ULong k;
  for( k = 0; k < p->length(); k++ ) {
    if( k != 0 )
      o << ",";
    o << " ";
    switch( p[ k ].mode ) {
    case CORBA::PARAM_IN:
      o << "in ";
      break;
    case CORBA::PARAM_OUT:
      o << "out ";
      break;
    case CORBA::PARAM_INOUT:
      o << "inout ";
      break;
    default:
      assert( 0 );
    }
    emit_idl_type( p[ k ].type_def );
    o << " " << p[ k ].name;
  }
  if( k != 0 )
    o << " ";
  o << ")" << indent;
  
  CORBA::ExceptionDefSeq_var exs = op->exceptions();
  if( exs->length() > 0 ) {
    o << endl;
    o << "raises( ";
    for( CORBA::ULong i = 0; i < exs->length(); i++ ) {
      if( i != 0 )
	o << ", ";
      CORBA::Contained_var c = _repo->lookup_id( exs[ i ]->id() );
      assert( !CORBA::is_nil( c ) );
      CORBA::String_var abs_name = c->absolute_name();
      o << abs_name;
    }
    o << " )";
  }
  CORBA::ContextIdSeq_var ctx = op->contexts();
  if( ctx->length() > 0 ) {
    o << endl;
    o << "context( ";
    for( CORBA::ULong i = 0; i < ctx->length(); i++ ) {
      if( i != 0 )
	o << ", ";
      o << "\"" << ctx[ i ] << "\"";
    }
    o << " )";
  }
  o << exdent << ";" << endl;
}

void
CodeGenIDL::emitValueMember( CORBA::ValueMemberDef_ptr vmd )
{
  if ( vmd->access() == CORBA::PRIVATE_MEMBER ) {
    o << "private ";
  }
  else {
    o << "public ";
  }

  CORBA::IDLType_var type_id = vmd->type_def();
  emit_idl_type( type_id );
  CORBA::String_var n = vmd->name();
  o << " " << n;
  emit_array_suffix (type_id);
  o << ";" << endl;
}

void CodeGenIDL::emitPrototypes( CORBA::Container_ptr in )
{
  CORBA::ContainedSeq_var c;

  // Emit attributes
  c = in->contents (CORBA::dk_Attribute, 1);
  for( CORBA::ULong i0 = 0; i0 < c->length(); i0++ ) {
    CORBA::AttributeDef_var attr = CORBA::AttributeDef::_narrow(c[i0]);
    assert (!CORBA::is_nil(attr));
    emitAttribute( attr );
  }

  // Emit operations
  c = in->contents (CORBA::dk_Operation, 1);
  for( CORBA::ULong i1 = 0; i1 < c->length(); i1++ ) {
    CORBA::OperationDef_var op = CORBA::OperationDef::_narrow(c[i1]);
    assert (!CORBA::is_nil(op));
    emitOperation( op );
  }

  // Emit value state
  c = in->contents (CORBA::dk_ValueMember, 1);
  for( CORBA::ULong i2 = 0; i2 < c->length(); i2++ ) {
    CORBA::ValueMemberDef_var vmd = CORBA::ValueMemberDef::_narrow(c[i2]);
    assert (!CORBA::is_nil(vmd));
    emitValueMember( vmd );
  }
}

void CodeGenIDL::emitLocal( CORBA::Contained_ptr con,
			    bool emit_semicolon )
{
  emit_repoid( con );
  switch( con->def_kind() ) {
  case CORBA::dk_Operation:
  case CORBA::dk_Attribute:
  case CORBA::dk_ValueMember:
    // Operation & attribute declarations are generated in emitPrototypes()
    break;
  case CORBA::dk_Struct:
    {
      CORBA::StructDef_var s = CORBA::StructDef::_narrow( con );
      emitIDLStruct( s, emit_semicolon );
      break;
    }
  case CORBA::dk_Union:
    {
      CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( con );
      emitIDLUnion( u, emit_semicolon );
      break;
    }
  case CORBA::dk_Constant:
    {
      CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( con );
      emitIDLConstant( co );
      break;
    }
  case CORBA::dk_Exception:
    {
      CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( con );
      emitIDLException( e );
      break;
    }
  case CORBA::dk_Enum:
    {
      CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( con );
      emitIDLEnum( e, emit_semicolon );
      break;
    }
  case CORBA::dk_Alias:
    {
      CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( con );
      emitIDLAlias( a );
      break;
    }
  case CORBA::dk_Native:
    {
      CORBA::NativeDef_var n = CORBA::NativeDef::_narrow( con );
      emitIDLNative( n );
      break;
    }
  case CORBA::dk_Value:
    {
      CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( con );
      emitIDLValue( v );
      break;
    }
  case CORBA::dk_ValueBox:
    {
      CORBA::ValueBoxDef_var v = CORBA::ValueBoxDef::_narrow( con );
      emitIDLValueBox( v );
      break;
    }
  default:
    assert( 0 );
  }
}

void CodeGenIDL::emitLocalDecls( CORBA::Container_ptr in )
{
  CORBA::ContainedSeq_var c;
  c = in->contents( CORBA::dk_all, 1 );
  for( CORBA::ULong i = 0; i < c->length(); i++ ) {
    emitLocal (c[i]);
  }
}

void CodeGenIDL::emitForwardDcl( CORBA::Container_ptr c )
{
  if (c->def_kind() == CORBA::dk_Interface) {
    CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow (c);
    CORBA::String_var name = in->name();
    if (in->is_abstract()) {
      o << "abstract ";
    }
    o << "interface " << name << ";" << endl << endl;
  }
  else if (c->def_kind() == CORBA::dk_Value) {
    CORBA::ValueDef_var val = CORBA::ValueDef::_narrow (c);
    CORBA::String_var name = val->name();
    if (val->is_abstract()) {
      o << "abstract ";
    }
    o << "valuetype " << name << ";" << endl << endl;
  }
  else {
    assert (0);
  }
}

void CodeGenIDL::emitIDL()
{
  _current_scope = CORBA::Container::_duplicate( _container );
  
  for( CORBA::ULong i = 0; i < _idl_objs.length(); i++ ) {

    CORBA::Contained_var c = CORBA::Contained::_narrow( _idl_objs[ i ]->obj );
    if( !CORBA::is_nil( c ) ) {
      CORBA::Container_var new_scope = c->defined_in();
      enter_scope( new_scope );
      
      emit_repoid( c );

      switch( c->def_kind() ) {
      case CORBA::dk_Interface:
	{
	  CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( c );
	  if( _idl_objs[ i ]->iface_as_forward )
	    emitForwardDcl( in );
	  else
	    emitIDLInterface( in );
	  break;
	}
      case CORBA::dk_Struct:
	{
	  CORBA::StructDef_var s = CORBA::StructDef::_narrow( c );
	  emitIDLStruct( s );
	  break;
	}
      case CORBA::dk_Union:
	{
	  CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( c );
	  emitIDLUnion( u );
	  break;
	}
      case CORBA::dk_Constant:
	{
	  CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( c );
	  emitIDLConstant( co );
	  break;
	}
      case CORBA::dk_Exception:
	{
	  CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( c );
	  emitIDLException( e );
	  break;
	}
      case CORBA::dk_Enum:
	{
	  CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( c );
	  emitIDLEnum( e );
	  break;
	}
      case CORBA::dk_Alias:
	{
	  CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( c );
	  emitIDLAlias( a );
	  break;
	}
      case CORBA::dk_Native:
	{
	  CORBA::NativeDef_var n = CORBA::NativeDef::_narrow( c );
	  emitIDLNative( n );
	  break;
	}
      case CORBA::dk_Value:
	{
	  CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( c );
	  if( _idl_objs[ i ]->iface_as_forward ) {
	    emitForwardDcl( v );
	  }
	  else {
	    emitIDLValue( v );
	  }
	  break;
	}
      case CORBA::dk_ValueBox:
	{
	  CORBA::ValueBoxDef_var v = CORBA::ValueBoxDef::_narrow( c );
	  emitIDLValueBox( v );
	  break;
	}
      default:
	cout << c->def_kind() << endl;
	assert( 0 );
      }
    }
  }

  // Close open modules
  enter_scope( _container );
}

void CodeGenIDL::emitIDLInterface( CORBA::InterfaceDef_ptr in )
{
  assert( in->def_kind() == CORBA::dk_Interface );
  CORBA::String_var n = in->name();
  string className = (const char *) n;

  if (in->is_abstract()) {
    o << "abstract ";
  }
  o << "interface " << className;
 
  CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
  if( bases->length() != 0 ) {
    // This interface *has* base interfaces
    o << " :" << indent << endl;
    for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
      CORBA::String_var base_name = bases[ i ]->absolute_name();
      o << base_name;
      if( i + 1 != bases->length() )
	o << ",";
      o << endl;
    }
    o << exdent;
  } else
    o << endl;
  
  o << BL_OPEN;
  
  // Emit local declarations
  emitLocalDecls( in );
  
  // Generate prototypes
  emitPrototypes( in );

  o << BL_CLOSE_SEMI << endl;
}

void CodeGenIDL::emitIDLStruct( CORBA::StructDef_ptr s, bool emit_semicolon )
{
  assert( s->def_kind() == CORBA::dk_Struct );

  vector<CORBA::IDLType_var> emitted_locals;
  CORBA::TypeCode_var tc = s->type();
  CORBA::String_var name = s->name();
  
  o << "struct " << name << " " << BL_OPEN;
  CORBA::StructMemberSeq_var m = s->members();
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    /*
     * If the type is defined in the same scope (meaning that we are its
     * container), and it hasn't been printed yet, emit it here.
     */

    CORBA::Contained_var cv = CORBA::Contained::_narrow (m[i].type_def);
    CORBA::Container_var con = CORBA::Container::_nil();

    for (CORBA::ULong j=0; j<emitted_locals.size(); j++) {
      if (emitted_locals[j]->_is_equivalent (m[i].type_def)) {
	cv = CORBA::Contained::_nil(); // don't print it again
	break;
      }
    }

    if (!CORBA::is_nil (cv)) {
      con = cv->defined_in ();
    }

    if (s->_is_equivalent (con)) {
      emitted_locals.push_back (CORBA::IDLType::_duplicate (m[i].type_def));
      emitLocal( cv, false );
    }
    else {
      emit_idl_type( m[ i ].type_def );
    }

    o << " " << m[ i ].name;
    emit_array_suffix( m[ i ].type_def );
    o << ";" << endl;
  }
  o << exdent << "}";
  if( emit_semicolon )
    o << ";" << endl << endl;
}

void CodeGenIDL::emitIDLUnion( CORBA::UnionDef_ptr u, bool emit_semicolon )
{
  assert( u->def_kind() == CORBA::dk_Union );

  vector<CORBA::IDLType_var> emitted_locals;
  CORBA::TypeCode_var tc = u->type();
  CORBA::String_var name = u->name();
  
  o << "union " << name << " switch( ";
  CORBA::IDLType_var discr = u->discriminator_type_def();
  emit_idl_type( discr );
  o << " ) " << BL_OPEN;
  CORBA::UnionMemberSeq_var m = u->members();
  tc = discr->type();

  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    CORBA::TypeCode_var label_tc = m[ i ].label.type();
    if( label_tc->is_octet() )
      o << "default:";
    else {
      o << "case ";
      if( tc->is_enum() ) {
	CORBA::String_var s;
	CORBA::ULong idx;
	CORBA::Boolean r = m[ i ].label.enum_get( idx );
	assert (r);
	s = (const char *) tc->unalias()->member_name( idx );
	o << s;
      } else
	o << &m[ i ].label;
      o << ":";
      if( i + 1 != m->length() &&
	  strcmp( m[ i ].name, m[ i + 1 ].name ) == 0 ) {
	o << endl;
	continue;
      }
    }

    /*
     * If the type is defined in the same scope (meaning that we are its
     * container), and it hasn't been printed yet, emit it here.
     */

    CORBA::Contained_var cv = CORBA::Contained::_narrow (m[i].type_def);
    CORBA::Container_var con = CORBA::Container::_nil();

    for (CORBA::ULong j=0; j<emitted_locals.size(); j++) {
      if (emitted_locals[j]->_is_equivalent (m[i].type_def)) {
	cv = CORBA::Contained::_nil(); // don't print it again
	break;
      }
    }

    if (!CORBA::is_nil (cv)) {
      con = cv->defined_in ();
    }

    o << indent << endl;
    if (u->_is_equivalent (con)) {
      emitted_locals.push_back (CORBA::IDLType::_duplicate (m[i].type_def));
      emitLocal( cv, false );
    }
    else {
      emit_idl_type( m[ i ].type_def );
    }

    o << " " << m[ i ].name;
    emit_array_suffix( m[ i ].type_def );
    o << ";" << exdent << endl;
  }
  o << exdent << "}";
  if( emit_semicolon )
    o << ";" << endl << endl;
}

void CodeGenIDL::emitIDLConstant( CORBA::ConstantDef_ptr c )
{
  assert( c->def_kind() == CORBA::dk_Constant );
  CORBA::String_var name = c->name();
  o << "const ";
  CORBA::IDLType_var type = c->type_def();
  CORBA::TypeCode_var tc = type->type();
  if( tc->kind() == CORBA::tk_fixed )
    o << "fixed";
  else
    emit_base_type( type );
  o << " " << name << " = ";
  CORBA::Any* a = c->value();
  o << a;
  delete a;
  if( tc->kind() == CORBA::tk_fixed )
    o << "D";
  o << ";" << endl;
}

void CodeGenIDL::emitIDLException( CORBA::ExceptionDef_ptr e )
{
  assert( e->def_kind() == CORBA::dk_Exception );

  vector<CORBA::IDLType_var> emitted_locals;
  CORBA::String_var name = e->name();
  
  o << "exception " << name << " " << BL_OPEN;
  CORBA::StructMemberSeq_var m = e->members();
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    /*
     * If the type is defined in the same scope (meaning that we are its
     * container), and it hasn't been printed yet, emit it here.
     */

    CORBA::Contained_var cv = CORBA::Contained::_narrow (m[i].type_def);
    CORBA::Container_var con = CORBA::Container::_nil();

    for (CORBA::ULong j=0; j<emitted_locals.size(); j++) {
      if (emitted_locals[j]->_is_equivalent (m[i].type_def)) {
	cv = CORBA::Contained::_nil(); // don't print it again
	break;
      }
    }

    if (!CORBA::is_nil (cv)) {
      con = cv->defined_in ();
    }

    if (e->_is_equivalent (con)) {
      emitted_locals.push_back (CORBA::IDLType::_duplicate (m[i].type_def));
      emitLocal( cv, false );
    }
    else {
      emit_idl_type( m[ i ].type_def );
    }

    o << " " << m[ i ].name;
    emit_array_suffix( m[ i ].type_def );
    o << ";" << endl;
  }
  o << BL_CLOSE_SEMI << endl;
}

void CodeGenIDL::emitIDLEnum( CORBA::EnumDef_ptr e, bool emit_semicolon )
{
  assert( e->def_kind() == CORBA::dk_Enum );

  CORBA::String_var name = e->name();
  o << "enum " << name << " " << BL_OPEN;

  CORBA::EnumMemberSeq_var m = e->members();
  
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    if( i != 0 )
      o << "," << endl;
    o << m[ i ];
  }
  o << exdent << endl << "}";
  if( emit_semicolon )
    o << ";" << endl << endl;
}

void CodeGenIDL::emitIDLAlias( CORBA::AliasDef_ptr a )
{
  assert( a->def_kind() == CORBA::dk_Alias );
  
  CORBA::IDLType_var orig = a->original_type_def();
  assert( !CORBA::is_nil( orig ) );
  
  CORBA::TypeCode_var orig_tc = orig->type();
  
  CORBA::String_var name = a->name();

#if 0
  if( orig_tc->is_string() ) {
    o << "typedef string " << name;
    emit_array_suffix( orig );
    o << ";" << endl << endl;
  } else
#endif
  if( orig_tc->is_objref() ) {
    CORBA::String_var abs_name;
    
    if( orig_tc->kind() == CORBA::tk_alias ) {
      // we have an alias of an alias
      CORBA::AliasDef_var alias = CORBA::AliasDef::_narrow( orig );
      assert( !CORBA::is_nil( alias ) );
      abs_name = alias->absolute_name();
    } else {
      // gotta be an interface
      assert( orig_tc->kind() == CORBA::tk_objref );
      CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( orig );
      if( !CORBA::is_nil( in ) )
	abs_name = in->absolute_name();
      else
	abs_name = (const char *) "Object";
    }

    o << "typedef " << abs_name << " " << name;
    emit_array_suffix( orig );
    o << ";" << endl << endl;
  } else {
    o << "typedef ";
    emit_idl_type( orig );
    o << " " << name;
    emit_array_suffix( orig );
    o << ";" << endl;
  }
  o << endl;
}

void
CodeGenIDL::emitIDLNative( CORBA::NativeDef_ptr n )
{
  CORBA::String_var name = n->name();
  o << "native " << name << ";" << endl << endl;
}

void
CodeGenIDL::emitIDLValue( CORBA::ValueDef_ptr v )
{
  CORBA::String_var n = v->name();

  if (v->is_abstract()) {
    o << "abstract ";
  }
  if (v->is_custom()) {
    o << "custom ";
  }
  o << "valuetype " << n;

  CORBA::ValueDef_var base_value = v->base_value();
  CORBA::ValueDefSeq_var abstract_base_values = v->abstract_base_values();
  CORBA::InterfaceDefSeq_var supported_interfaces = v->supported_interfaces();

  if (!CORBA::is_nil (base_value)) {
    o << " :" << indent << endl;
    if (v->is_truncatable()) {
      o << "truncatable ";
    }
    CORBA::String_var bn = base_value->absolute_name();
    o << bn;
  }

  if (abstract_base_values->length() > 0) {
    if (!CORBA::is_nil (base_value)) {
      o << ",";
    }
    else {
      o << " :" << indent << endl;
    }
    for( CORBA::ULong i=0; i<abstract_base_values->length(); i++ ) {
      CORBA::String_var bn = abstract_base_values[i]->absolute_name();
      o << endl << bn;
      if (i+1 != abstract_base_values->length()) {
	o << ",";
      }
    }
  }

  if (supported_interfaces->length() > 0) {
    if (!CORBA::is_nil (base_value) || abstract_base_values->length() > 0) {
      o << endl;
    }
    else {
      o << " ";
    }
    o << "supports";
    if (supported_interfaces->length() == 1) {
      o << " ";
    }
    else {
      o << endl;
    }
    for (CORBA::ULong i=0; i<supported_interfaces->length(); i++) {
      CORBA::String_var sn = supported_interfaces[i]->absolute_name();
      o << sn;
      if (i+1 != supported_interfaces->length()) {
	o << "," << endl;
      }
    }
  }

  if (!CORBA::is_nil (base_value) || abstract_base_values->length() > 0) {
    o << exdent;
  }

  o << endl << BL_OPEN;
  emitLocalDecls( v );

  // emit initializers
  CORBA::InitializerSeq_var initializers = v->initializers();
  for (CORBA::ULong i=0; i<initializers->length(); i++) {
    o << "factory " << initializers[i].name << " (";
    for (CORBA::ULong j=0; j<initializers[i].members.length(); j++) {
      if (j != 0) {
	o << ", ";
      }
      o << "in ";
      emit_idl_type( initializers[i].members[j].type_def );
      o << " " << initializers[i].members[j].name.in();
    }
    o << ");" << endl;
  }

  // emit prototypes
  emitPrototypes( v );
  o << BL_CLOSE_SEMI << endl;
}

void
CodeGenIDL::emitIDLValueBox( CORBA::ValueBoxDef_ptr vb )
{
  CORBA::IDLType_var orig = vb->original_type_def();
  CORBA::String_var n = vb->name();
  o << "valuebox " << n << " ";
  emit_idl_type( orig );
  emit_array_suffix( orig );
  o << ";" << endl << endl;
}

void CodeGenIDL::emit_idl_type_name( CORBA::IDLType_ptr t )
{
  CORBA::String_var tmp;
  string abs_name;
  
  switch( t->def_kind() ) {
  case CORBA::dk_Struct:
  case CORBA::dk_Union:
  case CORBA::dk_Enum:
  case CORBA::dk_Alias:
  case CORBA::dk_Interface:
  case CORBA::dk_Value:
  case CORBA::dk_ValueBox:
    {
      CORBA::Contained_var con = CORBA::Contained::_narrow( t );
      tmp = con->absolute_name();
      abs_name = tmp;
      break;
    }
  case CORBA::dk_Primitive:
    {
      CORBA::PrimitiveDef_var p = CORBA::PrimitiveDef::_narrow( t );
      if( p->kind() == CORBA::pk_any )
	o << "any";
      else if( p->kind() == CORBA::pk_objref )
	o << "Object";
      else
	assert( 0 );
      return;
    }
  default:
    cout << t->def_kind() << endl;
    assert( 0 );
  }
  if( abs_name[ 0 ] == ':' )
    abs_name = abs_name.substr( 2 );
  o << (char *) abs_name.c_str();
}

void CodeGenIDL::emit_array_suffix( CORBA::IDLType_ptr t )
{
  CORBA::TypeCode_var tc = t->type();
  assert( !CORBA::is_nil( tc ) );

  while( tc->kind() == CORBA::tk_array ) {
    o << "[ " << tc->length() << " ]";
    tc = tc->content_type();
  }
}

void CodeGenIDL::emit_array( CORBA::IDLType_ptr type )
{
  assert( type->def_kind() == CORBA::dk_Array );
  CORBA::ArrayDef_var a;
  CORBA::IDLType_var idl_type = CORBA::IDLType::_duplicate( type );
  while( idl_type->def_kind() == CORBA::dk_Array ) {
    a = CORBA::ArrayDef::_narrow( idl_type );
    assert( !CORBA::is_nil( a ) );
    idl_type = a->element_type_def();
  }
  emit_idl_type( idl_type );
}

void CodeGenIDL::emit_sequence( CORBA::IDLType_ptr type )
{
  assert( type->def_kind() == CORBA::dk_Sequence );
  CORBA::SequenceDef_var s = CORBA::SequenceDef::_narrow( type );
  CORBA::IDLType_var idl_type = s->element_type_def();
  
  o << "sequence<";
  emit_idl_type( idl_type );
  
  CORBA::ULong b = s->bound();
  if( b > 0 )
    o << ", " << b;
  
  o << " >";
}

void CodeGenIDL::emit_idl_type( CORBA::IDLType_ptr t )
{
  CORBA::String_var tmp;
  
  CORBA::TypeCode_var tc = t->type();
  assert( !CORBA::is_nil( tc ) );

  if( tc->is_alias() ) {
    emit_idl_type_name( t );
    return;
  }

  CORBA::PrimitiveDef_var prim = CORBA::PrimitiveDef::_narrow( t );
  if( !CORBA::is_nil( prim ) && prim->kind() == CORBA::pk_objref ) {
    o << "Object";
    return;
  }
  else if (!CORBA::is_nil( prim ) && prim->kind() == CORBA::pk_value_base) {
    o << "ValueBase";
    return;
  }

  // What about tk_abstract_interface?  
  if( tc->is_objref() ) {
    CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( t );
    tmp = in->absolute_name();
    string abs_name;
    abs_name = tmp;
    abs_name = abs_name.substr( 2 );
    o << abs_name;
    return;
  }

  if( !emit_base_type( t ) ) {
    switch( tc->kind() ) {
    case CORBA::tk_objref:
    case CORBA::tk_abstract_interface:
    case CORBA::tk_struct:
    case CORBA::tk_union:
    case CORBA::tk_enum:
    case CORBA::tk_alias:
    case CORBA::tk_any:
    case CORBA::tk_value:
    case CORBA::tk_value_box:
      emit_idl_type_name( t );
      break;
    case CORBA::tk_sequence:
      emit_sequence( t );
      break;
    case CORBA::tk_array:
      emit_array( t );
      break;
    case CORBA::tk_TypeCode:
      o << "TypeCode";
      break;
    default:
      assert( 0 );
    }
  }
}

bool CodeGenIDL::emit_base_type( CORBA::IDLType_ptr t )
{
  CORBA::TypeCode_var tc = t->type();
  assert( !CORBA::is_nil( tc ) );

  // Mapping of Base Data Types [16.5]
  switch( tc->kind() ) {
  case CORBA::tk_void:
    o << "void";
    break;
  case CORBA::tk_boolean:
    o << "boolean";
    break;
  case CORBA::tk_char:
    o << "char";
    break;
  case CORBA::tk_wchar:
    o << "wchar";
    break;
  case CORBA::tk_octet:
    o << "octet";
    break;
  case CORBA::tk_ushort:
    o << "unsigned short";
    break;
  case CORBA::tk_ulong:
    o << "unsigned long";
    break;
  case CORBA::tk_short:
    o << "short";
    break;
  case CORBA::tk_long:
    o << "long";
    break;
  case CORBA::tk_longlong:
    o << "long long";
    break;
  case CORBA::tk_ulonglong:
    o << "unsigned long long";
    break;
  case CORBA::tk_float:
    o << "float";
    break;
  case CORBA::tk_double:
    o << "double";
    break;
  case CORBA::tk_longdouble:
    o << "long double";
    break;
  case CORBA::tk_string:
    o << "string";
    if( tc->length() != 0 )
      o << "<" << tc->length() << ">";
    break;
  case CORBA::tk_wstring:
    o << "wstring";
    if( tc->length() != 0 )
      o << "<" << tc->length() << ">";
    break;
  case CORBA::tk_fixed:
    o << "fixed<" << tc->fixed_digits() << "," <<
      tc->fixed_scale() << ">";
    break;
  case CORBA::tk_alias:
    if( tc->is_base_type() ) {
      emit_idl_type_name( t );
      return true;
    } else
      return false;
    break;
  default:
    return false;
  }
  return true;
}

