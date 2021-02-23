#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {

  // 验证僵死进程
  int PID = fork();

  if(PID > 0) {
    
    printf("我是父进程！-----%d \n", getpid()); 
  }
  else {
    
    printf("我是子进程！-----%d\n",getpid());
  } 
  while(1) {

    printf("nihao!\n");
    sleep(1);
  }

  return 0;
}
