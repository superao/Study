#include "Myset.h"
using namespace std;

int main()
{
  Set<int> s;
  s.Insert(10);
  s.Insert(1);
  s.Insert(0);
  s.Insert(10);
  s.Insert(19);
  s.Insert(21);
  s.Insert(8);

  for(auto e : s)
  {
    cout << e << endl;
  }

  // 测试查找
  Set<int>::iterator it = s.Find(8);
  // 这里的迭代器必须重载 operator* 才能实现想要的访问。
  cout << *it << endl;


  return 0;
}
