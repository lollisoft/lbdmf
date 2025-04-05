typedef union 
{
  char              *ident;
  ParseNode         *node;
  CORBA::LongLong   _int;
  char             *_str;
  CORBA::Char       _char;
  CORBA::LongDouble _float;
  CORBA::LongDouble _fixed;
} YYSTYPE;
#define	T_AMPERSAND	258
#define	T_ANY	259
#define	T_ASTERISK	260
#define	T_ATTRIBUTE	261
#define	T_BOOLEAN	262
#define	T_CASE	263
#define	T_CHAR	264
#define	T_CHARACTER_LITERAL	265
#define	T_CIRCUMFLEX	266
#define	T_COLON	267
#define	T_COMMA	268
#define	T_CONST	269
#define	T_CONTEXT	270
#define	T_DEFAULT	271
#define	T_DOUBLE	272
#define	T_ENUM	273
#define	T_EQUAL	274
#define	T_EXCEPTION	275
#define	T_FALSE	276
#define	T_FIXED	277
#define	T_FIXED_PT_LITERAL	278
#define	T_FLOAT	279
#define	T_FLOATING_PT_LITERAL	280
#define	T_GREATER_THAN_SIGN	281
#define	T_IDENTIFIER	282
#define	T_IN	283
#define	T_INOUT	284
#define	T_INTEGER_LITERAL	285
#define	T_INTERFACE	286
#define	T_LEFT_CURLY_BRACKET	287
#define	T_LEFT_PARANTHESIS	288
#define	T_LEFT_SQUARE_BRACKET	289
#define	T_LESS_THAN_SIGN	290
#define	T_LONG	291
#define	T_MINUS_SIGN	292
#define	T_MODULE	293
#define	T_OCTET	294
#define	T_ONEWAY	295
#define	T_OUT	296
#define	T_PERCENT_SIGN	297
#define	T_PLUS_SIGN	298
#define	T_RAISES	299
#define	T_READONLY	300
#define	T_RIGHT_CURLY_BRACKET	301
#define	T_RIGHT_PARANTHESIS	302
#define	T_RIGHT_SQUARE_BRACKET	303
#define	T_SCOPE	304
#define	T_SEMICOLON	305
#define	T_SEQUENCE	306
#define	T_SHIFTLEFT	307
#define	T_SHIFTRIGHT	308
#define	T_SHORT	309
#define	T_SOLIDUS	310
#define	T_STRING	311
#define	T_STRING_LITERAL	312
#define	T_PRAGMA	313
#define	T_INCLUDE	314
#define	T_STRUCT	315
#define	T_SWITCH	316
#define	T_TILDE	317
#define	T_TRUE	318
#define	T_OBJECT	319
#define	T_TYPEDEF	320
#define	T_UNION	321
#define	T_UNSIGNED	322
#define	T_VERTICAL_LINE	323
#define	T_VOID	324
#define	T_WCHAR	325
#define	T_WSTRING	326
#define	T_UNKNOWN	327
#define	T_ABSTRACT	328
#define	T_VALUETYPE	329
#define	T_TRUNCATABLE	330
#define	T_SUPPORTS	331
#define	T_CUSTOM	332
#define	T_PUBLIC	333
#define	T_PRIVATE	334
#define	T_FACTORY	335
#define	T_NATIVE	336
#define	T_VALUEBASE	337


extern YYSTYPE yylval;
