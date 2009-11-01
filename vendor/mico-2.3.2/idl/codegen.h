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

#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <iostream.h>
#include <strstream.h>

#include <CORBA.h>
#include <mico/template_impl.h>

#include "dep.h"


#define BL_OPEN       "{" << endl << indent
#define BL_CLOSE      exdent << "}" << endl
#define BL_CLOSE_SEMI exdent << "};" << endl

enum OutputFormatting {
  indent,
  exdent
};


#ifdef _WINDOWS
MICO_MAKE_WRAPPER(MICO_WCharWrapper,MICO_WChar);
#endif


typedef ostream& (*endlnfp)(ostream &);

class Output;

class OutputStream
{
  friend class Output;

private:
  int         _indent;
  int         _current_indent;
  bool        _bofl;   // Beginning of line
  // changed for Cygnus CDK
  ostrstream  *_ostr;
  void checkBofL();

public:
  OutputStream( int indent );
  ~OutputStream ();
  void enterLevel();
  void leaveLevel();
  OutputStream &operator<<( const char *s );
  OutputStream &operator<<( const string &str );
  OutputStream &operator<<( const CORBA::WChar *s );
#if SIZEOF_LONG == 4
  // on 64 bit systems CORBA::Long is int
  OutputStream &operator<<( int i );
#endif
  OutputStream &operator<<( CORBA::LongDouble ld );
  OutputStream &operator<<( CORBA::Float f );
  OutputStream &operator<<( CORBA::Double d );
  OutputStream &operator<<( CORBA::LongLong ll );
  OutputStream &operator<<( CORBA::ULongLong ull );
  OutputStream &operator<<( CORBA::Long l );
  OutputStream &operator<<( CORBA::ULong ul );
  OutputStream &operator<<( CORBA::Short s );
  OutputStream &operator<<( CORBA::UShort us );
  OutputStream &operator<<( CORBA::Char c );
#ifdef _WINDOWS
  OutputStream &operator<<( MICO_WCharWrapper c );
#else
  OutputStream &operator<<( CORBA::WChar c );
#endif
  OutputStream &operator<<( const FixedBase &fb );
  OutputStream &operator<<( const CORBA::Any *a );
  OutputStream &operator<<( endlnfp e );
  OutputStream &operator<<( OutputFormatting f );
};

class Output
{
private:
  enum { MaxStreams = 4 };
  
  int           _current_stream;
  OutputStream* _streams[ MaxStreams ];
  ostream*      _ostr;
public:
  Output();
  ~Output();
  void start_output( ostream &o, int indent = 2 );
  void stop_output();
  void free_streams();
  void save_streams( Output &o );
  void restore_streams( Output &o );
  void switchStream( int stream );
  void enterLevel();
  void leaveLevel();
  Output &operator<<( const char *s );
  Output &operator<<( const string &str );
  Output &operator<<( const CORBA::WChar *s );
#if SIZEOF_LONG == 4
  // on 64 bit systems CORBA::Long is int
  Output &operator<<( int i );
#endif
  Output &operator<<( CORBA::LongDouble ld );
  Output &operator<<( CORBA::Float f );
  Output &operator<<( CORBA::Double d );
  Output &operator<<( CORBA::LongLong ll );
  Output &operator<<( CORBA::ULongLong ull );
  Output &operator<<( CORBA::Long l );
  Output &operator<<( CORBA::ULong ul );
  Output &operator<<( CORBA::Short s );
  Output &operator<<( CORBA::UShort us );
  Output &operator<<( CORBA::Char c );
#ifdef _WINDOWS
  Output &operator<<( MICO_WCharWrapper c );
#else
  Output &operator<<( CORBA::WChar c );
#endif
  Output &operator<<( const FixedBase &fb );
  Output &operator<<( const CORBA::Any *a );
  Output &operator<<( endlnfp e );
  Output &operator<<( OutputFormatting f );
};


class CodeGen
{
protected:

  Output  o;
  
  CORBA::Repository_var _repo;
  CORBA::Container_ptr  _container;
  IRObjSeq              _idl_objs;

  CORBA::IDLType_ptr lookup_result_by_id( const CORBA::RepositoryId id );
  CORBA::IDLType_ptr lookup_attribute_by_id( const CORBA::RepositoryId id );
  CORBA::InterfaceDefSeq* derived_interfaces( CORBA::InterfaceDef_ptr in );
  
private:
  void find_derived_interfaces( CORBA::Container_ptr con,
				CORBA::InterfaceDefSeq* derived,
				CORBA::RepositoryId id );

public:
  CodeGen( CORBA::Container_ptr con )
  {
    _container = con;
    if( con->def_kind() == CORBA::dk_Repository )
      _repo = CORBA::Repository::_narrow( con );
    else {
      CORBA::Contained_var contained = CORBA::Contained::_narrow( con );
      assert( !CORBA::is_nil( contained ) );
      _repo = contained->containing_repository();
    }

    // Build dependencies
    IDLDep dep( _container );
    _idl_objs = dep.build_dependencies();
    // dep.print();
  };
  virtual ~CodeGen ()
  {
  }
  virtual void emit( string &fnbase ) = 0;
};



#endif
