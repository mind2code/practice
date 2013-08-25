#include "list.h"
#include <stdio.h>

void destroy(void *);
int eq(const void *,const void*);

int main()
{
	list_t list;
	int *data;
	int i;

	printf("list_init\n");
	list_init(&list,destroy,eq);

	for(i=0;i<10;i++)
	{
		data=(int *)malloc(sizeof(int));
		*data=i;
		list_insert(&list,NULL,(void *)data);
		printf("insert %d\n",*data);	
	}
	list_show(&list);
	
	int j=4;
	if(list_is_member(&list,(void*)&j))
		printf("%d is in the list\n",j);

	for(i=0;i<10;i++)
	{
		list_remove(&list,NULL,(void**)&data);
		printf("remove %d\n",*data);
	}
	list_show(&list);
	printf("list_destroy\n");
	list_destroy(&list);
	return 0;
	
}

void destroy(void *data)
{
	free(data);
	printf("destroy\n");
}

int eq(const void *key1,const void *key2)
{
	if(*(int*)key1==*(int*)key2)
		return 1;
	return 0;
}
