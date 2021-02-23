#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  // 创建文件对象(写文件)
  ofstream outfile;
  outfile.open("./file.txt", ofstream::out);

  // 判断文件是否打开
  if(!outfile.is_open())
  {
    return  -1;
  }

  // 1. 向文件中写入数据 "operator >>"
  string date = "i am student!!\ni am zhangao!!";
  outfile << date;

  // 2. 向文件中写入数据 "write()"
  char s[1024] = {"i am a apple, hello world!"};
  outfile.write(s, 1024);

  // 关闭文件(手动关闭)
  outfile.close();

  // ############################################

  // 拷贝文件  Date.h --> file.h 
  ofstream fout;
  // 写 | 文件存在则清空原有数据
  fout.open("./file.h", ofstream::out | ofstream::trunc);
  if(!fout.is_open())
  {
    cout << "文件file.h打开失败" << endl;
    return -1;
  }

  ifstream fin;
  fin.open("./Date.h", ifstream::in);
  if(!fin.is_open())
  {
    cout << "文件Date.h打开失败" << endl;
    return -1;
  }

  while(!fin.eof())
  {
    // 方式 1: read, write 以字节为单位读取数据
    char date[1024] = {0};
    fin.read(date, 1024);
    // 获取当前实际读到的数据大小
    cout << "读取数据的大小:" << fin.gcount() << endl;
    cout << date << endl;
    fout.write(date, 1024);
    
    // 方式 2: >> , << 以空格，换行符，制表符为结束条件
    // string date;
    // fin >> date;
    // fout << date;
  }

  fin.close();
  fout.close();

  // 文件指针偏移:
  // seekp(): 文件指针偏移 / tellp(): 获取当前文件指针位置
  
  return 0;
}
