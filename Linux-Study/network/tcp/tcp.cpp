// 体会 TCP 协议的字节流特点
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
using namespace std;

#define PORT 8888
#define IP "192.168.248.129"

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket error");
        return -1;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, (void*)&sockaddr.sin_addr);
    socklen_t len = sizeof(sockaddr);
    int ret = bind(sockfd, (struct sockaddr*)&sockaddr, len);
    if(ret < 0)
    {
        perror("bind error");
        return -1;
    }

    ret = listen(sockfd, 100);
    if(ret < 0)
    {
        perror("listen error");
        return -1;
    }
    
    struct sockaddr_in clisockaddr;
    socklen_t clilen = sizeof(clisockaddr);
    int clisockfd = accept(sockfd, (struct sockaddr*)&clisockaddr, &clilen);
    if(clisockfd < 0)
    {
        perror("accept error");
        return -1;
    }

    while(1)
    {
        sleep(10);       // 客户端先发送 10 秒数据，观察一下服务器是否一次read全部读取完毕了。

        char buf[1024];
        int ret = read(clisockfd, buf, 1024);
        if(ret < 0)
        {
            perror("read error");
            continue;
        }

        cout << buf;

        cout << "当前一次read读取完毕" << endl;
    }

    return 0;
}

// 测试过程：
// 客户端
// nc 192.168.248.129 8888
// hello
// world
// !!!!
// hehehe
//
// 服务端
// hello
// world
// !!!!
// hehehe
// 当前一次read读取完毕
//
// 实验结果：
// 客户端调用 4 次send发送数据，而服务器只调用了一次read就将所有的数据全部读取出来了，这就体现了字节流的传输特性
