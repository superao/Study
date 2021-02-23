#include "Date.h"
#include <iostream>

using std::cout;
using std::endl;

// 重载相等号
bool Date::operator==(const Date& d) const{

  return this->_year == d._year 
    && this->_month == d._month 
    && this->_day == d._day;
}

// 重载不等号
bool Date::operator!=(const Date& d) const {

  return !(*this == d);
}

// 重载大于号
bool Date::operator>(const Date& d) const{

  // 如果 year 大于那么直接返回 true.
  if(this->_year > d._year) {

    return true;
  }
  // 如果相等判断月份
  else if(this->_year == d._year){

    if(this->_month > d._month) {

      return true;
    }
    // 如果年月都相等，那么判断天
    else if(this->_month == d._month) {

      if(this->_day > d._day) {

        return true;
      }
    }
  }

  return false;
}

// 重载大于等于号
bool Date::operator>=(const Date& d) const{

  // 代码复用,但是在服用的时候也要注意效率问题。
  if(*this == d || *this > d) {

    return true;
  }
  else {

    return false;
  }
}

// 重载小于号
bool Date::operator<(const Date& d) const{

  if(*this >= d) {

    return false;
  }
  else {

    return true;
  }
}

// 重载小于等于号
bool Date::operator<=(const Date& d) const{

  if(*this < d || *this == d) {

    return true;
  }
  else {

    return false;
  }
}

// 重载加等号
// 2019-5-13
// +2
// +24
// +1000
Date& Date::operator+=(int day) {

  if(day < 0) {

    *this -= -day;
  }
  else {

  // 先将 天数 加到日期的天数上,然后再循环进位.
  _day = _day + day;

  while(_day > Date::GetMonthDay(_year,_month)) {

    // 减去当月的天数。
    _day = _day - Date::GetMonthDay(_year,_month);

    // 月份进一位。
    if(_month == 12) {

      _year += 1;
      _month = 1;
    }

    _month += 1;

  }

  }

  return *this;
}

// 重载加号
Date Date::operator+(int day) const{

  // 创建临时的对象,方便最后返回
  Date ret;
  ret = *this;

  // 复用
  ret += day;

  return ret;
}

// 重载前置++
Date& Date::operator++() {

  *this += 1;

  return *this;
}

// 重载后置++
Date Date::operator++(int) {

  Date ret = *this;

  *this += 1;

  return ret;
}


// 重载减等号
// 2019-5-13
// -10
// -35
// -1000
Date& Date::operator-=(int day) {

  if(day < 0) {

    *this += -day;
  }
  else {

  // 先在原有日期的 天数 上,减掉 day.
  _day = _day - day;

  // 如果天小于 1 那么就借位,直到满足条件.
  while(_day <= 0) {

    // 保存上一个月的月份
    int last_month = 0;

    if(_month == 1) {

      _year -= 1;
      last_month = 12;
      _month = 12;
    }
    else {

      last_month = _month - 1;
      _month -= 1;
    }

    _day = _day + Date::GetMonthDay(_year, last_month);

  }

  }

  return *this;
}

// 重载减号
Date Date::operator-(int day) const{

  Date ret = *this;

  ret -= day;

  return ret;
}

// 重载前置--
Date& Date::operator--() {

  *this -= 1;

  return *this;
}

// 重载后置--
Date Date::operator--(int){

  Date ret = *this;

  *this -= 1;

  return ret;
}

// 重载日期减日期
int Date::operator-(const Date& d) const {

  // 思路:将其中一个小的日期作为基数,设置一个计数器,直到加到另一个大的日期为止。
  int count = 0;
  Date temp1;
  Date temp2;
  if(*this > d) {

    temp1 = d;
    temp2 = *this;
  }
  else {

    temp1 = *this;
    temp2 = d;
  }

  while(temp1 != temp2) {

    temp1++;
    count++;
  }

  return count;
}
