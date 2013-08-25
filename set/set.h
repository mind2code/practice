#ifndef SET_H
#define SET_H

#include <time.h>
#define MAXTIME 10
typedef struct setelem
{
	void *data;
	struct setelem *next;
	time_t updatetime;
}setelem_t;

typedef struct set
{
	int size;
	setelem_t *head;
	setelem_t *tail;
	int (*eq)(const void * key1,const void *key2);
	void (*destroy)(void *data);
}set_t;
//initiate set, success return 0, otherwise return 1
int set_init(set_t *set,int (*eq)(const void *,const void *),void (*destroy)(void *));
void set_destroy(set_t *set);
//success return 1, otherwise return 0
int set_is_member(set_t *set,const void *key);
int set_is_equal(set_t *set1,set_t *set2);
int set_is_subset(set_t *set1,set_t *set2);			//判断set1是set2的子集
//success return 0, otherwise return 1
int set_insert(set_t *set,const void *data);
int set_remove(set_t *set,void *data);//移除到数据使用什么指针还没确定
int set_union(set_t *set,set_t *set1,set_t *set2);		//set=set1 并 set2
int set_intersection(set_t *set,set_t *set1,set_t *set2);	//set=set1 交 set2
int set_difference(set_t *set,set_t *set1,set_t * set2);	//set=set1 差 set2
void set_update(set_t *set);//判断超时，移除超时数据
//int set_size(const set_t *set);
void set_show(set_t *set);
int set_removeall(set_t *set);
#define set_size(set) ((set)->size)

#endif
