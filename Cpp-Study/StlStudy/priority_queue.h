// 模拟实现 priority_queue
// 1.学习适配器模式
// 2.学习仿函数/函数对象

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// 仿函数:
template<class T>
struct Less
{
  bool operator()(const T& l, const T& r)
  {
    return l < r;
  }

};

template<class T>
struct Greater 
{
  bool operator()(const T& l, const T& r)
  {
    return l > r;
  }

};

// 数据类型     底层结构     **仿函数**:作用之一就是实现不同的逻辑 
template<class T, class Contianer = vector<T>, class Compare = Less<T>>
class Priority_queue
{
  
  public:
   // 注意：构造函数是不需要书写的，因为是自定义类型，这样的话，他会调用自己的构造函数来完成初始化
   
   // 创建对象,测试
   // Less<T> less;                    // 库函数: 建大堆
   // Greater<T> greater;              //         建小堆
  
   void AdjustUp(size_t pos)
   {
     // 父节点
     size_t father = (pos - 1) / 2;

     while(pos > 0)
     {
       // if(_con[pos] > _con[father])
       if(compare(_con[father], _con[pos]))
       {
         swap(_con[pos], _con[father]);
         pos = father;
         father = (pos - 1) / 2;
       }
       else
       {
         break;
       }
     }

   }

   void AdjustDown(size_t pos)
   {
     // 左孩子
     size_t child = pos * 2 + 1;

     while(child < _con.size())
     {
       // 如果右孩子比左孩子大，则孩子为右孩子
       // if(child + 1 < _con.size()
       //   && _con[child] < _con[child + 1])
       if(child + 1 < _con.size()
           && compare(_con[child], _con[child + 1]))
       {
         child++;
       }

       // if(_con[pos] < _con[child])
       if(compare(_con[pos], _con[child]))
       {
         // 将堆顶元素与孩子进行交换
         swap(_con[pos], _con[child]);

         pos = child;
         child = pos * 2 + 1;
       }
       else
       {
         break;
       }
     }

   }

   void push(const T& x)
   {
     _con.push_back(x);
     AdjustUp(_con.size() - 1);
   }

   const T& top()
   {
     return _con[0];
   }

   void pop()
   {
     // 先将堆顶元素进行交换
     swap(_con[0], _con[_con.size() - 1]);

     // 再将 size--
     _con.pop_back();

     // 再向下调整
     AdjustDown(0);
   }

   bool empty()
   {
     return _con.empty();
   }

  private:
    Contianer _con;  // 底层结构
    Compare compare; // 仿函数
};
