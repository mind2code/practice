/*
 *
 * 将一个unsigned int类型的数字转化为相应的字符串
 * @2013-2-10
 * 
 */
 
#include <stdio.h>

void itoa(unsigned int,char *,unsigned int);

int main()
{
    char str[15];
    unsigned int val=1234567890;
    //while(scanf("%d",&val))
    {
    itoa(val,str,16);
    printf("%s\n",str);
    }
    return 0;
}

void itoa(unsigned int val,char *str,unsigned int radix)
{
    char tab[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i=0,j;
    char tmp;

    do
    {
        str[i]=tab[val%radix];
        i++;
    }while(val/=radix);
    str[i]='\0';
    for(j=0;j<=(i-1)/2;j++)
    {
        tmp=str[j];
        str[j]=str[i-1-j];
        str[i-1-j]=tmp;
    }

}
