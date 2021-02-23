// 字符串匹配(暴力匹配)
#include <iostream>
#include <string>
using namespace std;

int strmatch(string& t, string& p)
{
  // 获取主串和模式串的长度
  int tlength = t.length();
  int plength = p.length();

  // 主串与模式串的下标
  int i = 0; 
  int j = 0;
  while(i < tlength && j < plength)
  {
    if(t[i] == p[j])
    {
      // 当前字符匹配成功
      i++;
      j++;
    }
    else 
    {
      // 当前字符匹配失败
      j = 0;
      i = i - j + 1;
    }
  }

  // 模式串已经到达末尾
  if(j == plength)
    return i - j;
  else 
    return -1;
}


int main()
{
  string a = "aacdaaaabcdef";
  string b = "bcd";

  cout << "匹配到的下标为: " << strmatch(a, b) << endl;
  return 0;
}
