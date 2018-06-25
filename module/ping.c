#include<sys/socket.h>
#include<stdio.h>
#include<netinet/ip_icmp.h>
#include<string.h>
#include <arpa/inet.h>
#include<netinet/ip.h>
#include <linux/if_ether.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include "ping.h"

/*ping*/
int ping(char *interfaces, char *saddr,char *daddr){
  int sock = 1;
  struct icmphdr *icmphdrinfo; //icmp用のヘッダー
  struct iphdr *ip;
  struct sockaddr_ll address;//アドレス用の構造体を宣言
    char* interface = interfaces; //インターフェース
/*addressの設定*/
address.sll_family = AF_PACKET;
address.sll_protocol = htons(ETH_P_ALL);
address.sll_ifindex = if_nametoindex(interface);
address.sll_halen = IFHWADDRLEN;


  //Raw socket without any protocol-header inside
  if((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    perror("Error while creating socket");
    return -1;
  }
//packetの作成
char packet[512];
memset(packet, 0, sizeof(packet));
struct ethhdr* ethheader;
char* shwaddr = "\x00\x00\x00\x00\x00\x00"; //送信元macアドレス (例えば"\x00\x00\x00\x00\x00\x00")
char* dhwaddr = "\x00\x00\x00\x00\x00\x01"; //宛先macアドレス
ethheader = (struct ethhdr*)packet;
ip = (struct iphdr*)(packet + ETH_HLEN);
icmphdrinfo = (struct icmphdr*)(packet + ETH_HLEN + sizeof(struct iphdr));

memcpy(ethheader->h_dest, dhwaddr, ETH_ALEN);
memcpy(ethheader->h_source, shwaddr, ETH_ALEN);
ethheader->h_proto = htons(0x0800);
//icmphdrinfo初期化

//icmphdrinfoにデータを代入
icmphdrinfo ->type = ICMP_ECHO;//エコーリクエスト
icmphdrinfo ->code = 0; //0固定
icmphdrinfo ->checksum=0;//checksumは後で
icmphdrinfo ->un.echo.id = 0;//id
icmphdrinfo ->un.echo.sequence = 0;//シーケンス番号
icmphdrinfo ->checksum = checksum((unsigned short *)icmphdrinfo, sizeof(*icmphdrinfo));
/*ipheaderの編集場所*/
char* sipaddr = saddr;
char* dipaddr  = daddr;
 ip ->version = 4;
 ip ->ihl = 5;
 ip ->tos = 0;
 ip ->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr));
 ip ->tot_len = sizeof(ip) + sizeof(icmphdrinfo);
 ip ->id = htons(1);
 ip ->frag_off = htons(0x4000);
 ip ->ttl = 32;
 ip ->protocol = 1;
 ip ->check = checksum((unsigned short *)ip, sizeof(*ip));
 inet_pton(AF_INET, sipaddr, &ip ->saddr);
 inet_pton(AF_INET, dipaddr, &ip ->daddr);
//checksumの計算
int err;
err = sendto(sock,packet, ETH_HLEN + sizeof(struct iphdr) + sizeof(struct icmphdr),0, (struct sockaddr *)&address, sizeof(address));//バッファー,size
if (err < 1) {
  perror("sendto");
}
  return 0;
}
