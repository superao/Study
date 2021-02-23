#include <iostream>
#include <assert.h>
#include <string.h>
#include <stdio.h>


class String{

// 迭代器部分的实现
public:

  typedef char* iterator;                  // 普通迭代器
  typedef const char* const_iterator;      // const 迭代器

  // 迭代器的相关函数
  iterator begin()
  {
    return _str;
  }

  iterator end() 
  {
    return _str + _size;
  }

  const_iterator cbegin() const
  {
    return _str;
  }

  const_iterator cend() const
  {
    return _str + _size;
  }

 // ------------------------------------------------------------ 
//  注释掉的代码只考虑了空间
//  // 构造函数(传统写法): 自己开空间,自己拷数据
//  String(const char* str = "")
//  {
//    if(str != NULL) 
//    {
//      // 1.开空间
//      _str = new char[strlen(str) + 1];
//
//      // 2.拷数据
//      memcpy(_str, str, strlen(str) + 1);
//
//    }
//  }
//
//  // 析构函数
//  ~String()
//  {
//    if(_str)
//    {
//      delete [] _str;
//      _str = NULL;
//    }
//  }
//
//
//  // 拷贝构造函数(深拷贝)
//  // s1(s2);
//  String(const String& s)
//  {
//    // 1.开新的空间
//    this->_str = new char[strlen(s._str) + 1];
//    
//    // 2.拷数据
//    memcpy(_str, s._str, strlen(s._str) + 1);
//  }
//
//  // 赋值运算符的重载(深拷贝)
//  // s1 = s2;
//  String& operator=(const String& s)
//  { 
//    // 注意:自己给自己赋值的话,就会野指针,其次当前只考虑 字符串 .
//    if(this != &s) 
//    {
//      // 1.先释放原来的空间
//      delete [] _str;
//
//      // 2.申请新的空间
//      _str = new char[strlen(s._str) + 1];
//
//      // 3.拷数据
//      memcpy(_str, s._str, strlen(s._str) + 1);
//    }
// 
//    return *this;
//  }
 
 // ---------------------------------------------------------------


// // ***************************************************************
//
//  // 现代写法:麻烦的事情让别人去做(复用)
//  // 构造函数(需要自己写)
//  String(const char* str = "")
//    :_str(NULL) // *** 特别注意列表初始化的好处 *** // 
//  {
//    if(str != NULL) 
//    {
//      // 1.开空间
//      _str = new char[strlen(str) + 1];
//
//      // 2.拷数据
//      memcpy(_str, str, strlen(str) + 1);
//    }
//  }
//
//  ~String()
//  {
//    if(_str)
//    {
//      delete [] _str;
//      _str = NULL;
//    }
//  }
//
//  // 拷贝构造函数
//  // s1(s2)
//  String(const String& s)
//    :_str(NULL)  // 这里必须进行列表初始化, 否则的话,下面的交换就会出现问题,导致野指针问题。
//  {
//    String tmp(s._str);
//    Swap(tmp);   
//  }
//
//  // 赋值运算符的重载
//  String& operator=(const String& s) 
//  {
//    String temp(s);
//    Swap(temp);
//
//    return *this;
//  }
// // ***************************************************************

  // C 风格字符串
  char* C_str()
  {
    return _str;
  }

  void Swap(String& s) 
  {
    std::swap(this->_str, s._str);
    std::swap(this->_size, s._size);
    std::swap(this->_capacity, s._capacity);
  }

  size_t Size()
  {
    return _size;
  }

  size_t Capacity()
  {
    return _capacity;
  }

  // 模拟实现 String 类
//  String(const char* str = "")
//    :_str(new char[strlen(str) + 1])
//    ,_size(0)
//    ,_capacity(0)
//  {
//    // 当字符串不为空时,再进行拷贝,否则,拷贝的是无效的信息
//    if(str)
//    {
//      // 拷贝数据
//      memcpy(_str, str, strlen(str) + 1);
//      _size = strlen(str);
//      _capacity = strlen(str);
//    }
//  }

  // 更加简单的写法:
  String(const char* str = "")
    :_str(NULL)
    ,_size(0)
    ,_capacity(0)
    // 这里需要初始化,小心 reserve 时出错.
  {
    _size = strlen(str);
    reserve(_size);
    if(str)
    {
      memcpy(_str, str, _size + 1);
    }
  }

  ~String()
  {
    if(_str)
    {
      delete [] _str;
    }
  }

  // 拷贝构造(复用代码)
  String(const String& s) 
    :_str(NULL)
  {
    String tmp(s._str);
    Swap(tmp);       // tmp.Swap(*this);
  }

  // 赋值运算符的重载
  String& operator=(String s)
  {
    Swap(s);

    return *this;
  }

  // 可读可写
  char operator[](size_t index)
  {
    return _str[index];
  }

  // 只读
  char operator[](size_t index) const
  {
    return _str[index];
  }

  void reserve(size_t n = 0)
  {
    // 说明:当我们在申请空间时,系统为了防止内存碎片化,通常根据自己的机制,做了一些处理,
    // 我们为了模仿 String 类的处理方式,我们以 8 作为基数来进行处理.
   
    if(n > Capacity() || n == 0)
    {

      if(n % 8 != 0) 
      {
        n = (n / 8 + 1) * 8;
      }
      else
      {
        n = n + 8;
      }

      // 预留一个作为反斜杠0
      char* newstr = new char[n];
      if(_str)
      {
        strcpy(newstr, _str);
        delete [] _str;
      }
      _str = newstr;
      _capacity = n - 1;

    }
  }

  void resize(size_t n, char ch = '\0')
  {
    if(n <= Size())
    {
      _size = n;
      _str[_size] = '\0';
    }
    else 
    {
      reserve(n);

      for(size_t i = Size(); i < n; i++) 
      {
        _str[i] = ch;
        _size++;
      }

      _str[_size] = '\0';

    }
  }

  String& operator+=(const char ch)
  {

    // 如果内存不够了,直接扩容两倍
    if(_size >= _capacity) 
    {
      // 扩容
      reserve(_capacity * 2);
    }

    // 放数据
    _str[_size++] = ch;
    _str[_size] = '\0';

    return *this;
  }

  String& operator+=(const char* str) 
  {

    // 如果容量不够,那么将按照需求扩容
    size_t newsize = _size + strlen(str);
    if(newsize > _capacity) 
    {
      reserve(newsize);
    }

    // 放数据
    strcpy(_str + _size, str);

    _size = newsize;

    return *this;
  }

  String operator+(const char* str)
  {
    String tmp(*this);
    tmp += str;
    return tmp;
  }

  String operator+(const char ch)
  {
    String tmp(*this);
    tmp += ch;
    return tmp;
  }

  void PushBack(const char ch) 
  {
    *this += ch;
  }

  void Append(const char* str)
  {
    *this += str;
  }

  void Append(const char ch)
  {
    *this += ch;
  }

  String& Insert(size_t pos, const char ch)
  {
    assert(pos <= _size);
    size_t newsize = _size + 1;
    if(newsize > _capacity)
    {
      // 增容
      reserve(_capacity * 2);
    }

    // 挪数据(注意这里的 size_t 特别坑)
    for(int i = _size - 1; i >= (int)pos; i--)
    {
      _str[i + 1] = _str[i];
    }

    // 放数据
    _str[pos] = ch;
    _size++;
    

    return *this;
  }
  String& Insert(size_t pos, const char* str)
  {
    assert(pos <= _size);
    size_t newsize = _size + strlen(str);
    if(newsize > _capacity)
    {
      reserve(newsize);
    }

    // 挪数据
    for(int i = _size - 1; i >= (int)pos; i--)
    {
      _str[i + strlen(str)] = _str[i];
    }

    // 放数据
    memcpy(_str + pos, str, strlen(str));
    _size += strlen(str);

    return *this;
  }

  String& Erase(size_t pos, size_t npos)
  {
   assert(pos < _size);
   if(npos >= _size - pos)
   {
     _str[pos] = '\0';
     _size = pos;
   }
   else 
   {
     // 挪数据
     for(int i = pos; i <(int)_size; i++)
     {
        _str[i] = _str[i + npos];
     }
     _size -= npos;
   }

   return *this;
  }

  size_t Find(char ch, size_t pos = 0)
  {
    assert(pos < _size);
    // 遍历字符串即可
    for(int i = pos; i <(int)_size; i++) 
    {
      if(_str[i] == ch)
      {
        return i;
      }
    }

    return npos;
  }

  size_t Find(const char* str, size_t pos = 0)
  {
    assert(pos < _size);
    const char* ret = strstr(_str + pos, str);
    if(ret != NULL)
    {
      return ret - _str;
    }
    else
    {
      return npos;
    }
  }

  bool operator<(String& s)
  {
    size_t i = 0;
    size_t j = 0;
    while(i < _size && j < s._size)
    {
      if(s._str[j] > _str[i])
      {
        return true;
      }
      else if(s._str[j] < _str[i])
      {
        return false;
      }

      i++;
      j++;
    }

    if(j < s._size)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  // 其他比较的函数思路相似.
private:

  char* _str;
  size_t _size;
  size_t _capacity;

  static size_t npos;
};

// 初始化静态成员变量
size_t String::npos = -1;
