#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>


int main() {

  int pid = fork();
  if(pid < 0) {

    perror("fork error");
    exit(-1);
  }
  else if(pid == 0) {

    sleep(5);
    exit(0);
  }
  



  // pid_t wait(int *status);
  // status :用于获取退出原因。
  // 返回值：退出的子进程的PID.
  //int statu;
  //int ret = wait(&statu);
  //printf("%d--%d\n",ret, pid);




  // pid_t waitpid(pid_t pid, int *status, int options);
  // pid:
  // -1: 等待任意子进程退出
  // >0: 等待指定的子进程退出
  // status:用于获取退出的原因
  // options:
  //        WNOHANG     将waitpid设置为非阻塞。
  // 返回值：-1：错误         0：没有子进程退出       >0:退出子进程的PID
  
  int statu;
  //int ret = waitpid(pid, &statu,WNOHANG);
  //printf("%d--%d\n",ret,pid);

  // 非阻塞常用操作：
  while((waitpid(pid, &statu,WNOHANG)) == 0) {
    printf("打麻将！！\n");
    sleep(1);
  }






  while(1) {

    printf("-----\n");
    sleep(1);
  }

  return 0;
}
