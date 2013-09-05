/*
 *
 * ¼ÙÆÚ¸üÐÂ°æ±¾£¬
 * usage:commend [file]
 * By yhl£¬2013-2-10
 * ¿¿¿¿¿中
 */

#include "pcap.h"
#ifndef WIN32
#include <netinet/in.h>
#include <stdlib.h>
#endif

/*IPv4 addrress struct*/
typedef struct ip4_address
{
  u_char byte1;
  u_char byte2;
  u_char byte3;
  u_char byte4;
}ip4_address_t;

/*IPv6 address struct*/
typedef struct ip6_address
{
  u_int part1;
  u_int part2;
  u_int part3;
  u_int part4;
}ip6_address_t;

/*IPv4 Header*/
typedef struct ip4_header
{
  u_char ver_ihl;//version & header length
  u_char tos;    //type of service
  u_short tlen;  //Total length
  u_short id;    //identification
  u_short flg_off;//Flags(3 bits)+Fragment offset(13 bits)
  u_char ttl;    //Time to live
  u_char proto;  //Protocol
  u_short crc;   //header checksum
  ip4_address_t saddr;
  ip4_address_t daddr;
}ip4_header_t;

/*IPv6 Header Struct*/
typedef struct ip6_header
{
  u_int ver_tc_fl;
  u_short pl;
  u_char nh;
  u_char ttl;
  ip6_address_t saddr;
  ip6_address_t daddr;
}ip6_header_t;

/*UDP header struct*/
typedef struct udp_header
{
  u_short sport;
  u_short dport;
  u_short len;    //Datagram length(include header)
  u_short crc;
}udp_header_t;

#ifndef WIN32
void itoa(unsigned int,char *,unsigned int);
#endif

int writefile(u_int,int);

static u_int ulen[2][11];
const u_int a[10]={0,20,40,80,160,320,640,1280,2560,5120};

void stat(const int flag,u_int udp_len);

/*
usage:commend [file]
success:return 0;
something wrong:return 1;
*/
int main(int arg,char **argv)
{
  if(arg>=3)
    {
      fprintf(stderr,"usage:commend [file]\n");
      return 1;
    }
  pcap_t *adhandle;
  char errbuf[PCAP_ERRBUF_SIZE];
  if(arg==1)
    {//list devices
      pcap_if_t *alldevs;
      pcap_if_t *d;
      int i=0;
      int inum;

      if(pcap_findalldevs(&alldevs,errbuf)==-1)
	{
	  fprintf(stderr,"Error in pcap_findalldevs:%s\n",errbuf);
	  return 1;
	}
      /*print devices list*/
      for(d=alldevs;d;d=d->next)
	{
	  printf("%d.%s",++i,d->name);
	    if(d->description)
	      printf("(%s)\n",d->description);
	    else
	      printf("(No descrption)\n");
	}
      if(i==0)
	{
	  printf("No interface found!\n");
	  return 1;
	}
      /*To choose a interface*/
      printf("To choose a interface number(1-%d):",i);
      scanf("%d",&inum);
      if(inum<1||inum>i)
	{
	  printf("Interface number out of rang.\n");
	  pcap_freealldevs(alldevs);
	  return 1;
	}
      /*jump to the interface*/
      for(d=alldevs,i=0;i<inum-1;d=d->next,i++);
      
      /*get adhandle*/
      if((adhandle=pcap_open_live(d->name,65535,1,1000,errbuf))==NULL)
	{
	  fprintf(stderr,"Error in pcap_open_live:%s\n",errbuf);
	  return 1;
	}
      if(pcap_datalink(adhandle)!=DLT_EN10MB)
	{
	  fprintf(stderr,"This is only works on Ethernet network\n");
	  return 1;
	}
    }
  else
    {//open file
      char *filename;
      FILE *fp;
      filename=argv[1];
      if((fp=fopen(filename,"r"))==NULL)
	{
	  fprintf(stderr,"Error in openfile:%s\n",filename);
	  return 1;
	}
      /*Get adhandle*/
      if((adhandle=pcap_open_offline(filename,errbuf))==NULL)
	{
	  fprintf(stderr,"Error in pcap_open_offline:%s\n",errbuf);
	  return 1;
	} 
    }
 
  /*Set filter*/
  /*u_int netmask;
  char packer_filter[]="udp";
  struct bpf_program fcode;

  if(d->addresses->netmask!=NULL)
    netmask=((struct sockaddr_in *)d->addrresses->netmask)->sin_addr.s_addr;
  else
    netmask=0xffffff;
  if(pcap_compile(adhandle,&fcode,packet_filter,1,netmask)<0)
    {
      fprintg(stderr,"Error in pcap_compile\n");
      pcap_freealldevs(alldevs);
      return 1;
    }
  if(pcap_setfilter(adhandle,&fcode)<0)
    {
      fprintf(stderr,"Error in setfilter\n");
      pcap_freealldevs(adhandle);
      return 1;
      }

      printf("Listening on %s...\n",d->description);*/

  struct pcap_pkthdr *header;
  const u_char *packet_data;
  int res;
  u_char version;

  while((res=pcap_next_ex(adhandle,&header,&packet_data))>=0)
    {
      if(res==0)
	continue;//timeout

      version=((*((u_char *)(packet_data+14)))&0xf0)>>4;
      udp_header_t *uh;
      u_int udp_len;

      if(version==6)
	{
	  ip6_header_t *ip6h=(ip6_header_t *)(packet_data+14);
	  if(ip6h->nh!=17)continue;
	  uh=(udp_header_t *)(packet_data+14+40);
	  udp_len=ntohs(uh->len)-8;
		stat(1,udp_len);
	}
      else if(version==4)
	{
	  ip4_header_t *ip4h=(ip4_header_t *)(packet_data+14);
	  if(ip4h->proto!=17)continue;
		if(ntohs(ip4h->flg_off)&0x1fff)continue;
	  u_int ip4hlen=(ip4h->ver_ihl&0xf)*4;
	  uh=(udp_header_t *)(packet_data+14+ip4hlen);
	  udp_len=ntohs(uh->len)-8;//UDP payload length
		stat(0,udp_len);
	}
      else
	{
	  fprintf(stderr,"IP version is unkonw\n");
	  continue;
	}
      if(udp_len<0)udp_len=0;
			writefile(udp_len,version);
    }
	system("pause");
}

int writefile(u_int udp_len,int flag)
{
  FILE *fp;
  char udp_len_str[20];
  char *filename=(char *)malloc(128*sizeof(char));
  if(flag==4)filename="./ip4.txt";
  else if(flag==6)filename="./ip6.txt";

  if(!(fp=fopen(filename,"a")))
    {
      fprintf(stderr,"Error in write file\n");
      return 1;
    }

  itoa(udp_len,udp_len_str,10);
  fputs(udp_len_str,fp);
  fputs("\n",fp);
  fclose(fp);
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

void stat(const int flag,u_int udp_len)
{
	int i=0;
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
	++ulen[flag][10];
	printf("Totel:IPv4:%u\t\tIPv6:%u\n",ulen[0][10],ulen[1][10]);
	printf("   Length:\tIPv4\t\tIPv6\n");
	for(i=0;i<9;i++)
	{
		if(udp_len>=a[i] && udp_len<a[i+1])ulen[flag][i]++;		
		printf("%5u-%5u:\t%u\t%6.2f%% | %u\t%6.2f%%\n",a[i], a[i+1]-1, ulen[0][i],(float)ulen[0][i]*100/(ulen[0][10]+ulen[1][10]),
			ulen[1][i],(float)ulen[1][i]*100/(ulen[1][10]+ulen[0][10]));
	}
	if(udp_len>=5120)ulen[flag][9]++;
	printf("%5u-\t:\t%u\t%6.2f%% | %u\t%6.2f%%\n",a[9],ulen[0][9],(float)ulen[0][9]*100/(ulen[1][10]+ulen[0][10]),
		ulen[1][9],(float)ulen[1][9]*100/(ulen[1][10]+ulen[0][10]));

}
