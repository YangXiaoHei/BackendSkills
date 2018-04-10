//
//  main.c
//  C
//
//  Created by YangHan on 2018/4/2.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <event.h>
#include <event2/event.h>

int tcp_connect_socket(const char *ip, short port) {
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_aton(ip, &serv.sin_addr);
    
    if (serv.sin_addr.s_addr == 0) {
        printf("IP 地址无效");
        return -1;
    }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    
    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect ");
        exit(1);
    }
    printf("-------- connect success ----------\n");
    return sockfd;
}

int main(int argc, const char * argv[]) {
    
    int fd = tcp_connect_socket("10.10.3.25", 8000);
    
    char buf[1024];
    bzero(buf, sizeof(buf));
    ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
    if (len < 0) {
        perror("read from terminal ");
        exit(1);
    }
    if (write(fd, buf, len) < 0) {
        perror("write ");
        exit(1);
    }
    return 0;
}
