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
#include <stdio.h>
#include <iostream.h>
#include <unistd.h>
#include <mico/ir_impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>
#include "parser.h"
#include "idlparser.h"
#include "codegen-c++.h"
#include "codegen-idl.h"
#include "codegen-midl.h"
#include "params.h"
#include "db.h"


#ifndef CPP
#define CPP "mico-cpp"
#endif



int main( int argc, char *argv[] )
{
  CORBA::Container_var container;
  CORBA::Repository_var repository;
  DB db;
  
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");
#ifdef _WINDOWS
  // Some parts of the idl-compiler can't handle backslashes in paths
  // replace all the backslashes by slashes
  // runtime library can handle slashes fine
  // assume that only paths have backslashes(true for now)
  // (changing the argv[] is allowed)
  for(int i=1; i<argc; i++)
  {
      char *argp=argv[i];
      while(argp && *argp)
      {
          if(*argp=='\\')
              *argp='/';
          
          argp++;
      }
  }
  
#endif
  
  IDLParam params( argc, argv );
  
  if( params.file.length() > 0 ) {
    string cmd = string("") + CPP + params.cpp_options + " " + params.file;
    FILE* inp_file = OSMisc::popen( cmd.c_str(), "r" );

    if( inp_file == NULL ) {
      cerr << "error: cannot open input file: " << params.file << endl;
      exit( 1 );
    }
    
    int dummy_char = fgetc (inp_file);
    if (dummy_char == EOF) {
      cerr << "error: cannot execute " << CPP << endl;
      exit( 1 );
    }
    ungetc (dummy_char, inp_file);

    if( params.cpp_only() ) {
      int ch = fgetc( inp_file );
      while( ch != EOF ) {
	fputc( ch, stdout );
	ch = fgetc( inp_file );
      }
      exit( 0 );
    }
    
    Parser parser( inp_file, params.file.c_str() );
    parser.parse();

    OSMisc::pclose( inp_file );

    db.set_parse_tree( parser.getRootNode() );

    repository = new Repository_impl();
    db.set_idl_container( repository );

    IDLParser idlParser( db );
    idlParser.collect();

    container = CORBA::Repository::_duplicate (repository);

    if( params.feed_ir ) {
      CORBA::Object_var obj =
        orb->resolve_initial_references ("InterfaceRepository");
      CORBA::Repository_var remote_repo = CORBA::Repository::_narrow( obj );
      assert( !CORBA::is_nil( remote_repo ) );

      db.set_idl_container( remote_repo );
      IDLParser idlParserForIR( db, params.feed_included_defs );
      idlParserForIR.collect();
      db.set_idl_container( repository );
    }
  }
  
  if( params.repo_id.length() > 0 ) {
    CORBA::Object_var obj =
        orb->resolve_initial_references ("InterfaceRepository");
    repository = CORBA::Repository::_narrow( obj );
    assert( !CORBA::is_nil( repository ) );

    if (strcmp (params.repo_id.c_str(), "::") == 0) {
      container = CORBA::Repository::_duplicate (repository);
    }
    else {
      CORBA::Contained_var contained =
	repository->lookup_id( (char *) params.repo_id.c_str() );
      if( CORBA::is_nil( contained ) ) {
	contained = repository->lookup( (char *) params.repo_id.c_str() );
	if( CORBA::is_nil( contained ) ) {
	  cerr << "error: repo-id " << params.repo_id << " not found in IR";
	  cerr << endl;
	  exit( 1 );
	}
      }
      container = CORBA::Container::_narrow( contained );
      if( CORBA::is_nil( container ) ) {
	cerr << "error: repo-id " << params.repo_id << " is not a container";
	cerr << endl;
	exit( 1 );
      }
      if( container->def_kind() != CORBA::dk_Module ) {
	cerr << "error: can only generate code from module";
	cerr << endl;
	exit( 1 );
      }
    }
    db.set_idl_container( container );
  }
  
  string name = params.name;
  string::size_type pos = name.rfind( "." );
  if( (int)pos >= 0 && pos < name.length() )
    name = name.substr( 0, pos );
  pos = name.rfind( "/" );
#ifdef _WINDOWS
   if (pos==string::npos)
     pos = name.rfind( "\\" );
#endif
  if( (int)pos >=0 && pos < name.length() )
    name = name.substr( pos + 1 );
  
  if( params.codegen_cpp ) {
    CodeGen *gen = new CodeGenCPP( db, params );
    gen->emit( name );
    delete gen;
  }

  if( params.codegen_idl ) {
    CodeGen *gen = new CodeGenIDL( db, params.emit_repoids );
    gen->emit( name );
    delete gen;
  }
  
  if( params.codegen_midl ) {
    CodeGen *gen = new CodeGenMIDL( db, params.emit_repoids );
    gen->emit( name );
    delete gen;
  }

  return 0;
}
