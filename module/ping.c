#include<sys/socket.h>
#include<stdio.h>
#include<netinet/ip_icmp.h>
#include<string.h>
#include<netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ping.h"
/*ping*/
int ping(char sendip){
  struct icmphdr icmphdrinfo; //icmp用のヘッダー
  int sock;//sock用
  sock = socket(AF_INET, SOCK_RAW,0);//SOCK_RAW ->ip or icmp ,AF_INET ->ipv4
  struct sockaddr_in address;//アドレス用の構造体を宣言
/*addressの設定*/
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(&sendip);
if (sock < 0) {
  perror("socket err");
  return 1;
}
//icmphdrinfo初期化
memset(&icmphdrinfo,0,sizeof(icmphdrinfo));
//icmphdrinfoにデータを代入
icmphdrinfo.type = ICMP_ECHO;//エコーリクエスト
icmphdrinfo.code = 0; //0固定
//checksumは後で
icmphdrinfo.un.echo.id = 0;//id
icmphdrinfo.un.echo.sequence = 0;//シーケンス番号

//checksumの計算
icmphdrinfo.checksum = checksum((unsigned short *)&icmphdrinfo, sizeof(icmphdrinfo));
int err;
err = sendto(sock,
           (char *)&icmphdrinfo, sizeof(icmphdrinfo),//バッファー,size,flags
           0, (struct sockaddr *)&address, sizeof(address));//バッファー,size
if (err < 1) {
  perror("sendto");
  return 2;
}
  return 0;
}
