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

#ifdef __MINGW32__
#define false FALSE
#define true TRUE
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
int stringsize = 0;
int allocationsize = 0;

char* strrealloccat(char* toAppend) {
	char* temp = rewrittenSchemaDDL;

	if (temp == NULL) {
		buffersize = strlen(toAppend)+1;
		rewrittenSchemaDDL = (char*) malloc(buffersize);
		rewrittenSchemaDDL[0] = 0;
		stringsize = buffersize;
	} else {
		long s = stringsize+strlen(toAppend)+1;
		if (buffersize >= s) {
            stringsize = s;
		} else {
            if (buffersize > 1000) allocationsize = 200;
            if (buffersize > 10000) allocationsize = 2000;
            if (buffersize > 100000) allocationsize = 20000;

			buffersize = s;

			if (allocationsize > 1) {
                rewrittenSchemaDDL = (char*) malloc(s+allocationsize);
                buffersize += allocationsize;
			} else {
                rewrittenSchemaDDL = (char*) malloc(s);
			}

            stringsize = s;
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
		char* templ = "CREATE TABLE \"%s\" (\n";
		char* buffer = (char*) malloc(strlen(templ) + strlen(table->name)+1);
		cols++;

		sprintf(buffer, templ, table->name);
		strrealloccat(buffer);

		free(buffer);
		templ = "\t\"%s\"\t%s";
		buffer = (char*) malloc(strlen(templ) + strlen(column->col) + strlen(column->type)+1);

		sprintf(buffer, templ, column->col, column->type);
		strrealloccat(buffer);
		free(buffer);

		return cols;
	}
	return cols;
}

int WriteColumnRule(Table* table, Column* column, int cols) {
	if (strcmp(column->type, "empty") != 0) {
		char* _templ = ",\n\t\"%s\"\t%s";
		char* buffer = (char*) malloc(strlen(_templ) + strlen(column->col) + strlen(column->type)+1);
		cols++;
		sprintf(buffer, _templ, column->col, column->type);
		strrealloccat(buffer);
		free(buffer);
		return cols;
	}
	return cols;
}

int WriteFirstPrimaryColumnRule(Table* table, PrimaryKey* column, int cols) {
	if (strcmp(column->type, "empty") != 0) {
		char* _templ = "\nCREATE TABLE \"%s\" (\n";
		char* buffer = (char*) malloc(strlen(_templ) + strlen(table->name)+1);
		cols++;

		sprintf(buffer, _templ, table->name);
		strrealloccat(buffer);

		free(buffer);
		_templ = "\t\"%s\"\t%s PRIMARY KEY";
		buffer = (char*) malloc(
		strlen(_templ) +
		strlen(column->col) +
		strlen(column->type)+1);

		sprintf(buffer, _templ, column->col, column->type);
		strrealloccat(buffer);
		free(buffer);

		return cols;
	}
	return cols;
}

int WritePrimaryColumnRule(Table* table, PrimaryKey* column, int cols) {
	if (strcmp(column->type, "empty") != 0) {
		char* _templ = ",\n\t\"%s\"\t%s PRIMARY KEY";
		char* buffer = (char*) malloc(strlen(_templ) + strlen(column->col) + strlen(column->type)+1);
		cols++;
		sprintf(buffer, _templ, column->col, column->type);
		strrealloccat(buffer);
		free(buffer);
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
			char* _templ = "ALTER TABLE \"%s\" ADD COLUMN \"%s\" INT;\n";
			char* buffer = (char*) malloc(strlen(_templ) + strlen(fk->tab) + strlen(fk->col)+1);

			sprintf(buffer, _templ, table->name, fk->col);
			strrealloccat(buffer);
		}

		/*
		 * triggers that do have to check for null
		 */
		else
		{
			char* _templ = "ALTER TABLE \"%s\" ADD COLUMN \"%s\" INT;\n";
			char* buffer = (char*) malloc(strlen(_templ) + strlen(fk->tab) + strlen(fk->col)+1);

			sprintf(buffer, _templ, table->name, fk->col);
			strrealloccat(buffer);
		}
	}

	if (at->type == ALTER_PK) {
		pk = at->pk;
		/*
		 * Columns that function as foreign keys
		 */
		char* _templ = "ALTER TABLE \"%s\" ADD CONSTRAINT \"%s\" INT PRIMARY KEY;\n";
		char* buffer = (char*) malloc(strlen(_templ) + strlen(pk->tab) + strlen(pk->col)+1);

		sprintf(buffer, _templ, pk->tab, pk->col);
		strrealloccat(buffer);
	}
#endif
}

void WriteForeignKeyMetaRules(Table* table, Altertable* at) {
	ForeignKey* fk;

	if (at->type == ALTER_FK) {
		char* _templ = NULL;
		char* buffer = NULL;

		fk = at->fk;

		_templ = "INSERT INTO \"lbDMF_ForeignKeys\" (\"PKTable\", \"PKColumn\", \"FKTable\", \"FKColumn\") VALUES ('%s', '%s', '%s', '%s');\n";
		buffer = (char*) malloc(strlen(_templ)+
							strlen(fk->ftab)+
							strlen(fk->fcol)+
							strlen(fk->tab)+
							strlen(fk->col)+1);
		sprintf(buffer, _templ, fk->ftab, fk->fcol, fk->tab, fk->col);
		strrealloccat(buffer);
		free(buffer);
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
			char* _templ = "CREATE TRIGGER \"fk_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL) AND NOT new.%s IS NULL\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_ins violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			char* buffer = (char*) malloc(	strlen(_templ)+
							strlen(fk->tab)+strlen(fk->col)+strlen(fk->tab)+
							strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+
							strlen(fk->tab)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+100);
			if (buffer == NULL) {
				printf("Fatal: Memory allocation failed!\n");
				exit(1);
			}
			sprintf(buffer, _templ, fk->tab, fk->col, fk->tab,
						fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col,
						fk->tab, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_templ = "CREATE TRIGGER \"fk_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL) AND NOT new.%s IS NULL\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_upd violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);

			buffer = (char*) malloc(	strlen(_templ)+
							strlen(fk->tab)+strlen(fk->col)+strlen(fk->tab)+
							strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+strlen(fk->col)+
							strlen(fk->tab)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+100);
			if (buffer == NULL) {
				printf("Fatal: Memory allocation failed!\n");
				exit(1);
			}
			sprintf(buffer, _templ, fk->tab, fk->col, fk->tab,
						fk->fcol, fk->ftab, fk->fcol, fk->col, fk->col,
						fk->tab, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_templ = "CREATE TRIGGER \"fk_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_del violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_templ)+
						strlen(fk->tab)+strlen(fk->col)+strlen(fk->ftab)+
						strlen(fk->col)+strlen(fk->tab)+strlen(fk->col)+strlen(fk->fcol)+
						strlen(fk->tab)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+100);
			if (buffer == NULL) {
				printf("Fatal: Memory allocation failed!\n");
				exit(1);
			}
			sprintf(buffer, _templ,
						fk->tab, fk->col, fk->ftab,
						fk->col, fk->tab, fk->col, fk->fcol,
						fk->tab, fk->col, table->name, fk->col);
			strrealloccat(buffer);
			free(buffer);
		}

		/*
		 * triggers that do have to check for null
		 */
		else
		{
			char* _templ = "CREATE TRIGGER \"fk_nullable_%s_%s_ins\" BEFORE INSERT ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_ins violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			char* buffer = (char*) malloc(strlen(_templ)+
					  strlen(table->name)+strlen(fk->col)+strlen(table->name)+
					  strlen(fk->col)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+
					  strlen(fk->tab)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+100);
			if (buffer == NULL) {
				printf("Fatal: Memory allocation failed!\n");
				exit(1);
			}
			sprintf(buffer, _templ,
					table->name, fk->col, table->name,
					fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col,
					fk->tab, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_templ = "CREATE TRIGGER \"fk_nullable_%s_%s_upd\" BEFORE UPDATE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((new.%s IS NOT NULL) AND ((SELECT %s FROM %s WHERE %s = new.%s) IS NULL))\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_upd violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_templ)+
					strlen(table->name)+strlen(fk->col)+strlen(table->name)+
					strlen(fk->col)+strlen(fk->fcol)+strlen(fk->ftab)+strlen(fk->fcol)+strlen(fk->col)+
					strlen(fk->tab)+strlen(fk->col)+strlen(fk->ftab)+strlen(fk->fcol)+100);

			sprintf(buffer, _templ,
					table->name, fk->col, table->name,
					fk->col, fk->fcol, fk->ftab, fk->fcol, fk->col,
					fk->col, fk->col, fk->ftab, fk->fcol);
			strrealloccat(buffer);

			_templ = "CREATE TRIGGER \"fk_nullable_%s_%s_del\" BEFORE DELETE ON %s FOR EACH ROW\n"
				   "BEGIN\n"
				   "    SELECT CASE WHEN ((SELECT %s FROM %s WHERE %s = old.%s) IS NOT NULL)\n"
				   "                 THEN RAISE(ABORT, 'fk_%s_%s_del violates foreign key %s(%s)')\n"
				   "    END;\n"
				   "END;\n";
			free(buffer);
			buffer = (char*) malloc(strlen(_templ)+
						strlen(table->name)+strlen(fk->col)+strlen(fk->ftab)+
						strlen(fk->col)+strlen(table->name)+strlen(fk->col)+strlen(fk->fcol)+
						strlen(fk->tab)+strlen(fk->col)+strlen(table->name)+strlen(fk->col)+100);
			sprintf(buffer, _templ,
					table->name, fk->col, fk->ftab,
					fk->col, table->name, fk->col, fk->fcol,
					fk->tab, fk->col, table->name, fk->col);
			strrealloccat(buffer);
			free(buffer);
		}
	}
}


void WriteTableSchema() {
    Table *table;
    Column *column;
    PrimaryKey *primarykey;
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

			if (colitem->type == TYPE_PRIMARYKEY) {
				primarykey = (PrimaryKey *)list_data(colitem);
				if (primarykey == NULL)
					goto next_column;
				if (cols > 0) {
					cols = WritePrimaryColumnRule(table, primarykey, cols);
				} else {
					cols = WriteFirstPrimaryColumnRule(table, primarykey, cols);
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
					if (cols > 0) wrotetable = 1;
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
				WriteForeignKeyMetaRules(table, at);
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

	if (rewrittenSchemaDDL) {
		free(rewrittenSchemaDDL);
		rewrittenSchemaDDL = NULL;
	}

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
	//WriteAlterTableSchema();
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
