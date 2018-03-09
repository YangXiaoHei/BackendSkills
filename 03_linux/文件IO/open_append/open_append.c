#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("至少需要 3 个命令行参数\n");
        exit(1);
    }
    
    int fd = open(argv[1], O_RDWR | O_APPEND);
    
    if (fd < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    printf("以 O_APPEND 的方式打开文件 %s 并写入数据 %s\n",argv[1], argv[2]);
    
    write(fd, argv[2], strlen(argv[2]));
    
    close(fd);
    
    return 0;
}
