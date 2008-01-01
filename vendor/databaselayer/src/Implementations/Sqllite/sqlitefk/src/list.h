#ifndef LIST_H
#define LIST_H

typedef struct list_element
{
    void *data;
    struct list_element *next;
} ListItem;

typedef struct list 
{
    int len;
    ListItem *head;
} List;

extern List *list_new(void);
extern void list_destroy(List *list);

extern int list_append(List *list, void *data);
extern ListItem *list_pop(List *list);

extern ListItem *list_head(List *list);
extern ListItem *list_tail(List *list);


extern ListItem *list_next(ListItem *item);

extern void *list_data(ListItem *item);

#endif
