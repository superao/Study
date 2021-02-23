// 浮点数二分法
#include <iostream>
using namespace std;

const double esp = 1e-8;

// 二分法求某个数的平方根
double Bsearch(double x, double l, double r)
{
    double res = 0.0;
    while(r - l > esp)
    {
        double mid = (l + r) / 2;
        if(mid * mid >= x) r = mid;
        else l = mid;
    }

    res = l;
    return res;
}

int main()
{
    double num = 0.0;
    cin >> num;

    // 二分范围:[-1e5, 1e5];
    cout << num << "的平方根: " << Bsearch(num, -1e5, 1e5) << endl;

    return 0;
}
