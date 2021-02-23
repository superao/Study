/* 学习使用文件系统调用函数接口 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main () {


  // 打开文件，进行操作
  // int open(const char *pathname, int flags);
  // 返回值:返回一个"文件描述符"
  // O_RDONLY O_WRONLY  O_RDWR(必选其一)(不会清空原有内容，从文件起始位置进行覆盖)    
  // O_CREAT  O_TRUNC   O_APPEND(可选项)
  int fd = open("./syswenjian.txt",O_RDWR | O_CREAT,0664);

  
  // 写入数据
  char* date = "5201314";
  write(fd, date, strlen(date));


  // 求文件大小
  // off_t lseek(int fd, off_t offset, int whence);
  // 返回值：返回从文件初始位置开始的偏移量。
  int bety = lseek(fd,0,SEEK_END);
 

  // 偏移文件指针 注：当文件写入完成后，文件指针在文件末尾，直接读取是读取不到数据的。
  lseek(fd,0,SEEK_SET);


  // 读取文件内容
  // ssize_t read(int fd, void *buf, size_t count);
  char buf[1024] = {'\0'};
  read(fd,buf,bety);


  // 打印文件内容。
  printf("文件内容：[%s]\n",buf);


  close(fd);
  return 0;
}

