/* 回顾库函数文件操作 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  // 当进行文件操作时，必须先打开文件才能进行文件的相应的操作。
  // FILE *fopen(const char *path, const char *mode);
  FILE* fp = fopen("./wenjian.txt","w+");

  // 写入数据
  char date[1024] = "以后要稳住啊,好好学习，天天进步！\n";
  fwrite(date,1,1024,fp);

  // 读取文件中的数据
  // 如果直接读取是读取不到的，因为，在刚才进行文件写入的时候，文件指针已经到了文件末尾，
  // 现在进行读取数据时，从文件末尾是读不到任何数据的。因此，需要使用 fseek(); 进行文件指针偏移。
 
  // 指针偏移：
  // int fseek(FILE *stream, long offset, int whence);
  // FIEL* stream : 文件指针。
  // long offset : 偏移量。
  // int whence :
  // SEEK_SET:文件起始位置。
  // SEEK_END:文件末尾。
  // SEEK_CUR:文件当前位置。
  fseek(fp,0,SEEK_SET);


  char buf[1024] = {'\0'};
  fread(buf,1,1024,fp);

  printf("文件内容：[%s]", buf);



  return 0;
}
