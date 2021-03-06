#include "list.h"
#include <stdio.h>

void free_m(void *);
int cmp_m(const void *,const void*,size_t);
void show_m(void *data);

int main()
{
	list_t list;
	int *data;
	int i;

	printf("list_init\n");
	list_init(&list,NULL,NULL,NULL);

	for(i=0;i<10;i++)
	{
		data=(int *)malloc(sizeof(int));
		*data=i;
		list_insert(&list,(void *)data);
		printf("insert %d\n",*data);	
	}
	list_show(&list,show_m);
	
	int j=4;
	if(list_is_member(&list,(void*)&j,sizeof(int)))
		printf("%d is in the list\n",j);

	for(i=0;i<10;i++)
	{
		list_remove(&list,(void**)&data,sizeof(int));
		printf("remove %d\n",*data);
	}
	list_show(&list,show_m);
	printf("list_destroy\n");
	list_destroy(&list);
	return 0;
	
}

void free_m(void *data)
{
	free(data);
	printf("destroy\n");
}

int cmp_m(const void *key1,const void *key2,size_t size)
{
	if(*(int*)key1==*(int*)key2)
		return 1;
	return 0;
}

void show_m(void *data)
{
	printf("%d\n",*(int*)data);
}
