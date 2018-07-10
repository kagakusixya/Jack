
#include<stdio.h>
#include "module/ping.h"
int main(int argc,char *argv[]){
  if(*argv[1]=='-'){
    switch (*(argv[1]+1)) {
      case 'p':
      ping(argv[2],argv[3],argv[4]);
      break;
      case 'b':
      brege(argv[2],argv[3]);
      break;
      default:
      puts("ERROR");
      }
  }
  return 0;
}
