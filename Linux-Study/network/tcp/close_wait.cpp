#include <iostream>
#include <sys/epoll.h>
#include <vector>
#include "tcp_socket.hpp"
using namespace std; 

#define NODESIZE 1024
#define LISTNODE 100

// Epoll 类
class Epoll 
{
    public:
        // 内核中创建eventpoll结构体
        bool Init()
        {
            _epfd = epoll_create(NODESIZE);
            if(_epfd < 0)
            {
                cout << "create error" << endl;
                return false;
            }

            return true;
        }

        // 添加用户关心socket事件
        bool Add(int sockfd, int events = EPOLLIN | EPOLLRDHUP)
        {
            struct epoll_event event;
            event.events = events;
            event.data.fd = sockfd;
            int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, sockfd, &event);
            if(ret < 0)
            {
                cout << "create error" << endl;
                return false;
            }

            return true;
        }

        // 删除某一个事件
        bool Del(int sockfd)
        {
            // 用来获取当前删除事件的信息
            struct epoll_event event;
            int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, &event);
            if(ret < 0)
            {
                cout << "delete error" << endl;
                return false;
            }

            return true;
        }

        // 进行事件监控
        bool Wait(vector<int>& lst, int sec = 3000)
        {
            struct epoll_event event[LISTNODE];
            int ret = epoll_wait(_epfd, event, LISTNODE, sec);
            if(ret < 0)
            {
                cout << "epoll_wait error" << endl;
                return false;
            }
            else if(ret == 0)
            {
                cout << "wait timeout" << endl;
                return false;
            }
            else 
            {
                // 事件触发
                for(int i = 0; i < ret; ++i)
                {
                    if(event[i].events & EPOLLRDHUP)
                    {
                        cout << "触发异常事件" << endl;

                    }
                    // 是否为可读事件
                    if(event[i].events & EPOLLIN)
                    {
                        cout << "触发可读事件！" << endl;
                        int fd = event[i].data.fd;
                        lst.push_back(fd);
                    }
                }
            }

            return true;
        }

    private:
        int _epfd;
};


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "./a.out 192.168.249.129 9000" << endl;
        return -1;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        cout << "socket error!" << endl;
        return -1;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    inet_pton(AF_INET, &ip[0], (void*)&sockaddr.sin_addr);
    socklen_t socklen = sizeof(sockaddr);
    int ret = bind(sockfd, (struct sockaddr*)& sockaddr, socklen);
    if(ret < 0)
    {
        cout << "bind error!" << endl;
        return -1;
    }

    ret = listen(sockfd, 1024);
    if(ret < 0)
    {
        cout << "listen error" << endl;
        return -1;
    }

    Epoll epoll;
    epoll.Init();
    epoll.Add(sockfd);
    while(1)
    {
        // epoll监听就绪事件
        vector<int> lst;
        epoll.Wait(lst);

        for(auto sock : lst)
        {
            if(sock == sockfd)
            {
                // 当前套接字为监听套接字
                struct sockaddr_in clisockaddr;
                socklen_t socklen = sizeof(clisockaddr);
                int clifd = accept(sock, (struct sockaddr*)&clisockaddr, &socklen);
                if(clifd < 0)
                {
                    cout << "accept error" << endl;
                }

                epoll.Add(clifd);
            }
            else 
            {
                // 读取套接字
                char buf[1024];
                int ret = read(sock, buf, 1024);
                if(ret == 0)        // 对端关闭
                {
                    cout << "peer errro!" << endl;
                    close(sock);
                    epoll.Del(sock);
                }
                if(ret < 0)
                {
                    cout << "read error" << endl;
                    return -1;
                }

                cout << buf;
            }
        }
    }
}
