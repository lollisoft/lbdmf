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
#include "parser.h"
#include <mico/template_impl.h>


extern FILE* yyin;
extern char* yytext;
extern int yylex();
/* extern int yydebug; */

Parser *theParser;


Parser::Parser( FILE *inp_file, const char *filename )
{
  idl_lexFile = toplevelFile = (char *) filename;
  yyin = inp_file;
}

void Parser::parse()
{
  theParser = this;
  idl_line_no = 0;
  /* yydebug = 1; */
  yyparse();
}


void Parser::setRootNode( ParseNode *node )
{
  rootNode = node;
}


ParseNode *Parser::getRootNode()
{
  return rootNode;
}


void Parser::parse_error( char *file, char *err, int line )
{
  string msg;
  
  msg = err;
  msg += " before '";
  msg += yytext;
  msg += "'";
  
  cerr << file << ":" << line << ": " << msg << endl;
  exit( 1 );
}

