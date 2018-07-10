#ifndef _PING_H_
#define _PING_H_

int ping(char *interfaces, char *saddr,char *daddr);
unsigned short checksum(unsigned short *buf, int bufsz);
void brege(char* interfacer,char* interfaces);
#endif
