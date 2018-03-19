#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    
    // 以只写打开管道，如果读端没有打开，那么该进程会阻塞
    int fd = open("./fifo", O_WRONLY);
    
    if (fd < 0) {
        perror("open ");
        exit(1);
    }
    
    char msg[] = "yang han is pig\n";
    
    if (write(fd, msg, strlen(msg)) < 0) {
        perror("write ");
        exit(1);
    }
    
    printf("进程 : %d 向管道写入 %zd 个字节\n", getpid(), strlen(msg));
    
    close(fd);
    
    return 0;
}
