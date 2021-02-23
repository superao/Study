#include <stdio.h>
#include <unistd.h>

int main() {
  
  
  printf("nihao,bit!\n");


  // 利用fork来创建新的进程。
  // 利用返回值来判断父子进程。
  pid_t pid = fork();
  if(pid > 0) {
    printf("这里是父进程:[%d]\n",pid);
  }else if(pid == 0) {
    printf("这里是子进程:[%d]\n",pid);
  }else{
    printf("子进程创建失败！");
  }

  printf("hehe\n");
  printf("hello bit!\n");

  return 0;
}

