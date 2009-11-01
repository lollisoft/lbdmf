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

#ifndef __CODEGENIDL_H__
#define __CODEGENIDL_H__

#include "codegen.h"
#include "db.h"


class CodeGenIDL : public CodeGen
{
private:
  
  bool                 _emit_repoids;
  CORBA::Container_var _current_scope;
  
  typedef SequenceTmpl<CORBA::TypedefDef_var,MICO_TID_DEF> TypedefDefSeq;
  
  void enter_scope( CORBA::Container_ptr c );
  
  void emit_repoid( CORBA::Contained_ptr c );
  void emitIDL();
  void emitIDLInterface( CORBA::InterfaceDef_ptr in );
  void emitIDLStruct( CORBA::StructDef_ptr s, bool emit_semicolon = true );
  void emitIDLUnion( CORBA::UnionDef_ptr u, bool emit_semicolon = true );
  void emitIDLConstant( CORBA::ConstantDef_ptr co );
  void emitIDLException( CORBA::ExceptionDef_ptr e );
  void emitIDLEnum( CORBA::EnumDef_ptr e, bool emit_semicolon = true );
  void emitIDLAlias( CORBA::AliasDef_ptr a );
  void emitIDLNative( CORBA::NativeDef_ptr n );
  void emitIDLValue( CORBA::ValueDef_ptr v );
  void emitIDLValueBox( CORBA::ValueBoxDef_ptr v );

  void emitAttribute( CORBA::AttributeDef_ptr attr );
  void emitOperation( CORBA::OperationDef_ptr op );
  void emitValueMember( CORBA::ValueMemberDef_ptr vmd );
  void emitPrototypes( CORBA::Container_ptr in );
  void emitForwardDcl( CORBA::Container_ptr in );
  void emitLocalDecls( CORBA::Container_ptr in );
  void emitLocal( CORBA::Contained_ptr in, bool emit_semicolon = true );

  void emit_idl_type_name( CORBA::IDLType_ptr t );
  void emit_sequence( CORBA::IDLType_ptr t );
  void emit_idl_type( CORBA::IDLType_ptr t );
  void emit_array( CORBA::IDLType_ptr t );
  void emit_array_suffix( CORBA::IDLType_ptr t );
  bool emit_base_type( CORBA::IDLType_ptr t );

public:
  CodeGenIDL( DB &db, bool emit_repoids );
  void emit( string &fnbase );
  string emit( CORBA::IRObject_ptr obj );
};



#endif
