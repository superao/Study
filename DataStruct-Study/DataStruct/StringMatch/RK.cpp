// RK 算法字符串匹配
// 本质: 借助哈希值的比较省去很多没有意义的比较
#include <iostream>
#include <string>
using namespace std;

// 计算哈希值(按照字符的排列顺序)
int StrHash(string& p)
{
  int length = p.length();
  int hashcode = 0;
  for(int i = 0; i < length; ++i)
  {
    hashcode += (p[i] - 'a');
  }

  return hashcode;
}

// 增量计算下一个子串的哈希值
int NextStrHash(string& s, int hashcode, char ch)
{
  int newhashcode = hashcode - s[0] + ch;             // s[0] 表示旧字符串第一个字符
  return newhashcode;                                 // ch 表示新字符最后一个字符
}

// 字符比对
bool StrCompare(string& t, string& p)
{
  int tlength = t.length();
  int plength = p.length();
  for(int i = 0; i < plength && tlength == plength; ++i)
  {
    if(t[i] != p[i])
    {
      return false;
    }
  }
  
  return true;
}

// RK 算法
int RkMatch(string& t, string& p)
{
  int tlength = t.length();
  int plength = p.length();

  // 模式串哈希值
  int phashcode = StrHash(p);
  for(int i = 0; i <= tlength - plength; ++i)
  {
    // 切割子串
    string temp = t.substr(i, plength);
    cout << temp << endl;

    // 计算子串哈希值
    int hashcode = StrHash(temp);

    // 哈希值相同后，逐个字符进行比对
    if(hashcode == phashcode && StrCompare(temp, p))
    {
      return i;              // 当前子串的下标   
    }
  }

  return -1;
}

int main()
{
  // 测试
  string t = "abcdefghaaab";
  string p = "aaab";

  cout << RkMatch(t, p) << endl;

  return 0;
}
