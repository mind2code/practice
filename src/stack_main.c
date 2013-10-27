#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void show(void* data);

int main()
{
	stack_t stack1;
	//int a[10]={0,1,2,3,4,5,6,7,8,9};
	int *p=(int*)malloc(sizeof(int));
	*p=123;
	int *b;
	stack_init(&stack1,NULL,NULL);
	stack_push(&stack1,(void*)p);
	stack_show(&stack1,show);
	p=(int*)malloc(sizeof(int));
	*p=456;
	stack_push(&stack1,(void*)p);
	p=(int*)malloc(sizeof(int));
	*p=789;
	stack_push(&stack1,(void*)p);
	stack_show(&stack1,show);
	b = (int *)stack_pop(&stack1);
	free(b);
	stack_show(&stack1,show);
	stack_destroy(&stack1);
	return 0;
}

void show(void *data)
{
	printf("%d\n",*(int*)data);
}
