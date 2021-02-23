// 测试 HTTP 断点续传 (只与一个客户端连接，仅用于测试)
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define IP "192.168.248.129"
#define PORT 8888
#define CHECKRET(ret) if((ret) < 0) \
{\
    perror("error"); \
}

class TcpSocket
{
    public:
        TcpSocket()
        {
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            CHECKRET(sockfd);
        }

        ~TcpSocket()
        {
            close(sockfd);
        }

        void Bind()
        {
            struct sockaddr_in saddr;
            saddr.sin_family = AF_INET;
            saddr.sin_port = htons(PORT);
            inet_pton(AF_INET, IP, (void*)&saddr.sin_addr);
            socklen_t slen = sizeof(saddr);
            int ret = bind(sockfd, (struct sockaddr*)&saddr, slen);
            CHECKRET(ret);
        }

        void Listen(int recvnum = 100)
        {
            int ret = listen(sockfd, recvnum);
            CHECKRET(ret);
        }

        int Accept(string& ip, int& port)
        {
            struct sockaddr_in cliaddr;
            socklen_t clen = sizeof(cliaddr);
            int clisockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clen);

            // 客户端 ip, port
            char buf[16];
            inet_ntop(AF_INET, (void*)&cliaddr.sin_addr, buf, 16);   // 点分十进制需要 16 个字符
            port = ntohs(cliaddr.sin_port);
            ip.assign(buf, 16);

            return clisockfd;
        }

    private:
        int sockfd;
};

int main()
{
    TcpSocket server;
    server.Bind();
    server.Listen();

    string ip;
    int port = 0;
    server.Accept(ip, port);

    cout << ip << ":" << port << endl;


    return 0;
}
