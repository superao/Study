// 单例模式 - 懒汉模式
//   不提前创建对象，什么时候使用，什么时候创建
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

// 单例模式 
class Singleton
{
    public:
        static Singleton* GetSingleton()
        {
            sleep(1);           // 让出CPU，放大现象
            pthread_mutex_lock(&mutex);
            if(singptr == NULL)
                singptr = new Singleton();
            else 
                cout << "该类已存在对象，不允许再次创建！" << endl;
            pthread_mutex_unlock(&mutex);

            return singptr;
        }

        ~Singleton()
        {
            pthread_mutex_destroy(&mutex);
        }

    private:
        Singleton()
        {
            cout << "私有普通构造器！" << endl;
        }

        static Singleton* singptr;

        static pthread_mutex_t mutex;
};

// 静态成员初始化: 类型 变量名
Singleton* Singleton::singptr = NULL;
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;

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
