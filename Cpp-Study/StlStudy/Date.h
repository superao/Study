#pragma once
#include <iostream>

using std::cout;
using std::endl;

// 定义一个 Data 类,学习类中的 6 的函数
class Date {

// 规范:
// 将成员函数设置为共有的,给外界提供接口,供外界使用.
public:

  // 返回该年该月的天数
  int GetMonthDay(int year, int month) {

    int Day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(year % 4 == 0 && 
        year % 100 != 0 &&
        year % 400 == 0 && 
        month == 2) {

      return 29;
    }

    return Day[month];
  }


  // 1.构造函数(初始化成员变量)
  Date(int year = 1900, int month = 1, int day = 1) {

    if(year >= 1900
        && month > 0 && month < 13
        && day > 0 && day <= GetMonthDay(year,month)){
      _year = year;
      _month = month;
      _day = day;
    }
    else {

      cout << "非法日期~~" << endl;
    }
  }
  // 2.析构函数(清理资源)
  // 由于该类没有开辟空间,不需要清理资源,所以(不需要写)或系统自动生成一个就OK.
  ~Date() {

  }

  // 3.拷贝构造函数(初始化对象时,拷贝资源)
  // 注意:这里必须是"引用做参数",否则,就会陷入无限递归之中.
  // Date b2(b1);
  Date(const Date& d) {

    _year = d._year;              // this->_year = d._year;
    _month = d._month;
    _day = d._day;
  }


  // 4.赋值运算符重载
  // 传引用的的好处,少了两次拷贝构造函数的调用
  // (分别是:1.传参时. 2.返回值时.)
  Date& operator=(const Date& d) {

    _year = d._year;              // this->_year = d._year;
    _month = d._month;
    _day = d._day;

    return *this;
  }

  // 注意:如果是双目运算符,只写一个参数,由于还有一个隐含的 this .
  // 并且用 const Date& 的原因是,在该函数体内没有地方需要修改它的值,所以用 const,这样的话 const 类型可以调用
  // 非 const 类型也可以调用.
  // 其次用引用的话,可以少一次赋值拷贝的过程.
  bool operator==(const Date& d) const;
  bool operator!=(const Date& d) const;
  bool operator>(const Date& d) const;
  bool operator>=(const Date& d) const;
  bool operator<(const Date& d) const;
  bool operator<=(const Date& d) const;


  Date& operator++();      // 前置++
  Date operator++(int);    // 后置++

  Date& operator--();
  Date operator--(int);

  Date operator+(int day) const;
  Date operator-(int day) const;
  int operator-(const Date& d) const;

  Date& operator+=(int day);

  Date& operator-=(int day);


  void Print() {

    cout << _year << "-" << _month << "-" << _day << endl;
  }


// 规范:
// 将成员变量设置为私有的,只能通过合法途径来访问它,防止外界对其造成破坏.
private:
  int _year;
  int _month;
  int _day;

};
