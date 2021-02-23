// 共享内存的基本操作:
// 1.创建
// 2.建立映射
// 3.内存操作
// 4.解除映射
// 5.删除

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>

#define IPC_KEY 0X12345678
#define PROJ_ID 0X112233


int main () {

  // 创建共享内存
  // key_t ftok(const char *pathname, int proj_id);
  // 通过文件inode结点号与proj_id生成一个k值。
  
  // int shmget(key_t key, size_t size, int shmflg);
  //  key:共享内存标识符
  //  size:共享内存大小
  //  shmflg:选项标志
  //      IPC_CREAT   共享内存不存在则创建，存在则打开
  //      IPC_EXCL    与IPC_CREAT同用，则共享内存存在时报错。
  //      shm_mode    权限
  //  返回值：标识符(代码中的操作句柄(遥控器),key是操作系统中的标识符(电视))              失败 ：-1
  
  // key_t ftok("./abc.txt",PROJ_ID);
  // key 的获取方式有两种 ：
  // 1.自定义一个数,将他作为共享内存表示符。
  // 2.通过文件inode结点号与proj_id生成一个k值。
  int shmid = shmget(IPC_KEY,1024,IPC_CREAT | 0664);
  if(shmid < 0) {

    perror("shmget error");
    return -1;
  }


  // 2.建立映射
  // void *shmat(int shmid, const void *shmaddr, int shmflg);
  // shmid :创建共享内存所返回的句柄。(遥控器)
  // shmaddr:置空 - 让操作系统为我们自动去分配地址空间。
  // shmflg:
  //      SHM_RDONLY:只读
  //      0:默认-可读可写
  //
  // 返回值：返回映射首地址      失败：(void*)-1;
  char* shmat_sta =(char*)shmat(shmid, NULL, 0);
  if(shmat == (void*)-1) {

    perror("shmat error");
    return -1;
  }

  // 内存操作
  int i = 0;
  while(1) {

   sprintf(shmat_sta,"我今天过分了，让人家生气了,不该这样的啊！ + %d\n", i++);
   sleep(1);
  }

  // 解除映射
  // int shmdt(const void *shmaddr);
  // shmaddr:映射的首地址
  shmdt(shmat_sta);

  // 删除
  // int shmctl(int shmid, int cmd, struct shmid_ds *buf);
  // shmid：操作句柄
  // cmd:   操作类型
  //    IPC_RMID 删除共享内存。
  // buf: 设置/获取共享内存信息。
  // 共享内存不会被直接删除，而是先判断它的链接是否位0
  // 为0 ：直接删除
  // 不为0 ：拒绝与后序进程继续进行链接，等到共享链接为0 时，自动删除。

  shmctl(shmid, IPC_RMID, NULL);

  return 0;

}
