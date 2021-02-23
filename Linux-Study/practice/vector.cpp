#include <iostream>
#include <vector>
#include <list>
using namespace std;
// 迭代器失效问题
int main()
{
  // 随便插入几个元素 
  vector<int> v;
  for(int i = 0; i < 10; ++i)
  {
    v.push_back(i);
  }

  // 查找，插入
  vector<int>::iterator it = v.begin() + 9;                    // 数组中第10个元素
  cout << *it << endl;
  v.insert(it, 10);
  cout << *it << endl;
  cout << *(it + 1) << endl;
  
  // 查找，删除
  vector<int>::iterator it1 = v.begin() + 2;
  cout << *it1 << endl;
  v.erase(it1);
  cout << *it1 << endl;

  // 结论：
  // vector在插入，删除结束之后迭代器位置不会变，但是由于它需要挪动数据，因此原来迭代器的位置里面存放的是别的值。
  // 因此，在插入删除元素之后需要更新迭代器的位置。
  return 0;
}
