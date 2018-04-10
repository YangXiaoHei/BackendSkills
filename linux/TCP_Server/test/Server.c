#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main() {
    
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = sizeof(cli);
    
    struct sockaddr_in serv;
    bzero(&cli, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8000);
    serv.sin_addr.s_addr = htons(INADDR_ANY);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    
    struct timeval s;
    
    printf("listen 之前 %ld : %zd\n", s.tv_sec, s.tv_usec);
    listen(sockfd, 10);
    printf("listen 之后 %ld : %zd\n", s.tv_sec, s.tv_usec);
    
    while (1) ;

    return 0;
}
