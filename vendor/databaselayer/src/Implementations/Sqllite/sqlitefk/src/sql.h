#ifndef FK_SQL_H
#define FK_SQL_H

#include "list.h"


typedef struct foreign {
    char *tab;
    char *col;
} Foreign;


typedef enum {
CONSTRAINT_PRIMARYKEY,
CONSTRAINT_FOREIGNKEY,
CONSTRAINT_NOTNULL
} ConstraintType;


typedef struct constraint
{
    ConstraintType type;

    Foreign foreign;
} Constraint;

typedef struct foreignkey
{
    char *tab;
    char *col;
    char *ftab;
    char *fcol;

    unsigned char notnull;
} ForeignKey;

typedef struct primarykey
{
    char *tab;
    char *col;
    char *type;

    unsigned char notnull;
} PrimaryKey;

#define ALTER_PK 1
#define ALTER_FK 2

typedef struct altertable
{
	int type;
	ForeignKey* fk;
	PrimaryKey* pk;
} Altertable;

typedef struct column
{
    char *col;
    char *type;
	char *_default;
    unsigned char notnull;
} Column;


typedef struct table
{
    char *name;

    List *columns;
} Table;

#ifdef __cplusplus
extern "C" {
#endif

List* getForeignKeyList(char* _table, char* sql_ddl);

char* rewriteSchemaOfDDL(char* sql_ddl);

#ifdef __cplusplus
}
#endif

#endif
