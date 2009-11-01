typedef union
{
     char valb;
     int vali;
     double vald;
     char *name;
     void *ptr;
} YYSTYPE;
#define	DOCROOT	258
#define	PORT	259
#define	CGI	260
#define	ALIAS	261
#define	MIME	262
#define	PIXDIR	263
#define	NOT	264
#define	EQ	265
#define	NEQ	266
#define	LEQ	267
#define	GEQ	268
#define	LE	269
#define	GR	270
#define	OR	271
#define	AND	272
#define	IN	273
#define	EXIST	274
#define	FIRST	275
#define	RANDOM	276
#define	MAX	277
#define	MIN	278
#define	WITH	279
#define	BOOL	280
#define	STRING	281
#define	ID	282
#define	NUM	283
#define	FLOAT	284


extern YYSTYPE yylval;
