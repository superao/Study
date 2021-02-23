#include <iostream>
#include <list>
using namespace std;
// list 的迭代器失效问题

int main()
{
  list<int> l;
  for(int i = 1; i < 10; ++i)
  {
    l.push_back(i);
  }

  // 输出头部结点
  auto it = l.begin();
  cout << *it << endl;

  // 插入元素(没有引起迭代器失效)
  l.insert(it, 10000);
  cout << *it << endl;
  cout << *l.begin() << endl;

  // 删除元素
  l.erase(it);
  cout << *it << endl;

  // 总结：
  // list插入元素之后，不会引起迭代器失效，而删除元素会引起迭代器失效问题。
  // 由于删除元素之后，迭代器所指向的空间已经被释放掉了，无法继续访问，因此迭代器 "失效"。

  return 0;
}
