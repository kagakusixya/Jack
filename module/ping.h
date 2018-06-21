#ifndef _PING_H_
#define _PING_H_

int ping(char sendip,char myip );
unsigned short checksum(unsigned short *buf, int bufsz);

#endif
