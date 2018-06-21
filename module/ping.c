#include<sys/socket.h>
#include<stdio.h>
#include<netinet/ip_icmp.h>
#include<string.h>
#include "ping.h"
/*ping*/
int ping(char sendip){
  struct icmphdr icmphdrinfo; //icmp用のヘッダー
  int sock;//sock用
  sock = socket(AF_INET, SOCK_RAW,0);
  //SOCK_RAW ->ip or icmp ,AF_INET ->ipv4
  struct sockaddr_in address;//アドレス用の構造体を宣言

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
  return 0;
}
