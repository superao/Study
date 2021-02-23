// 为某个源代码文件去掉注释
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool flag1 = 0;                         // 表示当前没有 /* 这个字符
bool flag2 = 0;                         // 表示当前没有 // 这个字符

// 储存文件
void Savefile()
{

}

// 解析字符
void RemoveComment(string& str)
{
  string str1 = "/*";
  string str2 = "//";
  string str3 = "\r\n";
  string str4 = "*/";

  // 查找 /* 字符位置
  size_t pos1 = str.find_first_of(str1);
  if(pos1 != string::npos)
  {
    // 查找 */  字符位置
    size_t pos2 = str.find_last_of(str3);
    if(pos2 == string::npos)
    {
      // 当前 */ 字符还未读取到，进行标记
      
    }
  }
}

// 读取源文件
void Readfile(const string& filestr)
{
  // 打开文件(读数据)
  ifstream fin;
  fin.open(filestr);
  if(!fin.is_open())
  {
    cout << "源文件打开失败!" << endl;
    return;
  }

  // 文件指针偏移到文件开头
  fin.seekg(0, fin.beg);

  // 循环处理数据
  while(!fin.eof())
  {
    char buf[1024];
    fin.read(buf, 1024);

    // 检测指定字符并去除其中注释
    string str;
    str.assign(buf, 1024);
    RemoveComment(str);
  }

  // 关闭文件
  fin.close();

  return ;
}

int main()
{
  return 0;
}
