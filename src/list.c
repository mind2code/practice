/*
 *2013-3-19
 *author: YHL
 *file: list.c
 */
#include "list.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

int cmp_d(const void *key1, const void *key2, size_t size)
{
	return memcmp(key1,key2,size);
}
void free_d(void *data)
{
	free(data);
}
int expire_d(void *data)
{
	return 0;
}

int list_size(const list_t* list)
{
	return list->size;
}

void list_init(list_t *list,free_t *free,cmp_t *cmp,expire_t *expire)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	if(free == NULL)
		list->free = free_d;
	else
		list->free = free;
	if(cmp == NULL)
		list->cmp = cmp_d;
	else
		list->cmp = cmp;
	if(expire == NULL)
		list->expire = expire_d;
	else
		list->expire = expire;
}

int list_insert(list_t *list, const void *data)
{
	list_elem_t *new_listelem;
	new_listelem=(list_elem_t *)malloc(sizeof(list_elem_t));
	if(new_listelem==NULL)
		return 1;
	
	new_listelem->data=(void *)data;

	if(list->head == NULL)
	{
		list->tail = new_listelem;
	}
	else
	{
		list->head->pre = new_listelem;
	}
	new_listelem->next = list->head;
	list->head = new_listelem;
	new_listelem->pre = NULL;
	list->size++;
	return 0;
}

int list_remove(list_t *list,const void *data, size_t size)
{
	if(list_size(list)==0)
		return -1;

	list_elem_t *cur = list->head;
	while(cur!=NULL && list->cmp(cur->data,data,size))
	{
		cur = cur->next;
	}
	if(cur == NULL)
		return -2;	//no such thing

	//key point, be careful
	if(list->head != cur)
		cur->pre->next = cur->next;
	else
		list->head = cur->next;
	if(list->tail != cur)
		cur->next->pre = cur->pre;
	else
		list->tail = cur->pre;

	//free
	list->free(cur->data);
	free(cur);
	list->size--;
	return 0;
}

void list_destroy(list_t *list)
{
	list_elem_t *cur = list->head;
	list_elem_t *p = NULL;
	
	while(list_size(list)>0)
	{
		list->free(cur->data);
		p = cur;
		cur = cur->next;//when the last one, cur->pre is unavailable
		free(p);
		list->size--;
	}
	list->head = list->tail = NULL;
}

void* list_is_member(const list_t *list,void *data, size_t size)
{
	if(list_size(list)==0)
		return NULL;

	list_elem_t *p=list->head;

	while(p != NULL)
	{
		if(!list->cmp(p->data,data,size))
			return p->data;
		p=p->next;
	}
	return NULL;
}
void list_show(list_t *list,void (*show)(void *data))
{
	if(list->size==0)
	{
		printf("The list is empty\n");
		return ;
	}
	printf("list printed:Head --> Tail\n");
	list_elem_t *p;
	p=list->head;
	while(p != NULL)
	{
		show(p->data);
		p=p->next;
	}
}
