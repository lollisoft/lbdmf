%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mempool.h"
#include "sql.h"

extern int yylex(void);
extern void yyerror(const char *msg);
extern char* yytext;
extern List *schema;
extern MemPool mempool;

%}

%union
{
    char         *str;
    ForeignKey   *fk;
    PrimaryKey   *pk;
    Column       *column;
    List         *list;
    Table        *table;
    Altertable   *altertable;
    Constraint   *cons;
}

%type <table>      table;
%type <list>       error schema tables columndefs fkcolumnconstraints pkcolumnconstraints altertables
%type <fk>         fkcolumndef
%type <pk>         pkcolumndef
%type <altertable> altertable
%type <column>     columndef
%type <cons>       fkcolumnconstraint pkcolumnconstraint
%type <str>        type TOK_TYPE 

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
	| tables ';'
	| tables ';' altertables
	| tables ';' altertables ';'
	| altertables ';'
	| altertables
;

altertables:
	altertable
        {
            if ($1) {
		Table* t = NULL;
		List* l = NULL;

		if ($$ == NULL) $$ = list_new();

                t = (Table *) malloc(sizeof(Table));

		l = list_new();
                list_append(l, $1, TYPE_ALTERTABLE);

		if ($1->type == ALTER_FK)
			t->name = $1->fk->tab;
                else
			t->name = $1->pk->tab;
		t->columns = l;
                list_append(schema, t, TYPE_TABLE);
		}
        }
    | altertables ';' altertable
        {
            if ($3) {
		Table* t = NULL;
		List* l = NULL;
		if ($$ == NULL) $$ = list_new();

                t = (Table *) malloc(sizeof(Table));

		l = list_new();
                list_append(l, $3, TYPE_ALTERTABLE);

		if ($3->type == ALTER_FK)
			t->name = $3->fk->tab;
                else
			t->name = $3->pk->tab;
                t->columns = l;
                list_append(schema, t, TYPE_TABLE);
		}
        }
    | error
        /* ignore errors outside
           table definitons */
;


altertable:
	ALTER TABLE '"' TOK_WORD '"' ADD CONSTRAINT '"' TOK_WORD '"' PRIMARY KEY '(' '"' TOK_WORD '"' ')'
        {
            Altertable *constraint = malloc(sizeof(Altertable));
			constraint->type = ALTER_PK;
            constraint->pk = (PrimaryKey *) malloc(sizeof(PrimaryKey));
            constraint->pk->tab = $4;
            constraint->pk->col = $15;

			$$ = constraint;
        }
	| ALTER TABLE TOK_WORD ADD CONSTRAINT TOK_WORD PRIMARY KEY '(' TOK_WORD ')'
        {
            Altertable *constraint = malloc(sizeof(Altertable));
			constraint->type = ALTER_PK;
            constraint->pk = (PrimaryKey *) malloc(sizeof(PrimaryKey));
            constraint->pk->tab = $3;
            constraint->pk->col = $10;

			$$ = constraint;
        }
	| ALTER TABLE TOK_WORD ADD CONSTRAINT TOK_WORD FOREIGN KEY '(' TOK_WORD ')' REFERENCES TOK_WORD '(' TOK_WORD ')'
        {
            Altertable *constraint = malloc(sizeof(Altertable));
			constraint->type = ALTER_FK;
            constraint->fk = (ForeignKey *) malloc(sizeof(ForeignKey));
            constraint->fk->tab = $3;
            constraint->fk->col = $10;

            constraint->fk->ftab = $13;
            constraint->fk->fcol = $15;
			$$ = constraint;
        }
	| ALTER TABLE '"' TOK_WORD '"' ADD CONSTRAINT '"' TOK_WORD '"' FOREIGN KEY '(' '"' TOK_WORD '"' ')' REFERENCES '"' TOK_WORD '"' '(' '"' TOK_WORD '"' ')'
        {
            Altertable *constraint = malloc(sizeof(Altertable));
			constraint->type = ALTER_FK;
            constraint->fk = (ForeignKey *) malloc(sizeof(ForeignKey));
            constraint->fk->tab = $4;
            constraint->fk->col = $15;

            constraint->fk->ftab = $20;
            constraint->fk->fcol = $24;
			$$ = constraint;
        }
;

tables:
    table
        {
            if ($1)
                list_append(schema, $1, TYPE_TABLE);
        }
    | tables ';' table
        {
            if ($3)
                list_append(schema, $3, TYPE_TABLE);
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
                $$->columns = $5;
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
                $$->columns = $7;
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
            if ($1) {
				list_append($$, $1, TYPE_COLUMN);
			}
        }
    | fkcolumndef
        {
            $$ = list_new();
            if ($1) {
				list_append($$, $1, TYPE_FOREIGNKEY);
			}
        }
    | pkcolumndef
        {
            $$ = list_new();
            if ($1) {
				list_append($$, $1, TYPE_PRIMARYKEY);
			}
        }
    | columndefs ',' columndef
        {
            if ($3) {
				list_append($$, $3, TYPE_COLUMN);
			}
        }
    | columndefs ',' fkcolumndef
        {
            if ($3) {
				list_append($$, $3, TYPE_FOREIGNKEY);
			}
        }
    | columndefs ',' pkcolumndef
        {
            if ($3) {
				list_append($$, $3, TYPE_PRIMARYKEY);
			}
        }
;

columndef:
    TOK_WORD type
        {
			Column* col = (Column *) malloc(sizeof(Column));
			col->col = $1;
			col->type = $2;
            $$ = col;
        }
    | '"' TOK_WORD '"' type
        {
			Column* col = (Column *) malloc(sizeof(Column));
			col->col = $2;
			col->type = $4;
            $$ = col;
        }
;

fkcolumndef:
    TOK_WORD type fkcolumnconstraints
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
                        {/*
                            case CONSTRAINT_PRIMARYKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (PrimaryKey *) malloc(sizeof(PrimaryKey));
                                        $$->col = $1;
                                        $$->tab = NULL;
                                    }
                                }
                                break;*/
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
    | '"' TOK_WORD '"' type fkcolumnconstraints
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

pkcolumndef:
    TOK_WORD type pkcolumnconstraints
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
                            case CONSTRAINT_PRIMARYKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (PrimaryKey *) malloc(sizeof(PrimaryKey));
                                        $$->col = $1;
										$$->type = $2;
                                        $$->tab = NULL;
                                    }
                                }
                                break;
/*                            case CONSTRAINT_FOREIGNKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
                                        $$->col = $1;
                                        $$->ftab = constraint->foreign.tab;
                                        $$->fcol = constraint->foreign.col;
                                    }
                                }
                                break;*/
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
    | '"' TOK_WORD '"' type pkcolumnconstraints
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
                            case CONSTRAINT_PRIMARYKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (PrimaryKey *) malloc(sizeof(PrimaryKey));
                                        $$->col = $2;
										$$->type = $4;
                                        $$->tab = NULL;
                                    }
                                }
                                break;
/*                            case CONSTRAINT_FOREIGNKEY:
                                {
                                    if ($$ == NULL)
                                    {
                                        $$ = (ForeignKey *) malloc(sizeof(ForeignKey));
                                        $$->col = $2;
                                        $$->ftab = constraint->foreign.tab;
                                        $$->fcol = constraint->foreign.col;
                                    }
                                }
                                break;*/
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
;					

type:
    /* empty */
	{
		$$ = "empty";
	}
    | TOK_TYPE
	{
		$$ = yyval.str;
	}
;


fkcolumnconstraints:
    fkcolumnconstraint
        {
			if ($$ == NULL) $$ = list_new();
            if ($1) {
				if ($1->type == CONSTRAINT_FOREIGNKEY) {
				    list_append($$, $1, TYPE_FOREIGNKEY);
				} else {
				    list_append($$, $1, TYPE_COLUMN);
				}
			}
        }
    | fkcolumnconstraints fkcolumnconstraint
        {
            if ($2) {
				if ($2->type == CONSTRAINT_FOREIGNKEY) {
				    list_append($$, $2, TYPE_FOREIGNKEY);
				} else {
				    list_append($$, $2, TYPE_COLUMN);
				}
			}
        }
;

pkcolumnconstraints:
    pkcolumnconstraints pkcolumnconstraint
        {
			//printf("List of pkcolumnconstraints is %p.\n", $1);
            if ($2) {
				if ($2->type == CONSTRAINT_PRIMARYKEY) {
					//if ($1 == $2) malloc_printf("Error: Item to be added is the list itself!\n");
				    list_append($1, $2, TYPE_PRIMARYKEY);
				} else {
				    list_append($1, $2, TYPE_COLUMN);
				}
			}
			if ($$ == NULL) $$ = $1;
        }
    | pkcolumnconstraint
        {
			$$ = list_new();
			//printf("List of pkcolumnconstraints is %p.\n", $$);
            if ($1) {
				if ($1->type == CONSTRAINT_PRIMARYKEY) {
					//if ($$ == $1) malloc_printf("Error: Item to be added is the list itself (list = %p, pkconstraint = %p)!\n", $$, $1);
				    list_append($$, $1, TYPE_PRIMARYKEY);
				} else {
				    list_append($$, $1, TYPE_COLUMN);
				}
			}
        }

;

pkcolumnconstraint:
    PRIMARY KEY        /* primary key */
        { 
            $$ = (Constraint *) malloc(sizeof(Constraint));
			//printf("Allocated primary key constraint: %p.\n", $$);
            $$->type = CONSTRAINT_PRIMARYKEY;
		}
    | DEFAULT TOK_WORD /* default */
        { $$ = NULL; }
    | UNIQUE           /* unique */
        { $$ = NULL; }
    | NOT NIL          /* not null */
        {
            $$ = (Constraint *) malloc(sizeof(Constraint));
            $$->type = CONSTRAINT_NOTNULL;
        }
;

fkcolumnconstraint:
	DEFAULT TOK_WORD /* default */
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
