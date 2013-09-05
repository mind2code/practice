#include "HashKit.h"

int hashsize[]={11,19,29,37};
int m;//哈希表长度，全局变量

//初始化哈希表,
//Input:指向哈希表H的指针
void InitHashTable(HashTable *H)
{
	int i;
	H->count=0;
	H->sizeindex=0;
	m=hashsize[0];
	H->elem=(ElemType*)malloc(hashsize[H->sizeindex]*sizeof(ElemType));
	if(!H->elem)
	  exit(0);
	for(i=0;i<hashsize[H->sizeindex];i++)
	  H->elem[i].key=NULLKEY;
}

//销毁哈希表
//指向哈希表H的指针
void destroyHashTable(HashTable *H)
{
	free(H->elem);
	H->count=0;
	H->sizeindex=0;
	H->elem=NULL;
}

//哈希函数
unsigned Hash(const KeyType key)
{
	return key%m;
}

//线性探测再散列
void collision(int *p)
{
	*p=++*p%m;
}
// 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据
Status searchHash(const HashTable *H,KeyType K,int *p,int *c)
{
	*p=Hash(K); // 求得哈希地址
	*c=0;
	while(H->elem[*p].key!=NULLKEY&&!EQ(K,H->elem[*p].key))
	{ // 该位置中填有记录．并且关键字不相等
	 (*c)++;
	 collision(p); // 求得下一探查地址p
	}
	if EQ(K,H->elem[*p].key)
	 return SUCCESS; // 查找成功，p返回待查数据元素位置
	else
	  {
		p=NULL;
		return UNSUCCESS;
	  } // 查找不成功(H.elem[p].key==NULLKEY)，p返回的是插入位置
}
Status SearchHash(const HashTable *H,KeyType K,int *p)
{
  int c;
  return searchHash(H,K,p,&c);
}

/*Status InsertHash(HashTable &,ElemType); // 对函数的声明
void RecreateHashTable(HashTable &H) // 重建哈希表
{ int i,count=H.count;
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   p=elem;
   printf("重建哈希表 ");
   for(i=0;i
   if((H.elem+i)->key!=NULLKEY) // 该单元有数据
   *p++=*(H.elem+i);
   H.count=0;
   H.sizeindex++; // 增大存储容量
   m=hashsize[H.sizeindex];
   p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
   if(!p)
     exit(OVERFLOW); // 存储分配失败
   H.elem=p;
   for(i=0;i
     H.elem[i].key=NULLKEY; // 未填记录的标志(初始化)
   for(p=elem;p
     InsertHash(H,*p);
}*/

Status InsertHash(HashTable *H,ElemType e)
// 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK；
{
	int c,p;
	if(searchHash(H,e.key,&p,&c)) // 表中已有与e有相同关键字的元素
	 return DUPLICATE;
	else
		if(c<hashsize[H->sizeindex]/2)
		{ // 插入e
		 H->elem[p]=e;
		 ++H->count;
		 return SUCCESS;
		}
		else
		{
//			RecreateHashTable(H); // 重建哈希表
			printf("冲突过多需要重新建表！\n");
			return UNSUCCESS;
		}
}

//删除指定元素
Status DeletHash(HashTable *H,KeyType K)
{
     int p;
     SearchHash(H,K,&p);
     H->elem[p].key=-1;
     H->elem[p].ord=0;
}

void TraverseHash(const HashTable *H,void(*Vi)(int,ElemType))
// 按哈希地址的顺序遍历哈希表
{
	int i;
	for(i=0;i<hashsize[H->sizeindex];i++)
	 if(H->elem[i].key!=NULLKEY) // 有数据
	   Vi(i,H->elem[i]);
}

void print(int p,ElemType r)//输出
{
   printf("address=%d (%d,%d) \n",p,r.key,r.ord);
}


