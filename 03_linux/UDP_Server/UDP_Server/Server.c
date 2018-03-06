//
//  Server.c
//  UDP_Server
//
//  Created by YangHan on 2018/3/6.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

#define SERVER_PORT 8000
#define MAX_LINE 1024

int main() {
    int             sockfd;
    struct          sockaddr_in serveraddr, clientaddr;
    char            buf[MAX_LINE];
    socklen_t       addrlen;
    char            ipstr[INET_ADDRSTRLEN];  //16 Byte
    
    // 置0
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));
    
    // 构造用于 UDP 通信的套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // 设置套接字地址
    serveraddr.sin_family       = AF_INET;
    serveraddr.sin_addr.s_addr  = htonl(INADDR_ANY); // 本地任意 IP
    serveraddr.sin_port         = htons(SERVER_PORT);
    
    bind(sockfd,
         (struct sockaddr *)&serveraddr,
         sizeof(serveraddr));
    
    while (1) {
        addrlen = sizeof(clientaddr);
        ssize_t len = recvfrom(sockfd,
                               buf,
                               sizeof(buf),
                               0,
                               (struct sockaddr *)&clientaddr,
                               &addrlen);
        
        inet_ntop(AF_INET,
                  &clientaddr.sin_addr.s_addr,
                  ipstr,
                  sizeof(ipstr));
        int port = ntohs(clientaddr.sin_port);
        printf("client IP : %s\tPORT : %d\n", ipstr, port);
        
        int i = 0;
        for (i = 0; i < len; i++) {
            buf[i] = toupper(buf[i]);
        }
        buf[i] = '\0';
        
        sendto(sockfd,
               buf,
               strlen(buf),
               0,
               (struct sockaddr *)&clientaddr,
               sizeof(clientaddr));
    }
    
    close(sockfd);
    
    return 0;
}
