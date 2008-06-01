%{
#include <stdio.h>
#include <string.h>
#include "sql.h"
#include "gram.tab.h"
#include "mempool.h"

extern MemPool mempool;

/* buffer for quoted strings */
static char buf[8192];
int buflen = 0;

#define bufcat(str, len) if (len >= (sizeof(buf) - buflen)) {\
                             fprintf(stderr, "Quoted string too long\n"); \
                             yyterminate(); \
                         } else { \
                             buflen += len; \
                             strcat(buf, str); \
                         }

%}

%option noyywrap

%x QUOTED
%x DQUOTED
%x COMMENT

type       (int)|(integer)|(bool)|(boolean)|(varchar\([0-9]+\))|(char\([0-9]+\))|(datetime)|(text)|(bpchar)

%%
<QUOTED,DQUOTED>[a-zA-Z0-9_-]+ { bufcat(yytext, yyleng); }
<QUOTED,DQUOTED>[ ]+           { bufcat(yytext, yyleng); }
<QUOTED,DQUOTED><<EOF>>        { 
                                   fprintf(stderr, "Unterminated quoted string\n");
                                   yyterminate();
                               }
<QUOTED>\"                     |
<DQUOTED>\'                    { bufcat(yytext, yyleng); }
<DQUOTED>\"                    |
<QUOTED>\'                     {
                                 BEGIN(INITIAL);
                                 yylval.str = pstrdup(&mempool, buf);
                                 memset(buf, '\0', sizeof(buf));
                                 buflen = 0;
                                 return TOK_WORD;
                               }
<QUOTED,DQUOTED>.              /* ignore */;
<COMMENT>\n                    { BEGIN(INITIAL); }
<COMMENT>.                     /* ignore */;
^--                            { BEGIN(COMMENT); }
{type}						   { 
                                 yylval.str = pstrdup(&mempool, yytext);

                                 return TOK_TYPE;
                               }
create                         return CREATE;
table                          return TABLE;
alter                          return ALTER;
add							   return ADD;
references                     return REFERENCES;
constraint                     return CONSTRAINT;
not                            return NOT;
null                           return NIL;
unique                         return UNIQUE;
primary                        return PRIMARY;
foreign                        return FOREIGN;
key                            return KEY;
default                        return DEFAULT;
[a-zA-Z0-9_-]+                 { 
                                 yylval.str = pstrdup(&mempool, yytext);

                                 return TOK_WORD;
                               }
\"                             { BEGIN(DQUOTED); }
\'                             { BEGIN(QUOTED); }
\;                             return yytext[0];
\,                             return yytext[0];
\(|\)                          return yytext[0];
\n+                            /* ignore */;
.                              /* ignore */;
%%

void
yyerror (const char *message)
{
       char    *p, *underline; 
        int     buflen  = strlen(YY_CURRENT_BUFFER->yy_ch_buf); 

        if (!buflen) 
                fprintf(stderr, "parser: %s at or near \"%s\"", 
                        message, yytext); 

        underline = (char*) malloc(buflen); 
        memset(underline, ' ', buflen); 
        *(underline + buflen) = '\0'; 

        for(p = underline + (buflen - yyleng); *p != '\0'; p++) 
                *p = '^'; 

        fprintf(stderr, "%s\n        %s\n        parser: %s at or near \"%s\"", 
                YY_CURRENT_BUFFER->yy_ch_buf, underline, 
                message, yytext); 

        free(underline); 

}


void
scanner_finish (void)
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
