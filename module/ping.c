#include<sys/socket.h>
#include<stdio.h>
#include<netinet/ip_icmp.h>
#include<string.h>
/*ping*/
int ping(char sendip,char myip ){
  struct icmphdr icmphdrinfo; //icmp用のヘッダー
  int sock;//sock用
  sock = socket(AF_INET, SOCK_RAW,0);
  //SOCK_RAW ->ip or icmp AF_INET ipv4
if (sock < 0) {
  perror("socket err");
  return 1;
}
/*icmphdrinfoにデータを代入*/

//icmphdrinfo初期化
memset(&icmphdrinfo,0,sizeof(icmphdrinfo));
  return 0;
}
