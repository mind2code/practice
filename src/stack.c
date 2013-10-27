#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmp_d(const void *key1,const void *key2, size_t size)
{
	return memcmp(key1,key2,size);
}
void free_d(void *data)
{
	free(data);
}

void stack_init(stack_t* stack,cmp_t *cmp, free_t *free)
{
	stack->size=0;
	stack->top=NULL;
	stack->bottom=NULL;
	if(cmp != NULL)
		stack->cmp = cmp;
	else
		stack->cmp = cmp_d;
	if(free != NULL)
		stack->free = free;
	else
		stack->free = free_d;
}

void stack_destroy(stack_t* stack)
{
	stack_elem_t *top=stack->top;
	while(stack->size)
	{
		stack->top=top->next;
		stack->size--;
		stack->free(top->data);
		free(top);
		top=stack->top;	
	}
	stack->top = stack->bottom = NULL;
}

void *stack_pop(stack_t* stack)
{
	if(stack->size==0)
		return NULL;

	stack_elem_t *del=stack->top;
	void * data = del->data;
	stack->top=stack->top->next;
	stack->size--;
	if(stack->size==0)
		stack->bottom=NULL;
	free(del);	
	return data;
}

int stack_push(stack_t* stack,const void *data)
{
	stack_elem_t *elem;
	elem=(stack_elem_t *)malloc(sizeof(stack_elem_t));
	if(elem==NULL)
		return 0;
	elem->data=(void *)data;
	if(stack->size==0)
		stack->bottom=elem;
	elem->next=stack->top;
	stack->top=elem;
	stack->size++;
	return 1;
}

void stack_show(stack_t *stack, show_t *show)
{
	if(stack->size==0)
	{
		printf("The stack is empty\n");
		return ;
	}
	stack_elem_t* elem=stack->top;
	while(elem!=NULL)
	{
		show(elem->data);
		elem=elem->next;
	}
}

int stack_read(stack_t* stack,void **data)
{
	if(stack->size==0)
		return 0;
	data=&(stack->top->data);
	return 1;
}
