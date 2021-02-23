// 学习使用 C++11 中的类型推导
#include <iostream>
#include <vector>
#include <typeinfo>     // 类型推导
using namespace std;

int* fun()
{
  cout << "test decltype" << endl;

  return NULL;
}

int main()
{
  // 编译时期:
  // 1.类型推导
  int a = 10;
  int b = 10;
  auto c = a + b;
  cout << typeid(c).name() << endl;
  
  // 2.迭代器类型
  vector<int> v{1, 4, 6, 7, 0, 19, 2};
  auto it = v.begin();
  cout << typeid(it).name() << endl;
  while(it != v.end())
  {
    cout << *it << endl;
    it++;
  }
  

  // 运行时期(只有运行之后才能知道类型)
  // 1.表达式运行之后的类型推导
  decltype(10.00 + 10) nc;
  cout << typeid(nc).name() << endl;

  // 2.函数返回值的类型推导
  decltype(fun()) ret;
  cout << typeid(ret).name() << endl;

  return 0;
}
