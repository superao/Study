// 为了实现 map set 容器(红黑树)打下基础
// 实现 Key / Value 模型的储存
#include <iostream>
#include <string>
#include "BST.h"
using namespace std;

void Test()
{
  BSTree<int> bt;
  bt.Insert(10);
  bt.Insert(1);
  bt.Insert(0);
  bt.Insert(12);
  bt.Insert(5);
  bt.Insert(7);
  bt.Insert(199);
  bt.Insert(200);
  bt.Insert(160);
  bt.Insert(10);
  bt.Insert(10);
  bt.Insert(10);

  auto f = bt.Find(12);
  cout << f->_key << endl;
  auto f1 = bt.Find(0);
  cout << f1->_key << endl;
  auto f2 = bt.Find(1);
  cout << f2->_key << endl;
  auto f3 = bt.Find(10);
  cout << f3->_key << endl;

  auto f4 = bt.Find(100);
  cout << f4 << endl;

  cout << "---------------------" << endl;

  bt.InOrder();

  cout << "---------------------" << endl;

  bt.Erase(10);
  bt.Erase(1);
  bt.Erase(0);
  bt.Erase(12);
  bt.Erase(5);
  bt.Erase(7);
  bt.Erase(199);
  bt.Erase(200);
  bt.Erase(160);
  bt.Erase(10000);

  bt.InOrder();

}

int main()
{
  Test();
  return 0;
}
