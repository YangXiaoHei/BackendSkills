#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("至少需要 3 个参数\n");
        exit(1);
    }
    
    umask(0);
    
    int fd_src = open(argv[1], O_RDONLY);
    int fd_dest = open(argv[2], O_CREAT | O_WRONLY, 0644);
    
    if (fd_src < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    if (fd_dest < 0) {
        perror(argv[2]);
        exit(1);
    }
    
    int len; char buf[1024];
    while ((len = read(fd_src, buf, sizeof(buf))) != 0) {
        if (len < 0) {
            perror("read fail : ");
            close(fd_src);
            close(fd_dest);
            exit(1);
        }
        if (write(fd_dest, buf, len) < 0) {
            perror("write fail : ");
            close(fd_src);
            close(fd_dest);
            exit(1);
        }
    }
    printf("复制成功!\n");
    close(fd_src);
    close(fd_dest);
    return 0;
}
