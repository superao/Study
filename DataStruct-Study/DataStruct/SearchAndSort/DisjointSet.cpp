// 并查集的基本操作实现
#include <iostream>
#include <vector>
using namespace std;

// 并查集实质上就是一个森林，森林中有某干颗树，一棵树表示一个集合，树中的元素表示集合中每一个元素。
// 为了区分不同的集合，以树的根节点作为该集合的标识。
// 并查集的常用操作：
//    1. find(): 当前元素的根节点(标识结点)。
//    2. union(): 将两个集合合并为一个集合。
//    3. issame(): 判断两个元素是否在一个集合中

// 未优化版本(数组表示树，数组中的元素用来表示父节点的位置)
class DisjointSet
{
  public:
    DisjointSet(int num = 20):forest(vector<int>(num))
    {
      // 刚开始默认自己本身就是一颗树
      for(size_t i = 0; i < forest.size(); ++i)
      {
        forest[i] = i;
      }
    }

    // 查找(递归根节点)
    int Find(int num)
    {
      int r = forest[num];
      if(r == num)
      {
        return r;
      }
      else 
      {
        return Find(r);
      }
    }
    
    // 联合(线性)
    void Union(int num1, int num2)
    {
      int num1root = Find(num1);
      int num2root = Find(num2);

      forest[num1root] = num2root;
    }

    // 判断是否在一个集合
    bool Issame(int num1, int num2)
    {
      return Find(num1) == Find(num2);
    }
    
  private:
    vector<int> forest;
};


// 上述版本有几个效率问题存在：
//    1. 当整个森林中只有少量树的时候，此时这个树是相当大的在进行查找的时候效率是非常低效的。(线性)
//    2. 当一个树比较大的时候，在进行两个树联合的时候如果选择不好也会导致也是非常低效的。(主要消耗在查找上)
// 解决思路：(解决树的高度问题)
//    1. 在两个集合合并的时候，尽量不影响树的高度，这样方便后续查找。只要能够快速查找出来，那么就能快速合并。
//    2. 在进行查找的时候，尽量压缩当前结点与根节点之间的路径长度，这样方便下次快速查找，不断依据这样的方法就可以压缩树的高度。


// 优化思路1：
//    由于影响效率的就是由于树的高度问题从而影响了它们两个的效率，那么我们在合并的时候将小树每次合并在大树上，
//    这样就不会影响树的高度，除非两个树的高度是相同这时才会使高度发生变化(+1) 接近O(1)
// 优化版本1(按秩合并, 秩用来表示高度)
class DisjointSet1
{
  public:
    DisjointSet1(int num = 20):forest(vector<int>(num)), rank(vector<int>(num))
    {
      // 刚开始默认自己本身就是一颗树
      for(size_t i = 0; i < forest.size(); ++i)
      {
        forest[i] = i;
      }
      // 刚开始高度默认为 0 
      for(size_t i = 0; i < rank.size(); ++i)
      {
        rank[i] = 0;
      }
    }

    // 查找(递归根节点)
    int Find(int num)
    {
      int r = forest[num];
      if(r == num)
      {
        return r;
      }
      else 
      {
        return Find(r);
      }
    }

    // 联合(小树合并在大树上)
    void Union(int num1, int num2)
    {
      int num1root = Find(num1);
      int num2root = Find(num2);

      // 原则：小树挂到大树上
      if(rank[num1root] > rank[num2root])
      {
        forest[num2root] = num1root;
      }
      else if(rank[num1root] < rank[num2root])
      {
        forest[num1root] = num2root;
      }
      else 
      {
        // 高度相同时任意联合，联合后 rank++;
        forest[num1root] = num2root;
        rank[num2root]++;
      }
    }
    
    // 判断是否在一个集合
    bool Issame(int num1, int num2)
    {
      return Find(num1) == Find(num2);
    }
  
  private:
    vector<int> forest;
    vector<int> rank;
};


// 优化思路2：
//    当我们在查找某个结点的父节点时顺便将它的父节点向上提升一次(此时父节点变为父节点的父节点)，这样就达到了路径压缩的效果。
//    方便下次进行查找，下次继续用此方式压缩路径，从而是我们的效率大大提升。O(1)
// 优化版本2:(路径压缩)
class DisjointSet2
{
  public:
    DisjointSet2(int num = 20):forest(vector<int>(num))
    {
      // 刚开始默认自己本身就是一颗树
      for(size_t i = 0; i < forest.size(); ++i)
      {
        forest[i] = i;
      }
    }

    // 查找
    int Find(int num)
    {
      // 循环查找根结点，顺便压缩路径
      while(forest[num] != num)
      {
        int next = forest[num];
        forest[num] = forest[forest[num]];                      // 当前结点的父节点变为父节点的父节点。
        num = next;
      }

      return num;
    }

    // 联合(路径在查找的时候已经进行了压缩，合并可以随便，但是最优的方式是采用按秩合并)
    void Union(int num1, int num2)
    {
      int num1root = Find(num1);
      int num2root = Find(num2);

      forest[num2root] = num1root;
    }
    
    // 判断是否在一个集合
    bool Issame(int num1, int num2)
    {
      return Find(num1) == Find(num2);
    }

    // 判断当前集合数量
    int Setsize()
    {
      int setsum = 0;
      for(int i = 0; i < (int)forest.size(); ++i)
      {
        int root = forest[i];
        if(root == i)
        {
          setsum++;
        }
      }

      return setsum;
    }

  private:
    vector<int> forest;
};

int main()
{
  DisjointSet2 s;
  s.Union(1, 5);
  s.Union(1, 8);
  s.Union(2, 4);
  s.Union(2, 9);
  s.Union(7, 10);
  s.Union(7, 6);
  s.Union(7, 12);
  s.Union(7, 17);
  s.Union(7, 13);
  s.Union(7, 16);

  cout << "6 的父结点为：" << s.Find(6) << endl;
  cout << "10 的父结点为：" << s.Find(10) << endl;
  cout << "7 的父结点为：" << s.Find(7) << endl;
  cout << "12 的父结点为：" << s.Find(12) << endl;
  cout << "17 的父结点为：" << s.Find(17) << endl;
  cout << "13 的父结点为：" << s.Find(13) << endl;
  cout << "16 的父结点为：" << s.Find(16) << endl;
  cout << "1 和 8 是否在一个集合中：" << s.Issame(1, 8) << endl;
  cout << "当前集合个数：" << s.Setsize() << endl;

  return 0;
}
