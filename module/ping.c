#include<sys/socket.h>
#include<stdio.h>
/*ping*/
int ping(char sendip,char myip ){
  //socketの作成
  int sock;
  sock = socket(AF_INET, SOCK_RAW,0);
  //SOCK_RAW ->ip or icmp AF_INET ipv4
if (sock < 0) {
  perror("socket err");
  return 1;
}
  return 0;
}
