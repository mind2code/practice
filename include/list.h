/*
 *2013-3-15 
 *author: YHL
 *file: list.h
 *update: 2013-10-27 00:00
 *description: a node has two link: next, pre
 */
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stddef.h>

typedef int cmp_f(const void *key1, const void *key2, size_t size);	//return 0 means eq, default is memcmp
typedef void free_f(void *data);	//default is free
typedef int expire_f(void *data);	//return 1 means expired, default never expired, that is to say, return 0

/*** data define ***/
typedef struct list_elem
{
	void *data;
	struct list_elem* next;
	struct list_elem* pre;
}list_elem_t;

typedef struct list
{
	list_elem_t *head;
	list_elem_t *tail;
	int size;
	cmp_f * cmp;
	free_f * free;
	expire_f * expire;
}list_t;
/*** data define end ***/

/*** function define ***/
void list_init(list_t *list, free_f *free, cmp_f *cmp, expire_f *expire);//if free,cmp,expire is NULL, use the default

void list_destroy(list_t *list);

int list_insert(list_t *list, const void *data);	//0,success;

int list_remove(list_t *list, const void *data, size_t size);	//0,success; -1,nothing in list; -2,no such thing

void* list_is_member(const list_t * list,void *data, size_t size);	//return ptr point to the data of list, or return NULL

void list_show(list_t* list, void (*show)(void *data));

int list_size(const list_t* list);
/*** function define end ***/

#endif
