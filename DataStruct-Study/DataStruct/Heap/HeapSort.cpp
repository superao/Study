// 堆排序(减而治之)
#include <iostream>
#include <vector>
using namespace std;

#define PARENT(i) ((i) - 1) / 2
#define LCHILD(i) ((i) * 2) + 1
#define RCHILD(i) ((i) + 1) * 2

// 仿函数(大于)
class Greater
{
  public:
    bool operator()(int num1, int num2)
    {
      return num1 > num2 ? true : false;
    }
};

// 仿函数(小于)
class Less
{
  public:
    bool operator()(int num1, int num2)
    {
      return num1 < num2 ? true : false;
    }
};

// 数据类型  仿函数(控制大小堆)
template<class T, class Com = Less>
class Heap 
{
  public:
    // 初始化向量
    Heap(vector<int>& array)
    {
      // 初始化堆(自下而上的向下调整 O(n))
      for(int i = array.size() - 1; i >= 0; --i)
      {
        AdjustDown(i, array.size(), array);
      }
    }

    // 排序(升序)
    void Sort(vector<T>& v)
    {
      for(int i = v.size() - 1; i >= 0; --i)
      {
        swap(v[0], v[i]);

        AdjustDown(0, i, v);
      }
    }

  public:
    // 向下调整
    void AdjustDown(const int i, const int n, vector<T>& v)
    {
      // 边界判断
      if(i >= n || i < 0)
      {
        return;
      }

      // 起始位置
      int index = i;
      while(index < n)
      {
        // 右孩子存在且优先级最高
        if(RCHILD(index) < n && compare(v[RCHILD(index)], v[index]) && compare(v[RCHILD(index)], v[LCHILD(index)]))
        {
          swap(v[index], v[RCHILD(index)]);
          index = RCHILD(index);
        }
        // 左孩子存在且优先级最高
        else if(LCHILD(index) < n && compare(v[LCHILD(index)], v[index]))
        {
          swap(v[index], v[LCHILD(index)]);
          index = LCHILD(index);
        }
        // 左右孩子都没有 || 优先级没有父结点高 
        else 
        {
          break;
        }
      }
    }

//    // 向上调整(用不到, Insert 的时候才使用) 
//    void AdjustUp(const int i)
//    {
//      // 边界条件
//      if(i < 0 || i >= v.size())
//      {
//        return;
//      }
//
//      // 起始位置
//      int index = i;
//      while(index >= 0 && v[index] > v[PARENT(index)])       // 由于 index 永远不会小于 0,因此可不必对父节点下标进行判断
//      {
//        swap(v[index], v[PARENT(index)]);
//        index = PARENT(index);
//      }
//    }

  private:
    Com compare;                     // **仿函数(函数对象)**
};

void HeapSort(vector<int>& array)
{
  Heap<int, Greater> heap(array);
  heap.Sort(array);
}

int main()
{
  vector<int> array = {2, 9, 4, 1, 5, 3, 8, 9, 10, 0};

  HeapSort(array);

  for(auto& e : array)
  {
    cout << e << endl;
  }

  return 0;
}
