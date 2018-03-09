#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/**
 *  使用 open 创建文件
 */
int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("create file need filename\n");
        exit(1);
    }
    
    
    int fd; char buf[] = "yang han is pig\n";
    
    umask(0);
    
    fd = open(argv[1], O_CREAT | O_RDWR, 0777);
    
    if (fd < 0) {
        perror("open_create ");
        exit(1);
    }
    
    write(fd, buf, strlen(buf));
    
    close(fd);
    
    return 0;
}
