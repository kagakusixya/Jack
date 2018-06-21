unsigned short checksum(unsigned short *buf, int bufsz){//checksumのテンプレート
  unsigned long sum = 0;
  while (bufsz > 1) {
    sum += *buf;
    buf++;
    bufsz -= 2;
  }
  if (bufsz == 1) {
    sum += *(unsigned char *)buf;
  }
  sum = (sum & 0xffff) + (sum >> 16);
  sum = (sum & 0xffff) + (sum >> 16);
  return ~sum;
}
