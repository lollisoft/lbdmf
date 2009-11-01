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

%{

#include <CORBA.h>

#include <iostream.h>
#include <fstream.h>
#include <strstream.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "prepro.h"
#include "parsenode.h"
#include "yacc.h"
#include <mico/template_impl.h>


#ifdef _WINDOWS
#define isatty _isatty
#endif


static CORBA::LongLong ascii_to_longlong( long base, const char *s )
{
  CORBA::LongLong ll = 0;
  while( *s != '\0' ) {
    char c = *s++;
    if( c >= 'a' )
      c -= 'a' - 'A';
    c -= '0';
    if( c > 9 )
      c -= 'A' - '0' - 10;
    ll = ll * base + c;
  }
  return ll;
}

static CORBA::LongDouble ascii_to_longdouble (const char *s)
{
  CORBA::LongDouble d;
#ifdef HAVE_SCANF_LF
  sscanf ((char *)s, "%Lf", &d);
#else
  /*
   * this is only an approximation and will probably break fixed<>
   * parameter calculation on systems where
   * sizeof(double) < sizeof(long double). but fortunately all
   * systems where scanf("%Lf") is known to be broken (Linux/Alpha
   * and HPUX) have sizeof(double) == sizeof(long double).
   */
  d = strtod ((char *)s, NULL);
#endif
  return d;
}

static char translate_char( const char *s )
{
  char c = *s++;
  
  if( c != '\\' )
    return c;
  c = *s;
  switch( c ) {
  case 'n':
    return '\n';
  case 't':
    return '\t';
  case 'v':
    return '\v';
  case 'b':
    return '\b';
  case 'r':
    return '\r';
  case 'f':
    return '\f';
  case 'a':
    return '\a';
  case '\\':
    return '\\';
  case '?':
    return '\?';
  case '\'':
    return '\'';
  case '"':
    return '"';
  case 'x':
  case 'X':
    return (char) ascii_to_longlong( 16, ++s );
  default:
    // Gotta be an octal
    return (char) ascii_to_longlong( 8, s );
  }
}


%}

%option noyywrap

/*--------------------------------------------------------------------------*/

Digits                  [0-9]+
Oct_Digit               [0-7]
Hex_Digit               [a-fA-F0-9]
Int_Literal		[1-9][0-9]*
Oct_Literal		0{Oct_Digit}*
Hex_Literal		(0x|0X){Hex_Digit}*
Esc_Sequence1           "\\"[ntvbrfa\\\?\'\"]
Esc_Sequence2           "\\"{Oct_Digit}{1,3}
Esc_Sequence3           "\\"(x|X){Hex_Digit}{1,2}
Esc_Sequence            ({Esc_Sequence1}|{Esc_Sequence2}|{Esc_Sequence3})
Char                    ([^\n\t\"\'\\]|{Esc_Sequence})
Char_Literal            "'"({Char}|\")"'"
String_Literal		\"({Char}|"'")*\"
Float_Literal1		{Digits}"."{Digits}?(e|E)("+"|"-")?{Digits}  
Float_Literal2		{Digits}(e|E)("+"|"-")?{Digits}
Float_Literal3          {Digits}"."{Digits}
Float_Literal4          {Digits}"."
Float_Literal5		"."{Digits} 
Float_Literal6		"."{Digits}(e|E)("+"|"-")?{Digits}  
Fixed_Literal1          {Digits}(d|D)
Fixed_Literal2          {Digits}"."(d|D)
Fixed_Literal3          "."{Digits}(d|D)
Fixed_Literal4          {Digits}"."{Digits}(d|D)

/*--------------------------------------------------------------------------*/

CORBA_Identifier	[a-zA-Z_][a-zA-Z0-9_]*

/*--------------------------------------------------------------------------*/



%%

[ \t\r]			;
[\n]			idl_line_no++;
"//"[^\n]*		;
"#pragma"[^\n]*\n       {
			  yylval._str = CORBA::string_dup( yytext );
                          idl_line_no++;
                          return T_PRAGMA;
                        }
"#"[^\n]*\n             {
                          preprocessor_directive( yytext );
			  yylval._str = CORBA::string_dup( yytext );
                          return T_INCLUDE;
                        }
"{"			return T_LEFT_CURLY_BRACKET;
"}"			return T_RIGHT_CURLY_BRACKET;
"["		 	return T_LEFT_SQUARE_BRACKET;
"]"			return T_RIGHT_SQUARE_BRACKET;
"("			return T_LEFT_PARANTHESIS;
")"			return T_RIGHT_PARANTHESIS;
":"			return T_COLON;
","			return T_COMMA;
";"			return T_SEMICOLON;
"="			return T_EQUAL;
">>"			return T_SHIFTRIGHT;
"<<"			return T_SHIFTLEFT;
"+"			return T_PLUS_SIGN;
"-"			return T_MINUS_SIGN;
"*"			return T_ASTERISK;
"/"			return T_SOLIDUS;
"%"			return T_PERCENT_SIGN;
"~"			return T_TILDE;
"|"			return T_VERTICAL_LINE;
"^"			return T_CIRCUMFLEX;
"&"			return T_AMPERSAND;
"<"			return T_LESS_THAN_SIGN;
">"			return T_GREATER_THAN_SIGN;

const			return T_CONST;
typedef			return T_TYPEDEF;
float			return T_FLOAT;
double			return T_DOUBLE;
char			return T_CHAR;
wchar			return T_WCHAR;
fixed                   return T_FIXED;
boolean			return T_BOOLEAN;
string			return T_STRING;
wstring			return T_WSTRING;
void			return T_VOID;
unsigned		return T_UNSIGNED;
long 			return T_LONG;
short			return T_SHORT;
FALSE			return T_FALSE;
TRUE			return T_TRUE;
struct			return T_STRUCT;
union			return T_UNION;
switch			return T_SWITCH;
case			return T_CASE;
default			return T_DEFAULT;
enum			return T_ENUM;
in			return T_IN;
out			return T_OUT;
interface		return T_INTERFACE;
abstract		return T_ABSTRACT;
valuetype		return T_VALUETYPE;
truncatable		return T_TRUNCATABLE;
supports		return T_SUPPORTS;
custom			return T_CUSTOM;
public			{
                          #ifdef USE_CORBA_2_1
			  yylval.ident = CORBA::string_dup( yytext );
			  return T_IDENTIFIER;
			  #else
			  return T_PUBLIC;
			  #endif
			}
private			{
			  #ifdef USE_CORBA_2_1
			  yylval.ident = CORBA::string_dup( yytext );
			  return T_IDENTIFIER;
			  #else
			  return T_PRIVATE;
			  #endif
			}
factory			return T_FACTORY;
native			return T_NATIVE;
ValueBase		return T_VALUEBASE;

"::"			return T_SCOPE; 

module			return T_MODULE;
octet			return T_OCTET;
any			return T_ANY;
sequence		return T_SEQUENCE;
readonly		return T_READONLY;
attribute		return T_ATTRIBUTE;
exception		return T_EXCEPTION;
oneway			return T_ONEWAY;
inout			return T_INOUT;
raises			return T_RAISES;
context			return T_CONTEXT;

Object                  return T_OBJECT;


{CORBA_Identifier}	{
			  yylval.ident = CORBA::string_dup(
			    yytext[0]=='_' ? yytext+1 : yytext );
			  return T_IDENTIFIER;
			}
{Float_Literal1}	|
{Float_Literal2}	|
{Float_Literal3}	|
{Float_Literal4}	|
{Float_Literal5}	|
{Float_Literal6}	{
			  yylval._float = ascii_to_longdouble( yytext );
			  return T_FLOATING_PT_LITERAL;
			}
{Fixed_Literal1}	|
{Fixed_Literal2}	|
{Fixed_Literal3}	|
{Fixed_Literal4}	{
                          string s = yytext;
                          s = s.substr( 0, s.length() - 1 );
			  yylval._fixed = ascii_to_longdouble (s.c_str());
			  return T_FIXED_PT_LITERAL;
			}
{Int_Literal}		{ 
			  yylval._int = ascii_to_longlong( 10, yytext );
			  return T_INTEGER_LITERAL;
			}
{Oct_Literal}		{
			  yylval._int = ascii_to_longlong( 8, yytext );
			  return T_INTEGER_LITERAL;
			}
{Hex_Literal}		{
			  yylval._int = ascii_to_longlong( 16, yytext + 2 );
			  return T_INTEGER_LITERAL;
			}
{Char_Literal}		{
                          string s( yytext );
                          s = s.substr( 1, s.length() - 2 );
			  yylval._char = translate_char( s.c_str() );
			  return T_CHARACTER_LITERAL;
			}
{String_Literal}	{
                          string s( yytext );
                          s = s.substr( 1, s.length() - 2 );
			  yylval._str = CORBA::string_dup( s.c_str() );
			  return T_STRING_LITERAL;
			}
.                       {
                          return T_UNKNOWN;
                        }

%%

