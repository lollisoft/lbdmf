grammar ui;
 
options {
    language=C;
    output=AST;
}

/* 
@lexer::header {
#define Hidden 99
}
*/
 
@header {
#define _empty NULL
}
 
@members {

}
 
UI	:	'ui'
	; 

END	:	'end'
	;
	
FORMS	:	'forms'
	;	
	
FORM	:	'form'
	;	
	
DECLARE	:	'declare'
	;

FIELD	:	'field'
	;	
	
DEFAULT	:	'default'
	;	
	
FIELDTYPE
	:	'fieldtype'
	;	
	
SHOWS
	:	'shows'
	;	
REFERS
	:	'refers'
	;	
AS
	:	'as'
	;	
USING
	:	'using'
	;	
USE
	:	'use'
	;	
	
OVER
	:	'over'
	;	

DATA
	:	'data'
	;	

INFER
	:	'infer'
	;	

YES
	:	'yes'
	;	

TODO
	:	'todo'
	;	

DOT
	:	'.'
	;	
	
/*------------------------------------------------------------------
 * PARSER RULES
 *------------------------------------------------------------------*/

ui    : UI identifier STRING (declare_data)? (declare_forms)? END UI
    ;
   
declare_forms
    :    DECLARE FORMS (form)* END FORMS
    |    DECLARE FORMS (default_fieldtype) (form)* END FORMS
    ;

default_fieldtype
    :    DEFAULT FIELDTYPE identifier
    ;


form   
  :    FORM identifier STRING (use_data)* (field)* END FORM
  ;

field
  :    FIELD identifier STRING SHOWS identifier (DOT identifier)? (AS identifier)?
  |    FIELD identifier STRING AS identifier
  |    FIELD identifier STRING REFERS identifier USING identifier OVER identifier DOT identifier
  |    FIELD identifier STRING
  ;

use_data
  :    USE DATA DOT identifier identifier (DEFAULT)?
  ;

declare_data
  :    DECLARE DATA (infer | use)? END DATA
  ;

use 
  :    USE STRING
  ;

infer
  :    INFER YES
  |    INFER TODO
  ;
   
/*
expr    : term ( ( PLUS | MINUS )  term )* ;
 
term    : factor ( ( MULT | DIV ) factor )* ;
 
factor  : NUMBER ;
*/

identifier
    :    ALPHA
    |    ALPHA NUMBER
    ;

/*------------------------------------------------------------------
 * LEXER RULES
 *------------------------------------------------------------------*/

//string_guts
//      : (~'"')*
// I do not really need escapes yet, so skip it due to antlrWorks bugs     
//    | (ESC | ~('"' | '\\'))*
//      ;

WHITESPACE
  :	( '\t' | ' ' | '\r' | '\n'| '\u000C' )+    { $channel = HIDDEN; }
  ;

// also a fragment rule perhaps?
fragment ESC
  :  ('\\' 's')
  |  ('\\' 'x')
  |  ('\\' 'd')
  |  ('\\' 'l')
  |  ('\\' '\\')
  ;

STRING    
  :  '"' (~'"')* '"'
  ;
 
NUMBER  
  : DIGITS
  ;

ALPHA
  :    ('a'..'z' | 'A'..'Z' | '_')+
  ;

//STRINGCHAR
//    :    (~'"')*
//    ;

 
fragment DIGITS
  : '0'..'9'+
  ;