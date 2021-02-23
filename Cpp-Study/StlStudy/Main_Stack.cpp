#include "stack.h"

void Test()
{
  Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);

  cout << s.size() << endl;
  cout << s.empty() << endl;
  cout << s.top() << endl;
  s.pop(); 
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
}

int main()
{

  Test();
  return 0;
}
