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

#ifndef __DB_H__
#define __DB_H__

#include "parsenode.h"


class DB
{
private:
  ParseNode* _parse_tree;

  CORBA::Container_var _con;
  
  typedef map<string, string, less<string> > RepoidFnameMap;
  RepoidFnameMap _repoid_fname_map;

  typedef vector<vector<string> > VecVecString;
  
  VecVecString    _current_scope;
  vector<string>  _current_prefix;
  vector<string>  _version_name;
  vector<string>  _version;
  vector<string>  _id_name;
  vector<string>  _id;

public:
  DB();
  ~DB();

  void set_parse_tree( ParseNode* node );
  ParseNode* get_parse_tree();

  void set_idl_container( CORBA::Container_ptr con );
  CORBA::Container_ptr get_idl_container();
  
  string gen_pseudo_repoid( CORBA::IDLType_ptr t );
  void register_anonym_type( ParseNode* node, CORBA::IDLType_ptr t );
  void register_repoid( ParseNode* node, string &id );

  bool repoid_defined( string& id );
  string get_fname_for_repoid( string& id );

  void enter_scope( string& name );
  void leave_scope();
  void enter_include_file();
  void leave_include_file();
  void switch_prefix( string& name );
  string get_current_prefix();
  void set_repo_version( string& name, string& version );
  void set_repo_id( string& name, string& id );
  void set_repoids( CORBA::Repository_ptr repo );
};


#endif
