// 最小生成树 -- Kruskal 算法(贪心策略: 局部最优 --> 整体最优)
// 无环，连通，最小
#include <iostream>
#include <vector>
using namespace std;

#define MAX 9999

class DisjointSet
{
  public:
    DisjointSet(int num)
    {
      forest.resize(num);
      for(size_t i = 0; i < forest.size(); ++i)
      {
        forest[i] = i;
      }
    }

    // 查找(路径压缩)
    int Find(int num)
    {
      while(forest[num] != num) 
      {
        int next = forest[num];
        forest[num] = forest[forest[num]];
        num = next;
      }

      return num;
    }

    // 联合
    void Union(int num1, int num2)
    {
      int num1root = Find(num1);
      int num2root = Find(num2);

      forest[num1root] = num2root;
    }

    // 判断
    bool Issame(int num1, int num2)
    {
      return Find(num1) == Find(num2);
    }

  private:
    vector<int> forest;
};

// 矩阵(无向图)
class Matrix
{
  public:
    Matrix(int num)
    {
      // 初始化矩阵
      graph.resize(num);
      flags.resize(num);
      for(int i = 0; i < num; ++i)
      {
        graph[i].resize(num, MAX);
        flags[i].resize(num, 0);
      }
    }

    // 获取最小权值坐标
    bool GetMin(int& x, int& y)
    {
      int max = MAX;
      for(size_t i = 0; i < graph.size(); ++i)
      {
        for(size_t j = 0; j < graph[i].size(); ++j)
        {
          if(graph[i][j] < max && flags[i][j] == 0)      // 1 已选用，2 已丢齐
          {
            max = graph[i][j];
            x = i;
            y = j;
          }
        }
      }

      return true;
    }

    // 设置权值(为了方便，只使用矩阵右上部分)
    bool SetWight(int x, int y, int wight)
    {
      graph[x][y] = wight; 

      return true;
    }

    // 采用
    bool Setflag1(int x, int y)
    {
      flags[x][y] = 1;
      
      return true;
    }

    // 丢弃
    bool Setflag2(int x, int y)
    {
      flags[x][y] = 2;
      
      return true;
    }

    // 打印
    void Print()
    {
      for(size_t i = 0; i < flags.size(); ++i)
      {
        for(size_t j = 0; j < flags[i].size(); ++j)
        {
          if(flags[i][j] == 1)
          {
            cout << "是";
          }
          else 
          {
            cout << "否";
          }
        }
        cout << endl;
      }
    }

  private:
    vector<vector<int> > graph;     // 无向图
    vector<vector<int> > flags;     // 选取标记: 0 表示未探测，1 表示已选用，2 表示丢弃
};

int main()
{
  // Kruskal 算法核心
  // A B C D E => 1 2 3 4 5 
  DisjointSet s(7);                    // 0 下标空闲
  Matrix graph(7);
  
  graph.SetWight(1, 2, 9);
  graph.SetWight(1, 4, 12);
  graph.SetWight(1, 5, 7);
  graph.SetWight(1, 6, 10);
  graph.SetWight(2, 3, 20);
  graph.SetWight(2, 4, 5);
  graph.SetWight(3, 5, 18);
  graph.SetWight(4, 5, 15);

  int v = 5;                      // n 个结点，构成无环连通需要 n - 1 条边
  while(v)
  {
    // 获取权值最小的边
    int x = 0; int y = 0;
    graph.GetMin(x, y);
    
    // 判断是否有环
    if(s.Issame(x, y) == true)
    {
      // 有环，丢弃
      graph.Setflag2(x, y);
      continue;
    }
    else 
    {
      // 无环，采用 
      s.Union(x, y);
      graph.Setflag1(x, y);
    }
    
    v--;
  }

  graph.Print();

  return 0;
}
