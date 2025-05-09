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

#ifndef __CODEGENCPP_UTIL_H__
#define __CODEGENCPP_UTIL_H__

/*
 * The WIN32 compiler VC++ is unable to initialize global variables.
 * We therefore need a workaround for initializing the _tc_* variables.
 * The #define WINDOWS_TC is activating this workaround. Once VC++
 * is getting closer to the level of other C++ compilers, this #define
 * can be removed.
 */
#define WINDOWS_TC

#include "idlparser.h"
#include "codegen.h"
#include "params.h"
#include "db.h"


#define _STUB   "_stub"
#define _SKEL   "_skel"


class CPPTypeFolder 
{
private:
  typedef SequenceTmpl<CORBA::TypeCode_var,MICO_TID_DEF> TypeCodeSeq;

  TypeCodeSeq _seq_types;
  TypeCodeSeq _arr_types;
  TypeCodeSeq _fix_types;

  bool check_for_sequence( CORBA::TypeCode_ptr seq );
  bool check_for_array( CORBA::TypeCode_ptr arr );
  bool check_for_fixed( CORBA::TypeCode_ptr fix );

  void do_type_folding( IRObjSeq& objs );
  
public:
  CPPTypeFolder( IRObjSeq& objs );
};


class CodeGenCPPUtil : public virtual CodeGen
{
protected:
  DB*                         _db;
  IDLParam&                   _params;

  set<string, less<string> >  _include_files;

  string                      _name_prefix;
  string                      _name_prefix_bak;
  CORBA::Container_var        _current_scope;
  bool                        _emit_rel_names;
  
  enum Storage {
    manual,
    automatic
  };

  /*
   * Util
   */  
  char* ID( const char* ident );
  void set_name_prefix( CORBA::Container_ptr c );
  void save_name_prefix();
  void restore_name_prefix();
  void enter_scope( CORBA::Container_ptr c, string toplevel_prefix );
  bool use_rel_names( bool );
  void emit_rel_name( CORBA::Object_ptr obj, bool transform = false );
  void emit_type_name( CORBA::Object_ptr obj );
  void emit_mangled_name( const char *s );
  bool check_for_included_defn( CORBA::IRObject_ptr obj );
  bool is_base_sequence( CORBA::SequenceDef_ptr sdef );
  bool is_variable_for_sii( CORBA::TypeCode_ptr );

  void emit_any_param( CORBA::IDLType_ptr p,
		       char *var_name, bool is_from );
  void emit_type_code( CORBA::TypeCode_ptr tc );
  void emit_type_code_name( CORBA::IDLType_ptr t );
  void emit_type_code_name( CORBA::IRObject_ptr obj );
  void emit_idl_type_name( CORBA::IDLType_ptr t );
  void emit_type_for_param( CORBA::IDLType_ptr t,
			    CORBA::ParameterMode mode );
  void emit_type_for_result( CORBA::IDLType_ptr t );
  void emit_sequence( CORBA::IDLType_ptr t );
  void emit_fixed( CORBA::IDLType_ptr t );
  void emit_array( CORBA::IDLType_ptr t );
  void emit_array_suffix( CORBA::IDLType_ptr t );
  void emit_array_slice_suffix( CORBA::IDLType_ptr t );
  CORBA::ULong compute_num_array_elem( CORBA::TypeCode_ptr tc );
  void emit_assignment( const string& d, const string &s,
			CORBA::IDLType_ptr t );
  void emit_type_for_variable( CORBA::IDLType_ptr t, Storage s );
  bool emit_base_type( CORBA::IDLType_ptr t );
  void emit_array_marshalling( CORBA::ArrayDef_ptr arr,
			       bool is_from,
			       int level );
  bool is_union_case_defined( CORBA::UnionMemberSeq& mem,
			      CORBA::Any &any );
  string generate_union_default_case_label( CORBA::IDLType_ptr discr,
					    CORBA::UnionMemberSeq &mem );
  void emit_union_member_decl( CORBA::IDLType_ptr t,
			       const char * name,
			       bool as_pure_virtual );
  void gen_mangled_name( string &str,
			 CORBA::IRObject_ptr obj,
			 bool for_an_instance,
			 bool first_call_to_gen = true );
  void emit_marshaller_ref( CORBA::IRObject_ptr obj,
			    bool for_an_instance = true );
  void emit_marshaller_suffix( CORBA::IRObject_ptr obj );

  bool check_for_possible_circle_rek( CORBA::ValueDef_ptr v,
				      CORBA::IRObject_ptr obj,
				      vector<CORBA::IRObject_var> & );
  bool check_for_possible_circle( CORBA::ValueDef_ptr v );

  bool contains_a_valuetype( CORBA::IRObject_ptr,
			     vector<CORBA::IRObject_var> * = 0);
  bool check_simple_clp_call( CORBA::OperationDescription & );

  bool is_var_inout( CORBA::IDLType_ptr );
  void emit_release( CORBA::IDLType_ptr, const char *var_name );

  bool use_builtin_marshaller( CORBA::TypeCode_ptr, string &name );

  // VC++ namespace-bug-workaround-helpers (tm)
  string vc_transform (const string &);
  string vc_emit_workaround (const string &prefix, const string &name);

public:
  CodeGenCPPUtil( DB &db, IDLParam& params );
};


#endif
