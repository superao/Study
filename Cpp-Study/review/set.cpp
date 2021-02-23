// set容器储存自定义类型的数据
#include <iostream>
#include <set>
#include <cstring>
using namespace std;

class Student
{
    public:
        Student(char* name, int age)
        {
            strcpy(_name, name);
            _age = age;
        }

    public:
        int _age;
        char _name[64];
};

// 仿函数(实现对象的比较方式)
struct func 
{
    bool operator()(const Student& left, const Student& right)
    {
        if(left._age < right._age)
            return true;
        else 
            return false;
    }
};

// template <class T, class Compare = less<T>, class Alloc = allocator<T>> 
// class set;

int main()
{
    Student s1("aa", 11);
    Student s2("bb", 33);
    Student s3("cc", 22);
    Student s4("dd", 44);
    Student s5("ee", 55);

    set<Student, func> s; 
    s.insert(s1);
    s.insert(s2);
    s.insert(s3);
    s.insert(s4);
    s.insert(s5);

    for(auto& e : s)
        cout << e._name << " " << e._age << endl;

    return 0;
}
