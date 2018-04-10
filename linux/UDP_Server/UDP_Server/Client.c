//
//  Client.c
//  UDP_Server
//
//  Created by YangHan on 2018/3/6.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SERVER_PORT 8000
#define MAX_LINE 1024

int main(int argc, char * argv[]) {
    
    if (argc < 2) {
        printf("参数个数不够!");
        exit(1);
    }
    
    char ipstr[] = "10.10.3.34";
    char buf[MAX_LINE];
    
    // 获取套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET,
              ipstr,
              &serveraddr.sin_addr.s_addr);
    
    // 向服务器发送数据
    sendto(sockfd,
           argv[1],
           strlen(argv[1]),
           0,
           (struct sockaddr *)&serveraddr,
           sizeof(serveraddr));
    
    // 从服务器接收数据
    socklen_t len = sizeof(serveraddr);
    recvfrom(sockfd,
             buf,
             strlen(argv[1]),
             0,
             (struct sockaddr *)&serveraddr,
             &len);
    
    printf("%s\n", buf);
    
    return 0;
}
