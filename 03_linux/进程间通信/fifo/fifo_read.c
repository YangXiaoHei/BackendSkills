#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    // 以只读打开读端，如果写端没有打开，会阻塞
    int fd = open("./fifo", O_RDONLY);
    
    if (fd < 0) {
        perror("open ");
        exit(1);
    }
    
    char buf[1024];
    int len;
    if ((len = read(fd, buf, sizeof(buf))) < 0) {
        perror("read ");
        exit(1);
    }
    
    
    printf("进程 : %d 从管道读取到 %d 个字节\n", getpid(), len);
    
    close(fd);
    
    
    return 0;
}
