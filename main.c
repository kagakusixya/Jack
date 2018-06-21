#include<stdio.h>
#include "module/ping.h"
int main(int argc,char *argv[]){
  int pin =ping(argv[1]);
  return 0;
}
