/*
 * fk.c
 * Released into the public domain August/15/2004
 *
 * Author: Cody Pisto <cpisto@gmail.com>
 *
 * Parses sqlite sql schema, and generates triggers to 
 * enforce foreign key constraints
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sql.h"
#include "mempool.h"

#ifdef BUILD_LIBRARY
#include <string.h>
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE; 

int             yylex( void ); 
YY_BUFFER_STATE yy_scan_string( const char * ); 
void            yy_delete_buffer( YY_BUFFER_STATE ); 

extern FILE* yyin;
extern int yyparse(void);
extern void scanner_finish(void);

List *schema;
MemPool mempool;

#ifndef BUILD_LIBRARY
int
main (int argc, char **argv)
#endif

#ifdef BUILD_LIBRARY
List* getForeignKeyList(char* _table, char* sql_ddl)
#endif
{
    int i,x;
    ListItem *tabitem, *fkitem;
    Table *table;
    ForeignKey *fk;
#ifdef BUILD_LIBRARY
	List *foreign_keys;
#endif

    schema = list_new();
    MemPoolCreate(&mempool, 4096);
    /* yyparse will fill the schema with
     * tables
     */
	 
	 
	if (sql_ddl == NULL) {
		yyin = fopen("test.sql", "rb");
		if (yyin == NULL) printf("Error: Can't open file.\n");
		yyparse();
		scanner_finish();
	} else {
		YY_BUFFER_STATE mybuf;
		mybuf = yy_scan_string(sql_ddl);
		yyparse();
		scanner_finish();
		//yy_delete_buffer(mybuf); 
	}
	

#ifdef BUILD_LIBRARY
    tabitem = list_head(schema);
    while (tabitem != NULL)
    {
        table = (Table *)list_data(tabitem);
		
		if (table == NULL)
			goto table_next;
		
		if (strcmp(table->name, _table) == 0) {
			foreign_keys = list_new();
			
			fkitem = list_head(table->fks);
			for (x = 0; fkitem; x++)
			{
				ForeignKey* copy_of_fk = (ForeignKey*) malloc(sizeof(ForeignKey));
				fk = (ForeignKey *)list_data(fkitem);
				if (fk == NULL)
					goto fk_next;
				
				copy_of_fk->col = strdup(fk->col);
				copy_of_fk->ftab = strdup(fk->ftab);
				copy_of_fk->fcol = strdup(fk->fcol);
				
				list_append(foreign_keys, copy_of_fk);
					
fk_next:					
				fkitem = list_next(fkitem);
			}
	        list_destroy(table->fks);
		}
table_next:		
		tabitem = list_next(tabitem);
	}
	
    list_destroy(schema);
    MemPoolDestroy(&mempool);
	return foreign_keys;
#endif

#ifndef BUILD_LIBRARY

    printf("BEGIN TRANSACTION;\n\n");

    /*
     * Iterate over the tables
     */
    tabitem = list_head(schema);
    for (i = 0; tabitem; i++)
    {
        table = (Table *)list_data(tabitem);

        /*
         * Iterate over foreign keys
         */
        fkitem = list_head(table->fks);
        for (x = 0; fkitem; x++)
        {
            fk = (ForeignKey *)list_data(fkitem);
            if (fk == NULL)
                goto next;

            /*
             * triggers that dont have to check for null
             */
            if (fk->notnull)
            {
                /* table */
                printf("CREATE TRIGGER \"fk_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL)\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, table->name, fk->fcol, fk->ftab, fk->fcol, fk->col,
                       fk->col, fk->ftab, fk->fcol);
                printf("CREATE TRIGGER \"fk_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL)\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, table->name, fk->fcol, fk->ftab, fk->fcol, fk->col,
                       fk->col, fk->ftab, fk->fcol);

                /* foreign table */
                printf("CREATE TRIGGER \"fk_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, fk->ftab, fk->col, table->name, fk->col, fk->fcol,
                       fk->fcol, table->name, fk->col);
            }

            /*
             * triggers that do have to check for null
             */
            else
            {
                /* table */
                printf("CREATE TRIGGER \"fk_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, table->name, fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col,
                       fk->col, fk->ftab, fk->fcol);
                printf("CREATE TRIGGER \"fk_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, table->name, fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col,
                       fk->col, fk->ftab, fk->fcol);

                /* foreign table */
                printf("CREATE TRIGGER \"fk_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
                       "BEGIN\n"
                       "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
                       "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
                       "    END;\n"
                       "END;\n", table->name, fk->col, fk->ftab, fk->col, table->name, fk->col, fk->fcol,
                       fk->fcol, table->name, fk->col);
            }

            printf("\n");

next:
            fkitem = list_next(fkitem);
        }

        list_destroy(table->fks);

        tabitem = list_next(tabitem);
    }

    list_destroy(schema);
    MemPoolDestroy(&mempool);

    printf("COMMIT;\n");

    return 0;
#endif // not BUILD_LIBRARY
}
