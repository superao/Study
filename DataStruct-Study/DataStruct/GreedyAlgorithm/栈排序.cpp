// 栈排序(插入排序)
#include <iostream>
#include <stack>
using namespace std;

void StackSort(stack<int>& r, stack<int>& s)
{
  if(r.size() == 0)
  {
    return ;
  }

  int tmp = 0;
  tmp = r.top();
  r.pop();           // 防止 random 栈中最后一个元素出来之后直接压入 s 栈导致栈中元素无序而所做的进一步判断。
  while(!r.empty() || (!s.empty() && s.top() > tmp))
  {
    if(s.empty() || s.top() <= tmp)                // 执行了多少步？ 小于会发生什么情况？(稳定性)
    {                                     
      // 压栈后，更新 tmp 
      s.push(tmp);
      tmp = r.top();
      r.pop();
    }
    else                                           // 执行了多少步？
    {
      // 将元素先暂时回退到 r 栈中
      r.push(s.top());
      s.pop();
    }
  }

  // 1. 当 random 中只有一个元素的时候，不能进入循环，因此直接将其压入栈中。
  // 2. 当 random 中的一个元素出来之后会放到 tmp 中，为了防止直接放入而导致的无序，因此需要在循环中多做一次判断。
  s.push(tmp);
}

// 问题解答：
// 当前元素 tmp 与 tmp 之前元素之间是否存在逆序对的情况并且执行的次数也与互为逆序对的两个元素的相对位置有关系。

int main()
{
  // 待排序元素
  int array[10] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2};

  stack<int> s;         // sorted
  stack<int> r;         // random

  for(int i = 0; i < 10; ++i)
  {
    r.push(array[i]);
  }

  StackSort(r, s);

  // 测试数据
  while(!s.empty())
  {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;

  return 0;
}
