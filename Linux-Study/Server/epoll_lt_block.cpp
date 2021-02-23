// 在阻塞socket下体会epoll的水平触发模式
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
using namespace std;

#define IP "192.168.248.129"
#define PROT 8888
#define ACCEPTQUE 128

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
    addr.sin_port = htons(PROT);
    inet_pton(AF_INET, IP, &addr.sin_addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind error");
        exit(-1);
    }

    listen(sockfd, ACCEPTQUE);

    // 默认只连接一个客户端  -->  为了测试LT工作模式
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(clifd < 0)
    {
        perror("accept error");
        exit(-1);
    }

    // epoll 监听(只监听读写事件)
    int epfd = epoll_create(1024);
    if(epfd < 0)
    {
        perror("epoll create error");
        exit(-1);
    }

    epoll_event event;
    event.events = EPOLLIN;      // 默认 LT 模式
    event.data.fd = clifd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &event);

    while(1)
    {
        epoll_event events[1024];
        int ret = epoll_wait(epfd, events, 1024, -1);    // 结论:当缓冲区有数据时会不断触发事件。
        if(ret <= 0)
        {
            perror("wait error");
            close(clifd);
            exit(-1);
        }

        for(int i = 0; i < ret; ++i)
        {
            if(events[i].events & EPOLLIN)
            {
                // 读取数据(只读一个字节)
                char buf[1024];
                read(events[i].data.fd, buf, 1);
                cout << buf << endl;
            }
        }

        sleep(1);
    }

    close(sockfd);
    
    return 0;
}
