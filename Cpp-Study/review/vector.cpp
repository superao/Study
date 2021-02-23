#include <iostream>
#include <vector>
using namespace std;

#if 1
// 插入元素时不增容
int main()
{
    vector<int> v{1, 3, 5, 7, 9, 10, 11, 23, 44};
    auto index = v.begin() + 3;
    auto ins = v.insert(index, 123);
    cout << *index << " " << *ins << endl;    // 7 123

    cout << *++index << endl;   // 7
    
    // 更新迭代器，使其不失效
    index = ins + 1;         // 7 出现在插入元素后的下一个位置
    cout << *index << endl;

    return 0;
}
#endif

#if 0
// 迭代器删除
int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   
    // 从头开始遍历
    int count = 1;
    auto cur = v.begin();
    while(cur != v.end())
    {
        if(count % 2 == 0)
            cur = v.erase(cur);
        else 
            cur++;

        count++;
    }

    for(auto e : v)
        cout << e << " ";
    cout << endl;
    
    return 0;
}
#endif
