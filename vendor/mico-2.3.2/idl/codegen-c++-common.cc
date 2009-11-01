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
#include "codegen-c++-common.h"
#include <mico/template_impl.h>
#include <mico/util.h>


#define TVAR( tc ) ( tc->is_variable() ? "TVarVar" : "TFixVar" )



CodeGenCPPCommon::CodeGenCPPCommon( DB &db, IDLParam& params )
  : CodeGen( db.get_idl_container() ),
    CodeGenCPPUtil( db, params )
{
}


void
CodeGenCPPCommon::emit_common()
{
  _current_scope = CORBA::Container::_duplicate( _container );
  
  for( CORBA::ULong i = 0; i < _idl_objs.length(); i++ ) {
    emit_idl_obj( _idl_objs[ i ] );
  }

  // Close open modules
  enter_scope( _container, "" );

  // emit POA Skeleton declarations
  o << "#ifndef MICO_CONF_NO_POA" << endl << endl;
  if (_params.poa && !_params.pseudo) {
    for (CORBA::ULong i2=0; i2<_idl_objs.length(); i2++) {
      emit_poa_obj (_idl_objs[i2], false);
    }
    enter_scope (_container, "POA_");
  }

  /*
   * We need a third pass to emit flattened POA Tie declarations
   * at global level
   */

  if (_params.poa && !_params.pseudo) {
    for (CORBA::ULong i3=0; i3<_idl_objs.length(); i3++) {
      emit_poa_obj (_idl_objs[i3], true);
    }
  }
  o << "#endif // MICO_CONF_NO_POA" << endl << endl;

  // emit OBV Skeleton declarations
  for (CORBA::ULong i4=0; i4<_idl_objs.length(); i4++) {
    emit_obv_obj (_idl_objs[i4]);
  }
  enter_scope (_container, "OBV_");
}

void CodeGenCPPCommon::emit_idl_obj( IRObj_ptr no )
{
  CORBA::IRObject_ptr obj = no->obj;
  
  if( check_for_included_defn( obj ) )
    return;
    
  CORBA::Contained_var c = CORBA::Contained::_narrow( obj );
  if( !CORBA::is_nil( c ) ) {
    CORBA::Container_var new_scope = c->defined_in();
    enter_scope( new_scope, "" );
    set_name_prefix( new_scope );
  }
  
  switch( obj->def_kind() ) {
  case CORBA::dk_Interface:
    {
      CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( obj );
      if( no->iface_as_forward ) {
	emit_ForwardDcl( in );
      } else {
	emit_Interface( in );
      }
      break;
    }
  case CORBA::dk_Struct:
    {
      CORBA::StructDef_var s = CORBA::StructDef::_narrow( obj );
      emit_Struct( s );
      break;
    }
  case CORBA::dk_Union:
    {
      CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( obj );
      emit_Union( u );
      break;
    }
  case CORBA::dk_Constant:
    {
      CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( obj );
      emit_Constant( co );
      break;
    }
  case CORBA::dk_Exception:
    {
      CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( obj );
      emit_Exception( e );
      break;
    }
  case CORBA::dk_Enum:
    {
      CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( obj );
      emit_Enum( e );
      break;
    }
  case CORBA::dk_Alias:
    {
      CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( obj );
      emit_Alias( a );
      break;
    }
  case CORBA::dk_String:
    {
      CORBA::StringDef_var s = CORBA::StringDef::_narrow( obj );
      emit_StringDef( s );
      break;
    }
  case CORBA::dk_Wstring:
    {
      CORBA::WstringDef_var ws = CORBA::WstringDef::_narrow( obj );
      emit_WstringDef( ws );
      break;
    }
  case CORBA::dk_Sequence:
    {
      CORBA::SequenceDef_var s = CORBA::SequenceDef::_narrow( obj );
      emit_SequenceDef( s );
      break;
    }
  case CORBA::dk_Fixed:
    {
      CORBA::FixedDef_var f = CORBA::FixedDef::_narrow( obj );
      emit_FixedDef( f );
      break;
    }
  case CORBA::dk_Array:
    {
      CORBA::ArrayDef_var a = CORBA::ArrayDef::_narrow( obj );
      emit_ArrayDef( a );
      break;
    }
  case CORBA::dk_Native:
    {
      CORBA::NativeDef_var n = CORBA::NativeDef::_narrow( obj );
      emit_Native( n );
      break;
    }
  case CORBA::dk_Value:
    {
      CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( obj );
      if( no->iface_as_forward ) {
	emit_ForwardDcl( v );
      } else {
	emit_Value( v );
      }
      break;
    }
  case CORBA::dk_ValueBox:
    {
      CORBA::ValueBoxDef_var v = CORBA::ValueBoxDef::_narrow( obj );
      emit_ValueBox( v );
      break;
    }
  default:
    assert( 0 );
  }
}

void
CodeGenCPPCommon::emit_marshal_prototype( CORBA::IRObject_ptr obj )
{
  if( _params.pseudo && !_params.any )
    return;

  /*
   * Here we declare a variable that references an instance
   * of a marshaller. If obj denotes an alias, the marshaller
   * is simply a reference to the original marshaller (and
   * therefore this reference needs to be initialized right here).
   * Otherwise there exists a class for the marshaller. In this
   * case the variable is initialized in the implementation.
   */
  CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( obj );
  if( CORBA::is_nil( a ) ) {
    // obj is not an alias
    o << "extern CORBA::StaticTypeInfo *";
    emit_marshaller_ref( obj );
    o << ";" << endl << endl;
  } else {
    // obj is an alias
    o.switchStream( 2 );
    o << "extern CORBA::StaticTypeInfo *";
    o << "&";
    emit_marshaller_ref( obj );
    o << ";" << endl << endl;
  }
}

void
CodeGenCPPCommon::emit_ForwardDcl( CORBA::Contained_ptr in )
{
  // Check if we already emitted the forward decls for this interface
  CORBA::String_var repo_id;
  repo_id = in->id();

  if( _forward_dcls.find( string( repo_id ) ) != _forward_dcls.end() )
    return;
  
  _forward_dcls.insert( string( repo_id ) );
  
  if (check_for_included_defn (in))
    return;
    
  CORBA::String_var tmp = in->name();
  CORBA::String_var className = (const char *) ID(tmp);
    
  o << "class " << className << ";" << endl;
  o << "typedef " << className << " *" << className <<
    "_ptr;" << endl;
  o << "typedef " << className << "_ptr " << className <<
    "Ref;" << endl;

  if (in->def_kind() == CORBA::dk_Interface) {
    o << "typedef ObjVar<" << className << "> " << className <<
      "_var;" << endl;
  }
  else {
    o << "typedef ValueVar<" << className << "> " << className <<
      "_var;" << endl;
  }
  o << "typedef " << className << "_var " << className << "_out;" << endl;
  o << endl;
}

void CodeGenCPPCommon::emitPrototypes( CORBA::Container_ptr in,
				       bool as_pure_virtual )
{
  CORBA::ContainedSeq_var c;

  // Emit attributes
  c = in->contents (CORBA::dk_Attribute, 1);
  for( CORBA::ULong j = 0; j < c->length(); j++ ) {
    CORBA::AttributeDef_var attr = CORBA::AttributeDef::_narrow(c[j]);
    assert (!CORBA::is_nil(attr));
    if( as_pure_virtual )
      o << "virtual ";
    CORBA::IDLType_var type_id = attr->type_def();
    CORBA::String_var n = attr->name();
    emit_type_for_result( type_id );
    o << " " << ID( n.in() ) << "()";
    if( as_pure_virtual )
      o << " = 0";
    o << ";" << endl;
    if( attr->mode() == CORBA::ATTR_NORMAL ) {
      if( as_pure_virtual )
	o << "virtual ";
      o << "void " << ID( n.in() ) << "( ";
      emit_type_for_param( type_id, CORBA::PARAM_IN );
      o << " value )";
      if( as_pure_virtual )
	o << " = 0";
      o << ";" << endl;
    }
  }

  if (c->length()) {
    o << endl;
  }

  // Emit operations
  c = in->contents (CORBA::dk_Operation, 1);
  for( CORBA::ULong j0 = 0; j0 < c->length(); j0++ ) {
    CORBA::OperationDef_var op = CORBA::OperationDef::_narrow(c[j0]);
    assert (!CORBA::is_nil (op));
    if( as_pure_virtual )
      o << "virtual ";
    CORBA::IDLType_var type_id = op->result_def();
    CORBA::String_var n = op->name();
    emit_type_for_result( type_id );
    o << " " << ID( n.in() ) << "(";
    CORBA::ParDescriptionSeq_var p = op->params();
    CORBA::ULong k;
    for( k = 0; k < p->length(); k++ ) {
      if( k != 0 )
	o << ",";
      o << " ";
      emit_type_for_param( p[ k ].type_def, p[ k ].mode );
      o << " " << ID(p[ k ].name);
    }

    // Do we have a context?
    CORBA::ContextIdSeq_var ctx = op->contexts();
    
    if( ctx->length() > 0 ) {
      if( p->length() > 0 )
	o << ", ";
      o << "CORBA::Context_ptr _ctx";
    }
    
    if( k != 0 || ctx->length() > 0 )
      o << " ";
    o << ")";
    if( as_pure_virtual )
      o << " = 0";
    o << ";" << endl;
  }

  if (c->length()) {
    o << endl;
  }

  // Emit value state
  bool pub = true;
  c = in->contents (CORBA::dk_ValueMember, 1);
  for( CORBA::ULong j1=0; j1 < c->length(); j1++ ) {
    CORBA::ValueMemberDef_var vmd = CORBA::ValueMemberDef::_narrow(c[j1]);
    assert (!CORBA::is_nil (vmd));

    if (vmd->access() == CORBA::PRIVATE_MEMBER && pub) {
      o << exdent << "protected:" << indent << endl;
      pub = false;
    }
    else if (vmd->access() == CORBA::PUBLIC_MEMBER && !pub) {
      o << exdent << "public:" << indent << endl;
      pub = true;
    }

    // mapping as for union members
    CORBA::IDLType_var m_type = vmd->type_def();
    CORBA::String_var m_name = vmd->name();
    emit_union_member_decl( m_type, m_name.in(), true );
  }

  if (c->length()) {
    o << endl;
  }
}

void CodeGenCPPCommon::emitLocalDecls( CORBA::Container_ptr in )
{
  CORBA::ContainedSeq_var c;
  c = in->contents( CORBA::dk_all, 1 );
  for( CORBA::ULong i = 0; i < c->length(); i++ ) {
    switch( c[ i ]->def_kind() ) {
    case CORBA::dk_Operation:
    case CORBA::dk_Attribute:
    case CORBA::dk_ValueMember:
      // Operation & attribute declarations are generated in emitPrototypes()
      break;
    case CORBA::dk_Struct:
      {
	CORBA::StructDef_var s = CORBA::StructDef::_narrow( c[ i ] );
	emit_Struct( s );
	break;
      }
    case CORBA::dk_Union:
      {
	CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( c[ i ] );
	emit_Union( u );
	break;
      }
    case CORBA::dk_Constant:
      {
	CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( c[ i ] );
	emit_Constant( co );
	break;
      }
    case CORBA::dk_Exception:
      {
	CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( c[ i ] );
	emit_Exception( e );
	break;
      }
    case CORBA::dk_Enum:
      {
	CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( c[ i ] );
	emit_Enum( e );
	break;
      }
    case CORBA::dk_Alias:
      {
	CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( c[ i ] );
	emit_Alias( a );
	break;
      }
    case CORBA::dk_Native:
      {
	CORBA::NativeDef_var n = CORBA::NativeDef::_narrow( c[ i ] );
	emit_Native( n );
	break;
      }
    case CORBA::dk_Value:
      {
	CORBA::ValueDef_var v = CORBA::ValueDef::_narrow( c[ i ] );
	emit_Value( v );
	break;
      }
    case CORBA::dk_ValueBox:
      {
	CORBA::ValueBoxDef_var v = CORBA::ValueBoxDef::_narrow( c[ i ] );
	emit_ValueBox( v );
	break;
      }
    default:
      assert( 0 );
    }
  }
}

void
CodeGenCPPCommon::emit_StringDef( CORBA::StringDef_ptr s )
{
  assert( s->def_kind() == CORBA::dk_String );

  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );

  o.switchStream( 1 );
  
  CORBA::TypeCode_var type_tc = s->type();
	  
  // Must be a bounded string
  assert( type_tc->length() > 0 );
  o << "extern CORBA::TypeCodeConst _tc_string_";
  o << type_tc->length();
  o << ";" << endl << endl;

  o.switchStream( 0 );

  restore_name_prefix();
}

void
CodeGenCPPCommon::emit_WstringDef( CORBA::WstringDef_ptr ws )
{
  assert( ws->def_kind() == CORBA::dk_Wstring );

  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );
  
  o.switchStream( 1 );
  
  CORBA::TypeCode_var type_tc = ws->type();
	  
  // Must be a bounded wstring
  assert( type_tc->length() > 0 );
  o << "extern CORBA::TypeCodeConst _tc_wstring_";
  o << type_tc->length();
  o << ";" << endl << endl;

  o.switchStream( 0 );

  restore_name_prefix();
}

void
CodeGenCPPCommon::emit_SequenceDef( CORBA::SequenceDef_ptr s )
{
  assert( s->def_kind() == CORBA::dk_Sequence );

  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );

  o.switchStream( 1 );
  
  // We need to generate the prototypes iff the option --any was given,
  // or we have a sequence of a base type. The latter need to be generated
  // because we don´t #include <mico/basic_seq.h> for compiling performance
  // reasons
  // kay: we dont need prototyepes for sequences of base types if
  //      any operator generation is turned off 
  if( _params.any ) {
    CORBA::TypeCode_var type_tc = s->type();
    o << "void operator<<=( CORBA::Any &_a, const ";
    emit_sequence( s );
    o << " &_s );" << endl;
    o << "void operator<<=( CORBA::Any &_a, ";
    emit_sequence( s );
    o << " *_s );" << endl;

    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    emit_sequence( s );
    o << " &_s );" << endl;
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    emit_sequence( s );
    o << " *&_s );" << endl << endl;
  }

  if( !is_base_sequence( s ) )
    emit_marshal_prototype( s );
  
  o.switchStream( 0 );

  restore_name_prefix();
}

void
CodeGenCPPCommon::emit_FixedDef( CORBA::FixedDef_ptr f )
{
  assert( f->def_kind() == CORBA::dk_Fixed );

  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );

  o.switchStream( 1 );

  CORBA::TypeCode_var type_tc = f->type();
  string fixed_name = "Fixed_";
  fixed_name += xdec( type_tc->fixed_digits() );
  fixed_name += "_";
  if( type_tc->fixed_scale() < 0 )
    fixed_name += string( "n" ) +
      xdec( -( type_tc->fixed_scale() ) );
  else
    fixed_name += xdec( type_tc->fixed_scale() );
  
  // We have to generate _var and _out type for a Fixed,
  // because unlike anonymous types, it can be passed as a
  // parameter type [20.11.1]
  
  // Emit _var type for Fixed
  o << "typedef TFixVar<";
  emit_fixed( f );
  o << " > " << fixed_name << "_var;" << endl;
  
  // Emit _out for Fixed
  o << "typedef ";
  emit_fixed( f );
  o << "& " << fixed_name << "_out;" << endl;
  
  // Emit TypeCode for Fixed
  if( _params.typecode ) {
    o << "extern CORBA::TypeCodeConst ";
    emit_type_code_name( f );
    o << ";" << endl;
  }

  // Emit any marshalling operators
  if( _params.any ) {
    o << "void operator<<=( CORBA::Any &_a, const ";
    emit_fixed( f );
    o << " &_f );" << endl;
    o << "void operator<<=( CORBA::Any &_a, ";
    emit_fixed( f );
    o << " *_f );" << endl;

    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    emit_fixed( f );
    o << " &_f );" << endl;
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    emit_fixed( f );
    o << " *&_f );" << endl << endl;
  }

  emit_marshal_prototype( f );

  o.switchStream( 0 );

  restore_name_prefix();
}

void
CodeGenCPPCommon::emit_ArrayDef( CORBA::ArrayDef_ptr a )
{
  assert( a->def_kind() == CORBA::dk_Array );

  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );

  o.switchStream( 1 );
  
  // SII marshaller
  emit_marshal_prototype( a );
  
  o.switchStream( 0 );

  restore_name_prefix();
}

void CodeGenCPPCommon::emit_Interface( CORBA::InterfaceDef_ptr in )
{
  assert( in->def_kind() == CORBA::dk_Interface );

  set_name_prefix( in );
  
  emit_ForwardDcl( in );
  
  CORBA::String_var n = in->name();
  string className = (const char *) ID(n);
  
  o << endl;

  //-----COMMON------------------------------------------------------
  o << "// Common definitions for interface " << className << endl;
  
  CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
  bool has_abstract_base = false;
  bool has_concrete_base = false;

  for (CORBA::ULong j0=0; j0<bases->length(); j0++) {
    if (bases[j0]->is_abstract()) {
      has_abstract_base = true;
    }
    else {
      has_concrete_base = true;
    }
  }

  o << "class " << className << " : " << indent << endl;
 
  if (in->is_abstract() && !has_abstract_base) {
    o << "virtual public CORBA::AbstractBase";
    if (bases->length()) o << "," << endl;
  }
  else if (!in->is_abstract()) {
    if (has_abstract_base && !has_concrete_base) {
      o << "virtual public CORBA::MixedBase";
      if (bases->length()) o << "," << endl;
    }
    else if (!has_abstract_base && !has_concrete_base) {
      o << "virtual public CORBA::Object";
      if (bases->length()) o << "," << endl;
    }
  }

  for (CORBA::ULong j1=0; j1<bases->length(); j1++) {
    CORBA::String_var base_name = bases[ j1 ]->absolute_name();
    o << "virtual public " << ID(base_name);
    if( j1 + 1 != bases->length() ) {
      o << ",";
      o << endl;
    }
  }
  o << exdent << endl;
  o << BL_OPEN;
  
  o << "public:" << indent << endl;

#ifdef _VC_NAMESPACE_BUG
  // Because Visual has problem with virtual base classes and
  // namespaces we need to make a typedef which will be
  // used by the code instead of the absolute path
  // typedef ::CosEventComm::PushSupplier _VCHACK_CosEventComm__PushSupplier
  // interestingly enough using the typedef works
  //  _VCHACK_CosEventComm__PushSupplier::_narrow_helper(...)
  
  for( CORBA::ULong i = 0; i < bases->length(); i++ ) {
    CORBA::String_var base_name = bases[ i ]->absolute_name();
    string name = ID (base_name);
    vc_emit_workaround ("", name);
  }
#endif
  
  o << "virtual ~" << className << "();" << endl;
  o << endl;

  o << "#ifdef HAVE_TYPEDEF_OVERLOAD" << endl;
  o << "typedef " << className << "_ptr _ptr_type;" << endl;
  o << "typedef " << className << "_var _var_type;" << endl;
  o << "#endif" << endl;
  o << endl;

  o << "static " << className << "_ptr _narrow( CORBA::Object_ptr obj );"
    << endl;
  o << "static " << className << "_ptr _narrow( CORBA::AbstractBase_ptr obj );"
    << endl;

  o << "static " << className << "_ptr _duplicate( ";
  o << className << "_ptr _obj )" << endl << BL_OPEN;
  if (!in->is_abstract()) {
    o << "CORBA::Object::_duplicate (_obj);" << endl;
  }
  else {
    o << "CORBA::AbstractBase::_duplicate (_obj);" << endl;
  }
  o << "return _obj;" << endl;
  o << BL_CLOSE << endl;

  o << "static " << className << "_ptr _nil()" << endl << BL_OPEN;
  o << "return 0;" << endl << BL_CLOSE << endl;

  /*
   * If we are abstract, support downcasting from ValueBase
   */

  if (in->is_abstract()) {
    o << "static " << className << "_ptr _downcast( CORBA::ValueBase * vb );"
      << endl;
  }

  /*
   * If we are concrete but have an abstract base, implement _to_object()
   */

  if (has_abstract_base && !in->is_abstract()) {
    o << "CORBA::Object_ptr _to_object();" << endl;
  }
  
  o << "virtual void *_narrow_helper( const char *repoid );" << endl;

  if (!_params.pseudo) {
    o << "static vector<CORBA::Narrow_proto> *_narrow_helpers;" << endl;
    o << "static bool _narrow_helper2( CORBA::Object_ptr obj );" << endl;
  }

  o << endl;

  // Emit local declarations
  emitLocalDecls( in );
  
  // Generate prototypes
  emitPrototypes( in, true );
  
  // Generate epilogue
  o << exdent << "protected:" << indent << endl;
  o << className << "() {};" << exdent << endl;
  o << "private:" << indent << endl;
  o << className << "( const " << className << "& );" << endl;
  o << "void operator=( const " << className << "& );" << exdent << endl;
  o << BL_CLOSE_SEMI << endl;

  if (!_params.pseudo) {
    // Emit TypeCode for interface
    if( _params.typecode ) {
      CORBA::Container_var def_in = in->defined_in();
      if( def_in->def_kind() == CORBA::dk_Repository )
	// We are on the toplevel
	o << "extern";
      else if( def_in->def_kind() == CORBA::dk_Module )
	// The current scope is not top level (inside a module)
    o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");
      else
	// The current scope is not top level (not inside a module)
	o << "static";
      o << " CORBA::TypeCodeConst _tc_" << className << ";" << endl << endl;
    }

    o.switchStream( 1 );
    save_name_prefix();
    set_name_prefix( CORBA::Container::_nil() );
    if( _params.any ) {
      // copying operator<<= for interface
      o << "void operator<<=( CORBA::Any &a, const ";
      emit_idl_type_name( in );
      o << " obj );" << endl;

      // non-copying operator<<= for interface
      o << "void operator<<=( CORBA::Any &a, ";
      emit_idl_type_name( in );
      o << "* obj_ptr );" << endl;

      // operator>>= for interface
      o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
      emit_idl_type_name( in );
      o << " &obj );" << endl << endl;
    }

    emit_marshal_prototype( in );
    
    o.switchStream( 0 );
    restore_name_prefix();
  }

  if (_params.pseudo) {
    // No stubs or skeletons for PIDL
    o << endl;
    return;
  }

  //-----STUB--------------------------------------------------------
  o << "// Stub for interface " << className << endl;
  
  o << "class " << className << _STUB << ":" << indent << endl;

  /*
   * For abstract interfaces, we add CORBA::Object to the stub's heritage
   */

  if (in->is_abstract()) {
    o << "virtual public CORBA::Object," << endl;
  }

  o << "virtual public " << className;
  for( CORBA::ULong j2 = 0; j2 < bases->length(); j2++ ) {
    CORBA::String_var base_name = bases[ j2 ]->absolute_name();
    o << "," << endl << "virtual public " << ID(base_name) << _STUB;
  }
  o << exdent << endl;

  o << BL_OPEN;
  
  o << "public:" << indent << endl;
  o << "virtual ~" << className << _STUB << "();" << endl;
  
  // Generate prototypes
  emitPrototypes( in, false );
  
  // Generate epilogue
  o << exdent << "private:" << indent << endl;
  o << "void operator=( const " << className << _STUB << "& );" << endl;
  o << exdent << BL_CLOSE_SEMI << endl;

  if (_params.poa && _params.poa_stubs) {
    //-----STUB2-------------------------------------------------------
    // This stub for objects in a colocated POA
    o << "#ifndef MICO_CONF_NO_POA" << endl << endl;
    o << "class " << className << _STUB << "_clp :" << indent << endl;
    o << "virtual public " << className << _STUB << "," << endl;
    
    if (bases->length() == 0) {
      o << "virtual public PortableServer::StubBase" << exdent << endl;
    }
    else {
      for (CORBA::ULong i2=0; i2<bases->length(); i2++) {
	CORBA::String_var base_name = bases[i2]->absolute_name();
	o << "virtual public " << ID(base_name) << _STUB << "_clp";
	if (i2+1 != bases->length()) {
	  o << ",";
	}
	o << endl;
      }
      o << exdent;
    }
    
    o << BL_OPEN;
    o << "public:" << indent << endl;
    o << className << _STUB << "_clp (PortableServer::POA_ptr, CORBA::Object_ptr);" << endl;
    o << "virtual ~" << className << _STUB << "_clp ();" << endl;
    
    // Generate prototypes
    emitPrototypes( in, false );
    
    // Generate epilogue
    o << exdent << "protected:" << indent << endl;
    o << className << _STUB << "_clp ();" << endl;
    o << exdent << "private:" << indent << endl;
    o << "void operator=( const " << className << _STUB << "_clp & );" << endl;
    o << exdent << BL_CLOSE_SEMI << endl;
    o << "#endif // MICO_CONF_NO_POA" << endl << endl;
  }

  //-----SKELETON----------------------------------------------------
  // Generate skeleton class for interface [18.3.1(6)], [18.4.5]
  if (_params.boa && !in->is_abstract()) {
    o << "class " << className << _SKEL << " :" << indent << endl;
    o << "virtual public ";
    o << "StaticMethodDispatcher," << endl;
    o << "virtual public " << className << exdent << endl;
    o << BL_OPEN;
    o << "public:" << indent << endl;
    o << className << _SKEL;
    o << "( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );";
    o << endl;
    o << "virtual ~" << className << _SKEL << "();" << endl;
    o << className << _SKEL << "( CORBA::Object_ptr obj );" << endl;
    o << "virtual bool dispatch( ";
    o << "CORBA::StaticServerRequest_ptr";
    o << " _req, CORBA::Environment &_env );" << endl;
    o << className << "_ptr _this();" << exdent << endl << endl;
    o << BL_CLOSE_SEMI << endl;
  }
}

/*
 * Generates default constructor, copy constructor and assignment
 * operator for structs and unions. These have to be generated due
 * to a g++ bug (g++ doesn't expand templates properly for the implicit
 * generated versions of these methods). Note that according to
 * the CORBA2 specs these shouldn't be defined (see [16.9(1)])
 */
void
CodeGenCPPCommon::emit_DefaultMembers( char *name )
{
  o << "#ifdef HAVE_EXPLICIT_STRUCT_OPS" << endl;

  // Default constructor
  o << name << "();" << endl;

  // Destructor
  o << "~" << name << "();" << endl;

  // Copy constructor
  o << name << "( const " << name << "& s );" << endl;
  
  // Assignment operator
  o << name << "& operator=( const " << name << "& s );" << endl;

  o << "#endif //HAVE_EXPLICIT_STRUCT_OPS" << endl;
  o << endl;
}
  


void CodeGenCPPCommon::emit_Struct( CORBA::StructDef_ptr s )
{
  assert( s->def_kind() == CORBA::dk_Struct );

  CORBA::String_var tmp = s->name();
  CORBA::String_var name = (const char *) ID(tmp);
  CORBA::StructMemberSeq_var m = s->members();
  CORBA::TypeCode_var tc = s->type();

  // Emit _var and _out type
  o << "struct " << name << ";" << endl;
  o << "typedef " << TVAR( tc ) << "<" << name << "> "
    << name << "_var;" << endl;
  o << "typedef " << name << "_var " << name << "_out;";
  o << endl << endl;

  o << "struct " << name << " " << BL_OPEN;
  o << "#ifdef HAVE_TYPEDEF_OVERLOAD" << endl;
  o << "typedef " << name << "_var _var_type;" << endl;
  o << "#endif" << endl;
  emitLocalDecls( s );
  emit_DefaultMembers( name );
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    // need typedefs for anonymous sequence members
    if (m[i].type->is_sequence() && !m[i].type->is_alias()) {
      o << "typedef ";
      emit_sequence (m[i].type_def);
      o << " _" << ID(m[i].name) << "_seq;" << endl;
      o << "_" << ID(m[i].name) << "_seq ";
      o << ID(m[i].name) << ";" << endl;
    }
    else {
      emit_type_for_variable( m[ i ].type_def, automatic );
      o << " " << ID(m[ i ].name);
      emit_array_suffix( m[ i ].type_def );
      o << ";" << endl;
    }
  }

  if (contains_a_valuetype (s)) {
    o << "// we contain a valuetype" << endl;
    o << "CORBA::Long _count_refs (CORBA::ValueBase::visited * = 0);" << endl;
    o << "void _release_members ();" << endl;
  }

  o << BL_CLOSE_SEMI << endl;

  // Emit TypeCode for struct
  if( _params.typecode && tc->is_freestanding() ) {
    CORBA::Container_var def_in = s->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");
    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << name << ";" << endl << endl;
  }
  
  // operator<<=
  o.switchStream( 1 );
  if( _params.any ) {
    tmp = s->absolute_name();
    CORBA::String_var abs_name = (const char *) ID(tmp);
    o << "void operator<<=( CORBA::Any &_a, const ";
    o << abs_name << " &_s );" << endl;
    o << "void operator<<=( CORBA::Any &_a, ";
    o << abs_name << " *_s );" << endl;
  
    // operator>>=
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    o << abs_name << " &_s );" << endl;
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    o << abs_name << " *&_s );" << endl << endl;
  }

  emit_marshal_prototype( s );
  
  o.switchStream( 0 );
}



void CodeGenCPPCommon::emit_Union( CORBA::UnionDef_ptr u )
{
  assert( u->def_kind() == CORBA::dk_Union );

  CORBA::String_var tmp = u->name();
  CORBA::String_var name = (const char *) ID(tmp);
  CORBA::UnionMemberSeq_var members = u->members();
  CORBA::TypeCode_var union_tc = u->type();

  // Emit _var and _out type
  o << "class " << name << ";" << endl;
  o << "typedef " << TVAR( union_tc ) << "<"
    << name << "> " << name << "_var;" << endl;
  o << "typedef " << name << "_var " << name << "_out;";
  o << endl << endl;

  o << "class " << name << " " << BL_OPEN;
  o << "public:" << indent << endl;
  o << "#ifdef HAVE_TYPEDEF_OVERLOAD" << endl;
  o << "typedef " << name << "_var _var_type;" << endl;
  o << "#endif" << endl;
  emitLocalDecls( u );

  // Emit declaration for the discriminator
  CORBA::IDLType_var discr = u->discriminator_type_def();
  emit_type_for_variable( discr, automatic );
  o << " _discriminator;" << endl << endl;

  // Generate member variables. Note: these can't be put in a C++
  // union as one would probably expect. The reason is that MICO
  // struct's are mapped to C++ struct's with explicit default
  // constructors and destructors (this is necessary due to a
  // g++ bug). But struct's with constructors are not allowed
  // in an union.
  CORBA::String_var last_name;
  last_name = (const char *) "";
  o << "struct __m " << BL_OPEN;

  bool has_explicit_default = false;
  
  for( CORBA::ULong i = 0; i < members->length(); i++ ) {
    CORBA::UnionMember& m = members[ i ];
    CORBA::TypeCode_var tc = members[ i ].label.type();
    if( tc->is_octet() )
      has_explicit_default = true;

    if( strcmp( last_name, m.name ) == 0 )
      // We already generated a declaration for this name
      continue;
    emit_type_for_variable( m.type_def, automatic );
    o << " " << ID(m.name);
    emit_array_suffix( m.type_def );
    o << ";" << endl;
    last_name = m.name;
  }
  o << exdent << "} _m;" << endl << endl;
  
  o << exdent << "public:" << indent << endl;

  emit_DefaultMembers( name );
  o << endl;
  
  // Emit discriminator functions
  o << "void _d( ";
  emit_type_for_param( discr, CORBA::PARAM_IN );
  o << " _p );" << endl;
  emit_type_for_result( discr );
  o << " _d() const;" << endl << endl;

  // Generate member accessor functions
  last_name = (const char *) "";
  for( CORBA::ULong i0 = 0; i0 < members->length(); i0++ ) {
    CORBA::UnionMember &m = members[ i0 ];

    if( strcmp( last_name, m.name ) == 0 )
      continue;
    last_name = m.name;
    
    CORBA::IDLType_var m_type = CORBA::IDLType::_duplicate( m.type_def );
    emit_union_member_decl( m_type, m.name.in(), false );
  }
  if( !has_explicit_default ) {
    // This union has no explicit default case label
    string default_label =
      generate_union_default_case_label( discr.in(), members.inout() );
    if( default_label.length() > 0 ) {
      // We have a case label left for an implicit default member
      o << "void _default();" << endl << endl;
    }
  }

  if (contains_a_valuetype (u)) {
    o << "// we contain a valuetype" << endl;
    o << "CORBA::Long _count_refs (CORBA::ValueBase::visited * = 0);" << endl;
    o << "void _release_members ();" << endl;
  }

  o << exdent << BL_CLOSE_SEMI << endl;
      
  // Emit TypeCode for union
  if( _params.typecode && union_tc->is_freestanding() ) {
    CORBA::Container_var def_in = u->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");

    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << name << ";" << endl << endl;
  }
  
  // operator<<=
  o.switchStream( 1 );
  if( _params.any ) {
    tmp = u->absolute_name();
    CORBA::String_var abs_name = (const char *) ID(tmp);
    o << "void operator<<=( CORBA::Any &_a, const ";
    o << abs_name << " &_u );" << endl;
    o << "void operator<<=( CORBA::Any &_a, ";
    o << abs_name << " *_u );" << endl;
    
    // operator>>=
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    o << abs_name << " &_u );" << endl;
    o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
    o << abs_name << " *&_u );" << endl << endl;
  }

  // SII marshaller
  emit_marshal_prototype( u );
  
  o.switchStream( 0 );
}



void CodeGenCPPCommon::emit_Constant( CORBA::ConstantDef_ptr c )
{
  assert( c->def_kind() == CORBA::dk_Constant );
  CORBA::String_var tmp = c->name();
  CORBA::String_var name = (const char *) ID(tmp);
  CORBA::Container_var def_in = c->defined_in();

  if( def_in->def_kind() == CORBA::dk_Repository ||
      def_in->def_kind() == CORBA::dk_Interface ) {
    o << "static const ";
  } else {
    o << "MICO_EXPORT_CONST_DECL const ";
  }
  CORBA::IDLType_var type = c->type_def();
  emit_base_type( type );
  o << " " << name;

  // If this const is declared on a nested scope, we need to
  // defer its initialization because some C++ compilers
  // choke on this
  if( def_in->def_kind() == CORBA::dk_Repository ) {
    // Only initialize if we are on global scope
    o << " = ";
    if( type->def_kind() == CORBA::dk_Fixed )
      o << "(CORBA::LongDouble) ";
    CORBA::Any* a = c->value();
    CORBA::TypeCode_var tc = a->type();
    if( tc->kind() == CORBA::tk_wstring || tc->kind() == CORBA::tk_wchar )
      o << "L";
    o << a;
    delete a;
  }
  o << ";" << endl;
}



void CodeGenCPPCommon::emit_Exception( CORBA::ExceptionDef_ptr e )
{
  assert( e->def_kind() == CORBA::dk_Exception );

  CORBA::String_var tmp = e->name();
  CORBA::String_var name = (const char *) ID(tmp);

  tmp = e->absolute_name();
  if (!strncmp (tmp.in(), "::CORBA", 7))
    // workaround for Cygnus CDK ...
    o << "struct " << name << " : public UserException " << BL_OPEN;
  else
    o << "struct " << name << " : public CORBA::UserException " << BL_OPEN;

  CORBA::StructMemberSeq_var m = e->members();
  emitLocalDecls( e );
  emit_DefaultMembers( name );

  // emit constructor for member initialization
  if( m->length() > 0 ) {
    /*
     * when defining a constructor that takes some arguments, we also
     * need to explicitly define a default constructor. Such a constructor
     * is already defined by emit_DefaultMembers if
     * HAVE_EXPLICIT_STRUCT_OPTS
     */
    o << "#ifndef HAVE_EXPLICIT_STRUCT_OPS" << endl;
    o << name << "();" << endl;
    o << "#endif //HAVE_EXPLICIT_STRUCT_OPS" << endl;

    // emit constructor for member initialization
    o << name << "( ";
    for( CORBA::ULong i = 0; i < m->length(); i++ ) {
      if( i != 0 )
	o << ", ";
      emit_type_for_param( m[ i ].type_def, CORBA::PARAM_IN );
      o << " _m" << i;
      emit_array_suffix( m[i].type_def );
    }
    o << " );" << endl;
  }
  o << endl;

  // Emit backward compatibility operators
  o << "#ifdef HAVE_STD_EH" << endl;
  o << name << " *operator->() { return this; }" << endl;
  o << name << "& operator*() { return *this; }" << endl;
  o << "operator " << name << "*() { return this; }" << endl;
  o << "#endif // HAVE_STD_EH" << endl;
  o << endl;
  
  o << "void _throwit() const;" << endl;
  o << "const char *_repoid() const;" << endl;
  o << "void _encode( CORBA::DataEncoder &en ) const;" << endl;
  o << "void _encode_any( CORBA::Any &a ) const;" << endl;
  o << "CORBA::Exception *_clone() const;" << endl;
  o << "static " << name << " *EXCEPTION_DOWNCAST( CORBA::Exception *ex );"
    << endl;
  o << "static const " << name
    << " *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );" << endl;
  
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    emit_type_for_variable( m[ i ].type_def, automatic );
    o << " " << ID(m[ i ].name);
    emit_array_suffix( m[ i ].type_def );
    o << ";" << endl;
  }
  o << BL_CLOSE_SEMI << endl;

  // Emit _catch types
  o << "#ifdef HAVE_STD_EH" << endl;
  o << "typedef " << name << " " << name << "_catch;" << endl;
  o << "#else" << endl;
  o << "typedef ExceptVar<" << name << "> " << name << "_var;" << endl;
  o << "typedef " << name << "_var " << name << "_out;" << endl;
  o << "typedef " << name << "_var " << name << "_catch;" << endl;
  o << "#endif // HAVE_STD_EH" << endl;
  o << endl;

  // Emit TypeCode for exception
  if( _params.typecode ) {
    CORBA::Container_var def_in = e->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");
    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << name << ";" << endl << endl;
  }

  // operator<<=
  o.switchStream( 1 );
  if( _params.any ) {
    tmp = e->absolute_name();
    CORBA::String_var abs_name = (const char *) ID(tmp);
    o << "void operator<<=( CORBA::Any &a, const ";
    o << abs_name << " &e );" << endl;
    o << "void operator<<=( CORBA::Any &a, ";
    o << abs_name << " *e );" << endl;
    
    // operator>>=
    o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
    o << abs_name << " &e );" << endl << endl;
    o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
    o << abs_name << " *&e );" << endl << endl;
  }

  // SII marshaller
  emit_marshal_prototype( e );
  
  o.switchStream( 0 );
}



void CodeGenCPPCommon::emit_Enum( CORBA::EnumDef_ptr e )
{
  assert( e->def_kind() == CORBA::dk_Enum );

  CORBA::String_var tmp = e->name();
  CORBA::String_var name = (const char *) ID(tmp);
  o << "enum " << name << " " << BL_OPEN;

  CORBA::EnumMemberSeq_var m = e->members();
  
  for( CORBA::ULong i = 0; i < m->length(); i++ ) {
    if( i != 0 )
      o << "," << endl;
    o << ID(m[ i ]);
    if( i == 0 )
      o << " = 0";
  }
  o << endl;
  o << BL_CLOSE_SEMI << endl;

  // Emit _out for enum
  o << "typedef " << name << "& " << name << "_out;";
  o << endl << endl;
  
  // Emit TypeCode for enum
  if( _params.typecode ) {
    CORBA::Container_var def_in = e->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");

    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << name << ";" << endl << endl;
  }

  // operator<<=
  o.switchStream( 1 );
  if( _params.any ) {
    tmp = e->absolute_name();
    CORBA::String_var abs_name = (const char *) ID(tmp);
    o << "void operator<<=( CORBA::Any &a, const ";
    o << abs_name << " &e );" << endl << endl;
    
    // operator>>=
    o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
    o << abs_name << " &e );" << endl << endl;
  }

  emit_marshal_prototype( e );
  
  o.switchStream( 0 );
}



void CodeGenCPPCommon::emit_Alias( CORBA::AliasDef_ptr a )
{
  assert( a->def_kind() == CORBA::dk_Alias );

  CORBA::IDLType_var orig = a->original_type_def();
  assert( !CORBA::is_nil( orig ) );
  
  CORBA::TypeCode_var orig_tc = orig->type();

  CORBA::String_var tmp = a->name();
  CORBA::String_var name = (const char *) ID(tmp);
  
  if( orig_tc->is_string() ) {
    o << "typedef char* " << name << ";" << endl;
    o << "typedef CORBA::String_var ";
    o << name << "_var;" << endl;
    o << "typedef CORBA::String_out ";
    o << name << "_out;" << endl << endl;
  } else if( orig_tc->is_wstring() ) {
    o << "typedef CORBA::WChar* " << name << ";" << endl;
    o << "typedef CORBA::WString_var ";
    o << name << "_var;" << endl;
    o << "typedef CORBA::WString_out ";
    o << name << "_out;" << endl << endl;
  } else if( orig_tc->is_objref() ) {
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
      if( !CORBA::is_nil( in ) ) {
	// Must be a regular object reference
	abs_name = in->absolute_name();
      } else {
	// We have an "Object" object reference
	abs_name = (const char *) "CORBA::Object";
      }
    }
    abs_name = (const char *) ID(abs_name);

    o << "typedef " << abs_name << " " << name << ";" << endl;
    o << "typedef " << abs_name << "_ptr " << name << "_ptr;" << endl;
    o << "typedef " << abs_name << "Ref " << name << "Ref;" << endl;
    o << "typedef " << abs_name << "_var " << name << "_var;" << endl;
    o << "typedef " << name << "_var " << name << "_out;" << endl;
    o << endl;
  } else if( orig_tc->is_valuetype() ) {
    CORBA::String_var abs_name;
    
    if( orig_tc->kind() == CORBA::tk_alias ) {
      // we have an alias of an alias
      CORBA::AliasDef_var alias = CORBA::AliasDef::_narrow( orig );
      assert( !CORBA::is_nil( alias ) );
      abs_name = alias->absolute_name();
    } else {
      // gotta be a value or a value box
      assert( orig_tc->kind() == CORBA::tk_value ||
	      orig_tc->kind() == CORBA::tk_value_box );
      CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( orig );
      CORBA::ValueBoxDef_var vb = CORBA::ValueBoxDef::_narrow( orig );
      if( !CORBA::is_nil( val ) ) {
	abs_name = val->absolute_name();
      } else if( !CORBA::is_nil( vb ) ) {
	abs_name = vb->absolute_name();
      }
      else {
	assert (0);
      }
    }
    abs_name = (const char *) ID(abs_name);
    o << "typedef " << abs_name << " " << name << ";" << endl;
    o << "typedef " << abs_name << "_ptr " << name << "_ptr;" << endl;
    o << "typedef " << abs_name << "Ref " << name << "Ref;" << endl;
    o << "typedef " << abs_name << "_var " << name << "_var;" << endl;
    o << "typedef " << name << "_var " << name << "_out;" << endl;
    o << endl;
  } else {
    o << "typedef ";
    emit_type_for_variable( orig, automatic );
    o << " " << name;
    emit_array_suffix( orig );
    o << ";" << endl;
    
    if( orig_tc->is_array() ) {

      // Determine the base type of the array (i.e. remove all
      // aliases and array declarations)
      CORBA::IDLType_var base_type = CORBA::IDLType::_duplicate( orig );
      CORBA::DefinitionKind dk = base_type->def_kind();
      while( dk == CORBA::dk_Alias || dk == CORBA::dk_Array ) {
	if( dk == CORBA::dk_Alias ) {
	  CORBA::AliasDef_var tmp = CORBA::AliasDef::_narrow( base_type );
	  assert( !CORBA::is_nil( tmp ) );
	  base_type = tmp->original_type_def();
	}
	if( dk == CORBA::dk_Array ) {
	  CORBA::ArrayDef_var tmp = CORBA::ArrayDef::_narrow( base_type );
	  assert( !CORBA::is_nil( tmp ) );
	  base_type = tmp->element_type_def();
	}
	dk = base_type->def_kind();
      }
	
      CORBA::ULong num_elem = compute_num_array_elem( orig_tc );

      if( orig_tc->kind() != CORBA::tk_alias ) {
	
	// Array slice
	o << "typedef ";
	emit_type_for_variable( orig, automatic );
	o << " " << name << "_slice";
	emit_array_slice_suffix( orig );
	o << ";" << endl;
	
	// _var for Array
	o << "typedef Array";
	o << (orig_tc->is_variable() ? "Var" : "Fix") << "Var<";
	emit_type_for_variable( base_type, automatic );
	o << "," << name << "_slice," << name << ",";
	o << num_elem << "> ";
	o << name << "_var;" << endl;
	
	// _out for Array
	o << "typedef " << name << "_var " << name << "_out;" << endl;
	
	// _forany for Array
	// First generate a dummy type that will be used to
	// disambiguate similar structural array types
	o << "enum _dummy_" << name << " { _dummy_" << name << "_0 };" << endl;
	o << "typedef Array";
	o << (orig_tc->is_variable() ? "Var" : "Fix") << "ForAny<";
	emit_type_for_variable( base_type, automatic );
	o << "," << name << "_slice," << name << ",";
	o << num_elem << ",_dummy_" << name << "> ";
	o << name << "_forany;" << endl;

	// Generate helping #define for second argument since it
	// may contain "," which confuse the preprocessor
	o << "#undef MICO_ARRAY_ARG" << endl;
	o << "#define MICO_ARRAY_ARG ";
	emit_type_for_variable( base_type, automatic );
	o << endl;
	
	// T_alloc for array
	o << "DECLARE_ARRAY_ALLOC(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;

	// T_dup for array
	o << "DECLARE_ARRAY_DUP(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;

	// T_free for array
	o << "DECLARE_ARRAY_FREE(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;

	// T_copy for array (MICO extension)
	o << "DECLARE_ARRAY_COPY(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;

	if( _params.any ) {
	  o.switchStream( 1 );
	  CORBA::String_var abs_name = a->absolute_name();
	  abs_name = (const char *) ID(abs_name);
	  
	  // operator<<=()
	  o << "void operator<<=( CORBA::Any &_a, const ";
	  o << abs_name << "_forany &_s );" << endl;
	  
	  // operator>>=()
	  o << "CORBA::Boolean operator>>=( const CORBA::Any &_a, ";
	  o << abs_name << "_forany &_s );" << endl;
	  o.switchStream( 0 );
	}
      } else {
	// We have an alias of an array

	// Array slice
	o << "typedef ";
	emit_type_for_variable( orig, automatic );
	o << "_slice " << name << "_slice";
	o << ";" << endl;
	
	// _var for Array
	o << "typedef ";
	emit_type_for_variable( orig, automatic );
	o << "_var " << name << "_var";
	o << ";" << endl;
	
	// _out for Array
	o << "typedef " << name << "_var " << name << "_out;" << endl;
	
	// _forany for Array
	o << "typedef ";
	emit_type_for_variable( orig, automatic );
	o << "_forany " << name << "_forany";
	o << ";" << endl;
	
	// Generate helping #define for second argument since it
	// may contain "," which confuse the preprocessor
	o << "#undef MICO_ARRAY_ARG" << endl;
	o << "#define MICO_ARRAY_ARG ";
	emit_type_for_variable( base_type, automatic );
	o << endl;
	
	// T_alloc for array
	o << "DECLARE_ARRAY_ALLOC(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;
	
	// T_dup for array
	o << "DECLARE_ARRAY_DUP(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;
	
	// T_free for array
	o << "DECLARE_ARRAY_FREE(" << name << ",MICO_ARRAY_ARG,"
	  << name << "_slice," << num_elem << ")" << endl;
      }
    }
  
    if( !orig_tc->is_base_type() && !orig_tc->is_enum() &&
	!orig_tc->is_array() ) {
      // We have to generate _var and _out types as well
      // First a hack for VC++. Since it cannot instantiate templates
      // of templates properly, we force an instantiation through
      // a dummy variable declaration
      o << "#ifdef _WINDOWS" << endl;
      o << "static " << name << " _dummy_" << name << ";" << endl;
      o << "#endif" << endl;
      
      o << "typedef ";
      if( orig_tc->is_sequence() ) {
	o << "TSeqVar<";
	emit_type_for_variable( orig, automatic );
	o << " >";
      } else {
	emit_type_for_variable( orig, automatic );
	o << "_var";
      }
      o << " " << name << "_var;" << endl;
      o << "typedef " << name << "_var " << name << "_out;" << endl << endl;
    }
  }

  // Emit TypeCode for alias
  if( _params.typecode ) {
    CORBA::Container_var def_in = a->defined_in();
    assert( !CORBA::is_nil( def_in ) );
    
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << (_params.windows_dll?"MICO_EXPORT_VAR_DECL":"MICO_EXPORT_TYPEVAR_DECL");
    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << name << ";" << endl << endl;
  }
}

void CodeGenCPPCommon::emit_Native( CORBA::NativeDef_ptr n )
{
  if (!_params.pseudo) {
    cerr << "error: native types only supported in locality constrained mode"
         << endl
         << "error: use idl compiler option --pseudo"
         << endl;
    exit (1);
  }
  CORBA::String_var tmp = n->name();
  CORBA::String_var name = (const char *) ID(tmp);
  tmp = n->absolute_name();
  o << "typedef MICO_Native";
  emit_mangled_name (tmp.in());
  o << " " << name << ";" << endl << endl;
}

void CodeGenCPPCommon::emit_Value( CORBA::ValueDef_ptr val )
{
  set_name_prefix( val );
  emit_ForwardDcl( val );

  CORBA::String_var n = val->name();
  string className = (const char *) ID(n);
  
  //-----COMMON------------------------------------------------------
  o << endl;
  o << "// Common definitions for valuetype " << className << endl;
  o << "class " << className << " : " << indent << endl;

  CORBA::ValueDef_var base_value = val->base_value ();
  CORBA::ValueDefSeq_var bases = val->abstract_base_values ();
  CORBA::InterfaceDefSeq_var supported = val->supported_interfaces ();

  /*
   * Inheritance for Valuetypes: We inherit from all base values, concrete
   * or not. According to the specs, we do not inherit from a concrete
   * supported interface (to avoid inheriting CORBA::Object), but we must
   * inherit an abstract supported interface.
   */

  if (CORBA::is_nil (base_value) && bases->length() == 0) {
    o << "virtual public CORBA::ValueBase";
  }
  else {
    if (!CORBA::is_nil (base_value)) {
      o << "virtual public ";
      CORBA::String_var base_name = base_value->absolute_name();
      o << ID(base_name);
      if (bases->length() > 0) {
	o << "," << endl;
      }
    }
    
    if (bases->length() > 0) {
      for (CORBA::ULong i=0; i<bases->length(); i++) {
	CORBA::String_var base_name = bases[i]->absolute_name();
	o << "virtual public " << ID(base_name);
	if (i+1 < bases->length()) {
	  o << "," << endl;
	}
      }
    }
  }

  if (supported->length() > 0) {
    for (CORBA::ULong i=0; i<supported->length(); i++) {
      if (supported[i]->is_abstract()) {
	CORBA::String_var supported_name = supported[i]->absolute_name();
	o << "," << endl << "virtual public " << ID(supported_name);
      }
    }
  }

  if (val->is_custom()) {
    o << "," << endl << "virtual public CORBA::CustomMarshal";
  }

  o << exdent << endl;

  o << BL_OPEN;
  o << "public:" << indent << endl;
  o << "static " << className << "* _downcast (CORBA::ValueBase *);" << endl;
  o << "static " << className << "* _downcast (CORBA::AbstractBase *);"
    << endl << endl;

  // Emit local declarations
  emitLocalDecls( val );

  // Generate prototypes
  emitPrototypes( val, true );

  // Emit prototypes for supported concrete interface
  if (supported->length() > 0) {
    for (CORBA::ULong i=0; i<supported->length(); i++) {
      if (!supported[i]->is_abstract()) {
	o << exdent << "public:" << indent << endl;
	emitPrototypes( supported[i], true );
      }
    }
  }
  
  // Generate epilogue
  o << exdent << "public:" << indent << endl;
  if (!val->is_abstract()) {
    o << "CORBA::ValueBase * _copy_value ();" << endl;
  }
  o << "CORBA::ValueDef_ptr get_value_def ();" << endl;
  o << "virtual void * _narrow_helper (const char *);" << endl;
  o << "void _get_marshal_info (vector<string> &, CORBA::Boolean &);" << endl;
  o << "void _marshal_members (CORBA::DataEncoder &);" << endl;
  o << "CORBA::Boolean _demarshal_members (CORBA::DataDecoder &);" << endl;
  if (check_for_possible_circle (val)) {
    o << "CORBA::Long _count_refs (CORBA::ValueBase::visited * = 0);" << endl;
    o << "void _release_members ();" << endl;
  }

  /*
   * If we support an abstract interface, implement _to_value()
   */

  if (supported->length() > 0) {
    bool supports_abstract = false;
    for (CORBA::ULong i=0; i<supported->length(); i++) {
      if (supported[i]->is_abstract()) {
	supports_abstract = true;
	break;
      }
    }
    if (supports_abstract) {
      o << "CORBA::ValueBase * _to_value ();" << endl;
    }
  }

  o << endl << exdent << "protected:" << indent << endl;
  o << className << " ();" << endl;
  o << "virtual ~" << className << " ();" << endl;
  if (!val->is_abstract() && !val->is_custom() &&
      !check_for_possible_circle (val)) {
    o << "void _copy_members (const " << className << "&);" << endl;
  }
  o << endl << exdent << "private:" << indent << endl;
  o << className << " (const " << className << " &);" << endl;
  o << "void operator= (const " << className << " &);" << exdent << endl;
  o << BL_CLOSE_SEMI << endl;

  /*
   * If we have initializers, dump an _init class
   */

  CORBA::InitializerSeq_var isv = val->initializers();

  if (isv->length() > 0) {
    o << "class " << className << "_init : public CORBA::ValueFactoryBase"
      << endl;
    o << BL_OPEN;
    o << "public:" << indent << endl;
    o << "virtual ~" << className << "_init ();" << endl;
    o << "static " << className
      << "_init * _downcast (CORBA::ValueFactory);" << endl;
    o << "void * _narrow_helper (const char *);" << endl;
    o << endl;
    for (CORBA::ULong i=0; i<isv->length(); i++) {
      o << "virtual " << className << " * " << isv[i].name << " (";
      for (CORBA::ULong j=0; j<isv[i].members.length(); j++) {
	if (j) {
	  o << ", ";
	}
	emit_type_for_param (isv[i].members[j].type_def, CORBA::PARAM_IN);
	o << " " << ID(isv[i].members[j].name);
      }
      o << ") = 0;" << endl;
    }
    
    o << endl << exdent << "protected:" << indent << endl;
    o << className << "_init ();" << endl;
    o << exdent;
    o << BL_CLOSE_SEMI << endl;
  }

  // Emit TypeCode for value
  if( _params.typecode ) {
    CORBA::Container_var def_in = val->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << "MICO_EXPORT_VAR_DECL";
    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << className << ";" << endl << endl;
  }

  o.switchStream( 1 );
  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );
  if( _params.any ) {
    // operator<<= for value (copying)
    o << "void operator<<=( CORBA::Any &a, const ";
    emit_idl_type_name( val );
    o << " val );" << endl;
    
    // operator<<= for value (non-copying)
    o << "void operator<<=( CORBA::Any &a, ";
    emit_idl_type_name( val );
    o << "* val_ptr );" << endl;
    
    // operator>>= for value
    o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
    emit_idl_type_name( val );
    o << " & val_ptr );" << endl << endl;
  }

  emit_marshal_prototype( val );
  
  o.switchStream( 0 );
  restore_name_prefix();
}

void CodeGenCPPCommon::emit_ValueBox( CORBA::ValueBoxDef_ptr vb )
{
  CORBA::String_var n = vb->name();
  string className = (const char *) ID(n);

  //-----COMMON------------------------------------------------------
  o << endl;
  o << "// Common definitions for valuebox " << className << endl;
  o << "class " << className << " : ";
  o << indent << endl;
  o << "virtual public CORBA::ValueBase," << endl;
  o << "virtual public CORBA::DefaultValueRefCountBase" << exdent << endl;
  o << BL_OPEN;

  CORBA::IDLType_var boxed_value = vb->original_type_def ();
  CORBA::IDLType_var orig = CORBA::IDLType::_duplicate (boxed_value);

  while (orig->def_kind() == CORBA::dk_Alias) {
    CORBA::AliasDef_var ad = CORBA::AliasDef::_narrow (orig);
    orig = ad->original_type_def ();
  }

  CORBA::TypeCode_var tc = orig->type ();
  tc = tc->unalias ();

  switch (tc->kind()) {
  case CORBA::tk_short:
  case CORBA::tk_long:
  case CORBA::tk_ushort:
  case CORBA::tk_ulong:
  case CORBA::tk_float:
  case CORBA::tk_double:
  case CORBA::tk_boolean:
  case CORBA::tk_char:
  case CORBA::tk_octet:
  case CORBA::tk_TypeCode:
  case CORBA::tk_objref:
  case CORBA::tk_enum:
  case CORBA::tk_longlong:
  case CORBA::tk_ulonglong:
  case CORBA::tk_longdouble:
  case CORBA::tk_wchar:
    // basic types, enums and object references
    {
      o << "private:" << indent << endl;
      emit_type_for_variable (boxed_value, automatic);
      o << " value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
      emit_type_for_result (boxed_value);
      o << " _value () const;" << endl;
      o << "void _value (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
    }
    break;

  case CORBA::tk_struct:
    {
      o << "private:" << indent << endl;
      emit_type_name (boxed_value);
      o << "_var value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
      o << "const ";
      emit_type_name (boxed_value);
      o << "& _value () const;" << endl;
      emit_type_name (boxed_value);
      o << "& _value ();" << endl;
      o << "void _value (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;

      // generate member accessor functions
      CORBA::StructDef_var sd = CORBA::StructDef::_narrow (orig);
      CORBA::StructMemberSeq_var sv = sd->members ();
      for (CORBA::ULong i=0; i<sv->length(); i++) {
	CORBA::IDLType_var mt = CORBA::IDLType::_duplicate (sv[i].type_def);
	emit_union_member_decl (mt.in(), sv[i].name.in(), false);
      }
    }
    break;
    
  case CORBA::tk_string:
  case CORBA::tk_wstring:
    {
      string char_type;
      string string_type;

      if (tc->kind() == CORBA::tk_string) {
	char_type = "char";
	string_type = "CORBA::String_var";
      }
      else {
	char_type = "CORBA::WChar";
	string_type = "CORBA::WString_var";
      }

      o << "private:" << indent << endl;
      o << string_type << " value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (" << char_type << " *);" << endl;
      o << className << " (const " << char_type << " *);" << endl;
      o << className << " (const " << string_type << " &);" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (" << char_type << " *);" << endl;
      o << className << " & operator= (const " << char_type << " *);" << endl;
      o << className << " & operator= (const " << string_type << " &);"
	<< endl;
      o << endl;
      o << "const " << char_type << " * _value () const;" << endl;
      o << "void _value (" << char_type << " *);" << endl;
      o << "void _value (const " << char_type << " *);" << endl;
      o << "void _value (const " << string_type << " &);" << endl;
      o << endl;
      o << char_type << " & operator[] (CORBA::ULong);" << endl;
      o << char_type << " operator[] (CORBA::ULong) const;" << endl;
    }
    break;

  case CORBA::tk_union:
    {
      o << "private:" << indent << endl;
      emit_type_name (boxed_value);
      o << "_var value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
      o << "const ";
      emit_type_name (boxed_value);
      o << "& _value () const;" << endl;
      emit_type_name (boxed_value);
      o << "& _value ();" << endl;
      o << "void _value (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;

      /*
       * For union member access, we overload operator->
       */

      emit_type_name (boxed_value);
      o << "* operator->() const;" << endl;
    }
    break;

  case CORBA::tk_sequence:
    {
      CORBA::SequenceDef_var sd = CORBA::SequenceDef::_narrow (orig);
      CORBA::IDLType_var mt = sd->element_type_def();

      o << "public:" << indent << endl;
      o << "typedef ";
      emit_type_for_variable (mt, automatic);
      o << " _elem_type;" << endl;
      o << "typedef ";
      emit_type_for_variable (boxed_value, automatic);
      o << " _value_type;" << endl;
      o << "typedef TSeqVar<_value_type> _value_var;" << endl;
      o << endl << exdent << "private:" << indent << endl;
      o << "_value_var value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (const _value_type &);" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << className << " (CORBA::ULong);" << endl;
      o << className << " (CORBA::ULong, CORBA::ULong, _elem_type *, "
	<< "CORBA::Boolean = FALSE);" << endl;

      o << endl;
      o << className << " & operator= (const _value_type &);" << endl;
      o << endl;
      o << "const _value_type & _value () const;" << endl;
      o << "_value_type & _value ();" << endl;
      o << "void _value (const _value_type &);" << endl;

      /*
       * Inherited stuff <groan>
       */
      o << endl;
      o << "const _elem_type & operator[] (CORBA::ULong) const;" << endl;
      o << "_elem_type & operator[] (CORBA::ULong);" << endl;
      o << "CORBA::ULong maximum () const;" << endl;
      o << "CORBA::Boolean release () const;" << endl;
      o << "void replace (CORBA::ULong, CORBA::ULong, "
	<<               "_elem_type *, CORBA::Boolean = FALSE);" << endl;
      o << "void length (CORBA::ULong);" << endl;
      o << "CORBA::ULong length () const;" << endl;
      o << "static _elem_type * allocbuf (CORBA::ULong);" << endl;
      o << "static void freebuf (_elem_type *);" << endl;
    }
    break;

  case CORBA::tk_any:
    {
      CORBA::PrimitiveDef_var pd = CORBA::PrimitiveDef::_narrow (boxed_value);

      o << "private:" << indent << endl;
      if (!CORBA::is_nil (pd) && pd->kind() == CORBA::pk_any) {
	o << "CORBA::Any";
      }
      else {
	emit_type_name (boxed_value);
      }
      o << "_var value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
      o << "const ";
      if (!CORBA::is_nil (pd) && pd->kind() == CORBA::pk_any) {
	o << "CORBA::Any";
      }
      else {
	emit_type_name (boxed_value);
      }
      o << "& _value () const;" << endl;
      if (!CORBA::is_nil (pd) && pd->kind() == CORBA::pk_any) {
	o << "CORBA::Any";
      }
      else {
	emit_type_name (boxed_value);
      }
      o << "& _value ();" << endl;
      o << "void _value (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
    }
    break;

  case CORBA::tk_array:
    {
      /*
       * The IDL grammar does not allow valueboxes of anonymous arrays,
       * i.e. we're always referring to an outside alias. This simplifies
       * our type handling somewhat wrt sequences
       */

      o << "private:" << indent << endl;
      emit_type_name (boxed_value);
      o << "_var value;" << endl;
      o << endl << exdent << "public:" << indent << endl;
      o << className << " ();" << endl;
      o << className << " (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << className << " (const " << className << " &);" << endl;
      o << endl;
      o << className << " & operator= (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;
      o << endl;
      o << "const ";
      emit_type_name (boxed_value);
      o << "_slice * _value () const;" << endl;
      emit_type_name (boxed_value);
      o << "_slice * _value ();" << endl;
      o << "void _value (";
      emit_type_for_param (boxed_value, CORBA::PARAM_IN);
      o << ");" << endl;

      o << endl;
      o << "const ";
      emit_type_name (boxed_value);
      o << "_slice & operator[] (CORBA::ULong) const;" << endl;
      emit_type_name (boxed_value);
      o << "_slice & operator[] (CORBA::ULong);" << endl;
    }
    break;

  case CORBA::tk_fixed:
    {
      // XXX
      assert (0);
    }
    break;

  default:
    assert (0);
  }

  // same for all
  o << endl;
  if (orig->def_kind() == CORBA::dk_Sequence) {
    o << "const _value_type & _boxed_in () const;" << endl;
    o << "_value_type & _boxed_inout ();" << endl;
    o << "_value_type *& _boxed_out ();" << endl;
  }
  else if (orig->def_kind() == CORBA::dk_Array) {
    o << "const ";
    emit_type_name (boxed_value);
    o << "_slice * _boxed_in () const;" << endl;
    emit_type_name (boxed_value);
    o << "_slice * _boxed_inout ();" << endl;
    emit_type_name (boxed_value);
    if (tc->is_variable()) {
      o << "_slice *& _boxed_out ();" << endl;
    }
    else {
      o << "_slice * _boxed_out ();" << endl;
    }
  }
  else {
    emit_type_for_param (boxed_value, CORBA::PARAM_IN);
    o << " _boxed_in () const;" << endl;
    emit_type_for_param (boxed_value, CORBA::PARAM_INOUT);
    o << " _boxed_inout ();" << endl;
    emit_type_for_param (boxed_value, CORBA::PARAM_OUT);
    o << " _boxed_out ();" << endl;
  }
  o << endl;

  // standard stuff
  o << "static " << className << "* _downcast (CORBA::ValueBase *);" << endl;
  o << "static " << className << "* _downcast (CORBA::AbstractBase *);"
    << endl << endl;

  o << "CORBA::ValueBase * _copy_value ();" << endl;
  o << "CORBA::ValueDef_ptr get_value_def ();" << endl;
  o << "void * _narrow_helper (const char *);" << endl;
  o << "void _get_marshal_info (vector<string> &, CORBA::Boolean &);" << endl;
  o << "void _marshal_members (CORBA::DataEncoder &);" << endl;
  o << "CORBA::Boolean _demarshal_members (CORBA::DataDecoder &);" << endl;

  o << endl << exdent << "protected:" << indent << endl;
  o << "~" << className << " ();" << endl;
  o << endl << exdent << "private:" << indent << endl;
  o << "void operator= (const " << className << " &);" << endl;
  o << exdent << BL_CLOSE_SEMI << endl;

  o << "typedef ValueVar<" << className << "> "
    << className << "_var;" << endl;
  o << "typedef " << className << "_var "
    << className << "_out;" << endl;
  o << endl;

  if (_params.typecode) {
    CORBA::Container_var def_in = vb->defined_in();
    if( def_in->def_kind() == CORBA::dk_Repository )
      // We are on the toplevel
      o << "extern";
    else if( def_in->def_kind() == CORBA::dk_Module )
      // The current scope is not top level (inside a module)
      o << "MICO_EXPORT_VAR_DECL";
    else
      // The current scope is not top level (not inside a module)
      o << "static";
    o << " CORBA::TypeCodeConst _tc_" << className << ";" << endl << endl;
  }

  // operator<<= and operator>>=
  o.switchStream( 1 );
  save_name_prefix();
  set_name_prefix( CORBA::Container::_nil() );

  if( _params.any ) {
    // operator<<= for value (copying)
    o << "void operator<<=( CORBA::Any &a, const ";
    emit_idl_type_name( vb );
    o << " vb );" << endl;
    
    // operator<<= for value (non-copying)
    o << "void operator<<=( CORBA::Any &a, ";
    emit_idl_type_name( vb );
    o << "* vb_ptr );" << endl;

    // operator>>= for value
    o << "CORBA::Boolean operator>>=( const CORBA::Any &a, ";
    emit_idl_type_name( vb );
    o << " & vb_ptr );" << endl << endl;
  }

  emit_marshal_prototype( vb );
  o.switchStream( 0 );
  restore_name_prefix();
}

/*
 * Emit definitions for PortableServer skeleton classes.
 *
 * The C++ mapping dictates that the skeleton class for an interface
 * B within module A becomes POA_A::B, which is in the POA_A namespace.
 *
 * This does not work for ties when mapping modules to structs (lacking
 * true namespaces). Therefore, CORBA 2.3 flattens tie names to be in
 * the global namespace.
 */

void
CodeGenCPPCommon::emit_poa_obj (IRObj_ptr no, bool global_ties)
{
  CORBA::IRObject_ptr obj = no->obj;
  
  if (check_for_included_defn (obj))
    return;

  if ((obj->def_kind() == CORBA::dk_Interface ||
       obj->def_kind() == CORBA::dk_Value) && no->iface_as_forward)
    return;

  /*
   * Produce "flattened" ties on global level
   */

  if (global_ties) {
    switch (obj->def_kind()) {
    case CORBA::dk_Interface:
      {
	CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( obj );
	emit_poa_ties (in, true);
      }
      break;

    case CORBA::dk_Value:
      {
	CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( obj );
	CORBA::InterfaceDefSeq_var supported = val->supported_interfaces ();
	bool supports_concrete = false;
	for (CORBA::ULong i=0; i<supported->length(); i++) {
	  if (!supported[i]->is_abstract()) {
	    supports_concrete = true;
	    break;
	  }
	}
	if (supports_concrete) {
	  emit_poa_ties (val, true);
	}
      }
      break;
    }
    return;
  }

  /*
   * Produce skeletons and ties in their proper modules
   */

  CORBA::Contained_var c = CORBA::Contained::_narrow ( obj );
  if( !CORBA::is_nil( c ) ) {
    CORBA::Container_var new_scope = c->defined_in();
    enter_scope( new_scope, "POA_" );
  }

  switch (obj->def_kind()) {
  case CORBA::dk_Interface:
    {
      CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( obj );
      emit_poa_skel (in);
      emit_poa_ties (in, false);
    }
    break;

  case CORBA::dk_Value:
    {
      CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( obj );
      CORBA::InterfaceDefSeq_var supported = val->supported_interfaces ();
      bool supports_concrete = false;
      for (CORBA::ULong i=0; i<supported->length(); i++) {
	if (!supported[i]->is_abstract()) {
	  supports_concrete = true;
	  break;
	}
      }
      if (supports_concrete) {
	emit_poa_skel (val);
	emit_poa_ties (val, false);
      }
    }
    break;
  }
}

/*
 * PortableServer Skeleton class
 */

void
CodeGenCPPCommon::emit_poa_skel (CORBA::Container_ptr c)
{
  CORBA::Contained_var con = CORBA::Contained::_narrow (c);
  CORBA::String_var n = con->name();
  CORBA::String_var a = con->absolute_name();
  string className = (const char *) ID(n);
  string absName = (const char *) ID(a);
  absName = absName.substr (2);

  string prefix;
  CORBA::Container_var def_in = con->defined_in ();
  if (def_in->def_kind() == CORBA::dk_Repository) {
    prefix = "POA_";
  }
  else {
    prefix = "";
  }

  bool oldurn = use_rel_names (false);

  CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow (c);
  CORBA::ValueDef_var val = CORBA::ValueDef::_narrow (c);

  assert (!CORBA::is_nil (in) || !CORBA::is_nil (val));

  if (!CORBA::is_nil (val)) {
    CORBA::InterfaceDefSeq_var supported = val->supported_interfaces ();
    for (CORBA::ULong i=0; i<supported->length(); i++) {
      if (!supported[i]->is_abstract()) {
	in = CORBA::InterfaceDef::_duplicate (supported[i]);
	break;
      }
    }
  }

  if (CORBA::is_nil (val)) {
    /*
     * Inheritance for interfaces
     */

    CORBA::InterfaceDefSeq_var bc = in->base_interfaces ();

    o << "class " << prefix << className << " : ";
    if (bc->length() == 0) {
      o << "virtual public PortableServer::StaticImplementation" << endl;
    } else {
      o << indent << endl;
      for (CORBA::ULong i=0; i<bc->length(); i++) {
	CORBA::String_var base_name = bc[i]->absolute_name();
	string absBaseName = (const char *) ID (base_name);
	absBaseName = absBaseName.substr (2);
	o << "virtual public POA_" << absBaseName;
	if (i+1 != bc->length()) {
	  o << ",";
	}
	o << endl;
      }
      o << exdent;
    }
  }
  else {
    /*
     * Inheritance for Valuetypes that support an Interface.
     * We derive from the supported Interface's skeleton classes, and
     * from the skeleton classes of a concrete base, if it also supports
     * an interface.
     */

    o << "class " << prefix << className << " : ";
    o << indent << endl;

    CORBA::InterfaceDefSeq_var supported;
    CORBA::String_var base_name = in->absolute_name();
    string absBaseName = (const char *) ID (base_name);
    absBaseName = absBaseName.substr (2);
    o << "virtual public POA_" << absBaseName;

    CORBA::ValueDef_var base_value = val->base_value ();
    if (!CORBA::is_nil (base_value)) {
      supported = base_value->supported_interfaces ();
      bool base_supports_concrete = false;
      for (CORBA::ULong i=0; i<supported->length(); i++) {
	if (!supported[i]->is_abstract()) {
	  base_supports_concrete = true;
	  break;
	}
      }
      if (base_supports_concrete) {
	base_name = base_value->absolute_name();
	absBaseName = (const char *) ID (base_name);
	absBaseName = absBaseName.substr (2);
	o << "," << endl << "virtual public POA_" << absBaseName;
      }
    }

    o << "," << endl << "virtual public " << absName;
    o << exdent << endl;
  }

  o << BL_OPEN;
  o << "public:" << indent << endl;
  o << "virtual ~" << prefix << className << " ();" << endl;

  /*
   * For Value Types, _this returns a pointer to the supported
   * concrete interface
   */

  if (!CORBA::is_nil (val)) {
    CORBA::String_var base_name = in->absolute_name();
    string absBaseName = (const char *) ID (base_name);
    absBaseName = absBaseName.substr (2);
    o << absBaseName << "_ptr _this ();" << endl;
  }
  else {
    o << absName << "_ptr _this ();" << endl;
  }
  o << "bool dispatch (CORBA::StaticServerRequest_ptr);" << endl;
  o << "virtual void invoke (CORBA::StaticServerRequest_ptr);" << endl;
  o << "virtual CORBA::Boolean _is_a (const char *);" << endl;
  o << "virtual CORBA::InterfaceDef_ptr _get_interface ();" << endl;
  o << "virtual CORBA::RepositoryId _primary_interface";
  o <<   " (const PortableServer::ObjectId &,";
  o <<    " PortableServer::POA_ptr);" << endl;
  o << endl;
  o << "virtual void * _narrow_helper (const char *);" << endl;
  if (CORBA::is_nil (val)) {
    o << "static " << prefix << className << " * _narrow";
    o <<   " (PortableServer::Servant);" << endl;
  }
  if (_params.poa_stubs) {
    o << "virtual CORBA::Object_ptr _make_stub"
      <<   " (PortableServer::POA_ptr, CORBA::Object_ptr);" << endl;
  }
  o << endl;

  /*
   * Prototypes only needed for Interfaces; Valuetypes inherit them
   * from the "main" class
   */

  if (!CORBA::is_nil (in)) {
    emitPrototypes (in, true);
  }

  o << exdent << "protected:" << indent << endl;
  o << prefix << className << " () {};" << endl << endl;
  o << exdent << "private:" << indent << endl;
  o << prefix << className << " (const " << prefix << className << " &);" << endl;
  o << "void operator= (const " << prefix << className << " &);" << endl;
  o << exdent << BL_CLOSE_SEMI << endl;

  use_rel_names (oldurn);
}

/*
 * PortableServer Tie class
 */

void
CodeGenCPPCommon::emit_poa_ties (CORBA::Container_ptr c,
				 bool global_ties)
{
  CORBA::Contained_var con = CORBA::Contained::_narrow (c);
  CORBA::String_var n = con->name();
  string className = (const char *) ID(n);
  string mainName = className;

  if (!_params.poa_ties) {
    return;
  }

  // XXX
  if (c->def_kind() == CORBA::dk_Value) {
    return;
  }

  string prefix;
  CORBA::Container_var def_in = con->defined_in ();

  if (global_ties) {
    if (def_in->def_kind() == CORBA::dk_Repository) {
      // already did top-level ones
      return;
    }
    size_t pos;
    CORBA::String_var a = con->absolute_name();
    mainName = (const char *) ID (a);
    mainName = mainName.substr (2);
    className = mainName;
    while ((pos = className.find ("::")) != (size_t) -1) {
      className.replace (pos, 2, "_");
    }
    prefix = (const char *) "POA_";

    o << "#ifndef HAVE_NAMESPACE" << endl << endl;
  }
  else {
    if (def_in->def_kind() == CORBA::dk_Repository) {
      prefix = (const char *) "POA_";
    }
    else {
      prefix = (const char *) "";
      o << "#ifdef HAVE_NAMESPACE" << endl << endl;
    }
  }

  bool oldurn = use_rel_names (false);

  /*
   * Tie class must inherit directly or indirectly from POA_Tie_Base,
   * and from the interface's base class.
   */

  CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow (c);
  CORBA::ValueDef_var val = CORBA::ValueDef::_narrow (c);

  CORBA::InterfaceDefSeq_var bc = in->base_interfaces ();

  o << "template<class T>" << endl;
  o << "class " << prefix << className << "_tie : " << indent << endl;
  if (bc->length() == 0) {
    o << "virtual public POA_Tie_Base<T>," << endl;
  }
  else {
    /*
     * Take namespace flattening into account for base classes.
     * On toplevel, classes can inherit either from the flattened
     * ones (not HAVE_NAMESPACE) or from the normal ones (having
     * HAVE_NAMESPACE).
     * Else, we only have to emit either flattened or normal ones
     * depending on global_ties.
     */

    for (CORBA::ULong i=0; i<bc->length(); i++) {
      CORBA::String_var base_name = bc[i]->absolute_name();
      string absBaseName = (const char *) ID (base_name);
      absBaseName = absBaseName.substr (2);

      string flatBaseName = absBaseName;
      size_t pos;

      while ((pos = flatBaseName.find ("::")) != (size_t) -1) {
	flatBaseName.replace (pos, 2, "_");
      }

      if ( !(flatBaseName == absBaseName) ) {
	if (def_in->def_kind() == CORBA::dk_Repository) {
	  o << "#ifdef HAVE_NAMESPACE" << endl;
	}
	if (def_in->def_kind() == CORBA::dk_Repository || !global_ties) {
	  o << "virtual public POA_" << absBaseName << "_tie<T>," << endl;
	}
	if (def_in->def_kind() == CORBA::dk_Repository) {
	  o << "#else" << endl;
	}
	if (def_in->def_kind() == CORBA::dk_Repository || global_ties) {
	  o << "virtual public POA_" << flatBaseName << "_tie<T>," << endl;
	}
	if (def_in->def_kind() == CORBA::dk_Repository) {
	  o << "#endif" << endl;
	}
      }
      else {
	o << "virtual public POA_" << absBaseName << "_tie<T>," << endl;
      }
    }
  }
  o << "virtual public " << prefix << mainName << exdent << endl;
  o << BL_OPEN;
  o << "public:" << indent << endl;
  
  o << prefix << className << "_tie (T &t)" << indent << endl;
  o << ": POA_Tie_Base<T> (&t, PortableServer::POA::_nil(), FALSE)"
    << exdent << endl << "{}" << endl;
  
  o << prefix << className << "_tie (T &t, PortableServer::POA_ptr _poa)"
    << indent << endl;
  o << ": POA_Tie_Base<T> (&t, _poa, FALSE)"
    << exdent << endl << "{}" << endl;
  
  o << prefix << className << "_tie (T *t, CORBA::Boolean _rel = TRUE)"
    << indent << endl;
  o << ": POA_Tie_Base<T> (t, PortableServer::POA::_nil(), _rel)"
    << exdent << endl << "{}" << endl;
  
  o << prefix << className << "_tie (T *t, PortableServer::POA_ptr _poa, CORBA::Boolean _rel = TRUE)"
    << indent << endl;
  o << ": POA_Tie_Base<T> (t, _poa, _rel)"
    << exdent << endl << "{}" << endl;
  o << "virtual ~" << prefix << className << "_tie ();" << endl;
  o << endl;
  o << "PortableServer::POA_ptr _default_POA ();" << endl;
  o << endl;
  
  emitPrototypes (in, false);
  
  o << exdent << "protected:" << indent << endl;
  o << prefix << className << "_tie () {};" << endl << endl;
  o << exdent << "private:" << indent << endl;
  o << prefix << className << "_tie (const "
    << prefix << className << "_tie<T> &);" << endl;
  o << "void operator= (const " << prefix << className << "_tie<T> &);"
    << endl;
  o << exdent << BL_CLOSE_SEMI << endl;
  
  /*
   * PortableServer Tie Implementations
   */
  
  o << "template<class T>" << endl;
  o << prefix << className << "_tie<T>::~"
    << prefix << className << "_tie ()" << endl;
  o << BL_OPEN << BL_CLOSE << endl;
  
  o << "template<class T>" << endl;
  o << "PortableServer::POA_ptr" << endl;
  o << prefix << className << "_tie<T>::_default_POA ()" << endl;
  o << BL_OPEN;
  o << "if (!CORBA::is_nil (POA_Tie_Base<T>::poa)) " << BL_OPEN;
  o << "return PortableServer::POA::_duplicate (POA_Tie_Base<T>::poa);"
    << endl;
  o << BL_CLOSE;

  string servantbase = "PortableServer::ServantBase";
#ifdef _VC_NAMESPACE_BUG
  servantbase = vc_emit_workaround ("", servantbase);
#endif
  o << "return " << servantbase << "::_default_POA ();" << endl;
  o << BL_CLOSE << endl;
  
  /*
   * Tie Delegation
   */

  CORBA::Container::DescriptionSeq_var dsv =
    in->describe_contents (CORBA::dk_Attribute, TRUE, -1);

  // Emit attributes
  for (CORBA::ULong j0=0; j0<dsv->length(); j0++) {
    CORBA::AttributeDescription * attr;
    CORBA::Boolean r = (dsv[j0].value >>= attr);
    assert (r);
    CORBA::IDLType_var type_id = lookup_attribute_by_id (attr->id);

    o << "template<class T>" << endl;
    emit_type_for_result (type_id);
    o << endl;
    o << prefix << className << "_tie<T>::" << ID(attr->name) << " ()" << endl;
    o << BL_OPEN;
    o << "return POA_Tie_Base<T>::ptr->" << ID(attr->name) << " ();" << endl;
    o << BL_CLOSE << endl;

    if (attr->mode == CORBA::ATTR_NORMAL) {
      o << "template<class T>" << endl;
      o << "void" << endl;
      o << prefix << className << "_tie<T>::" << ID(attr->name) << " (";
      emit_type_for_param (type_id, CORBA::PARAM_IN);
      o << " value)" << endl;
      o << BL_OPEN;
      o << "POA_Tie_Base<T>::ptr->" << ID(attr->name) << " (value);" << endl;
      o << BL_CLOSE << endl;
    }
  }

  dsv = in->describe_contents (CORBA::dk_Operation, TRUE, -1);

  // Emit operations
  for (CORBA::ULong j1=0; j1<dsv->length(); j1++) {
    CORBA::OperationDescription * op;
    CORBA::Boolean r = (dsv[j1].value >>= op);
    assert (r);
    CORBA::IDLType_var type_id = lookup_result_by_id (op->id);
    CORBA::TypeCode_var tc = type_id->type();

    o << "template<class T>" << endl;
    emit_type_for_result (type_id);
    o << endl;
    o << prefix << className << "_tie<T>::" << ID(op->name) << " (";

    CORBA::ULong k;
    for (k=0; k<op->parameters.length(); k++) {
      if( k != 0 )
	o << ", ";
      emit_type_for_param (op->parameters[k].type_def, op->parameters[k].mode);
      o << " " << ID(op->parameters[k].name);
    }

    // Do we have a context?
    CORBA::ContextIdSeq& ctx = op->contexts;
    
    if (op->contexts.length() > 0) {
      if (op->parameters.length() > 0)
	o << ", ";
      o << "CORBA::Context_ptr _ctx";
    }

    o << ")" << endl;
    o << BL_OPEN;

    if (tc->kind() != CORBA::tk_void) {
      o << "return ";
    }

    o << "POA_Tie_Base<T>::ptr->" << ID(op->name) << " (";
    
    for (k=0; k<op->parameters.length(); k++) {
      if (k != 0)
	o << ", ";
      o << ID(op->parameters[k].name);
    }

    if (op->contexts.length() > 0) {
      if (op->parameters.length() > 0)
	o << ", ";
      o << "_ctx";
    }

    o << ");" << endl;
    o << BL_CLOSE << endl;
  }

  if (def_in->def_kind() != CORBA::dk_Repository) {
    o << "#endif" << endl << endl;
  }

  use_rel_names (oldurn);
}

/*
 * The C++ mapping dictates that implementation classes for a valuetype
 * B within module A becomes OBV_A::B, which is in the OBV_A namespace.
 */

void
CodeGenCPPCommon::emit_obv_obj (IRObj_ptr no)
{
  CORBA::IRObject_ptr obj = no->obj;
  
  if (check_for_included_defn (obj))
    return;

  if( obj->def_kind() != CORBA::dk_Value || no->iface_as_forward )
    return;

  /*
   * Produce implementation class in its proper module
   */

  CORBA::Contained_var c = CORBA::Contained::_narrow ( obj );
  if( !CORBA::is_nil( c ) ) {
    CORBA::Container_var new_scope = c->defined_in();
    enter_scope( new_scope, "OBV_" );
  }

  switch (obj->def_kind()) {
  case CORBA::dk_Value:
    {
      CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( obj );
      assert (!CORBA::is_nil (val));
      if (!val->is_abstract()) {
	emit_obv_skel (val);
      }
      break;
    }
  }
}

void
CodeGenCPPCommon::emit_obv_skel (CORBA::ValueDef_ptr val)
{
  CORBA::String_var n = val->name();
  CORBA::String_var a = val->absolute_name();
  string className = (const char *) ID(n);
  string absName = (const char *) ID(a);
  absName = absName.substr (2);

  string prefix;
  CORBA::Container_var def_in = val->defined_in ();
  if (def_in->def_kind() == CORBA::dk_Repository) {
    prefix = "OBV_";
  }
  else {
    prefix = "";
  }

  bool oldurn = use_rel_names (false);

  /*
   * A class with default member implementations
   */

  CORBA::ValueDef_var base_value = val->base_value ();
  CORBA::ValueDefSeq_var bases = val->abstract_base_values ();
  CORBA::ContainedSeq_var members = val->contents (CORBA::dk_ValueMember, 1);

  o << endl;
  o << "// OBV class for valuetype " << className << endl;
  o << "class " << prefix << className << " :";
  if (!CORBA::is_nil (base_value)) {
    o << indent << endl;
  }
  else {
    o << " ";
  }
  o << "virtual public " << absName;
  if (!CORBA::is_nil (base_value)) {
    CORBA::String_var base_name = base_value->absolute_name();
    string abn = ID(base_name);
    abn = abn.substr (2);
    o << "," << endl << "virtual public OBV_" << abn << exdent;
  }
  o << endl << BL_OPEN;
  o << "protected:" << indent << endl;
  o << prefix << className << " ();" << endl;

  if (members->length() > 0) {
    o << prefix << className << " (";
    for (CORBA::ULong i0=0; i0<members->length(); i0++) {
      CORBA::ValueMemberDef_var vmd =
	CORBA::ValueMemberDef::_narrow (members[i0]);
      CORBA::IDLType_var idt = vmd->type_def ();
      CORBA::String_var name = vmd->name ();
      CORBA::TypeCode_var tc = idt->type ();
      /*
       * Must take care of anonymous types
       */
      if (tc->is_sequence() && !tc->is_alias()) {
	o << "const ";
	emit_sequence (idt);
	o << "&";
      }
      else if (tc->is_array() && !tc->is_alias()) {
	o << "const ";
	emit_array (idt);
      }
      else {
	emit_type_for_param (idt.in(), CORBA::PARAM_IN);
      }
      o << " _" << name.in();
      if (tc->is_array() && !tc->is_alias()) {
	emit_array_suffix (idt);
      }
      if (i0+1 != members->length()) {
	o << ", ";
      }
    }
    o << ");" << endl;
  }
  o << "virtual ~" << prefix << className << "();" << endl;
  o << endl;

  bool pub = false;
  for (CORBA::ULong i1=0; i1<members->length(); i1++) {
    CORBA::ValueMemberDef_var vmd =
      CORBA::ValueMemberDef::_narrow (members[i1]);
    CORBA::IDLType_var idt = vmd->type_def ();
    CORBA::String_var name = vmd->name ();
    
    if (vmd->access() == CORBA::PRIVATE_MEMBER && pub) {
      o << exdent << "protected:" << indent << endl;
      pub = false;
    }
    else if (vmd->access() == CORBA::PUBLIC_MEMBER && !pub) {
      o << exdent << "public:" << indent << endl;
      pub = true;
    }

    // mapping as for union members
    emit_union_member_decl( idt.in(), name.in(), false );
  }

  o << endl << exdent << "private:" << indent << endl;
  o << "struct _M " << BL_OPEN;
  for (CORBA::ULong i2=0; i2<members->length(); i2++) {
    CORBA::ValueMemberDef_var vmd =
      CORBA::ValueMemberDef::_narrow (members[i2]);
    CORBA::IDLType_var idt = vmd->type_def ();
    CORBA::String_var name = vmd->name ();
    emit_type_for_variable (idt.in(), automatic);
    o << " " << ID(name.in());
    emit_array_suffix (idt.in());
    o << ";" << endl;
  }
  o << exdent << "} _m;" << endl;
  o << exdent << BL_CLOSE_SEMI << endl;

  use_rel_names (oldurn);
}
