#include <iostream>
#include "hash_open.h"
using namespace std;

void Test()
{
  HashTable<int, int> tab;
  tab.Insert(10);
  tab.Insert(1);
  tab.Insert(15);
  tab.Insert(3);
  tab.Insert(100);
  tab.Insert(1000);
  tab.Insert(33);

  auto it = tab.begin();
  while(it != tab.end())
  {
    cout << *it << endl;
    ++it;
  }
}



int main()
{
  Test();
  return 0;
}
