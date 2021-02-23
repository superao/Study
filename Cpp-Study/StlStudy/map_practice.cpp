#include <iostream>
#include <map>
#include <string>
using namespace std;


// 模拟实现 value_type
template<class k, class v>
struct Pair  // Key/Value 键值对 
{
  Pair(const k& key = k(), const v& value = v()): first(key), second(value)  {} 
  k first;
  v second;
};
typedef Pair<class k, class v> value_type;


// 模拟实现 make_pair 函数模板
template <class k, class v>
inline pair<k, v> Make_pair(const k key, const v value)
{
  return pair<k, v> (key, value);
}


// 模拟实现 operator[]  等价于  (*((this->insert(make_pair(k,mapped_type()))).first)).second
// template<class k, class v>
// v& operator[](const k& key)
// {
//   pair<iterator, bool> tmp = insert(key, v());
//   return tmp.first->second;  
// }



// 练习使用 map 容器 (Key/Value 模型)
void Test()
{
  // 3 种插入方式
  map<string, string> m;
  m.insert(pair<string, string> ("sort", "排序"));
  m.insert(pair<string, string> ("apple", "苹果"));
  m.insert(pair<string, string> ("insert", "插入"));
  m.insert(pair<string, string> ("erase", "删除"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("vector", "向量"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("string", "字符串"));

  m.insert(Make_pair("hello", "您好"));

  // 插入 + 修改
  m["super"] = "超级的";

  map<string, string>::iterator it = m.begin();
  while(it != m.end())
  {
    // it->()->first;
    cout << it->first << ":" << it->second << endl;
    it++;
  }

  // 查找 + 删除
  map<string, string>::iterator pos = m.find("string");
  cout << pos->first << ":" << pos->second << endl;
  if(pos != m.end())
  {
    m.erase(pos);
  }

  // 修改
  m["string"] = "hello world!";

  for(auto& e : m)
  {
    cout << e.first << ":" << e.second << endl;
  }

  cout << m.count("sort") << endl;

}




// 练习使用 multiset 容器
void Test1()
{
  multimap<string, string> m;
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("sort", "排序"));
  m.insert(pair<string, string> ("apple", "苹果"));
  m.insert(pair<string, string> ("insert", "插入"));
  m.insert(pair<string, string> ("erase", "删除"));
  m.insert(pair<string, string> ("string", "字符串"));
  m.insert(pair<string, string> ("apple", "hello"));
  m.insert(pair<string, string> ("apple", "world"));

  // 返回中序中的第一个
  auto pos = m.find("apple");
  cout << pos->first << ":" << pos->second << endl;
 
  cout << "-----------------" << endl;


  for(auto& e : m)
  {
    cout << e.first << ":" << e.second << endl;
  }

  // 删除 string 并且返回删除的个数
  cout << m.erase("string") << endl;

  for(auto& e : m)
  {
    cout << e.first << ":" << e.second << endl;
  }

}


int main()
{
  Test1();
  return 0;
}
