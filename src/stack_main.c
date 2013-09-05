#include "stack.h"
#include <stdlib.h>

int eq(const void *data1,const void *data2);
void destroy(void *data);

int main()
{
	stack_t stack1;
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int *p=(int*)malloc(sizeof(int));
	*p=123;
	int b;
	stack_init(&stack1,eq,destroy);
	stack_push(&stack1,(void*)p);
	stack_show(&stack1);
	p=(int*)malloc(sizeof(int));
	*p=456;
	stack_push(&stack1,(void*)p);
	p=(int*)malloc(sizeof(int));
	*p=789;
	stack_push(&stack1,(void*)p);
	stack_show(&stack1);
	stack_pop(&stack1,(void*)&b);
	stack_show(&stack1);
	stack_destroy(&stack1);
	return 0;
}

int eq(const void *data1,const void *data2)
{
	if(*(int*)data1 == *(int*)data2)
		return 1;
	return 0;
}
void destroy(void *data)
{
	free(data);
}
