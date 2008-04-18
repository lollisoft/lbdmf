%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mempool.h"
#include "sql.h"

extern int yylex(void);
extern void yyerror(const char *msg);

extern List *schema;
extern MemPool mempool;

%}

%union
{
    char         *str;
    ForeignKey   *fk;
    List         *list;
    Table        *table;
    Constraint   *cons;
}

%type <table> table;
%type <list>  error schema tables columndefs columnconstraints altertables
%type <fk>    columndef altertable
%type <cons>  columnconstraint 

%token CREATE
%token TABLE
%token ALTER
%token CONSTRAINT FOREIGN
%token ADD REFERENCES NOT NIL PRIMARY KEY DEFAULT UNIQUE
%token TOK_TYPE
%token <str> TOK_WORD

%left '(' ')'

%%

schema:
    tables
	| tables ';' altertables
	| altertables
;

altertables:
	altertable
        {
            if ($1) {
				if ($$ == NULL) $$ = list_new();

                Table* t = (Table *) malloc(sizeof(Table));

				List* l = list_new();
                list_append(l, $1);

                t->name = $1->tab;
                t->fks = l;
                list_append(schema, t);
			}
        }
    | altertables ';' altertable
        {
            if ($3) {
				if ($$ == NULL) $$ = list_new();

                Table* t = (Table *) malloc(sizeof(Table));

				List* l = list_new();
                list_append(l, $3);

                t->name = $3->tab;
                t->fks = l;
                list_append(schema, t);
			}
        }

    | error
        /* ignore errors outside
           table definitons */

;

altertable:
	ALTER TABLE TOK_WORD ADD CONSTRAINT TOK_WORD FOREIGN KEY '(' TOK_WORD ')' REFERENCES TOK_WORD '(' TOK_WORD ')'
        {
            //ForeignKey *constraint;
            $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
            $$->tab = $3;
			// $5 = constraint
            $$->col = $10;

            $$->ftab = $13;
            $$->fcol = $15;
        }
	
	| ALTER TABLE '"' TOK_WORD '"' ADD CONSTRAINT '"' TOK_WORD '"' FOREIGN KEY '(' '"' TOK_WORD '"' ')' REFERENCES '"' TOK_WORD '"' '(' '"' TOK_WORD '"' ')'
        {
            //ForeignKey *constraint;
            $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
            $$->tab = $4;
			// $9 = constraint
            $$->col = $15;

            $$->ftab = $20;
            $$->fcol = $24;
        }
;

tables:
    table
        {
            if ($1)
                list_append(schema, $1);
        }
    | tables ';' table
        {
            if ($3)
                list_append(schema, $3);
        }
    | error
        /* ignore errors outside
           table definitons */
;

table:
    CREATE TABLE TOK_WORD '(' columndefs ')'
        {
            /* did we get at least one
                foreign key column ? */
            if ($5->len > 0)
            {
                $$ = (Table *) malloc(sizeof(Table));
                $$->name = $3;
                $$->fks = $5;
                //fprintf(stderr, "Parsed table %s\n", $3);
            }
            /* no foreign keys on this table
               ignore it */
            else
            {
                list_destroy($5);
                $$ = NULL;
            }
        }
    | CREATE TABLE '"' TOK_WORD '"' '(' columndefs ')'
        {
            /* did we get at least one
                foreign key column ? */
            if ($7->len > 0)
            {
                $$ = (Table *) malloc(sizeof(Table));
                $$->name = $4;
                $$->fks = $7;
                //fprintf(stderr, "Parsed table %s\n", $3);
            }
            /* no foreign keys on this table
               ignore it */
            else
            {
                list_destroy($7);
                $$ = NULL;
            }
        }
;

columndefs:
    columndef
        {
            $$ = list_new();
            if ($1)
                list_append($$, $1);
        }
    | columndefs ',' columndef
        {
            if ($3)
                list_append($$, $3);
        }
;

columndef:
    TOK_WORD type
        { $$ = NULL }
    | '"' TOK_WORD '"' type
        { $$ = NULL }
    | TOK_WORD type columnconstraints
        {
            $$ = NULL;

            if ($3)
            {
                if ($3->len > 0)
                {
                    int i;
                    unsigned char notnull = 0;
                    Constraint *constraint;
                    ListItem *item;

                    item = list_head($3);
                    for (i = 0; item; i++)
                    {
                        constraint = (Constraint *)list_data(item);
                        
                        switch  (constraint->type)
                        {
                            case CONSTRAINT_FOREIGNKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
                                        $$->col = $1;
                                        $$->ftab = constraint->foreign.tab;
                                        $$->fcol = constraint->foreign.col;
                                    }
                                }
                                break;
                            case CONSTRAINT_NOTNULL:
                                notnull = 1;
                                break;
                            default:
                                break;
                        }
                        
                        item = list_next(item);
                    }

                    if ($$)
                        $$->notnull = notnull;
                }
                list_destroy($3);
            }
        }
    | '"' TOK_WORD '"' type columnconstraints
        {
            $$ = NULL;

            if ($5)
            {
                if ($5->len > 0)
                {
                    int i;
                    unsigned char notnull = 0;
                    Constraint *constraint;
                    ListItem *item;

                    item = list_head($5);
                    for (i = 0; item; i++)
                    {
                        constraint = (Constraint *)list_data(item);
                        
                        switch  (constraint->type)
                        {
                            case CONSTRAINT_FOREIGNKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
                                        $$->col = $2;
                                        $$->ftab = constraint->foreign.tab;
                                        $$->fcol = constraint->foreign.col;
                                    }
                                }
                                break;
                            case CONSTRAINT_NOTNULL:
                                notnull = 2;
                                break;
                            default:
                                break;
                        }
                        
                        item = list_next(item);
                    }

                    if ($$)
                        $$->notnull = notnull;
                }
                list_destroy($5);
            }
        }
    | CONSTRAINT TOK_WORD FOREIGN KEY '(' TOK_WORD ')' REFERENCES TOK_WORD '(' TOK_WORD ')'
        {
            //ForeignKey *constraint;
            $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
            $$->col = $6;

            $$->ftab = $9;
            $$->fcol = $11;
        }
    | CONSTRAINT '"' TOK_WORD '"' FOREIGN KEY '(' '"' TOK_WORD '"' ')' REFERENCES '"' TOK_WORD '"' '(' '"' TOK_WORD '"' ')'
        {
            //ForeignKey *constraint;
            $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
            $$->col = $9;

            $$->ftab = $14;
            $$->fcol = $18;
        }
;

type:
    /* empty */
    | TOK_TYPE
;

columnconstraints:
    columnconstraint
        {
			if ($$ == NULL) $$ = list_new();
            if ($1)
                list_append($$, $1);
        }
    | columnconstraints columnconstraint
        {
            if ($2)
                list_append($$, $2);
        }
;

columnconstraint:
    PRIMARY KEY        /* primary key */
        { $$ = NULL; }
    | DEFAULT TOK_WORD /* default */
        { $$ = NULL; }
    | UNIQUE           /* unique */
        { $$ = NULL; }
    | NOT NIL          /* not null */
        {
            $$ = (Constraint *) malloc(sizeof(Constraint));
            $$->type = CONSTRAINT_NOTNULL;
        }
    | REFERENCES TOK_WORD '(' TOK_WORD ')' /* reference */
        {
            $$ = (Constraint *) malloc(sizeof(Constraint));
            $$->type = CONSTRAINT_FOREIGNKEY;

            $$->foreign.tab = $2;
            $$->foreign.col = $4;
        }
;

%%
