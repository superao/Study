// 利用 "适配器模式" 实现 "栈"(先进后出)
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

//       参数类型    适配容器(用一个容器来适配出来所需要的容器)
template<class T, class Container = deque<T> >
class Stack 
{
  public:
    bool empty()
    {
      return _con.empty();
    }

    int size()
    {
      return _con.size();
    }

    T& top()
    {
      return _con.back();
    }

    void push(const T& e)
    {
      _con.push_back(e);
    }

    void pop()
    {
      _con.pop_back();
    }

  private:
    Container _con; // 容器(可以调用原来容器的成员函数)

};

