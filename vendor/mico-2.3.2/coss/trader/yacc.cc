
/*  A Bison parser, made from yacc.yy
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 1 "yacc.yy"

#include <CORBA.h>

extern "C" {

#include "parse.h"
#ifdef _WINDOWS
#include <malloc.h>
#endif

void yyerror(char *s);
void initFlex( const char *s );

};

int yylex();


#line 19 "yacc.yy"
typedef union
{
     char valb;
     int vali;
     double vald;
     char *name;
     void *ptr;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		62
#define	YYFLAG		-32768
#define	YYNTBASE	37

#define YYTRANSLATE(x) ((unsigned)(x) <= 284 ? yytranslate[x] : 49)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
    36,    33,    31,     2,    32,     2,    34,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    30,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     3,     5,     8,    11,    14,    16,    18,    20,
    24,    26,    30,    32,    36,    40,    44,    48,    52,    56,
    58,    62,    64,    68,    70,    74,    78,    80,    84,    88,
    90,    93,    95,    99,   102,   104,   106,   108,   110
};

static const short yyrhs[] = {    -1,
    39,     0,    38,     0,    24,    39,     0,    22,    39,     0,
    23,    39,     0,    20,     0,    21,     0,    40,     0,    41,
    16,    41,     0,    41,     0,    42,    17,    42,     0,    42,
     0,    43,    10,    43,     0,    43,    11,    43,     0,    43,
    13,    43,     0,    43,    12,    43,     0,    43,    14,    43,
     0,    43,    15,    43,     0,    43,     0,    44,    18,    27,
     0,    44,     0,    45,    30,    45,     0,    45,     0,    45,
    31,    46,     0,    45,    32,    46,     0,    46,     0,    46,
    33,    47,     0,    46,    34,    47,     0,    47,     0,     9,
    48,     0,    48,     0,    35,    40,    36,     0,    19,    27,
     0,    27,     0,    28,     0,    29,     0,    26,     0,    25,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    73,    74,    75,    78,    79,    80,    81,    82,    85,    88,
    89,    92,    93,    96,    97,    98,    99,   100,   101,   102,
   105,   106,   109,   110,   113,   114,   115,   118,   119,   120,
   123,   124,   127,   128,   129,   130,   131,   132,   133
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DOCROOT",
"PORT","CGI","ALIAS","MIME","PIXDIR","NOT","EQ","NEQ","LEQ","GEQ","LE","GR",
"OR","AND","IN","EXIST","FIRST","RANDOM","MAX","MIN","WITH","BOOL","STRING",
"ID","NUM","FLOAT","'~'","'+'","'-'","'*'","'/'","'('","')'","constraint","preferences",
"bool","bool_or","bool_and","bool_compare","expr_in","expr_twiddle","expr","term",
"factor_non","factor", NULL
};
#endif

static const short yyr1[] = {     0,
    37,    37,    37,    38,    38,    38,    38,    38,    39,    40,
    40,    41,    41,    42,    42,    42,    42,    42,    42,    42,
    43,    43,    44,    44,    45,    45,    45,    46,    46,    46,
    47,    47,    48,    48,    48,    48,    48,    48,    48
};

static const short yyr2[] = {     0,
     0,     1,     1,     2,     2,     2,     1,     1,     1,     3,
     1,     3,     1,     3,     3,     3,     3,     3,     3,     1,
     3,     1,     3,     1,     3,     3,     1,     3,     3,     1,
     2,     1,     3,     2,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     1,
     0,     0,     7,     8,     0,     0,     0,    39,    38,    35,
    36,    37,     0,     3,     2,     9,    11,    13,    20,    22,
    24,    27,    30,    32,    31,    34,     5,     6,     4,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    33,    10,    12,    14,    15,    17,
    16,    18,    19,    21,    23,    25,    26,    28,    29,     0,
     0,     0
};

static const short yydefgoto[] = {    60,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24
};

static const short yypact[] = {    -9,
    17,   -26,-32768,-32768,    12,    12,    12,-32768,-32768,-32768,
-32768,-32768,    12,-32768,-32768,-32768,     6,    13,    -8,    32,
    -7,   -25,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    -2,
    12,    12,    12,    12,    12,    12,    12,    12,     8,    12,
    12,    12,    12,    12,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,     1,   -25,   -25,-32768,-32768,    51,
    61,-32768
};

static const short yypgoto[] = {-32768,
-32768,    22,    49,    33,    31,    20,-32768,    25,     7,    16,
    65
};


#define	YYLAST		66


static const short yytable[] = {     1,
    26,    33,    34,    35,    36,    37,    38,    43,    44,     2,
     3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     1,    31,    40,    41,    42,    13,    27,    28,    29,    32,
     2,    41,    42,    45,    54,     2,     8,     9,    10,    11,
    12,     8,     9,    10,    11,    12,    13,    56,    57,    39,
    61,    13,    48,    49,    50,    51,    52,    53,    58,    59,
    62,    30,    47,    46,    55,    25
};

static const short yycheck[] = {     9,
    27,    10,    11,    12,    13,    14,    15,    33,    34,    19,
    20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
     9,    16,    30,    31,    32,    35,     5,     6,     7,    17,
    19,    31,    32,    36,    27,    19,    25,    26,    27,    28,
    29,    25,    26,    27,    28,    29,    35,    41,    42,    18,
     0,    35,    33,    34,    35,    36,    37,    38,    43,    44,
     0,    13,    32,    31,    40,     1
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/local/pkg/bison/1.25/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/local/pkg/bison/1.25/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 73 "yacc.yy"
{ setConstraintsParseTree( 0L ); ;
    break;}
case 2:
#line 74 "yacc.yy"
{ setConstraintsParseTree( yyvsp[0].ptr ); ;
    break;}
case 3:
#line 75 "yacc.yy"
{ ;
    break;}
case 4:
#line 78 "yacc.yy"
{ setPreferencesParseTree( newWITH( yyvsp[0].ptr ) ); ;
    break;}
case 5:
#line 79 "yacc.yy"
{ setPreferencesParseTree( newMAX( yyvsp[0].ptr ) ); ;
    break;}
case 6:
#line 80 "yacc.yy"
{ setPreferencesParseTree( newMIN( yyvsp[0].ptr ) ); ;
    break;}
case 7:
#line 81 "yacc.yy"
{ setPreferencesParseTree( newFIRST() ); ;
    break;}
case 8:
#line 82 "yacc.yy"
{ setPreferencesParseTree( newRANDOM() ); ;
    break;}
case 9:
#line 85 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 10:
#line 88 "yacc.yy"
{ yyval.ptr = newOR( yyvsp[-2].ptr, yyvsp[0].ptr ); ;
    break;}
case 11:
#line 89 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 12:
#line 92 "yacc.yy"
{ yyval.ptr = newAND( yyvsp[-2].ptr, yyvsp[0].ptr ); ;
    break;}
case 13:
#line 93 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 14:
#line 96 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 1 ); ;
    break;}
case 15:
#line 97 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 2 ); ;
    break;}
case 16:
#line 98 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 3 ); ;
    break;}
case 17:
#line 99 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 4 ); ;
    break;}
case 18:
#line 100 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 5 ); ;
    break;}
case 19:
#line 101 "yacc.yy"
{ yyval.ptr = newCMP( yyvsp[-2].ptr, yyvsp[0].ptr, 6 ); ;
    break;}
case 20:
#line 102 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 21:
#line 105 "yacc.yy"
{ yyval.ptr = newIN( yyvsp[-2].ptr, newID( yyvsp[0].name ) ); ;
    break;}
case 22:
#line 106 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 23:
#line 109 "yacc.yy"
{ yyval.ptr = newMATCH( yyvsp[-2].ptr, yyvsp[0].ptr ); ;
    break;}
case 24:
#line 110 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 25:
#line 113 "yacc.yy"
{ yyval.ptr = newCALC( yyvsp[-2].ptr, yyvsp[0].ptr, 1 ); ;
    break;}
case 26:
#line 114 "yacc.yy"
{ yyval.ptr = newCALC( yyvsp[-2].ptr, yyvsp[0].ptr, 2 ); ;
    break;}
case 27:
#line 115 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 28:
#line 118 "yacc.yy"
{ yyval.ptr = newCALC( yyvsp[-2].ptr, yyvsp[0].ptr, 3 ); ;
    break;}
case 29:
#line 119 "yacc.yy"
{ yyval.ptr = newCALC( yyvsp[-2].ptr, yyvsp[0].ptr, 4 ); ;
    break;}
case 30:
#line 120 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 31:
#line 123 "yacc.yy"
{ yyval.ptr = newNOT( yyvsp[0].ptr ); ;
    break;}
case 32:
#line 124 "yacc.yy"
{ yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 33:
#line 127 "yacc.yy"
{ yyval.ptr = newBRACKETS( yyvsp[-1].ptr ); ;
    break;}
case 34:
#line 128 "yacc.yy"
{ yyval.ptr = newEXIST( yyvsp[0].name ); ;
    break;}
case 35:
#line 129 "yacc.yy"
{ yyval.ptr = newID( yyvsp[0].name ); ;
    break;}
case 36:
#line 130 "yacc.yy"
{ yyval.ptr = newNUM( yyvsp[0].vali ); ;
    break;}
case 37:
#line 131 "yacc.yy"
{ yyval.ptr = newFLOAT( yyvsp[0].vald ); ;
    break;}
case 38:
#line 132 "yacc.yy"
{ yyval.ptr = newSTRING( yyvsp[0].name ); ;
    break;}
case 39:
#line 133 "yacc.yy"
{ yyval.ptr = newBOOL( yyvsp[0].valb ); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/local/pkg/bison/1.25/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 138 "yacc.yy"


void yyerror ( char *s )  /* Called by yyparse on error */
{
    printf ("ERROR: %s\n", s);
}

void mainParse( const char *_code )
{
  initFlex( _code );
  yyparse();
}
