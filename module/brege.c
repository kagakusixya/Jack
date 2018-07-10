#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>
#include<net/ethernet.h>
#include<linux/if.h>
#include<sys/ioctl.h>
#include <linux/if_packet.h>
//return 0　正常
//reutn -1 システム的異常
//return 1 異常
int prin(struct ether_header *eh,FILE *fp){
  fprintf(fp,"%02X\n",ntohs(eh->ether_type));
  switch (ntohs(eh->ether_type)) {
    case ETH_P_IP:
      fprintf(fp,"(IP)\n");
      break;
    case  ETH_P_IPV6:
      fprintf(fp,"(IPV6)\n");
      break;
    case ETH_P_ARP:
      fprintf(fp,"(ARP)\n");
      break;
    default:
      fprintf(fp,"(unknow)\n");
      break;
  }
  return 0;
}
int id=0;
int brege(char* interfacer,char* interfaces){
  //受け入れ
  int size;
  struct ifreq ifreq;
  struct sockaddr_ll sa;
  //socketの作成
  char buf[2048];
    memset(buf, 0, sizeof(buf));
  int soc = socket(PF_PACKET, SOCK_RAW,htons(ETH_P_ALL));

  memset(&ifreq,0,sizeof(struct ifreq));
  strncpy(ifreq.ifr_name,interfacer,sizeof(ifreq.ifr_name)-1);
  if(ioctl(soc,SIOCGIFINDEX,&ifreq)<0){
    perror("ioctl");
    close(soc);
  }
  sa.sll_family=PF_PACKET;
  sa.sll_protocol=htons(ETH_P_ALL);
  sa.sll_ifindex=ifreq.ifr_ifindex;
  if(bind(soc,(struct sockaddr *)&sa,sizeof(sa))<0){
    perror("bind");
    close(soc);
    return -1;
  }
  if(ioctl(soc,SIOCGIFFLAGS,&ifreq)<0){
  perror("ioctl");
}
  while(1){
    if( size=read(soc,buf,sizeof(buf))<=0){
      perror("read");
      }else{
      if(size<=sizeof(struct ether_header)){
        printf("----------------\nid:%d\n",id++);
        prin((struct ether_header *)buf,stdout);
      }
    }
  }
  //返し
  close(soc);
  return 0;
}
