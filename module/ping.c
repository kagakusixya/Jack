#include<sys/socket.h>
#include<stdio.h>
#include<netinet/ip_icmp.h>
#include<string.h>
#include <arpa/inet.h>
#include<netinet/ip.h>
#include <linux/if_ether.h>
#include "ping.h"

/*ping*/
int ping(char *sendip){
  struct icmphdr icmphdrinfo; //icmp用のヘッダー
  int sock;//sock用
  struct sockaddr_in address;//アドレス用の構造体を宣言
/*addressの設定*/
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(sendip);

  sock = socket(AF_INET,SOCK_RAW,IPPROTO_RAW);//SOCK_RAW ->ip or icmp ,AF_INET ->ipv4
if (sock < 0) {
  perror("socket err");
  return 1;
}
/*ipheaderの編集場所*/
struct in_addr ip_src = { .s_addr = htonl(0x0a000001) }; /* 10.0.0.1 */
struct in_addr ip_dst = { .s_addr = htonl(0x0a000002) }; /* 10.0.0.2 */
struct ip ip;
memset(&ip, 0, sizeof(struct ip));
 ip.ip_v = IPVERSION;
 ip.ip_hl = sizeof(struct ip) >> 2;
 ip.ip_tos = 0;
 ip.ip_len = sizeof(struct ip);
 ip.ip_id = 0;
 ip.ip_off = IP_DF|0;
 ip.ip_ttl = 255;
 ip.ip_p = IPPROTO_RAW;
 ip.ip_sum = 0;
 memcpy(&ip.ip_src, &ip_src, sizeof(struct in_addr));
 memcpy(&ip.ip_dst, &ip_dst, sizeof(struct in_addr));
//icmphdrinfo初期化
memset(&icmphdrinfo,0,sizeof(icmphdrinfo));
//icmphdrinfoにデータを代入
icmphdrinfo.type = ICMP_ECHO;//エコーリクエスト
icmphdrinfo.code = 0; //0固定
icmphdrinfo.checksum=0;//checksumは後で
icmphdrinfo.un.echo.id = 0;//id
icmphdrinfo.un.echo.sequence = 0;//シーケンス番号

//checksumの計算
icmphdrinfo.checksum = checksum((unsigned short *)&icmphdrinfo, sizeof(icmphdrinfo));
int err;
err = sendto(sock,&ip, sizeof(ip),0, (struct sockaddr *)&address, sizeof(address));//バッファー,size
if (err < 1) {
  perror("sendto");
}
  return 0;
}
