#ifndef HASHKIT
#define HASHKIT

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define NULLKEY -1

#define EQ(a,b) ((a)==(b))

typedef int Status;
typedef int KeyType;

typedef struct
{
	KeyType key;
	int ord;
}ElemType;
typedef struct
{
	ElemType *elem;
	int count;
	int sizeindex;
}HashTable;

//操作：初始化哈希表
//操作前：H指向一个哈希表
//操作后：初始化为空的哈希表
void InitHashTable(HashTable *H);
//操作：销毁哈希表
//操作前：H指向一个哈希表
//操作后：收回分配的内存空间
void DestroyHashTable(HashTable *H);
//操作：查询哈希表
//操作前：H指向一个N哈希表，K是一个待查寻的关键值
//操作后：查询成功返回SUCCESS，否则返回UNSUCCESS，p指向待查的数据索引
Status SearchHash(const HashTable *H,KeyType K,int *p);
//操作：删除哈希表中的元素
//操作前：H指向哈希表，K为待删除的元素关键值
//操作后：删除成功返回SUCCESS，否则返回UNSUCCESS
Status DeletHash(HashTable *H,KeyType K);
//操作：插入哈希表
//操作前：H指向待插入的哈希表，e为待插入的元素
//操作后:插入成功返回SUCCESS，否则返回UNSUCCESS
Status InsertHash(HashTable *H,ElemType e);
//操作：遍历整个哈希表
//操作前：H指向哈希表，Vi为需要执行的操作
//操作后：无
void TraverseHash(const HashTable *H,void(*Vi)(int,ElemType));
void print(int p,ElemType r);

#endif
