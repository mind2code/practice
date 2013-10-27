/*
 * update: 2013-10-27
 * time: 2013-3-18
 * author: YHL
 * file:stack.h
 */
#ifndef STACK_H
#define STACK_H
#include <stddef.h>

typedef int cmp_t(const void *key1, const void *key2, size_t size);
typedef void free_t(void *data);
typedef void show_t(void *data);

/*** data define ***/
typedef struct stack_elem
{
	void * data;
	struct stack_elem* next;
}stack_elem_t;

typedef struct stack
{
	int size;
	stack_elem_t *top;
	stack_elem_t *bottom;
	cmp_t *cmp;
	free_t *free;
}stack_t;
/*** data define end ***/

/*** function define ***/
void stack_init(stack_t *stack,cmp_t *cmp,free_t *free);

void stack_destroy(stack_t *stack);

void * stack_pop(stack_t* stack);	//remove an element of the stack,success return 1

int stack_popall(stack_t* stack);		//success return 1

int stack_push(stack_t* stack,const void *data);//success return 1

int stack_read(stack_t* stack,void **data);

void stack_show(stack_t* stack,show_t *show);
/*** function define end ***/

#endif
