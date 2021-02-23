#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Vector 
{
  public:
    Vector(int size):_start(new int[size]){}

    // 列表初始化
    Vector(const initializer_list<int>& list)
      :_start(new int[list.size()])
    {
      int index = 0;
      for(auto& e : list)
      {
        _start[index++] = e;
      }

      cout << "Vector(const initializer_list<int>& list)" << endl;
    }

  private:
    int* _start;
    int* _end;
    int* _capacity;
};

class A
{
  public:
    A(int a, int b) :_a(a), _b(b) { cout << "A()" << endl; }
  private:
    int _a;
    int _b;
};

int main()
{
  // 多个对象的初始化列表
  Vector v{1, 2, 5, 6, 8, 9};

  // 单个对象的初始化列表(标准库默认支持)
  A a{1, 3};
  
//  // c++98 
//  int array[] = {1, 2, 5, 8};
//  int a = {1 + 3}; 
//  // vector<int> v{1, 4, 6};  C++98 不支持
//  
//  // c++11
//  int a1{3};
//
//  vector<int>  v{1, 4, 7, 10};
//  for(auto e : v)
//  {
//    cout << e << endl;
//  }
//
//  map<int, int> m{{1, 3}, {3, 6}, {0, 89}};
//  for(auto e : m)
//  {
//    cout << e.first << ":" << e.second << endl;
//  }


  return 0;
}
