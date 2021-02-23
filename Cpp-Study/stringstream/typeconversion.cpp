// 使用 stringstream 类进行类型转换
#include <iostream>
#include <sstream>
using namespace std;

// int -> string 
void int_string(int& num, string& str)
{
    stringstream sstream;
    sstream << num;
    sstream >> str;
}

// char* -> int 
void charptr_int(char* str, int& num)
{
    stringstream sstream;
    sstream << str;
    sstream >> num;
}

// double -> string 
void double_string(double& num, string& str)
{
    stringstream sstream;
    sstream << num;
    sstream >> str;
}

// string -> double 
void string_double(string& str, double& num)
{
    stringstream sstream;
    sstream << str;
    sstream >> num;
}

int main()
{
    int num = 12345;
    string str;
    cout << "转化之前: " << str << endl;
    int_string(num, str); 
    cout << "转化之后: " << str << endl;
    
    cout << "--------------------------" << endl;

    char* data = "88888888";
    int numdata = 0;
    cout << "转化之前: " << numdata << endl;
    charptr_int(data, numdata);
    cout << "转化之后: " << numdata << endl;

    cout << "--------------------------" << endl;

    double dnum = 12.234435;
    string dstr;
    cout << "转化之前: " << dstr << endl;
    double_string(dnum, dstr);
    cout << "转化之后: " << dstr << endl;

    cout << "--------------------------" << endl;

    string ss = "1231.232";
    double dd = 0.0;
    cout << "转化之前: " << dd << endl;
    string_double(ss, dd);
    cout << "转化之后: " << dd << endl;

    return 0;
}
