#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    int fds[2];
    
    if (pipe(fds) < 0) {
        perror("pipe ");
        exit(1);
    }
    
    int read_endian = 0, write_endian = 1;
    
    printf("管道缓冲区读大小 : %zd B\n", fpathconf(fds[read_endian], _PC_PIPE_BUF));
    printf("管道缓冲区写大小 : %zd B\n", fpathconf(fds[write_endian], _PC_PIPE_BUF));
    
    return 0;
    
}
