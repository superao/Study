#include "string.h"
#include <string>
using namespace std;

void Test()
{

  String s1;
  cout << s1.C_str() << endl;

  String s2("Hello World, Change World!");
  cout << s2.C_str() << endl;

  s1 = s2;
  cout << s1.C_str() << endl;

  String S(s2);
  cout << S.C_str() << endl;

  cout << "我是分割线---------------" << endl;

  string s3;
  cout << s3.c_str() << endl;

  string s4("哈哈哈，呵呵呵，哦哦哦");
  cout << s4.c_str() << endl;

}

void Test1()
{

  String s1;
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;

  String s2("superao");
  cout << s2.Size() << endl;
  cout << s2.Capacity() << endl;
  cout << s2.C_str() << endl;

  String::iterator it = s2.begin();
  while(it != s2.end())
  {
    *it = 'H';
    it++;
  }

  for(size_t i = 0; i < s2.Size(); i++) 
  {
    cout << s2[i] << " ";
  }
  cout << endl;

}

void Test2()
{
  string s1("1234");
  s1.reserve(3);
  cout << s1.size() << endl;
  cout << s1.capacity()<< endl;
  cout << s1.c_str() << endl;
  s1.reserve(10);
  cout << s1.size() << endl;
  cout << s1.capacity()<< endl;
  cout << s1.c_str() << endl;

  cout << "----------------------" << endl;
  String S1;
  cout << S1.Size() << endl;
  cout << S1.Capacity() << endl;
  S1.reserve(6);
  cout << S1.Size() << endl;
  cout << S1.Capacity() << endl;
  S1.resize(20, 'H');
  cout << S1.Size() << endl;
  cout << S1.Capacity() << endl;
  cout << S1.C_str() << endl;

  cout << "----------------------" << endl;

  String S2("hehe,haha,666");
  cout << S2.Size() << endl;
  cout << S2.Capacity() << endl;
  cout << S2.C_str() << endl;
  // S2.resize(4);
  cout << S2.Size() << endl;
  cout << S2.Capacity() << endl;
  cout << S2.C_str() << endl;
  S2.resize(20,'o');
  cout << S2.Size() << endl;
  cout << S2.Capacity() << endl;
  cout << S2.C_str() << endl;


}

void Test3()
{

  String s1("hehejun");
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;
  s1.PushBack('1');
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;
  s1.Append("hello,world");
  s1.Append('!');
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;
  s1 = s1 + "wenzihao";
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;


}

void Test4()
{
  String s1("hehedfgdfhdfh");
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;
  s1.Insert(0,'/');
  cout << s1.C_str() << endl;
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  s1.Insert(0, "sd;hfishfosdihpihvoidhfspobsd");
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;
  s1.Erase(40,30000);
  cout << s1.Size() << endl;
  cout << s1.Capacity() << endl;
  cout << s1.C_str() << endl;

}

void Test5()
{
  String s1("haha,hehe");
  cout << s1.Find(',') << endl;
  cout << s1.Find("hehe") << endl;

  String s2("hah");
  cout << (s2 < s1) << endl; 
}

int main() 
{

  Test5();

  return 0;
}
