// 为某个源代码文件去掉注释
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

// 字符状态定义
// 1. //    段注释(注意续行符)
// 2. /* */ 多行注释
// 3. " "   双引号模式
// 4. 正文信息

int flag = 4;             // 默认为正文信息

// 去除注释
void RemoveComment(ofstream& fout, char& cur, char& last)
{
  switch(flag)
  {
    case 4:                              // 既要存储正文字符又同时为每个字符定义状态
      {                                  // 判断当前字符与上一个字符的关系从而为每个字符定义状态
        if(cur == '/')                   // 有时可能当前无法判断，那么先进行储存，在下次的时候将会判断得出
        {
          if(last == '/')
            flag = 1;
        }
        else if(cur == '*')
        {
          if(last == '/')
            flag = 2;
        }
        else if(cur == '"')
        {
          fout << cur; 
          flag = 3;
        }
        else 
        {
          if(last == '/')            // 5/2 这种情况由于在上一次并没有处理到，因此在下一次遍历到2的时候将/进行写入
            fout << last;
          fout << cur;
          flag = 4;
        }

        last = cur;
        break;
      }
    case 3:
      {
        fout << cur;
        if(cur == '"')
          flag = 4;
        break;
      }
    case 2:
      {
        if(cur == '/' && last == '*')
        {
          flag = 4;
        }
        break;
      }
    case 1:
      {
        if(last != '\\' && cur == '\n')
        {
          last = '\0';                    // 更新last，防止下次读取某个字符后误判为 "/2" 这种情况
          flag = 4;
        }
        break;
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

  // 将文件指针偏移到文件开头
  fin.seekg(0, fin.beg);
  
  // 储存文件
  string filename = "./text.cpp";
  ofstream fout(filename);

  char cur;                      // 当前字符
  char last = '\0';              // 上一个字符

  // 读取数据
  while(!fin.eof())
  {
    fin.get(cur);

    // 为每个字符进行标记
    RemoveComment(fout, cur, last);
  }

  // 关闭文件
  fin.close();
  fout.close();
}

int main()
{
  string file = "./继承与组合.cpp";
  Readfile(file);

  return 0;
}
