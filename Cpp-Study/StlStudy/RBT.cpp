#include "RBT.h"
using namespace std;

void Test()
{
  RBTree<int, int> rb;
  rb.Insert(make_pair(10,10));
  rb.Insert(make_pair(13,13));
  rb.Insert(make_pair(1,1));
  rb.Insert(make_pair(7,7));
  rb.Insert(make_pair(19,19));
  rb.Insert(make_pair(9,9));
  rb.Insert(make_pair(8,8));
  rb.Insert(make_pair(11,11));

  cout << rb.IsRBTree() << endl;
  rb.Inorder();
}

int main()
{
  Test();
  return 0;
}
