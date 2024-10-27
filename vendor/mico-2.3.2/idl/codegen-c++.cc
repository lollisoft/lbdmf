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
#include "codegen-c++.h"
#include <mico/template_impl.h>
#include <mico/util.h>


static char *copyright[] = {
  "/*",
  " *  MICO --- a free CORBA implementation",
  " *  Copyright (C) 1997-98 Kay Roemer & Arno Puder",
  " *",
  " *  This file was automatically generated. DO NOT EDIT!",
  " */"
};

const int copyright_size = sizeof( copyright ) / sizeof( char * );



CodeGenCPP::CodeGenCPP( DB &db, IDLParam &params )
  : CodeGen( db.get_idl_container() ),
    CodeGenCPPUtil( db, params ),
    CodeGenCPPCommon( db, params ),
    CodeGenCPPStub( db, params ),
    CodeGenCPPSkel( db, params ),
    CodeGenCPPImpl( db, params )
{
}


void CodeGenCPP::emit( string &fn )
{
  string fnbase       = fn;
  string fnHeader     = fnbase + "." + _params.hh_suffix;
  string fnStub       = fnbase + "." + _params.cpp_suffix;
  string fnSkel       = fnbase + "_skel." + _params.cpp_suffix;
  string fnImplSuffix = "_impl";
  string fnImplH      = fnbase + fnImplSuffix + "." + _params.hh_suffix;
  string fnImplCPP    = fnbase + fnImplSuffix + "." + _params.cpp_suffix;

  for( string::size_type i = 0; i < fnbase.length(); i++ ) {
    fnbase[ i ] = isalnum( fnbase[ i ] ) ? toupper( fnbase[ i ] ) : '_';
  }

  CPPTypeFolder folder( _idl_objs );
  
  ofstream header( fnHeader.c_str() );

  for( int i0 = 0; i0 < copyright_size; i0++ )
    header << copyright[ i0 ] << endl;
  
  header << endl;
  header << "#if !defined(__" << fnbase << "_H__) || ";
  header << "defined(MICO_NO_TOPLEVEL_MODULES)" << endl;
  header << "#define __" << fnbase << "_H__" << endl;
  header << endl;
  header << "#ifndef MICO_NO_TOPLEVEL_MODULES" << endl;
  header << "#include <CORBA.h>" << endl;
  if( _params.no_exceptions )
    header << "#define MICO_CONF_NO_EXCEPTIONS" << endl;
  if (!_params.mico_core)
    header << "#include <mico/throw.h>" << endl;
  header << "#endif" << endl << endl;

  o.start_output( header );
  o.switchStream( 1 );
  o << "#if !defined(MICO_NO_TOPLEVEL_MODULES) || ";
  o << "defined(MICO_MODULE__GLOBAL)";
  o << endl << endl;
  o.switchStream( 0 );
  emit_common();
  o.switchStream( 1 );
  o << "#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || ";
  o << "defined(MICO_MODULE__GLOBAL)";
  o << endl << endl;
  o.switchStream( 0 );
  o.stop_output();
  
  header << endl;
  header << "#if !defined(MICO_NO_TOPLEVEL_MODULES) && "
         << "!defined(MICO_IN_GENERATED_CODE)" << endl;
  header << "#include <mico/template_impl.h>" << endl;
  header << "#endif" << endl;
  header << endl;

  header << "#endif" << endl;
  
  ofstream impl( fnStub.c_str() );

  for( int i1 = 0; i1 < copyright_size; i1++ )
    impl << copyright[ i1 ] << endl;

  impl << endl;

  // This addition is a quick hack to enable building generated implementation files
  // without further modifications using MinGW compiler within my code base and make
  // system
  impl << "#ifdef __MINGW32__" << endl;
  impl << "#include <cstring>" << endl;
  impl << "#endif" << endl;

  if (!_params.mico_core) {
    impl << "#include ";
    impl << ( _params.relative_paths ? "<" : "\"" );
    impl << fnHeader;
    impl << ( _params.relative_paths ? ">" : "\"" );
    impl << endl << endl;
  }
  else {
    impl << "#include <CORBA.h>" << endl;
    if( _params.no_exceptions ) {
      impl << "#define MICO_CONF_NO_EXCEPTIONS" << endl;
    }
    impl << "#include <mico/throw.h>" << endl;
    impl << "#include <mico/template_impl.h>" << endl << endl;
  }

  impl << "//--------------------------------------------------------" << endl;
  impl << "//  Implementation of stubs" << endl;
  impl << "//--------------------------------------------------------" << endl;

  o.start_output( impl );
#ifdef WINDOWS_TC
  o.switchStream( 1 );
  o << "struct __tc_init_" << fnbase << " {" << endl;
  o << indent << "__tc_init_" << fnbase << "()" << endl;
  o << BL_OPEN;

  o.switchStream( 2 );
  o << indent << indent;
  
  o.switchStream( 0 );
#endif
  
  emit_stub();

#ifdef WINDOWS_TC
  o.switchStream( 2 );
  o << BL_CLOSE << BL_CLOSE_SEMI << endl;
  o << "static __tc_init_" << fnbase << " __init_" << fnbase << ";" << endl;
  o << endl;
  o.switchStream( 0 );
#endif
  o.stop_output();

  if (_params.pseudo) {
    return;
  }

  if (_params.cpp_skel) {
    ofstream skel( fnSkel.c_str() );

    for( int i1 = 0; i1 < copyright_size; i1++ )
      skel << copyright[ i1 ] << endl;
  
    if (!_params.mico_core) {
      skel << "#include ";
      skel << ( _params.relative_paths ? "<" : "\"" );
      skel << fnHeader;
      skel << ( _params.relative_paths ? ">" : "\"" );
      skel << endl << endl;
    }
    else {
      skel << "#include <CORBA.h>" << endl;
      if( _params.no_exceptions ) {
        skel << "#ifdef HAVE_EXCEPTIONS" << endl;
        skel << "#undef HAVE_EXCEPTIONS" << endl;
        skel << "#include <mico/throw.h>" << endl;
        skel << "#define HAVE_EXCEPTIONS 1" << endl;
        skel << "#else" << endl;
        skel << "#include <mico/throw.h>" << endl;
        skel << "#endif" << endl;
      } else {
        skel << "#include <mico/throw.h>" << endl;
      }
      skel << "#include <mico/template_impl.h>" << endl << endl;
    }

    skel << "//--------------------------------------------------------"
	 << endl;
    skel << "//  Implementation of skeletons"
	 << endl;
    skel << "//--------------------------------------------------------"
	 << endl;

    o.start_output( skel );
    emit_skel();
    o.stop_output();
  } else {
    impl << "//--------------------------------------------------------"
	 << endl;
    impl << "//  Implementation of skeletons"
	 << endl;
    impl << "//--------------------------------------------------------"
	 << endl;

    o.start_output( impl );
    emit_skel();
    o.stop_output();
  }


  if( !_params.cpp_impl ) {
    // no c++ implementation generation requested
    return;
  }

  // ------- implementation generator: start --------
  // Never overwrite files, since this could cause
  // a programmer to loose his entire implementation

#ifdef _WINDOWS
#define noreplace trunc
#endif

  ofstream implheader( fnImplH.c_str(), ios::noreplace|ios::trunc|ios::out );
  ofstream implcpp( fnImplCPP.c_str(), ios::noreplace|ios::trunc|ios::out );

  bool cont = true;
  
  if( !implheader ) {
    cerr << "warning: C++ implementation generation: "
	 << "file " << fnImplH << " already exists!" << endl;
    cont = false;
  }

  if(!implcpp) {
    cerr << "warning: C++ implementation generation: "
	 << "file " << fnImplCPP << " already exists!" << endl;
    cont = false;
  }

  if( !cont ) {
    cerr << "warning: C++ implementation generation cancelled!" << endl;
    return;
  }
  
  // ----- implementation generator: header -------
  implheader << endl;
  implheader << "#ifndef __" << fnbase << "_IMPL_H__" << endl;
  implheader << "#define __" << fnbase << "_IMPL_H__" << endl;
  implheader << endl;
  implheader << "#include ";
  implheader << ( _params.relative_paths ? "<" : "\"" );
  implheader << fnHeader;
  implheader << ( _params.relative_paths ? ">" : "\"" );
  implheader << endl << endl;

  o.start_output( implheader );
  emit_impl_h();
  o.stop_output();

  implheader << endl << "#endif" << endl;
  
  // ---- implementation generator: c++-file ------
  implcpp << endl;
  implcpp << "#include ";
  implcpp << ( _params.relative_paths ? "<" : "\"" );
  implcpp << fnImplH;
  implcpp << ( _params.relative_paths ? ">" : "\"" );
  implcpp << endl << endl;

  o.start_output( implcpp );
  emit_impl_cpp();
  o.stop_output();
}
