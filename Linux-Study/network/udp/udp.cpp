// 体会 UDP 协议的数据报特点
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#define PORT 8888
#define IP "192.168.248.129"

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket error");
        return -1;
    }

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &sockaddr.sin_addr);
    socklen_t len = sizeof(sockaddr);
    int ret = bind(sockfd, (struct sockaddr*)&sockaddr, len);
    if(ret < 0)
    {
        perror("bind error");
        return -1;
    }

    while(1)
    {
        sleep(10);     // 先让客户端发送 10 秒数据，观察一下服务器是否一次read全部读取完毕了。

        char buf[1024];
        memset(buf, 0, 1024);
        int ret = read(sockfd, buf, 1024);
        if(ret < 0)
        {
            perror("read error");
            continue;
        }

        cout << buf;

        cout << "当前一次read读取完毕！" << endl;
    }

    return 0;
}

// 测试过程：
// 客户端
// nc -u 192.168.248.129 8888
// hello
// world
// !!!!
// hehehe
//
// 服务端
// hello
// 当前一次read读取完毕！
// world
// 当前一次read读取完毕！
// !!!!
// 当前一次read读取完毕！
// hehehe
// 当前一次read读取完毕！
//
// 实验结果：
// 客户端调用 4 次send发送数据，那么服务器也是需要调用了 4 次read去读取数据，
// 它不像 TCP 那样一次read就读取完毕了，这就是数据报的传输特性。
