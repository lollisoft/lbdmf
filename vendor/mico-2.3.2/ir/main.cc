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
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/ir_impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>
#include "parser.h"
#include "idlparser.h"
#include "codegen-idl.h"

#ifndef CPP
#define CPP "mico-cpp"
#endif


static CORBA::Repository_ptr therepo;
static string thedb;

void save_db ()
{
  if (thedb.length() > 0) {
    cerr << "saving database " << thedb << ".idl ... " << flush;
    DB db;
    db.set_idl_container (therepo);
    CodeGenIDL gen (db, true );
    gen.emit (thedb);
    cerr << "done." << endl;  
  }
}

void
sighandler (int)
{
  save_db ();
  exit (0);
}

void usage( const char *progname )
{
  cerr << "usage: " << progname << " [<options>]" << endl;
  cerr << "possible <options> are:" << endl;
  cerr << "    --help" << endl;
  cerr << "    --db <idl database file>" << endl;
  cerr << "    --ior <IOR ref file>" << endl;
  exit( 1 );
}

int main( int argc, char *argv[] )
{
  signal (SIGINT, sighandler);
  signal (SIGTERM, sighandler);

  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  MICOGetOpt::OptMap opts;
  opts["--help"] = "";
  opts["--db"]   = "arg-expected";
  opts["--ior"]  = "arg-expected";

  MICOGetOpt opt_parser (opts);
  if (!opt_parser.parse (argc, argv))
    usage (argv[0]);

  string reffile;

  for (MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
       i != opt_parser.opts().end(); ++i) {
    string arg = (*i).first;
    string val = (*i).second;

    if (arg == "--db") {
      thedb = val;
    } else if (arg == "--ior") {
      reffile = val;
    } else if (arg == "--help") {
      usage( argv[ 0 ] );
    } else {
      usage( argv[ 0 ] );
    }
  }
  if (argc != 1) {
    usage( argv[ 0 ] );
  }

  CORBA::Object_var obj =
      orb->resolve_initial_references ("InterfaceRepository");
  therepo = CORBA::Repository::_narrow (obj);
  assert (!CORBA::is_nil (therepo));

  if (thedb.length() > 0) {
      string fn = thedb + ".idl";

      if (OSMisc::access (fn.c_str(), OSMisc::ACCESS_READ)) {
	  cerr << "warning: database " << fn << " does not exist." << endl;
      } else {
	  string cmd = string("") + CPP + " " + fn;
	  FILE* inp_file = OSMisc::popen( cmd.c_str(), "r" );

	  if (inp_file == NULL) {
	      cerr << "warning: cannot open database: " << fn << endl;
	  } else {
              int dummy_char = fgetc (inp_file);
              if (dummy_char == EOF) {
                  cerr << "error: cannot execute " << CPP << endl;
                  exit( 1 );
              }
              ungetc (dummy_char, inp_file);

	      cerr << "reading in database " << fn << " ... " << flush;
	      Parser parser (inp_file, fn.c_str());
	      parser.parse();

	      DB db;
              db.set_idl_container (therepo);
              db.set_parse_tree (parser.getRootNode());
	      IDLParser idlparser (db);
	      idlparser.collect();
	      cerr << "done." << endl;
	  }
	  OSMisc::pclose (inp_file);
      }
  }

  if (reffile.length() > 0) {
    ofstream out (reffile.c_str());
    if (!out) {
      cerr << "error: cannot open output file " << reffile.c_str() << endl;
    }
    else {
      CORBA::String_var repoior = orb->object_to_string (therepo);
      out << repoior.in() << endl;
      out.close ();
    }
  }

  boa->impl_is_ready( CORBA::ImplementationDef::_nil() );
  orb->run ();
  return 0;
}
