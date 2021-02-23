// 左式堆(堆的高效合并)
// 时间复杂度为 O(logn)
#include <iostream>
#include <vector>
using namespace std;

// 树结点
template<class T>
struct TreeNode
{
  T _date;                         // 结点数据
  struct TreeNode* _par;           // 父结点
  struct TreeNode* _left;          // 左孩子
  struct TreeNode* _right;         // 右孩子
  int _npl;                        // 空结点路径长度
};

// 树状堆(左式堆的相关操作)
template<class T>
class TreeHeap 
{
  public:
    // 初始化结点
    TreeNode<T>* Init(const T date, int npl = 0, 
        TreeNode<T>* leftptr = nullptr, TreeNode<T>* rightptr = nullptr, TreeNode<T>* par = nullptr)
    {
      TreeNode<T>* node = new TreeNode<T>;
      node->_date = date;
      node->_left = leftptr;
      node->_right = rightptr;
      node->_par = par;
      node->_npl = npl;

      return node;
    }

    // 插入操作
    bool Insert(const T date)
    {
      // 将该结点看作为一个堆
      TreeNode<T>* node = Init(date);

      // 将两个堆进行合并
      root = Merge(root, node);

      return true;
    }

    // 删除操作(同时获取优先级较高的元素)
    T Delete()
    {
      // 备份优先级最高的元素
      T tmp = root->_date;

      TreeNode<T>* troot = root;

      // 将两个小子堆进行合并
      root = Merge(root->_left, root->_right);

      delete troot;

      return tmp;
    }

    // 合并操作(静态函数)
    static TreeNode<T>* Merge(TreeNode<T>* root1, TreeNode<T>* root2)
    {
      // 递归基(当前某一个树为空，返回另一个树)
      if(root1 == nullptr) return root2; 
      if(root2 == nullptr) return root1;

      // 判断两个堆的根节点值(默认 root1 为大者)                // 满足堆序性
      if(root1->_date < root2->_date)
      {
        swap(root1, root2);
      }

      // 右子堆与另一个堆进行合并
      root1->_right = Merge(root1->_right, root2);
      root1->_right->_par = root1;

      // 交换，更新 NPL 值
      if(!root1->_left || root1->_left->_npl < root1->_right->_npl)
      {
        swap(root1->_left, root1->_right);                       // 选择 npl 较大的子树作为左子树，从而可以满足左倾性。
      }

      root1->_npl = root1->_right ? root1->_right->_npl + 1 : 1; // 由于堆满足左倾性，所以当前元素的 npl 为右子树 npl 值 + 1.
                                                                 // (右子树不存在时，npl 值为 0) 
      return root1;
    }

  public:
    TreeNode<T>* root; 
};


int main()
{
  // 测试左式堆的相关操作(暴力构建左式堆)
  TreeHeap<int> lheap;
  lheap.root = lheap.Init(17, 2);
  TreeNode<int>* node1 = lheap.Init(13, 1);
  TreeNode<int>* node2 = lheap.Init(12, 1);
  TreeNode<int>* node3 = lheap.Init(6, 1);
  lheap.root->_left = node1;
  node1->_par = lheap.root;
  lheap.root->_right = node2;
  node2->_par = lheap.root;
  node1->_left = node3;
  node3->_par = node1;
  
  TreeHeap<int> rheap;
  rheap.root = rheap.Init(15, 2);
  TreeNode<int>* nodee1 = rheap.Init(10, 1);
  TreeNode<int>* nodee2 = rheap.Init(8, 1);
  rheap.root->_left = nodee1;
  rheap.root->_right = nodee2;
  nodee1->_par = rheap.root;
  nodee2->_par = rheap.root;

  // 合并操作
  lheap.root = TreeHeap<int>::Merge(lheap.root, rheap.root);

  // 插入操作
  lheap.Insert(100);

  // 打印
  for(int i = 0; i < 8; ++i)
  {
    cout << lheap.Delete() << endl;
  }
  
  return 0;
}
