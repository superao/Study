#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s = "abc";
  cout << s.size() << endl;         // 不包含反斜杠0的长度
  cout << s[s.size()] << endl;      // 表示 反斜杠0 
  return 0;
}
