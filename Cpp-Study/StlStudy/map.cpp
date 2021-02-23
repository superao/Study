#include "Mymap.h"
#include <string>
#include <vector>

void Map_Test()
{
  Map<int, int> m;
  m.Insert(make_pair(1, 2));
  m.Insert(make_pair(2, 3));
  m.Insert(make_pair(5, 6));
  m.Insert(make_pair(7, 9));
  m.Insert(make_pair(9, 0));

  for(auto& e : m)
  {
    cout << e.second << endl;
  }

  // 利用 [] 来统计次数
  string vs[] = {"sort", "insert", "hello", "sort", "insert"};
 
  Map<string, int> mscount;
  for(const auto& e : vs)
  {
    mscount[e]++;
  }

  for(const auto& e : mscount)
  {
    cout << e.first << ":" << e.second << endl;
  }

  Map<int, int>::iterator it = m.Find(make_pair(7, 9));
  cout << it->first << ":" << it->second << endl;
}

int main()
{
  Map_Test();
  return 0;
}
