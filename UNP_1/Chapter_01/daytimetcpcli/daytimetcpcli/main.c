//
//  main.c
//  daytimetcpcli
//
//  Created by YangHan on 2018/4/10.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9999);
    ;
    if (inet_aton("127.0.0.1", &serv.sin_addr) < 0) {
        perror("IP ");
        exit(1);
    }
    
    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect ");
        exit(1);
    }
    char buf[1024];
    ssize_t n = 0;
    int cnt = 0;
    ssize_t cur = 0;
    while ((n = read(sockfd, buf, sizeof(buf))) > 0) {
        
        cnt++;
        
        buf[n] = 0;
        printf("第 %d 次循环接收到 : %s\n",cnt, buf);
        
        
//        if (fputs(buf, stdout) < 0) {
//            perror("fputs ");
//            exit(1);
//        }
    }
    
    printf("接收循环次数 : %d\n", cnt);
    
    if (n < 0) {
        perror("read");
        exit(1);
    }
    
    return 0;
}
