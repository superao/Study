#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

int main()
{
  // 4. 字符串修剪 trim(): 修剪字符串两端
  string str = "            string      str     ";
  cout << "str = " << str << endl;
  trim(str);             // 直接修剪原有字符串
  // trim_copy(str)      // 不修剪原有字符串
  cout << "修剪后:" << str << endl;
  
  // 修剪字符串左端
  string str1 = "            string      str     ";
  trim_left(str1);
  cout << "修剪后:" << str1 << endl;

  // 修剪字符串右端
  string str2 = "            string      str     ";
  trim_right(str2);
  cout << "修剪后:" << str2 << endl;

  // 以指定字符进行修剪 trim_if(); 
  string str3 = "#######*str*#######";
  struct is_flags
  {
    bool operator()(const char ch)
    { 
      return ch == '#';
    }
  };
  trim_if(str3, is_flags());
  cout << "修剪后:" << str3 << endl;

  // 5.字符串替换，删除
  string str4 = "hello Hello hello world!!";
  ireplace_first(str4, "hello", "boost");             // 用 boost 替换第一个 hello(改变原有字符串, _copy不改变字符串, i前缀忽略大小写)
  cout << str4 << endl;

  ireplace_all(str4, "hello", "HEEH");
  cout << str4 << endl;
  
  ireplace_last(str4, "!!", "##");
  cout << str4 << endl;
  
  erase_last(str4, "##"); 
  cout << str4 << endl;


  return 0;
}
