#ifndef FK_SQL_H
#define FK_SQL_H

#include "list.h"


typedef struct foreign {
    char *tab;
    char *col;
} Foreign;


typedef enum {
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
    char *col;
    char *ftab;
    char *fcol;

    unsigned char notnull;
} ForeignKey;


typedef struct table
{
    char *name;

    List *fks;
} Table;

List* getForeignKeyList(char* _table);

#endif
