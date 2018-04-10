#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>

int main() {
    
    struct sockaddr_in serv, cli;
    bzero(&serv, sizeof(serv));
    bzero(&cli, sizeof(cli));
    
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8000);
    inet_aton("10.10.3.25", &serv.sin_addr);
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int t = connect(fd, (struct sockaddr *)&serv, sizeof(serv));
    if (t < 0) {
        perror("connect ");
        exit(1);
    }
    
    printf("connect 返回\n");
    
    while (1);
    
    return 0;
}
