#include <stdio.h>
#include <stdlib.h>
#include "set.h"

#define UPDATE
#define IS_MEMBER
#define DIFF
#define UNION
#define INTERSECTION
#define IS_EQUAL
#define IS_SUBSET
int eq(const void * key1,const void * key2);
void destroy(void *data);

int main()
{
	set_t set1,set2;
	set_init(&set1,eq,destroy);
	set_init(&set2,eq,destroy);
	
	int i;
	int a[10]={0,1,2,3,4,5,6,7,8,9};
	int *data;
	for(i=0;i<5;i++)//test set_insert
	{
		data=(int *)malloc(sizeof(int));
		*data=i;
		set_insert(&set1,(void *)data);
		printf("Insert %d into set1\n",*data);
		printf("wait for 2s...\n");
		sleep(2);
	}
	printf("set1:");
	set_show(&set1);//set1:0,1,2,3,4

	data=a;
	set_remove(&set1,(void*)(data+4));
	printf("set1:");
	set_show(&set1);//set1:0,1,2,3
	//set_removeall(&set1);
	
	data=(int*)malloc(sizeof(int));
	*data=15;
	set_insert(&set1,(void*)data);
	printf("set1:");
	set_show(&set1);//set1:0,1,2,3,15

	printf("\n\n");
	for(i=0;i<10;i++)
	{
		data=(int *)malloc(sizeof(int));
		*data=i;
		set_insert(&set2,(void *)data);
	}
	printf("set2:");
	set_show(&set2);//set2:0,1,2,3,4,5,6,7,8,9
#ifdef IS_MEMBER
	for(i=0;i<7;i++)//测试set_is_member
	{
		
		if(set_is_member(&set1,(void *)&i))
		{
			printf("%d is in set1\n",i);
		}
		else
			printf("%d is not in set1\n",i);
	}
#endif
#ifdef UNION
	set_t setu;
	set_init(&setu,eq,destroy);
	set_union(&setu,&set1,&set2);//test set_union
	printf("setu:");
	set_show(&setu);//setu:0,1,2,3,4,5,6,7,8,9,15
#endif
#ifdef INTERSECTION
	set_t seti;
	set_init(&seti,eq,destroy);	
	set_intersection(&seti,&set1,&set2);
	printf("seti:");
	set_show(&seti);//seti:0,1,2,3
#endif
#ifdef IS_EQUAL
	printf("Testing set_is_equal\n");
	printf("set1:");
	set_show(&set1);
	printf("set:");
	set_show(&set1);

	if(set_is_equal(&set1,&set1))
		printf("set1 eq set3\n");
#endif
#ifdef IS_SUBSET
	printf("Testing set_is_subset\n");
	printf("set1:");
	set_show(&set1);
	printf("set3:");
	set_show(&set1);
	if(set_is_subset(&set1,&set1))
		printf("set1 is set3's subset\n");
#endif
#ifdef DIFF
	printf("Testint difference\n");
	printf("set1:");
	set_show(&set1);
	printf("set2:");
	set_show(&set2);
	set_t setd;
	set_init(&setd,eq,destroy);
	set_difference(&setd,&set2,&set1);
	printf("setd:");
	set_show(&setd);//	
#endif
#ifdef UPDATE
	sleep(15);
	set_show(&set1);	
#endif
	set_destroy(&setu);
	set_destroy(&set1);
	set_destroy(&set2);
	set_destroy(&setd);
	set_destroy(&seti);
	return 0;
}

int eq(const void * key1,const void * key2)
{
	if(*(int*)key1 == *(int*)key2)
		return 1;
	return 0;
}
void destroy(void *data)
{
	free(data);
}
