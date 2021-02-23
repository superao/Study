// 学习了解RAII，学习并实现智能指针
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
class Auto_Ptr
{
  public:
    // 实现RAII
    Auto_Ptr(T* ptr = nullptr) :_ptr(ptr) {}
    ~Auto_Ptr()
    {
      if(_ptr)
        delete _ptr;
    }

    // 拷贝构造(管理权转移)
    Auto_Ptr(Auto_Ptr& ap)
      :_ptr(ap._ptr) // 转移管理权
    {
      ap._ptr = nullptr;
    }

    // 赋值构造(管理权转移)
    Auto_Ptr& operator=(Auto_Ptr& ap)
    {
      if(&ap != this)
      {
        // 释放自身的资源(防止内存泄漏)
        if(_ptr)
          delete _ptr;

        // 转移管理权
        _ptr = ap._ptr;
        ap._ptr = nullptr;
      }

      return *this;
    }

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

  // 普通指针
//  Date* pd = new Date;
//  pd->_day = 15;
//  pd->_month = 9;
//  pd->_year = 2019;
//  cout << pd->_year << " " << pd->_month << " " << pd->_day << endl;
//  delete pd;

//  // 智能指针auto_ptr
//  Auto_Ptr<Date> p(new Date);
//  p->_day = 10;
//  p->_month = 100;
//  p->_year = 2100;
//  cout << p->_year << " " << p->_month << " " << p->_day << endl;
//
  // 使用库中的auto_ptr
  auto_ptr<Date> ap(new Date);
  ap->_day = 11;
  ap->_month = 210;
  ap->_year = 1111;
  cout << ap->_year << " " << ap->_month << " " << ap->_day << endl;

  auto_ptr<Date> ap1(ap);
  ap1->_day = 1222;
  cout << ap1->_year << " " << ap1->_month << " " << ap1->_day << endl;
  // ap->_day = 100000;   // 指针已经悬空，导致野指针访问。

  auto_ptr<Date> ap2(new Date);
  ap2 = ap1;
  ap2->_day = 2222;
  // ap1->_day = 00000;      // 原来的指针指针也悬空，
  cout << ap2->_year << " " << ap2->_month << " " << ap2->_day << endl;

//  总结：auto_ptr 虽然可以利用RAII的思想进行指针的管理，但是在拷贝构造的时候，赋值构造的时候,
//  它的解决思路是 "管理权转移的一种思想，这样的话，导致原来的指针悬空，从而会导致野指针的访问"

//  // 使用自己实现的auto_ptr
//  Auto_Ptr<Date> AP(new Date);
//  AP->_day = 2019;
//  AP->_month = 2019;
//  (*AP)._year = 2019;
//  cout << AP->_day << " " << AP->_month << " " << AP->_year << endl;
//
//  Auto_Ptr<Date> AP1(AP);
//  AP1->_day = 201;
//  AP1->_month = 201;
//  (*AP1)._year = 201;
//  cout << AP1->_day << " " << AP1->_month << " " << AP1->_year << endl;
//  // AP->_day = 1;   // 悬空
//
//  Auto_Ptr<Date> AP2(new Date);
//  AP2 = AP1;
//  AP2->_day = 10000;
//  // AP1->_day = 10; // 悬空
//  cout << AP2->_day << " " << AP2->_month << " " << AP2->_year << endl;

  return 0;
}
