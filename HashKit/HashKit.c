#include "HashKit.h"

int hashsize[]={11,19,29,37};
int m;//��ϣ�����ȣ�ȫ�ֱ���

//��ʼ����ϣ��,
//Input:ָ���ϣ��H��ָ��
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

//���ٹ�ϣ��
//ָ���ϣ��H��ָ��
void destroyHashTable(HashTable *H)
{
	free(H->elem);
	H->count=0;
	H->sizeindex=0;
	H->elem=NULL;
}

//��ϣ����
unsigned Hash(const KeyType key)
{
	return key%m;
}

//����̽����ɢ��
void collision(int *p)
{
	*p=++*p%m;
}
// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
Status searchHash(const HashTable *H,KeyType K,int *p,int *c)
{
	*p=Hash(K); // ��ù�ϣ��ַ
	*c=0;
	while(H->elem[*p].key!=NULLKEY&&!EQ(K,H->elem[*p].key))
	{ // ��λ�������м�¼�����ҹؼ��ֲ����
	 (*c)++;
	 collision(p); // �����һ̽���ַp
	}
	if EQ(K,H->elem[*p].key)
	 return SUCCESS; // ���ҳɹ���p���ش�������Ԫ��λ��
	else
	  {
		p=NULL;
		return UNSUCCESS;
	  } // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)��p���ص��ǲ���λ��
}
Status SearchHash(const HashTable *H,KeyType K,int *p)
{
  int c;
  return searchHash(H,K,p,&c);
}

/*Status InsertHash(HashTable &,ElemType); // �Ժ���������
void RecreateHashTable(HashTable &H) // �ؽ���ϣ��
{ int i,count=H.count;
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   p=elem;
   printf("�ؽ���ϣ�� ");
   for(i=0;i
   if((H.elem+i)->key!=NULLKEY) // �õ�Ԫ������
   *p++=*(H.elem+i);
   H.count=0;
   H.sizeindex++; // ����洢����
   m=hashsize[H.sizeindex];
   p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
   if(!p)
     exit(OVERFLOW); // �洢����ʧ��
   H.elem=p;
   for(i=0;i
     H.elem[i].key=NULLKEY; // δ���¼�ı�־(��ʼ��)
   for(p=elem;p
     InsertHash(H,*p);
}*/

Status InsertHash(HashTable *H,ElemType e)
// ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK��
{
	int c,p;
	if(searchHash(H,e.key,&p,&c)) // ����������e����ͬ�ؼ��ֵ�Ԫ��
	 return DUPLICATE;
	else
		if(c<hashsize[H->sizeindex]/2)
		{ // ����e
		 H->elem[p]=e;
		 ++H->count;
		 return SUCCESS;
		}
		else
		{
//			RecreateHashTable(H); // �ؽ���ϣ��
			printf("��ͻ������Ҫ���½�����\n");
			return UNSUCCESS;
		}
}

//ɾ��ָ��Ԫ��
Status DeletHash(HashTable *H,KeyType K)
{
     int p;
     SearchHash(H,K,&p);
     H->elem[p].key=-1;
     H->elem[p].ord=0;
}

void TraverseHash(const HashTable *H,void(*Vi)(int,ElemType))
// ����ϣ��ַ��˳�������ϣ��
{
	int i;
	for(i=0;i<hashsize[H->sizeindex];i++)
	 if(H->elem[i].key!=NULLKEY) // ������
	   Vi(i,H->elem[i]);
}

void print(int p,ElemType r)//���
{
   printf("address=%d (%d,%d) \n",p,r.key,r.ord);
}

