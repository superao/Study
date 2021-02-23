// 数据结构 --- 堆(复习)
#include <iostream>
#include <vector>
using namespace std;

// 假设当前元素的下标为 i 
#define PARENT(i) ((i) - 1) / 2
#define LCHILD(i) ((i) * 2) + 1
#define RCHILD(i) ((i) + 1) * 2

class Heap
{
  public:
    // 初始化向量
    Heap(const vector<int> array, int lo, int hi) 
      :v(array)
    {
      Heapify(lo, hi);
    }

    // 获取优先级最大的元素
    int GetMax()
    {
      return v[0];
    }

    // 删除优先级最大的元素
    int DelMax()
    {

      int max = v[0];

      // 将末尾元素补充到堆顶
      v[0] = v[v.size() - 1];

      // 移除最后一个元素
      v.pop_back();

      // 向下调整
      AdjustDown(0, v.size());
      
      return max;
    }

    // 插入一个元素
    void Insert(int e)
    {
      // 尾插新元素
      v.push_back(e);

      // 向上调整
      AdjustUp(v.size() - 1);
    }

  private:
    // 批量建堆(区间)
    void Heapify(int lo, int hi)
    {
      // 自下向上的向下调整(O(n))
      for(int i = hi; i >= lo; --i)
      {
        AdjustDown(i, v.size());
      }
    }

    // 向上调整
    void AdjustUp(int index)
    {
      if(index >= (int)v.size())
      {
        return;
      }

      // 如果不是根节点并且当前结点优先级大于父节点优先级(如果出现相同也进行交换，那么到达根位置时会控制不住一直循环下去)
      while(0 <= index && 0 <= PARENT(index) && v[index] > v[PARENT(index)])
      {
        int next = PARENT(index);
        swap(v[index], v[PARENT(index)]);
        index = next;
      }
    }

    // 向下调整
    void AdjustDown(int index, int n)
    {
      if(index < 0 || n < 0)
      {
        return;
      }

      while(index < n)
      {
        int next = 0;
        
        // 如果有右孩子且右孩子优先级最大(有右孩子必有左孩子)
        if(RCHILD(index) < n && v[RCHILD(index)] > v[index] && v[RCHILD(index)] > v[LCHILD(index)])
        {
          swap(v[index], v[RCHILD(index)]);
          next = RCHILD(index);
        }
        // 左孩子存在且左孩子优先级大于父节点优先级
        else if(LCHILD(index) < n && v[LCHILD(index)] > v[index]) 
        {
          swap(v[index], v[LCHILD(index)]);
          next = LCHILD(index);
        }
        else 
        {
          break;
        }

        index = next;
      }
    }

  private:
    vector<int> v;               // 组合(降低耦合性)
};

int main()
{
  vector<int> v = {2, 9, 5, 7, 4, 10, 1, 10, 12, 16, 20};

  Heap heap(v, 0, v.size() - 1);
  heap.Insert(100);
  heap.Insert(101);
  heap.Insert(0);
  heap.Insert(104);
  
  for(int i = 0; i < (int)v.size() + 4; ++i)
  {
    cout << heap.DelMax() << endl;
  }

  return 0;
}
