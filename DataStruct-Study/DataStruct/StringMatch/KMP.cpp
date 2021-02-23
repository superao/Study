// KMP 字符串匹配
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

// 构建 Next 数组
int* BulidNext(string& p)
{
  int* next = (int*)malloc(p.length());

  // 设置哨兵
  next[0] = -1;

  // 递推求解
  int i = 0;       // next 数组下标
  int t = -1;      // t 为数组中的数据
  while(i >= 0 && i < (int)p.length())
  {
    if(t < 0 || p[i] == p[t])
    {
      next[++i] = ++t;        // next[i + 1] = next[i] + 1; 
    }
    else 
    {
      t = next[t];            // 向前递推，直到找到相同的字符
    }
  }

  // 测试 next 数组
  for(int i = 0; i < (int)p.length(); ++i)
  {
    cout << next[i] << endl;
  }

  return next;
}

// KMP 字符串匹配
int KmpMatch(string& t, string& p)
{
  // 创建 Next 表
  int* next = BulidNext(p);
  
  // 定义主串与模式串的下标指针
  int i = 0;
  int j = 0;
  int tlength = t.length();
  int plength = p.length();

  // 匹配
  while(i < tlength && j < plength)
  {
    if(j < 0 || t[i] == p[j])                      // j < 0 表示主串的字符与通配符进行匹配
    {
      ++i;
      ++j;
    }
    else 
    {
      // 当发生失配之后，主串不在回溯
      j = next[j];
    }
  }

  if(j >= plength)
  {
    // 匹配成功
    return i - j;
  }
  else 
    return -1;
}

int main()
{
  string t = "chinchinchilla";
  string p = "chinchilla";

  cout << "匹配成功的下标为:" << KmpMatch(t, p) << endl;

  return 0;
}
