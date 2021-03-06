// 匿名管道的使用
// int pipe(int pipefd[2]);
//    pipefd:输出型参数 --- 用于获取管道操作句柄
//    pipefd[0] : 管道的读入端
//    pipdfd[1] : 管道的写入端
// 返回值：0     失败：-1;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main () {

  int pipefd[2];

  int ret = pipe(pipefd);
  if(ret < 0) {

    perror("pipe error");
    return -1;
  }

  // 使用匿名管道实现子进程与父进程之间的通信
  // 父进程-读        子进程-写
  int pid = fork();
  if(pid < 0) {

    perror("fork error");
    return -1;
  }
  else if(pid == 0) {


    // 关闭子进程读端
    // close(pipefd[0]);


    // 子进程-写
    sleep(5); // 让父进程先运行。
    char* str = "好饿啊~~~";
    write(pipefd[1], str,1024);  
  }
  else {
    
    // 关闭父进程读端。
    // close(pipefd[0]);
    // sleep(100000);


    // 父进程-读
    char buf[1024] = {0};
    ret = read(pipefd[0],buf,1024);
    if(ret < 0) {

      perror("read error");
      return -1;
    }
    else {

      printf("%s\n", buf);
    }
  
  }

  return 0;
}
