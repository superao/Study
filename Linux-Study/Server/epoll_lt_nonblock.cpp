// 非阻塞socket下的epoll的lt模式
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
using namespace std;

#define IP "192.168.248.129"
#define PORT 8888
#define ACCEPTQUE 1024

void SetNonBlock(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket error");
        exit(-1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind error");
        exit(-1);
    }

    listen(sockfd, ACCEPTQUE);

    // 只连接一个客户端(方便测试实验结果)
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(clifd < 0)
    {
        perror("accept error");
        exit(-1);
    }

    SetNonBlock(clifd);

    // epoll监听事件
    int epfd = epoll_create(1024);

    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = clifd;
    int epret = epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &event);
    if(epret < 0)
    {
        perror("epoll ctl error");
        exit(-1);
    }

    while(1)
    {
        epoll_event events[1024];
        int ret = epoll_wait(epfd, events, 1024, 0);    // 非阻塞，方便观察现象
        if(ret < 0)
        {
            perror("epoll wait error");
            close(clifd);
            exit(-1);
        }
        else if(ret == 0)
        {
            cout << "没有事件触发！" << endl;
        }

        for(int i = 0; i < ret; ++i)
        {
            if(events[i].events & EPOLLIN)
            {
                // while(1)    测试非阻塞socket最好采用循环读取，才能看到效果
                char buf[1024];
                int ret = read(events[i].data.fd, buf, 1);
                if(ret < 0)
                {
                    if(errno == EAGAIN)
                    {
                        cout << "当前没有消息！" << endl;
                        continue;
                    }
                    perror("read error");
                    exit(-1);
                }
                else if(ret == 0)
                {
                    cout << "对端关闭！" << endl;
                    // 删除该事件
                }
                else 
                {
                    cout << buf << "-------------------" << endl;
                }
            }
        }

        sleep(1);
    }

    return 0;
}
