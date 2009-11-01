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

#ifndef __PARAMS_H__
#define __PARAMS_H__


class IDLParam 
{
public:
  string         cpp_options;
  string         name;
  string         file;
  string         cpp_suffix;
  string         hh_suffix;
  bool           relative_paths;
  string         repo_id;
  vector<string> inc_paths;
  bool           feed_ir;
  bool           feed_included_defs;
  bool           codegen_cpp;
  bool           cpp_impl;
  bool           cpp_skel;
  bool           codegen_idl;
  bool           codegen_midl;
  bool           emit_repoids;
  bool           query_server_for_narrow;
  bool           no_exceptions;
  bool           pseudo;
  bool           boa;
  bool           poa;
  bool           any;
  bool           typecode;
  bool           poa_ties;
  bool           poa_stubs;
  bool           windows_dll;
  bool           mico_core;
  bool           gen_included_defs;
  bool           gen_full_dispatcher;
  
public:
  IDLParam( int argc, char *argv[] );
  
  bool cpp_only();
  
private:
  int    _argc;
  char** _argv;

  bool _cpp_only;
  
  void set_defaults();
  void parse_params();
  void check_params();
  void usage();
  void config();
};


#endif
