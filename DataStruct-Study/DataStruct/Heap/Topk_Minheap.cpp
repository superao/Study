// 利用堆的偏序关系，建立小堆寻找 TopK 元素
// 思路如下：
//    利用向量的前几个元素建立一个小堆，扫描其他元素。
//    如果其他元素比堆中的任何一个元素大(与堆顶元素比较)，那么将用该元素进行替换。
//    最后此堆的所有元素将会是该向量中最大的几个元素。
#include <iostream>
#include <vector>
#include <queue>
#include <functional>                                               // 仿函数头文件
using namespace std;

template<class T>
bool Topk(vector<T>& random, vector<int>& result, int k)
{
  // 利用向量的迭代器区间进行构造(向量迭代器类型)
  auto start = random.begin();
  auto end = start + k;
  priority_queue<T, vector<T>, greater<T>> heap(start, end);      // **建立小堆(默认建立大堆)**

  // 扫描其他元素，更新堆中结点
  for(int i = k; i < random.size(); ++i)
  {
    if(random[i] > heap.top())
    {
      heap.pop();
      heap.push(random[i]);
    }
  }

  while(!heap.empty())
  {
    result.push_back(heap.top());
    heap.pop();
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
