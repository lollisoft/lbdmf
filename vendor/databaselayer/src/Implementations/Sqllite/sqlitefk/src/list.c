#include <stdlib.h>
#include <string.h>
#include "list.h"

List *
list_new (void)
{
    List *list = (List *) malloc(sizeof(List));
    list->len = 0;
    list->head = NULL;
#ifdef DEBUG
    printf("new list <%p>\n", list);
#endif
    return list;
}

void printDeleteInfo(ListItem* item) {
	char* itemtype = "";
	switch (item->type) {
		case TYPE_COLUMN:
			itemtype = "TYPE_COLUMN";
			break;
		case TYPE_FOREIGNKEY:
			itemtype = "TYPE_FOREIGNKEY";
			break;
		case TYPE_PRIMARYKEY:
			itemtype = "TYPE_PRIMARYKEY";
			break;
		case TYPE_TABLE:
			itemtype = "TYPE_TABLE";
			break;
		case TYPE_ALTERTABLES:
			itemtype = "TYPE_ALTERTABLES";
			break;
		case TYPE_ALTERTABLE:
			itemtype = "TYPE_ALTERTABLE";
			break;
		case TYPE_COLUMNS:
			itemtype = "TYPE_COLUMNS";
			break;
	}
#ifdef DEBUG
	printf("Destroy listitem of type %s.\n", itemtype);
#endif
}

void printAppendInfo(ListItem* item) {
	char* itemtype = "";
	switch (item->type) {
		case TYPE_COLUMN:
			itemtype = "TYPE_COLUMN";
			break;
		case TYPE_FOREIGNKEY:
			itemtype = "TYPE_FOREIGNKEY";
			break;
		case TYPE_PRIMARYKEY:
			itemtype = "TYPE_PRIMARYKEY";
			break;
		case TYPE_TABLE:
			itemtype = "TYPE_TABLE";
			break;
		case TYPE_ALTERTABLES:
			itemtype = "TYPE_ALTERTABLES";
			break;
		case TYPE_ALTERTABLE:
			itemtype = "TYPE_ALTERTABLE";
			break;
		case TYPE_COLUMNS:
			itemtype = "TYPE_COLUMNS";
			break;
	}
#ifdef DEBUG
	printf("Append listitem of type %s (item = %p, data = %p, size = %d).\n", itemtype, item, item->data, sizeof(item));
#endif
}

void
list_destroy (List *list)
{
    ListItem *item, *next;

    item = list->head;
    while (item != NULL)
    {
        /* free data */
#ifdef DEBUG
		printDeleteInfo(item);
		printf("Free up the data in item.\n");
#endif
        free(item->data);

        /* save the next pointer */
        next = item->next;
        /* free item */
#ifdef DEBUG
		printf("Free up the item.\n");
#endif
        free(item);

        /* move on to next */
        item = next;
    }
#ifdef DEBUG
	printf("Free up the list.\n");
#endif
    free(list);
}


int
list_append(List *list, void *data, int _type)
{
    ListItem *tail;
    int i;
    ListItem *_new = (ListItem *) malloc(sizeof(ListItem));

    if (_new == NULL)
        return -1;

    _new->next = NULL;
    _new->data = data;
    _new->type = _type;

#ifdef DEBUG
	printAppendInfo(_new);
#endif

    if (list->len == 0)
    {
        list->head = _new;
        i = 0;
    }
    else
    {
        tail = list->head;
        for (i = 1; tail->next; i++)
            tail = tail->next;

        tail->next = _new;
    }

    list->len = i + 1;
#ifdef DEBUG
    printf("appended '%s' as item #%d to list <%p>\n", data, i, list);
#endif
    return i;
}

ListItem *
list_pop (List *list)
{
    ListItem *item;

    /* empty list */
    if (list->len == 0)
    {
        return NULL;
    }
    /* list with one entry */
    else if (list->len == 1)
    {
        item = list->head;
        list->head = NULL;
    }
    else
    {
        ListItem *prev;

        item = list_tail(list);
        prev = list->head;
        while (prev->next != item)
            prev = prev->next;
        prev->next = NULL;
    }
    (list->len)--;
    return item;
}


ListItem *
list_head (List *list)
{
    return list->head;
}


ListItem *
list_tail (List *list)
{
    ListItem *item;

    if (list->head == NULL)
        return NULL;

    item = list->head;
    while (item->next)
        item = item->next;

    return item;
}


ListItem *
list_next (ListItem *item)
{
    return item->next;
}


void *
list_data (ListItem *item)
{
    return item->data;
}
