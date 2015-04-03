grammar ui;
 
options {
    language=C;
    output=AST;
}
 
tokens {
/*
    PLUS    = '+' ;
    MINUS   = '-' ;
    MULT    = '*' ;
    DIV     = '/' ;    
*/
    UI      = 'ui' ;
    ENDUI   = 'end ui' ;
}
 
@lexer::header {
#define Hidden 99
} 
 
 
@members {

}
 
/*------------------------------------------------------------------
 * PARSER RULES
 *------------------------------------------------------------------*/

ui	: UI identifier string (declare_data)? ENDUI;

declare_data 
	:	'declare data' (infer | use)? 'end data'
	;

use	:	'use' string
	;

infer	:	'infer' 'yes'
// Non existing is no
//	|	'infer' 'no'
	|	'infer' 'todo'
	;
	
/* 
expr    : term ( ( PLUS | MINUS )  term )* ;
 
term    : factor ( ( MULT | DIV ) factor )* ;
 
factor  : NUMBER ;
*/

/*------------------------------------------------------------------
 * LEXER RULES
 *------------------------------------------------------------------*/

string 
  :  '"' string_guts '"'
  ;

identifier
	:	(ALPHA)+ NUMBER
	|	(ALPHA)+
	;

string_guts
  	: (~'"')*
// I do not really need escapes yet, so skip it due to antlrWorks bugs  	
//	| (ESC | ~('"' | '\\'))*
  	;

// also a fragment rule perhaps?
fragment ESC
  :  ('\\' 's')
  |  ('\\' 'x')
  |  ('\\' 'd')
  |  ('\\' 'l')
  |  ('\\' '\\')
  ;

  
NUMBER  : (DIGIT)+ ;

ALPHA  
	:	'a'..'z' | 'A'..'Z' ;

fragment WHITESPACE : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+    { $channel = Hidden; } ;
 
fragment DIGIT  : '0'..'9' ;
