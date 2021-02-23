// 单例模式 - 饿汉模式
//   main函数进入之前就已经初始化好对象
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class Singleton
{
    public:
        // 通过特殊的方式来构造对象
        static Singleton* GetSingleton()
        {
            sleep(1);                              // 让出CPU，放大现象
            if(singptr == NULL)
                singptr = new Singleton();
            else 
                cout << "该类已存在一个对象，不允许再次创建！" << endl;

            return singptr;
        }
    private:
        Singleton()
        {
            cout << "私有传统构造器！" << endl; 
        }

        static Singleton* singptr;
};

// 初始化对象(线程安全)
Singleton* Singleton::singptr = Singleton::GetSingleton();

void* handler(void*)
{
    Singleton* s1 = Singleton::GetSingleton();
    Singleton* s2(s1);

    cout << "s1对象地址: " << s1 << endl;
    cout << "s2对象地址: " << s2 << endl;

    pthread_exit(NULL);
}

int main()
{
    cout << "inter main()!" << endl;

    for(int i = 0; i < 100; ++i)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, handler, NULL);
        pthread_detach(tid);
    }

    sleep(10);

    return 0;
}
