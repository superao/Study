#include <iostream>
#include <queue>
using namespace std;

typedef struct Node 
{
  int _k;
  struct Node* _left = nullptr;
  struct Node* _right = nullptr;
} Node;

void BFS(Node* root, vector<vector<int>>& vv)
{
  // 创建队列用于广搜
  queue<Node*> bfs;

  // 初始化
  Node* cur = root;
  bfs.push(cur);

  // 用于控制格式
  while(!bfs.empty())
  {
    vector<int> v;    // 储存每一层的数据
    queue<Node*> next;// 储存下一层的结点

    // 此循环用于广度优先搜索
    while(!bfs.empty())
    {
      Node* front = bfs.front();
      bfs.pop();
      v.push_back(front->_k);


      if(front->_left)
      {
        next.push(front->_left);
      }
      if(front->_right)
      {
        next.push(front->_right);
      }
    }
    // 将所要输出的数据放到二维数组中
    vv.push_back(v);
    // 进行下一层广搜
    bfs = next;
  }

}

void TreeTest()
{
  Node* a = new Node;
  a->_k = 1;
  Node* b = new Node;
  b->_k = 2;
  Node* c = new Node;
  c->_k = 3;
  Node* d = new Node;
  d->_k = 4;
  Node* e = new Node;
  e->_k = 5;
  Node* f = new Node;
  f->_k = 6;

  a->_left = c;
  a->_right = e;
  c->_left = b;
  c->_right = d;
  d->_right = f;

  vector<vector<int>> vv;

  BFS(a, vv);
  for(auto ee : vv)
  {
    for(auto e : ee)
    {
      cout << e;
    }
    cout << endl;
  }
}

int main()
{
  TreeTest();
  return 0;
}
