#include "set.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int set_init(set_t *set,int (*eq)(const void *,const void *),void (*destroy)(void *))
{
	set->size=0;
	set->head=NULL;
	set->eq=eq;
	set->destroy=destroy;
}

void set_destroy(set_t *set)
{
	set_removeall(set);
	memset(set,0,sizeof(set));
}

int set_insert(set_t *set,const void *data)
{
	set_update(set);
	if(set_is_member(set,data))
		return 1;

	setelem_t *new_elem;
	new_elem=(setelem_t*)malloc(sizeof(setelem_t));
	if(new_elem==NULL)
		return 1;
	new_elem->data=(void *)data;
	time(&(new_elem->updatetime));

	if(set_size(set)==0)
		set->tail=new_elem;
	new_elem->next=set->head;
	set->head=new_elem;
	set->size++;	
	return 0;
}

int set_remove(set_t *set,void *data)
{
	if(set_size(set)==0)
		return 1;

	setelem_t *pre;
	setelem_t *del;
	pre=del=set->head;
	while(del != NULL)
	{
		if(!eq(del->data,data))
		{
			pre=del;
			del=del->next;
			continue;
		}
		if(set_size(set)==1)
		{
			set->tail=NULL;
			set->head=NULL;
		}
		else
			if(del==set->head)
				set->head=del->next;
			else
				pre->next=del->next;
		set->size--;
		set->destroy(del->data);
		free(del);
		return 0;
	}

	return 1;
}

int set_removeall(set_t *set)
{
	if(set_size(set)==0)
		return 0;

	setelem_t *p=set->head;
	while(p != NULL)
	{
		set->head=p->next;
		set->destroy(p->data);
		free(p);
		p=set->head;	
	}
	set->tail=NULL;
	return 0;
}

int set_is_member(set_t* set,const void *key)
{
	set_update(set);
	if(0==set_size(set))
		return 0;

	setelem_t* p=set->head;
	while(p != NULL)
	{
		if(eq(p->data,key))
			return 1;
		p=p->next;
	}

	return 0;
}

int set_is_equal(set_t *set1,set_t *set2)
{
	set_update(set1);
	set_update(set2);

	if(set_size(set1) != set_size(set2))
		return 0;
	if(set_is_subset(set1,set2))
		return 1;
}

int set_is_subset(set_t* set1,set_t* set2)
{
	set_update(set1);
	set_update(set2);

	if(set_size(set1)==0)
		return 1;
	if(set_size(set1) > set_size(set2))
		return 0;

	setelem_t *set1elem=set1->head;
	setelem_t *set2elem;
	while(set1elem != NULL)
	{
		if(!set_is_member(set2,set1elem->data))
			return 0;
		set1elem=set1elem->next;	
	}
	return 1;
}
//注意！如果操作失败，则set会被销毁。
int set_union(set_t *set,set_t *set1,set_t *set2)
{
	set_update(set1);
	set_update(set2);

	setelem_t *p=set1->head;
	while(p != NULL)//insert set1 into set
	{	
		if(set_insert(set,p->data)==0)
			p=p->next;
		else
		{
			set_destroy(set);
			return 1;
		}
	}
	p=set2->head;
	while(p != NULL)
	{
		if(!set_is_member(set1,p->data))
			if(set_insert(set,p->data)!=0)
			{
				set_destroy(set);
				return 1;
			}
		p=p->next;		
	}
	return 0;

}

int set_intersection(set_t* set,set_t* set1,set_t* set2)
{
	set_update(set1);
	set_update(set2);

	setelem_t * p=set1->head;
	while(p != NULL)
	{
		if(set_is_member(set2,p->data))
			if(set_insert(set,p->data)!=0)
			{
				set_destroy(set);
				return 1;
			}
		p=p->next;
	}
	return 0;
}

int set_difference(set_t *set,set_t *set1,set_t * set2)
{
	set_update(set1);
	set_update(set2);

	setelem_t * p=set1->head;
	while(p != NULL)
	{
		if(!set_is_member(set2,p->data))
			if(set_insert(set,p->data)!=0)
			{
				set_destroy(set);
				return 1;
			}
		p=p->next;
	}
	return 0;
}

void set_update(set_t *set)
{
	setelem_t *p=set->head;
	time_t nowtime;
	time(&nowtime);
	while(p != NULL)
	{
		if((nowtime - p->updatetime) > MAXTIME)
			set_remove(set,p->data);
		p=p->next;
	}
}

void set_show(set_t *set)
{
	set_update(set);
	if(set->head==NULL)
	{
		printf("The set is empty\n");
		return ;
	}
	setelem_t * p;
	p=set->head;
	while(p!=NULL)
	{
		printf("%d\t",*(int *)(p->data));
		p=p->next;
	}
	printf("\n\n");
}
