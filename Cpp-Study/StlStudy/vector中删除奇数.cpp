// vector 数组中删除奇数元素
#include <iostream>
#include <vector>
using namespace std;

void Remove(vector<int>& array)
{
  auto it = array.begin();
  while(it != array.end())
  {
    if(*it % 2 == 0)
    {
      // 偶数
      it++;
    }
    else 
    {
      // 奇数
      it = array.erase(it);         // vector 删除元素后需要重新更新迭代器，而不是一味的进行++操作
    }
  }
}

int main()
{
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Remove(arr);

  for(auto e : arr)
  {
    cout << e << endl;
  }

  return 0;
}
