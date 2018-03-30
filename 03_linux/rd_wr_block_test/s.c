#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8000);
    serv.sin_addr.s_addr = htons(INADDR_ANY);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    int on = 1;
    if (setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) ) < 0) {
        perror("setsockopt ");
        exit(1);
    }
    
    if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind ");
        exit(1);
    }
    
    if (listen(sockfd, 10) < 0) {
        perror("listen ");
        exit(1);
    }
    
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = sizeof(cli);
    int newfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (newfd < 0) {
        perror("accpet ");
        exit(1);
    }
    printf("accept 成功 ------ %d\n", newfd);
    
//    sleep(10);
    
    printf("睡醒了\n");
    
    char buf[1024];
    bzero(buf, sizeof(buf));
    ssize_t rd_len = read(newfd, buf, sizeof(buf));
    if (rd_len < 0) {
        perror("recv ");
        exit(1);
    }
    
    buf[rd_len] = 0;
    printf("收到客户端的消息 : %s\n", buf);
    
    return 0;
}
