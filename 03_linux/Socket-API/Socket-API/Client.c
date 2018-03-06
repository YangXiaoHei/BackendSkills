//
//  Client.c
//  Socket-API
//
//  Created by YangHan on 2018/3/6.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#define SERVER_PORT 8000
#define MAX_BUF_SIZE 4096

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("客户端没有在 socket管道写入数据\n");
        exit(1);
    }
    
    // socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 要连接的服务器 socket
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    char serv_ip_str[] = "10.10.3.34";
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip_str, &servaddr.sin_addr.s_addr);
    
    // connect
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    // 缓冲区
    char buf[MAX_BUF_SIZE];
    bzero(buf, sizeof(buf));
    
    // 将数据传给服务器
    write(sockfd, argv[1], strlen(argv[1]));
    
    // 从服务器返回数据
    read(sockfd, buf, sizeof(buf));
    
    // 打印服务器返回数据
    printf("%s\n", buf);
    
    // 关闭 socket
    close(sockfd);
    
    return 0;
}


