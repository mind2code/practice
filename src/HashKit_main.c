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
       printf("Key in the HashTable%d�ļ�¼���޷��ٲ����¼(%d,%d) ",r[i].key,r[i].key,r[i].ord);
   }
   printf("All the HashTable: \n");
   TraverseHash(&h,print);

   printf("the key for search: ");
   scanf("%d",&k);
   j=SearchHash(&h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("û�ҵ� ");
   printf("the key to delete��\n");
   scanf("%d",&k);
   DeletHash(&h,k);
   TraverseHash(&h,print);
/*   j=InsertHash(&h,r[i]); // �����N����¼
   if(j==UNSUCCESS) // �ؽ���ϣ��
     j=InsertHash(&h,r[i]); // �ؽ���ϣ������²���
   printf("����ϣ��ַ��˳������ؽ���Ĺ�ϣ��: ");
   TraverseHash(h,print);
   printf("����������Ҽ�¼�Ĺؼ���: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("û�ҵ� ");*/
   destroyHashTable(&h);
   system("pause");
}
