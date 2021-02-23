// 学习使用Boost库中的常用字符串分割函数
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;

int main()
{
  // 1. 字符串拼接函数join();
  vector<string> v;
  v.push_back("hello");
  v.push_back("world!");
  v.push_back("olleh");
  string str = boost::join(v, "hello boost!");
  cout << "str = " << str << endl;
  
  // 2. 满足判断式的字符串拼接函数join_if()
  struct is_contain_ll
  {
    bool operator()(const string& str)
    {
      return boost::contains(str, "ll");
    }
  };
  string str_if = boost::join_if(v, "##", is_contain_ll());
  cout << "str_if = " << str_if << endl;

  // 3. 字符串分割函数 split() 和 is_any_of()
  // is_any_of(): 表示所传入字符串中任意一个字符
  string s = "hello#world#hehe*haha*hi";
  vector<string> vstr;                          
  boost::split(vstr, s, boost::is_any_of("#*"));
  for(auto e : vstr)
  {
    cout << e << endl;
  }

  // 4. 字符串查找
  string find_str = "hello world, i am a Student. olleh dlrow";
  // 查找第一次出现的字符串 find_first();
  boost::iterator_range<string::iterator> rge;
  rge = boost::find_first(find_str, "l");
  cout << rge << endl;
  // 定位区间
  cout << "所查字符串区间:" << rge.begin() - find_str.begin() << "," << rge.end() - find_str.begin() << endl;

  // ifind_first(): i开头表示忽略大小写
  boost::iterator_range<string::iterator> rge1;
  rge = boost::ifind_first(find_str, "student");
  cout << "rge = " << rge << endl;
  cout << "所查字符串区间:" << rge.begin() - find_str.begin() << "," << rge.end() - find_str.begin() << endl;
  
  // 查找最后一次出现的字符串 find_last();
  rge = boost::find_last(find_str, "l");
  cout << "rge = " << rge << endl;
  cout << "所查字符串区间:" << rge.begin() - find_str.begin() << "," << rge.end() - find_str.begin() << endl;

  // 查找第几次出现的字符串 find_nth();
  rge = boost::find_nth(find_str, "l", 3);
  cout << "rge = " << rge << endl;
  cout << "所查字符串区间:" << rge.begin() - find_str.begin() << "," << rge.end() - find_str.begin() << endl;

  // 查找前几个出现的字符串 find_head();
  rge = boost::find_head(find_str, 3);
  cout << "rge = " << rge << endl;
  cout << "所查字符串区间:" << rge.begin() - find_str.begin() << "," << rge.end() - find_str.begin() << endl;
  
  // 查找所有指定的字符串 find_all();
  vector<string> v_findall;
  boost::find_all(v_findall, find_str, "l");
  cout << "查询结果:" << v.size() << endl;
  cout << "遍历结果:" << endl;
  for(auto& e : v)
  {
    cout << e << endl;
  }

  return 0;
}
