#ifndef LIST_H
#define LIST_H

#define TYPE_COLUMN 1
#define TYPE_FOREIGNKEY 2
#define TYPE_PRIMARYKEY 3
#define TYPE_TABLE 4
#define TYPE_ALTERTABLES 5
#define TYPE_ALTERTABLE 6
#define TYPE_COLUMNS 7


typedef struct list_element
{
    void *data;
	int type;
    struct list_element *next;
} ListItem;

typedef struct list 
{
    int len;
    ListItem *head;
} List;

extern List *list_new(void);
extern void list_destroy(List *list);

extern int list_append(List *list, void *data, int _type);
extern ListItem *list_pop(List *list);

extern ListItem *list_head(List *list);
extern ListItem *list_tail(List *list);


extern ListItem *list_next(ListItem *item);

extern void *list_data(ListItem *item);

#endif
