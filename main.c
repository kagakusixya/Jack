#include<stdio.h>
#include "module/ping.h"
int main(int argc,char *argv[]){
  int pin =ping(*argv[1]);
  if(pin==1){
    printf("socket err\n");
  }else if(pin ==2){
    printf("sendto err\n");
  }
  return 0;
}
