//
//  Server.c
//  Socket-API
//
//  Created by YangHan on 2018/3/6.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define MAX_BUF_SIZE   4096

int main() {
    
    // socket
    struct sockaddr_in servaddr, clienaddr;
    bzero(&servaddr, sizeof(servaddr));
    bzero(&clienaddr, sizeof(clienaddr));
    
    // 创建一个 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // bind
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // listen
    listen(sockfd, 128);
    
    // accept
    char ipstr[MAX_BUF_SIZE];
    while (1) {
        int addrlen = sizeof(clienaddr);
        
        // 阻塞直到客户端连接
        int confd = accept(sockfd,
                           (struct sockaddr *)&clienaddr,
                           (socklen_t *)&addrlen);
        
        // 将 IP 地址的 numeric 换成 presentation
        inet_ntop(AF_INET,
                  &clienaddr.sin_addr.s_addr,
                  ipstr,
                  sizeof(ipstr));
        
        // 客户端端口号
        int port = ntohs(clienaddr.sin_port);
        
        // 打印请求客户端的 IP 地址和 端口号
        printf("client ip : %s  port : %d\n", ipstr, port);
        
        // 关闭 socket
        close(confd);
    }
    close(sockfd);
}
