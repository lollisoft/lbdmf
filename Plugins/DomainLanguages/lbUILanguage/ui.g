grammar ui;
 
options {
    language=C;
    output=AST;
}
 
tokens {
    PLUS    = '+' ;
    MINUS   = '-' ;
    MULT    = '*' ;
    DIV = '/' ;
}
 
@lexer::header {
#define Hidden 99
} 
 
 
@members {

}
 
/*------------------------------------------------------------------
 * PARSER RULES
 *------------------------------------------------------------------*/
 
expr    : term ( ( PLUS | MINUS )  term )* ;
 
term    : factor ( ( MULT | DIV ) factor )* ;
 
factor  : NUMBER ;
 
 
/*------------------------------------------------------------------
 * LEXER RULES
 *------------------------------------------------------------------*/
 
NUMBER  : (DIGIT)+ ;
 
WHITESPACE : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+    { $channel = Hidden; } ;
 
fragment DIGIT  : '0'..'9' ;