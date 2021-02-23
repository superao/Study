// 非阻塞socket下epoll的ET模式
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;

#define IP "192.168.248.129"
#define PROT 8888
#define ACCEPTQUE 128

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
    addr.sin_port = htons(PROT);
    inet_pton(AF_INET, IP, &addr.sin_addr);
    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind error");
        exit(-1);
    }

    listen(sockfd, ACCEPTQUE);

    // 默认只连接一个客户端  -->  方便测试ET工作模式
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(clifd < 0)
    {
        perror("accept error");
        exit(-1);
    }

    SetNonBlock(clifd);

    // epoll 监听(只监听读事件)
    int epfd = epoll_create(1024);
    if(epfd < 0)
    {
        perror("epoll create error");
        exit(-1);
    }

    epoll_event event;
    event.events = EPOLLIN | EPOLLET;     // epoll的ET模式
    event.data.fd = clifd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &event);

    while(1)
    {
        epoll_event events[1024];
        int ret = epoll_wait(epfd, events, 1024, -1);
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
                while(1)
                {
                    // 读取数据(只读一个字节)
                    char buf[1024];
                    int ret = read(events[i].data.fd, buf, 1); // 此处采用非阻塞read，反复读取数据，直到一次触发所有数据读取完毕。
                    if(ret < 0)
                    {
                        if(errno == EAGAIN)
                        {
                            cout << "当前没有数据可读！" << endl;
                            break;
                        }

                        perror("read error");
                        exit(-1);
                    }
                    else if(ret == 0)
                    {
                        cout << "对端关闭！" << endl;
                        // 删除事件
                        close(events[i].data.fd);
                        break;
                    }

                    cout << buf << endl;
                }
            }
        }

        sleep(1);
    }

    close(sockfd);

    return 0;
}
