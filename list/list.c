/*
 *2013-3-19
 *author: YHL
 *file: list.c
 */
#include "list.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

void list_init(list_t *list,void (*destroy)(void *),int (*eq)(const void *,const void *))
{
	list->head=NULL;
	list->tail=NULL;
	list->size=0;
	list->destroy=destroy;
	list->eq=eq;
}

int list_insert(list_t *list,listelem_t *elem,const void *data)
{
	listelem_t *new_listelem;
	new_listelem=(listelem_t *)malloc(sizeof(listelem_t));
	if(new_listelem==NULL)
		return 1;
	new_listelem->data=(void *)data;
	new_listelem->updatetime=clock();

	if(elem==NULL)//insert after head
	{
		if(list_size(list)==0)
			list->tail=new_listelem;
		new_listelem->next=list->head;
		list->head=new_listelem;
	}
	else//insert after elem
	{
		if(list_size(list)==0)
			list->tail=new_listelem;
		new_listelem->next=elem->next;
		elem->next=new_listelem;
	}
	list->size++;
	return 0;
}

int list_remove(list_t *list,listelem_t *elem,void **data)
{
	if(list_size(list)==0)
		return 1;
	listelem_t *old_elem;
	if(elem==NULL)//remove after head
	{
		if(list_size(list)==1)
			list->tail=NULL;
		*data=list->head->data;
		old_elem=list->head;
		list->head=list->head->next;
	}	
	else//remove elem->next 
	{
		if(list_size(list)==1)
			list->tail=NULL;
		*data=elem->next->data;
		old_elem=elem->next;
		elem=elem->next->next;
	}
	free(old_elem);
	list->size--;
	return 0;
}

void list_destroy(list_t *list)
{
	void *data;
	
	while(list_size(list)>0)
	{
		if(list_remove(list,NULL,&data)==0)
			list->destroy(data);
	}
	memset(list,0,sizeof(list));
}

int list_is_member(const list_t *list,void *data)
{
	if(list_size(list)==0)
		return 0;
	listelem_t *p=list->head;
	while(p!=NULL)
	{
		if(eq(p->data,data))
			return 1;
		p=p->next;
	}
	return 0;
}
void list_show(list_t *list)
{
	if(list->size==0)
	{
		printf("The list is empty\n");
		return ;
	}
	printf("Head -------> Tail\n");
	listelem_t *p;
	p=list->head;
	while(p != NULL)
	{
		printf("%d\t",*(int*)p->data);
		p=p->next;
	}
	printf("\n");
}
