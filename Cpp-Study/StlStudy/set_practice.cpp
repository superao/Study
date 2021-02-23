#include <iostream>
#include <set>
#include <string>
using namespace std;

// set 容器
void Test()
{
  // insert
  set<int> s;
  s.insert(10);
  s.insert(20);
  s.insert(1);
  s.insert(23);
  s.insert(5);
  s.insert(1);
  s.insert(1);


  // 迭代器遍历(中序遍历)
  set<int>::iterator it = s.begin();
  while(it != s.end())
  {
    cout << *it << endl;
    it++;
  }


  // 查找
  set<int>::iterator pos = s.find(23);
  if(pos != s.end())
  {
    s.erase(pos);
  }
  s.erase(20);
  
  // 迭代器遍历(中序遍历)
  set<int>::iterator it1 = s.begin();
  while(it1 != s.end())
  {
    cout << *it1 << endl;
    it1++;
  }

}

// multiset 容器
void Test1()
{
  multiset<int> s;
  s.insert(10);
  s.insert(1);
  s.insert(12);
  s.insert(14);
  s.insert(5);
  s.insert(6);
  s.insert(5);
  s.insert(5);
  s.insert(5);

  for(auto& e : s)
  {
    cout << e << endl;
  }
  
  // 统计 5 出现了几次
  cout << s.count(5) << endl;
  
  // 删除元素 5, 并统计删除的个数 
  cout << s.erase(5) << endl;

  // 查找元素
  auto pos = s.find(14);
  if(pos != s.end())
  {
    cout << *pos << endl;
  }
}

int main()
{
  Test1();
  return 0;
}
