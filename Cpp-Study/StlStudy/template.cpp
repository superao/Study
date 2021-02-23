// 模板进阶的学习
// 1.学习使用非类型的模板参数
// 2.模板的特化(类模板的特化，函数模板的特化)
// 3.模板的分离编译问题

#include <iostream>
#include "template.h"
using namespace std;

void ArryTest()
{
  Array<int, 10> a;
  a.show();

  Array<double, 1000> a1;
  a1.show();

  // Array<int, 10.3> a2; 非类型模板参数必须是整形家族

}


void FunTest()
{
  int a = 10; 
  int b = 20;
  cout << Isequal(a, b) << endl;

  // 这样的话，其实比较的是两个地址是否相同，并不是达到了真正的本意，因此，我们需要对字符串类型需要特殊处理才能比较大小i(函数特化)。
  char* str1 = "hello";
  char* str2 = "hello";
  Isequal(str1, str2);
}

void ClassTest()
{
  MyClass<char, char> c1;
  c1.show();

  MyClass<int, int> c2;
  c2.show();

  MyClass<int, char> c3(20, 'b');
  c3.show();

  MyClass<char*, char*> c4;
  c4.show();

  // 总结:
  // 对于类模板来说，偏特化是对模板参数的一些限制(两种限制方式)，全特化是对模板参数的确定化。
}


int main()
{

  // Fun<int, int>(); 
  // Fun<char, char>();
  // Fun<char, int>();

  // 总结:
  // 函数模板在示例化的时候，最先匹配的是类型最匹配的，如果没有，则编译器才会进行示例化推演

  // FunTest();
  

  ClassTest();

  return 0;
}
