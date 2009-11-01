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
#include "params.h"



IDLParam::IDLParam( int argc, char *argv[] )
{
  _argc = argc;
  _argv = argv;
  _cpp_only = false;
  set_defaults();
  parse_params();
  check_params();
}

void
IDLParam::set_defaults()
{
  cpp_suffix = "cc";
  hh_suffix = "h";
  relative_paths = false;
  feed_ir = false;
  feed_included_defs = false;
  codegen_cpp = true;
  cpp_impl = false;
  cpp_skel = false;
  codegen_idl = false;
  codegen_midl = false;
  emit_repoids = false;
  query_server_for_narrow = true;
#ifdef HAVE_EXCEPTIONS
  no_exceptions = false;
#else
  no_exceptions = true;
#endif
  pseudo = false;
  boa = true;
  poa = false;
  any = false;
  typecode = false;
  poa_ties = true;
  poa_stubs = true;
  windows_dll=false;
  mico_core = false;
  gen_included_defs = false;
  gen_full_dispatcher = false;
}

void
IDLParam::parse_params()
{
  MICOGetOpt::OptMap opts;
  opts["--feed-ir"]               = "";
  opts["--feed-included-defs"]    = "";
  opts["--no-exceptions"]         = "";
  opts["--codegen-c++"]           = "";
  opts["--no-codegen-c++"]        = "";
  opts["--codegen-idl"]           = "";
  opts["--no-codegen-idl"]        = "";
  opts["--codegen-midl"]          = "";
  opts["--no-codegen-midl"]       = "";
  opts["--c++-suffix"]            = "arg-expected";
  opts["--c++-impl"]              = "";
  opts["--c++-skel"]              = "";
  opts["--hh-suffix"]             = "arg-expected";
  opts["--relative-paths"]        = "";
  opts["--emit-repoids"]          = "";
  opts["--do-not-query-server-for-narrow"] = "";
  opts["--repo-id"]               = "arg-expected";
  opts["--name"]                  = "arg-expected";
  opts["--version"]               = "";
  opts["--config"]                = "";
  opts["--help"]                  = "";
  opts["--poa"]                   = "";
  opts["--no-poa"]                = "";
  opts["--boa"]                   = "";
  opts["--no-boa"]                = "";
  opts["--pseudo"]                = "";
  opts["--any"]                   = "";
  opts["--typecode"]              = "";
  opts["--no-poa-ties"]           = "";
  opts["--no-poa-stubs"]          = "";
  opts["--windows-dll"]           = "";
  opts["--mico-core"]             = "";
  opts["--gen-included-defs"]     = "";
  opts["--gen-full-dispatcher"]   = "";
  
  // Preprocessor options
  opts["-I"]                      = "arg-expected";
  opts["-D"]                      = "arg-expected";
  opts["-E"]                      = "";
  opts["-M"]                      = "";
  opts["-MG"]                     = "";
  opts["-MM"]                     = "";
  opts["-MD"]                     = "";
  opts["-MMD"]                    = "";
  
  
  MICOGetOpt opt_parser( opts );
  if( !opt_parser.parse( _argc, _argv ) )
    usage();

  for( MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
       i != opt_parser.opts().end(); i++ ) {
    string arg = (*i).first;
    string val = (*i).second;

    if (arg == "-I") {
      // remove ./'s
      int pos;
      while ((pos = val.find ("/./")) >= 0)
	val.replace (pos, 2, "", 0);
      if (val.find ("./") == 0)
	val.replace (0, 2, "", 0);

      cpp_options += " ";
      cpp_options += arg + val;
      inc_paths.push_back (val);
    } else if (arg == "-D") {
      cpp_options += " ";
      cpp_options += arg + val;
    } else if( arg == "-E" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if( arg == "-M" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if( arg == "-MG" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if( arg == "-MM" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if( arg == "-MD" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if( arg == "-MMD" ) {
      cpp_options += " ";
      cpp_options += arg;
      _cpp_only = true;
    } else if (arg == "--feed-ir") {
      feed_ir = true;
    } else if( arg == "--feed-included-defs" ) {
      feed_included_defs = true;
    } else if (arg == "--no-exceptions") {
      no_exceptions = true;
    } else if (arg == "--codegen-c++") {
      codegen_cpp = true;
    } else if (arg == "--no-codegen-c++") {
      codegen_cpp = false;
    } else if (arg == "--codegen-idl") {
      codegen_idl = true;
    } else if (arg == "--no-codegen-idl") {
      codegen_idl = false;
    } else if (arg == "--codegen-midl") {
      codegen_midl = true;
    } else if (arg == "--no-codegen-midl") {
      codegen_midl = false;
    } else if( arg == "--c++-suffix" ) {
      cpp_suffix = val;
    } else if( arg == "--c++-impl" ) {
      cpp_impl = true;
    } else if( arg == "--c++-skel" ) {
      cpp_skel = true;
    } else if( arg == "--hh-suffix" ) {
      hh_suffix = val;
    } else if( arg == "--relative-paths" ) {
      relative_paths = true;
    } else if (arg == "--emit-repoids") {
      emit_repoids = true;
    } else if( arg == "--do-not-query-server-for-narrow" ) {
      query_server_for_narrow = false;
    } else if (arg == "--repo-id") {
      repo_id = val;
    } else if (arg == "--name") {
      name = val;
    } else if (arg == "--boa") {
      boa = true;
    } else if (arg == "--no-boa") {
      boa = false;
    } else if (arg == "--poa") {
      poa = true;
    } else if (arg == "--no-poa") {
      poa = false;
    } else if (arg == "--pseudo") {
      pseudo = true;
    } else if (arg == "--any") {
      any = true;
    } else if (arg == "--windows-dll") {
      windows_dll = true;
    } else if (arg == "--typecode") {
      typecode = true;
    } else if (arg == "--no-poa-ties") {
      poa_ties = false;
    } else if (arg == "--no-poa-stubs") {
      poa_stubs = false;
    } else if (arg == "--mico-core") {
      mico_core = true;
    } else if (arg == "--gen-included-defs") {
      gen_included_defs = true;
    } else if (arg == "--gen-full-dispatcher") {
      gen_full_dispatcher = true;
    } else if (arg == "--version") {
      cout << "MICO Version " << MICO_VERSION << endl;
      exit( 0 );
    } else if (arg == "--config") {
      config();
    } else if (arg == "--help") {
      usage();
    } else {
      usage();
    }
  }
  if (_argc > 2) {
    usage();
  }
  if (_argc == 2) {
    if (name == "")
      name = _argv[1];
    file = _argv[1];
  }
}

bool
IDLParam::cpp_only()
{
  return _cpp_only;
}

void
IDLParam::check_params()
{
#ifdef HAVE_EXCEPTIONS
  if( no_exceptions && !codegen_cpp ) {
    cerr << "error: --no-exceptions can only be used in conjunction ";
    cerr << "with --codegen-c++" << endl;
    exit( 1 );
  }
#endif
  if( repo_id.length() > 0 && feed_ir ) {
    cerr << "error: --repo-id and --feed-ir can not be used together" << endl;
    exit( 1 );
  }
  if( feed_included_defs && !feed_ir ) {
    cerr << "error: use --feed-included-defs only in conjunction "
	 << "with --feed-ir" << endl;
    exit( 1 );
  }
  if( repo_id.length() > 0 && file.length() > 0 ) {
    cerr << "error: --repo-id and file name can not be used together" << endl;
    exit( 1 );
  }
  if( repo_id.length() == 0 && file.length() == 0 ) {
    cerr << "error: must either specify a file name or --repo-id";
    cerr << endl;
    exit( 1 );
  }
  if( repo_id.length() > 0 && (!codegen_cpp && !codegen_idl) ) {
    cerr << "error: must either specify --codegen-c++ or --codegen-idl";
    cerr << endl;
    exit( 1 );
  }
  if( repo_id.length() > 0 && (!codegen_cpp && !codegen_idl && !codegen_midl) ) {
    cerr << "error: must either specifiy --codegen-c++, --codegen-idl, "
	 << "or --codegen-midl" << endl;
    exit( 1 );
  }
  if( repo_id.length() > 0 && name.length() == 0 ) {
    cerr << "error: use --name to specify a filename prefix";
    cerr << endl;
    exit( 1 );
  }
  if( emit_repoids && !codegen_idl ) {
    cerr << "error: use --emit-repoids only in conjunction with --codegen-idl";
    cerr << endl;
    exit( 1 );
  }
  if( any && !codegen_cpp ) {
    cerr << "error: use --any only in conjunction with --codegen-c++";
    cerr << endl;
    exit( 1 );
  }
  if( typecode && !codegen_cpp ) {
    cerr << "error: use --typecode only in conjunction with --codegen-c++";
    cerr << endl;
    exit( 1 );
  }
  if( file.length() > 0 && !feed_ir ) {
    if( !codegen_cpp && !codegen_idl && !codegen_midl) {
      cerr << "error: must either specify --codegen-c++, --codegen-idl, or "
	   << "--codegen-midl" << endl;
      exit( 1 );
    }
  }
  if( file.length() > 0 && name == file && codegen_idl ) {
    cerr << "error: use --name to specify a filename prefix";
    cerr << endl;
    exit( 1 );
  }
  if( pseudo && query_server_for_narrow ) {
    query_server_for_narrow = FALSE;
  }
  if( pseudo && !codegen_cpp ) {
    cerr << "error: --pseudo only works with --codegen-c++";
    cerr << endl;
    exit( 1 );
  }
  if( cpp_impl && !codegen_cpp ) {
    cerr << "error: --c++-impl can only be used in conjunction ";
    cerr << "with --codegen-c++" << endl;
    exit( 1 );
  }
  if( cpp_skel && !codegen_cpp ) {
    cerr << "error: --c++-skel can only be used in conjunction ";
    cerr << "with --codegen-c++" << endl;
    exit( 1 );
  }

  if( any )
    typecode = true;
}

void
IDLParam::usage()
{
  cerr << "usage: " << _argv[ 0 ] << " [<options>] [<file>]" << endl;
  cerr << "possible <options> are:" << endl;
  cerr << "    --help" << endl;
  cerr << "    --version" << endl;
  cerr << "    --config" << endl;
  cerr << "    --feed-ir" << endl;
  cerr << "    --feed-included-defs" << endl;
  cerr << "    --no-exceptions" << endl;
  cerr << "    --codegen-c++" << endl;
  cerr << "    --no-codegen-c++" << endl;
  cerr << "    --codegen-idl" << endl;
  cerr << "    --no-codegen-idl" << endl;
  cerr << "    --codegen-midl" << endl;
  cerr << "    --no-codegen-midl" << endl;
  cerr << "    --c++-suffix <filename-suffix>" << endl;
  cerr << "    --c++-impl" << endl;
  cerr << "    --c++-skel" << endl;
  cerr << "    --hh-suffix <filename-suffix>" << endl;
  cerr << "    --relative-paths" << endl;
  cerr << "    --emit-repoids" << endl;
  cerr << "    --do-not-query-server-for-narrow" << endl;
  cerr << "    --repo-id <repository-id>" << endl;
  cerr << "    --name <filename-prefix>" << endl;
  cerr << "    --poa" << endl;
  cerr << "    --no-poa" << endl;
  cerr << "    --boa" << endl;
  cerr << "    --no-boa" << endl;
  cerr << "    --no-poa-ties" << endl;
  cerr << "    --no-poa-stubs" << endl;
  cerr << "    --pseudo" << endl;
  cerr << "    --any" << endl;
  cerr << "    --typecode" << endl;
  cerr << "    --windows-dll" << endl;
  cerr << "    --mico-core" << endl;
  cerr << "    --gen-included-defs" << endl;
  cerr << "    --gen-full-dispatcher" << endl;
  exit( 1 );
}

void
IDLParam::config()
{
  cout << "MICO version...........: " << MICO_VERSION << endl;

  cout << "supported CORBA version: ";
#ifdef USE_CORBA_2_1
  cout << "2.1" << endl;
#else
  string version = MICO_VERSION;
  int i = version.find_last_of( "." );
  cout << version.substr( 0, i ) << endl;
#endif

  cout << "exceptions.............: ";
#ifdef HAVE_EXCEPTIONS
#ifdef HAVE_STD_EH
  cout << "CORBA compliant" << endl;
#else
  cout << "MICO specific" << endl;
#endif
#else
  cout << "no" << endl;
#endif

  cout << "modules are mapped to..: ";
#ifdef HAVE_NAMESPACE
  cout << "namespaces" << endl;
#else
  cout << "structs" << endl;
#endif

  cout << "STL is.................: ";
#ifdef HAVE_MINI_STL
  cout << "miniSTL" << endl;
#else
  cout << "system supplied" << endl;
#endif

  cout << "SSL support............: ";
#ifdef HAVE_SSL
  cout << "yes" << endl;
#else
  cout << "no" << endl;
#endif

  cout << "loadable modules.......: ";
#ifdef HAVE_DYNAMIC
  cout << "yes" << endl;
#else
  cout << "no" << endl;
#endif

  exit (0);
}
