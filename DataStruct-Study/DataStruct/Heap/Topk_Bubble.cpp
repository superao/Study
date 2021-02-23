// 海量数据 TopK 问题
// 利用起泡的方式来解决数据 TopK 问题
// 时间复杂度为 O(k * N)
#include <iostream>
#include <vector>
using namespace std;

template<class T>
bool Topk(vector<T>& random, vector<T>& result, int K)
{
  // 扫描 K 次数据
  for(int i = 1; i <= K; ++i)
  {
    // 每扫描一次进行一次起泡
    for(int j = 1; j < random.size(); ++j)
    {
      // 起泡
      if(random[j - 1] > random[j])
      {
        swap(random[j - 1], random[j]);
      }
    }
  }

  // 传出数据
  for(int i = random.size() - 1, count = 0; i >= 0 && count != K; --i, ++count)
  {
    result.push_back(random[i]);
  }

  return true;
}

int main()
{
  int k = 6;
  // 待查找数据
  vector<int> array = {2, 9, 4, 1, 5, 3, 8, 10, 21, 22, 100, 99};
  vector<int> result;
  result.reserve(k);

  Topk(array, result, k);

  for(auto& e : result)
  {
    cout << e << endl;
  }
  
  return 0;
}
