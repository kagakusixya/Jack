
#include<stdio.h>
#include "module/ping.h"
int main(int argc,char *argv[]){
  int pin =ping(argv[1],argv[2],argv[3]);
  return 0;
}
