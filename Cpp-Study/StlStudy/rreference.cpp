// 体现 移动语义 
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class String
{
    public:
        String(const char* buf = "")
        {
            cout << "String(const char* buf = "")" << endl;
            if(buf == nullptr)
            {
                _buf = "";
            }

            _buf = new char[strlen(buf) + 1];
            strcpy(_buf, buf);

            Ccount++;
        }

        String(const String& str)
            :_buf(new char[strlen(str._buf) + 1])
        {
            cout << "String(const String& str)" << endl;
            strcpy(_buf, str._buf);

            Ccount++;
        }

        String& operator=(const String& str)
        {
            cout << "String operator=(const String& str)" << endl;
            if(str._buf == _buf)
                return *this;

            if(_buf)
                delete [] _buf;

            _buf = new char[strlen(str._buf) + 1];
            strcpy(_buf, str._buf);

            Ccount++;
            
            return *this;
        }

        #if 1 

        // 浅拷贝
        String(String&& str)      // 不能加 const，变成常引用后，无法实现移动语义 (str._buf无法修改)
            :_buf(str._buf)
        {
            cout << "String(String&& str)" << endl;
            str._buf = nullptr;

            Mcount++;
        }

        String& operator=(String&& str)
        {
            cout << "String operator=(String&& str)" << endl;
            if(str._buf == _buf)
                return *this;

            if(_buf)
                delete [] _buf;

            _buf = str._buf;
            str._buf = nullptr;

            Mcount++;

            return *this;
        }

        #endif

        ~String()
        {
            if(_buf)
                delete [] _buf;
        }
    private:
        char* _buf;

    public:
        static int Ccount;      // 统计拷贝构造函数的调用次数
        static int Mcount;      // 统计移动构造函数的调用次数
};

int String::Ccount = 0;
int String::Mcount = 0;

//String&& GetString(const char* cstr)
//{
//    String temp(cstr);
//    return move(temp);
//}

int main()
{
    //String s1("hello");
    //String s2(GetString("world"));
   
    #if 0 
    // 没有移动构造，移动赋值的情况下
    vector<String> vStr;
    vStr.reserve(1000);
    for(int i = 0; i < 1000; ++i)
    {
        vStr[i] = "hello world!";
    }

    cout << String::Ccount << endl;

    #elif 0

    // 在有移动构造，移动赋值的情况下
    vector<String> vStr;
    vStr.reserve(1000);
    for(int i = 0; i < 1000; ++i)
    {
        vStr[i] = String("hello world!");
    }

    cout << String::Ccount << endl;
    cout << String::Mcount << endl;
    
    #endif

    #if 0
    // 左值引用示例: 
    int a = 10;
    int& ra = a;         // 左值引用
    ra = 20;
    cout << a << " : " << ra << endl;

    const int& cra = 10;
    cra = 20;

    string&& rstr = "hello";

    cout << rstr << endl;

    rstr = "world!";

    cout << rstr << endl;
    #endif



    return 0;
}
