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

#define SERVER_PORT 8000

int main() {

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
    
    // 关闭 socket
    close(sockfd);
    
    return 0;
}


