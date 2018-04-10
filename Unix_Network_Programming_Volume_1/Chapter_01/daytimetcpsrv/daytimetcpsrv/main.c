//
//  main.c
//  daytimetcpsrv
//
//  Created by YangHan on 2018/4/10.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_addr.s_addr = htons(INADDR_ANY);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8000);
    
    int on = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&on , sizeof(int)) < 0) {
        perror("setsockopt ");
        exit(1);
    }
    
    if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind ");
        exit(1);
    }
    
    if (listen(sockfd, 100) < 0) {
        perror("listen ");
        exit(1);
    }
    
    int connfd;
    char buf[1024];
    
    
    time_t ticks;
    while (1) {
        if ((connfd = accept(sockfd, NULL, NULL)) < 0) {
                perror("accept ");
                exit(1);
            }
        printf("哈哈\n");
        
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        write(connfd, buf, strlen(buf));
    
        close(connfd);
    }
    
    return 0;
}
