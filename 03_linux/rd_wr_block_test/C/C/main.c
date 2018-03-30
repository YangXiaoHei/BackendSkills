#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main () {
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8000);
    const char *ip = "10.10.3.7";
    inet_pton(AF_INET, ip, &serv.sin_addr.s_addr);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
//        exit(1);
    }
    
    int rel = connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (rel < 0) {
        perror("connect ");
//        exit(1);
    }
//    int l = 1 * 100 * 100;
//    char *buf = malloc(l);
//    if (buf == NULL) {
//        perror("malloc ");
////        exit(1);
//    }
//    for (int i = 0; i < l; i++) {
//        buf[i] = 'a';
//    }
//    buf[l - 1] = 0;
    
    char buf[] = "yanghan";
    
    printf("开始 write\n");
    ssize_t len = write(sockfd, buf, strlen(buf));
    printf("结束 write\n");
    if (len < 0) {
        perror("write");
    }
    if (len == 0) {
        printf("len = 0\n");
    }
    
    printf("结束 len = %zd\n", len);
    
    return 0;
}

