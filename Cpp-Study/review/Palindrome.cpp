// 判断一个字段串能否转化为回文串
#include <iostream>
#include <map>
using namespace std;

bool isPalindrome(string str)
{
    if(!str.size()) return false;

    map<char, int> strcount;
    for(auto& e : str)
        strcount[e]++;

    int count = 0;
    for(auto& e : strcount)
    {
        if(e.second % 2 != 0)
            count++;
    }

    if(count > 1) return false;
    else return true;
}

int main()
{
    cout << isPalindrome("aabbc") << endl;

    cout << isPalindrome("aabbcc") << endl;

    cout << isPalindrome("aba") << endl;

    cout << isPalindrome("ab") << endl;

    return 0;
}
