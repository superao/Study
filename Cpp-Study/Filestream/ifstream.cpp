#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  // 创建对象(读)
  ifstream fin;
  // 默认打开方式(ifstream::in)
  fin.open("./file.h");
  if(!fin.is_open())
  {
    cout << "文件打开失败" << endl;
    return -1;
  }
  
  // 利用文件指针偏移计算文件大小
  // seekg(): 文件指针偏移 / tellg(): 返回指针当前的值
  fin.seekg(0, ios::beg);
  streampos filestart = fin.tellg(); 
  cout << "文件起始位置: " << filestart << endl;
  fin.seekg(0, ios::end);
  streampos fileend = fin.tellg();
  cout <<"文件结束位置: " << fileend << endl;
  cout << "文件大小: " << fileend - filestart << endl;

  // 完整读取一个文件的内容
  while(!fin.eof())
  {
    // 为了保证读取的数据与源文件一样使用 read .
    char buf[1024] = {0};
    fin.read(buf, 1024);
    cout << buf << endl;
  }
  // 当数据读取完毕之后，此时文件指针已经到达文件末尾

  fin.close();
  
  return 0;
}
