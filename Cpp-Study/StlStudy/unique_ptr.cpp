// 在 auto_ptr 的基础上学习并实现 unique_ptr 智能指针
#include <memory>
#include <iostream>
using namespace std;
class Date
{
  public:
    int _year;
    int _month;
    int _day;

    ~Date()
    {
      cout << "~Date()" << endl;
    }
};

template<class T>
class Unique_Ptr
{
  public:
    // 实现RAII(资源获取立即进行初始化)
    Unique_Ptr(T* ptr = nullptr) :_ptr(ptr) {}
    ~Unique_Ptr()
    {
      if(_ptr)
        delete _ptr;
    }

    // 拷贝构造
    Unique_Ptr(Unique_Ptr& ap) = delete;
    // 赋值构造
    Unique_Ptr& operator=(Unique_Ptr& ap) = delete;

    // 实现指针的功能
    T& operator*()
    {
      return *_ptr;
    }

    T* operator->()
    {
      return _ptr;
    }

  private:
    T* _ptr;
};

int main()
{
  // 使用库中的 unique_ptr 对我们的Date对象指针进行管理
//  unique_ptr<Date> up(new Date);
//  up->_day = 100;
//  up->_month = 100;
//  (*up)._year = 100;
//  cout << up->_year << " " << up->_month << " " << up->_day << endl;
  //unique_ptr<Date> up1(up);
  //unique_ptr<Date> up2(new Date);
  //up2 = up;
  
  // 总结：unique_ptr 对对象的拷贝构造，赋值构造的解决方法就是将其删除，不让用户进行拷贝构造，赋值构造，
  // 从而解决了 auto_ptr 原指针悬空的问题，但是它的本质上是没有解决掉问题，只是在一定程度上回避了该问题。
  
  Unique_Ptr<Date> up(new Date);
  up->_day = 100;
  up->_month = 100;
  (*up)._year = 100;
  cout << up->_year << " " << up->_month << " " << up->_day << endl;
  //Unique_Ptr<Date> up1(up);
  //Unique_Ptr<Date> up2(new Date);
  //up2 = up;

  return 0;
}
