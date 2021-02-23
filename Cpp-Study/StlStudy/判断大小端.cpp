#include <iostream>
using namespace std;

// 方法 1 :
int Fun()
{
  int a = 10;
  char ch = 0xff;

  return ch & a;
}

// 方法 2 :
int Fun2()
{
  int a = 10;

  return (char)a;
}

// 方法 3 :
int Fun3()
{
  union {
    int a;
    char b;
  }un;
  un.a = 10;

  return un.b;
}
int main() 
{

  cout << Fun() << endl;
  cout << Fun2() << endl;
  cout << Fun3() << endl;
  return 0;
}
