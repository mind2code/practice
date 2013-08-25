/*
 *2013-3-18
 *author: YHL
 *file:stack.h
 */
#ifndef STACK_H
#define STACK_H

typedef struct stackelem
{
	void * data;
	struct stackelem* next;
}stackelem_t;

typedef struct stack
{
	int size;
	stackelem_t *top;
	stackelem_t *bottom;
	int (*eq)(const void *key1,const void *key2);
	void (*destroy)(void *data);
}stack_t;

//initiate the stack
void stack_init(stack_t *stack,int (*eq)(const void *data1,const void *data2),void (*destroy)(void *data));
//destroy the stack
void stack_destroy(stack_t *stack);
//remove an element of the stack,success return 1
int stack_pop(stack_t* stack,void **ptrdata);
//remove all elements of the stack,let th stack like after stack_init().success return 1
int stack_popall(stack_t* stack);
//success return 1
int stack_push(stack_t* stack,const void *data);
//read on top
int stack_read(stack_t* stack,void **data);

#endif
