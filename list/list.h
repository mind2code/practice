/*
 *2013-3-15 
 *author: YHL
 *file: liat.h
 *PS: updatetime is not used
 */
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct listelem
{
	void *data;
	struct listelem* next;
	long updatetime;
}listelem_t;

typedef struct list
{
	listelem_t *head;
	listelem_t *tail;
	int size;
	int (*eq)(const void *key1,const void *key2);
	void (*destroy)(void *data);
}list_t;

void list_init(list_t *list,void (*destroy)(void *),int (*eq)(const void *,const void *));
void list_destroy(list_t *list);
int list_insert(list_t *list,listelem_t *elem,const void *data);
int list_remove(list_t *list,listelem_t *elem,void **data);
int list_is_member(const list_t * list,void *data);

#define list_size(list) ((list)->size)

#endif
