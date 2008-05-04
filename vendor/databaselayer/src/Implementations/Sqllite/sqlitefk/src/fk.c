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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sql.h"
#include "mempool.h"

#ifdef BUILD_LIBRARY
#include <string.h>
#endif

#ifdef __WATCOMC__
#define false FALSE
#define true TRUE
#endif

#ifdef OSX
#define false FALSE
#define true TRUE
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

// The buffer to write the rewritten schema to
char* rewrittenSchemaDDL = NULL;
int buffersize = 0;

char* strrealloccat(char* toAppend) {
	char* temp = rewrittenSchemaDDL;

	if (rewrittenSchemaDDL == NULL) {
		buffersize = strlen(toAppend)+1;
		rewrittenSchemaDDL = (char*) malloc(buffersize);
		rewrittenSchemaDDL[0] = 0;
	} else {
		long s = strlen(rewrittenSchemaDDL)+strlen(toAppend)*2;
		if (buffersize >= s) {
		} else {
			buffersize = s;
			rewrittenSchemaDDL = (char*) malloc(s);
			rewrittenSchemaDDL[0] = 0;
			strcat(rewrittenSchemaDDL, temp);
			free(temp);
		}
	}

	if (toAppend != NULL) strcat(rewrittenSchemaDDL, toAppend);
	return rewrittenSchemaDDL;
}

int WriteFirstColumnRule(Table* table, Column* column, int cols) {
	if (strcmp(column->type, "empty") != 0) {
		cols++;
		char* _template = "CREATE TABLE \"%s\" (\n";
		char* buffer = (char*) malloc(strlen(_template) + strlen(table->name)+1);
		
		sprintf(buffer, _template, table->name);
		strrealloccat(buffer);
		
		free(buffer);
		_template = "\t\"%s\"\t%s";
		buffer = (char*) malloc(strlen(_template) + strlen(column->col) + strlen(column->type)+1);
		
		sprintf(buffer, _template, column->col, column->type);
		strrealloccat(buffer);
		
		return cols;
	}
	return cols;
}

int WriteColumnRule(Table* table, Column* column, int cols) {
	if (strcmp(column->type, "empty") != 0) {
		char* _template = ",\n\t\"%s\"\t%s";
		char* buffer = (char*) malloc(strlen(_template) + strlen(column->col) + strlen(column->type)+1);
		cols++;
		sprintf(buffer, _template, column->col, column->type);
		strrealloccat(buffer);
		return cols;
	}
	return cols;
}

void WriteAlterTableRules(Table* table, Altertable* at) {
	ForeignKey* fk;
	PrimaryKey* pk;

#ifdef bla
	if (at->type == ALTER_FK) {
		fk = at->fk;
		/*
		 * Columns that function as foreign keys
		 */
		if (fk->notnull)
		{
			char* _template = "ALTER TABLE \"%s\" ADD COLUMN \"%s\" INT;\n";
			char* buffer = (char*) malloc(strlen(_template) + strlen(fk->tab) + strlen(fk->col)+1);

			sprintf(buffer, _template, table->name, fk->col);
			strrealloccat(buffer);
		}
		
		/*
		 * triggers that do have to check for null
		 */
		else
		{
			char* _template = "ALTER TABLE \"%s\" ADD COLUMN \"%s\" INT;\n";
			char* buffer = (char*) malloc(strlen(_template) + strlen(fk->tab) + strlen(fk->col)+1);

			sprintf(buffer, _template, table->name, fk->col);
			strrealloccat(buffer);
		}
	}
#endif

	if (at->type == ALTER_PK) {
		pk = at->pk;
		/*
		 * Columns that function as foreign keys
		 */
		char* _template = "ALTER TABLE \"%s\" ADD CONSTRAINT \"%s\" INT PRIMARY KEY;\n";
		char* buffer = (char*) malloc(strlen(_template) + strlen(pk->tab) + strlen(pk->col)+1);

		sprintf(buffer, _template, pk->tab, pk->col);
		strrealloccat(buffer);
	}
}

void WriteTriggerRules(Table* table, Altertable* at) {
	ForeignKey* fk;
	
	if (at->type == ALTER_FK) {
		fk = at->fk;
		/*
		 * triggers that dont have to check for null
		 */
		if (fk->notnull)
		{
			char* _template = "CREATE TRIGGER \"fk_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL)\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			char* buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(table->name)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+1);
			sprintf(buffer, _template, table->name, fk->col, table->name, fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_template = "CREATE TRIGGER \"fk_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL)\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(table->name)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+1);
			sprintf(buffer, _template, table->name, fk->col, table->name, fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_template = "CREATE TRIGGER \"fk_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+strlen(fk->fcol)+strlen(fk->fcol)+strlen(table->name)+strlen(fk->col)+1);
			sprintf(buffer, _template, table->name, fk->col, fk->ftab, fk->col, table->name, fk->col, fk->fcol, fk->fcol, table->name, fk->col);
			strrealloccat(buffer);
		}
		
		/*
		 * triggers that do have to check for null
		 */
		else
		{
			char* _template = "CREATE TRIGGER \"fk_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			char* buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+1);
			sprintf(buffer, _template, table->name, fk->col, table->name, fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_template = "CREATE TRIGGER \"fk_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+1);
			sprintf(buffer, _template, table->name, fk->col, table->name, fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);
			
			_template = "CREATE TRIGGER \"fk_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
				   "                 THEN RAISE(ABORT, '%s violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_template)+strlen(table->name)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+strlen(fk->fcol)+strlen(fk->fcol)+strlen(table->name)+strlen(fk->col)+1);
			sprintf(buffer, _template, table->name, fk->col, fk->ftab, fk->col, table->name, fk->col, fk->fcol, fk->fcol, table->name, fk->col);
			strrealloccat(buffer);
		}
	}
}


void WriteTableSchema() {
    Table *table;
    Column *column;
	ListItem *tabitem, *colitem;
    int i,x,cols,wrotetable;
    /*
     * Iterate over the tables
     */
    tabitem = list_head(schema);
    for (i = 0; tabitem; i++)
    {
		cols = 0;
		wrotetable = 0;
        table = (Table *)list_data(tabitem);

        /*
         * Iterate over columns
         */
        colitem = list_head(table->columns);
        for (x = 0; colitem; x++)
        {
			if (colitem->type == TYPE_COLUMN) {
				column = (Column *)list_data(colitem);
				if (column == NULL)
					goto next_column;
				if (cols > 0) {
					cols = WriteColumnRule(table, column, cols);
				} else {
					cols = WriteFirstColumnRule(table, column, cols);
					if (cols > 0) wrotetable = 1;
				}
			}

			if (colitem->type == TYPE_FOREIGNKEY) {
				column = (Column *)list_data(colitem);
				if (column == NULL)
					goto next_column;
				if (cols > 0) {
					cols = WriteColumnRule(table, column, cols);
				} else {
					cols = WriteFirstColumnRule(table, column, cols);
				}
			}

next_column:
            colitem = list_next(colitem);
        }
		if (wrotetable == 1) strrealloccat("\n);\n");
		
        //list_destroy(table->columns);

        tabitem = list_next(tabitem);
    }
}

void WriteAlterTableSchema() {
    Table *table;
    Altertable *at;
	ListItem *tabitem, *colitem;
    int i,x;
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
        colitem = list_head(table->columns);
        for (x = 0; colitem; x++)
        {
			if (colitem->type == TYPE_ALTERTABLE) {
				at = (Altertable*)list_data(colitem);
				if (at == NULL)
					goto next_fk;
				WriteAlterTableRules(table, at);
			}

next_fk:
            colitem = list_next(colitem);
        }

        tabitem = list_next(tabitem);
    }
}

void WriteTriggerSchema() {
    Table *table;
    Altertable *at;
	ListItem *tabitem, *colitem;
    int i,x;
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
        colitem = list_head(table->columns);
        for (x = 0; colitem; x++)
        {
			if (colitem->type == TYPE_ALTERTABLE) {
				at = (Altertable *)list_data(colitem);
				if (at == NULL)
					goto next_fk;
				WriteTriggerRules(table, at);
			}

next_fk:
            colitem = list_next(colitem);
        }

        tabitem = list_next(tabitem);
    }
}

void CleanupSchema(List* _schema) {
    Table *table;
	ListItem *tabitem;
    int i;
    /*
     * Iterate over the tables
     */
    tabitem = list_head(_schema);
    for (i = 0; tabitem; i++)
    {
        table = (Table *)list_data(tabitem);
        list_destroy(table->columns);
        tabitem = list_next(tabitem);
    }
}

char* rewriteSchemaOfDDL(char* sql_ddl) {
	bool haveItems = false;
#ifdef BUILD_LIBRARY
	List *foreign_keys;
#endif
#ifndef BUILD_LIBRARY
	char* sql_ddl = NULL;
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
	
	WriteTableSchema();
	WriteAlterTableSchema();
	WriteTriggerSchema();

	CleanupSchema(schema);

    list_destroy(schema);
    MemPoolDestroy(&mempool);

	return rewrittenSchemaDDL;
}

void cleanupSchema(List* schema) {

}

#ifndef BUILD_LIBRARY
int
main (int argc, char **argv)
#endif

#ifdef BUILD_LIBRARY
List* getForeignKeyList(char* _table, char* sql_ddl)
#endif
{
	bool haveItems = false;
	ListItem *tabitem, *colitem;
    Table *table;
#ifdef BUILD_LIBRARY
	List *foreign_keys;
#endif
#ifndef BUILD_LIBRARY
	char* sql_ddl = NULL;
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
			int x;
			ForeignKey *fk;
			foreign_keys = list_new();
			
			colitem = list_head(table->columns);
			for (x = 0; colitem; x++)
			{
				if (colitem->type == TYPE_ALTERTABLE) {
					ForeignKey* copy_of_fk = (ForeignKey*) malloc(sizeof(ForeignKey));
					fk = (ForeignKey *)list_data(colitem);
					if (fk == NULL)
						goto fk_next;
					
					copy_of_fk->col = strdup(fk->col);
					copy_of_fk->ftab = strdup(fk->ftab);
					copy_of_fk->fcol = strdup(fk->fcol);
					
					list_append(foreign_keys, copy_of_fk, TYPE_FOREIGNKEY);
					haveItems = true;
				}					
fk_next:					
				colitem = list_next(colitem);
			}
		}

        list_destroy(table->columns);
table_next:		
		tabitem = list_next(tabitem);
	}
	
    list_destroy(schema);
    MemPoolDestroy(&mempool);
	if (haveItems) return foreign_keys;
	else return NULL;
#endif

#ifndef BUILD_LIBRARY

    printf("BEGIN TRANSACTION;\n\n");

	WriteTableSchema();
	WriteAlterTableSchema();
	WriteTriggerSchema();

	CleanupSchema(schema);

    list_destroy(schema);
    MemPoolDestroy(&mempool);

	printf(rewrittenSchemaDDL);

    printf("COMMIT;\n");

    return 0;
#endif // not BUILD_LIBRARY
}
