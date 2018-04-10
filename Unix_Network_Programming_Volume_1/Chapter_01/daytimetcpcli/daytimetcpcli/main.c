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
    serv.sin_port = htons(8000);
    ;
    if (inet_aton("10.10.3.33", &serv.sin_addr) < 0) {
        perror("IP ");
        exit(1);
    }
    
    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect ");
        exit(1);
    }
    char buf[1024];
    ssize_t n;
    while ((n = read(sockfd, buf, sizeof(buf))) > 0) {
        buf[n] = 0;
        if (fputs(buf, stdout) < 0) {
            perror("fputs ");
            exit(1);
        }
    }
    
    if (n < 0) {
        perror("read");
        exit(1);
    }
    
    return 0;
}
