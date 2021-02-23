#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>


int main() {
  
  //extern int errno;
  int pid = fork();
  if(pid < 0) {
    
    perror("fork error");
    printf("fork error:%s\n",strerror(errno));
  }

  
  //printf("%s\n",strerror(2));
  
  // 打印所有事先定义好的错误信息。
  //int i = 0;
  //for(i = 0; i < 256; i++) {
  //  printf("%s\n",strerror(i));
  //}
  
  
  printf("hello bit!!");
  
  sleep(3);
  
  _exit(0);
  exit(0);

  return 0;
}
