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

#ifndef __IDLPARSER_H__
#define __IDLPARSER_H__

#include "parsenode.h"
#include <CORBA.h>
#include "db.h"
#include "const.h"


class IDLParser
{
private:

  ParseNode*                 _root;
  ParseNode*                 _current_parse_node;
  bool                       _feed_included_defs;
  CORBA::Repository_ptr      _repo;
  char*                      _version;
  set<string, less<string> > _forward_dcl;
  set<string, less<string> > _seen_iface;
  DB*                        _db;

  void current_parse_node( ParseNode* node );
  ParseNode* current_parse_node();
  
  char* gen_repo_id( ParseNode *node );
  
  void add_forward_dcl( char* id );
  void remove_forward_dcl( char* id );
  bool is_in_forward_dcl( char* id );
  bool is_iface_defined( char* id );
  
  void scan( CORBA::Container_ptr con, ParseNode *node );

  void collectPragma( CORBA::Container_ptr con, ParseNode *node );
  void collectInclude( CORBA::Container_ptr con, ParseNode *node );
  void check_pragma_syntax( bool condition, ParseNode *node );
  void collectModule( CORBA::Container_ptr con, ParseNode *node );
  void collectTypedef( CORBA::Container_ptr con, ParseNode *node );
  void collectNative( CORBA::Container_ptr con, ParseNode *node );
  CORBA::ArrayDef_ptr collectArray( CORBA::Container_ptr con,
				    CORBA::IDLType_ptr orig,
				    ParseNode *node );
  void collectException( CORBA::Container_ptr con, ParseNode *node );
  void collectConstDcl( CORBA::Container_ptr con, ParseNode *node );
  void collectConstFixedDcl( CORBA::Container_ptr con, ParseNode *node );
  CORBA::StructDef_ptr collectStruct( CORBA::Container_ptr con,
				      ParseNode *node );
  void collectStructMembers( CORBA::Container_ptr con,
			     ParseNode *n, CORBA::StructMemberSeq &m );
  void collectStructMember( CORBA::Container_ptr con,
			    ParseNode *n, CORBA::StructMemberSeq &m );
  void collectStructMemberDeclarators( CORBA::Container_ptr con,
				       ParseNode *n,
				       CORBA::IDLType_ptr t,
				       CORBA::StructMemberSeq &m );
  void collectStructMemberDeclarator( CORBA::Container_ptr con,
				      ParseNode *n,
				      CORBA::IDLType_ptr t,
				      CORBA::StructMemberSeq &m );

  CORBA::UnionDef_ptr collectUnion( CORBA::Container_ptr con,
				    ParseNode *node );
  CORBA::IDLType_ptr collectUnionSwitchTypeSpec( CORBA::Container_ptr con,
						 ParseNode *node );
  void collectUnionElementSpec( CORBA::Container_ptr con,
				ParseNode *node,
				CORBA::UnionMember& member );
  void collectUnionCaseLabel( CORBA::Container_ptr con,
			      ParseNode *node,
			      CORBA::IDLType_ptr switch_type,
			      CORBA::UnionMember& member ) ;
  void collectUnionCases( CORBA::Container_ptr con,
			  ParseNode *node,
			  CORBA::IDLType_ptr switch_type,
			  CORBA::UnionMemberSeq& members );
  void collectUnionMembers( CORBA::Container_ptr con,
			    ParseNode *node,
			    CORBA::IDLType_ptr switch_type,
			    CORBA::UnionMemberSeq& members );
 
  void collectForwardDcl( CORBA::Container_ptr con, ParseNode *node,
			  CORBA::Boolean is_abstract );
  void collectInterface( CORBA::Container_ptr con, ParseNode *node );
  void collectRaisesExpr( CORBA::Container_ptr con, ParseNode *node,
			  CORBA::ExceptionDefSeq &exs );
  void collectContextExpr( ParseNode *node, CORBA::ContextIdSeq &ctx );
  void collectMethod( CORBA::Container_ptr con, ParseNode *node );
  void collectAttribute( CORBA::Container_ptr con, ParseNode *node,
			 CORBA::AttributeMode mode );

  void collectValueForwardDcl( CORBA::Container_ptr con, ParseNode *node,
			       CORBA::Boolean is_abstract );
  void collectValueBoxDcl( CORBA::Container_ptr con, ParseNode *node );
  void collectValueDcl( CORBA::Container_ptr con, ParseNode *node,
			CORBA::Boolean is_abstract );
  void collectStateMember( CORBA::Container_ptr con, ParseNode *node,
			   CORBA::Visibility vis );

  CORBA::EnumDef_ptr collectEnum( CORBA::Container_ptr con, ParseNode *node );
  void collectEnumMembers( CORBA::EnumMemberSeq& m, ParseNode *n );
  
  CORBA::IDLType_ptr collectType( CORBA::Container_ptr con, ParseNode *p );
  CORBA::ScopedName collectScopedName( ParseNode *n );
  bool is_TypeCode( ParseNode *n );
  bool is_Principal( ParseNode *n );
  Const collectConst( CORBA::Container_ptr con, ParseNode *p );
public:
  IDLParser( DB &db, bool feed_included_defs = true );
  ~IDLParser();
  void collect();
};


#endif
