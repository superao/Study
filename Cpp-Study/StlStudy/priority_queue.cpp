// 学习使用优先级队列,并且实现
// 功能: 随便进数据,出优先级最高的(注:可当作堆来进行使用)
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include "priority_queue.h"
using namespace std;

void Test()
{
  // int 类型 底层结构: vector<int> 仿函数: less<int>
  priority_queue<int> pq;   // 无参构造函数
  pq.push(1);
  pq.push(12);
  pq.push(2);
  pq.push(5);

  while(!pq.empty())
  {
    cout << pq.top() << endl;
    pq.pop();
  }

  // 利用一段迭代器区间来构造一个优先级队列
  int a[5] = {1,5,23,7,2};
  priority_queue<int, vector<int>, greater<int>> q(a, a + 5);

  while(!q.empty())
  {
    cout << q.top() << endl;
    q.pop();
  }

  // 使用过程的总结:
  // 1.构造函数有两种(无参和迭代器区间)
  // 2.他没有迭代器.(注意的是: 迭代器只有容器才有，并且有些容器是没有迭代器的)
  // 3.建大堆(less) 建小堆(greater)

}

void myqueuetest()
{
  Priority_queue<int, vector<int>, Greater<int>> q;
  q.push(12);
  q.push(1);
  q.push(20);
  q.push(2);
  q.push(100);

  while(!q.empty())
  {
    cout << q.top() << endl;
    q.pop();
  }
}

int main()
{

  // Test();
  myqueuetest();

  return 0;
}
