#include <stdio.h>
#include <stdlib.h>
#include "HashKit.h"

int main()
{
   ElemType r[10]={{12,3},{1,2},{11,1},{22,4},{23,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
   HashTable h;
   int i,p;
   Status j;
   KeyType k;
   InitHashTable(&h);
   for(i=0;i<10;i++)
   {
     j=InsertHash(&h,r[i]);
     if(j==DUPLICATE)
       printf("Key in the HashTable%d的记录，无法再插入记录(%d,%d) ",r[i].key,r[i].key,r[i].ord);
   }
   printf("All the HashTable: \n");
   TraverseHash(&h,print);

   printf("the key for search: ");
   scanf("%d",&k);
   j=SearchHash(&h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到 ");
   printf("the key to delete：\n");
   scanf("%d",&k);
   DeletHash(&h,k);
   TraverseHash(&h,print);
/*   j=InsertHash(&h,r[i]); // 插入第N个记录
   if(j==UNSUCCESS) // 重建哈希表
     j=InsertHash(&h,r[i]); // 重建哈希表后重新插入
   printf("按哈希地址的顺序遍历重建后的哈希表: ");
   TraverseHash(h,print);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到 ");*/
   destroyHashTable(&h);
   system("pause");
}
