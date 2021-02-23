#include <memory>
#include <iostream>
using namespace std;

class ListNode
{
  public:
    //shared_ptr<ListNode> _prev;
    //shared_ptr<ListNode> _next;
    weak_ptr<ListNode> _prev;
    weak_ptr<ListNode> _next;
    int _date;

    ~ListNode(){ cout << "~ListNode()" << endl; }
};
   
int main()
{
  // 循环引用问题
  shared_ptr<ListNode> sp1(new ListNode);
  shared_ptr<ListNode> sp2(new ListNode);
  sp1->_next = sp2;   // shared_ptr 对 weak_ptr 进行赋值
  sp2->_prev = sp1;

  return 0;
}

