#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void stack_init(stack_t* stack,int (*eq)(const void *data1,const void *data2),void (*destroy)(void *data))
{
	stack->size=0;
	stack->top=NULL;
	stack->bottom=NULL;
	stack->eq=eq;
	stack->destroy=destroy;
}

void stack_destroy(stack_t* stack)
{
	stackelem_t *top=stack->top;
	while(stack->size)
	{
		stack->top=top->next;
		stack->size--;
		stack->destroy(top->data);
		free(top);
		top=stack->top;	
	}
	memset(stack,0,sizeof(stack_t));
}

int stack_pop(stack_t* stack,void **ptrdata)
{
	if(stack->size==0)
		return 0;
	stackelem_t *del=stack->top;
	stack->top=stack->top->next;
	stack->size--;
	ptrdata=&del->data;
	if(stack->size==0)
		stack->bottom=NULL;	
	return 1;
}

int stack_push(stack_t* stack,const void *data)
{
	stackelem_t *elem;
	elem=(stackelem_t *)malloc(sizeof(stackelem_t));
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

void stack_show(stack_t *stack)
{
	if(stack->size==0)
	{
		printf("The stack is empty\n");
		return ;
	}
	stackelem_t* elem=stack->top;
	while(elem!=NULL)
	{
		printf("%d\t",*(int*)elem->data);
		elem=elem->next;
	}
	printf("\n");
}

int stack_read(stack_t* stack,void **data)
{
	if(stack->size==0)
		return 0;
	data=&(stack->top->data);
	return 1;
}
