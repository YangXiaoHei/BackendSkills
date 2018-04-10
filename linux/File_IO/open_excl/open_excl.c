#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    int fd;
    
    umask(0);
    
    // 创建一个已存在的文件 如果文件已经存在，返回错误
    fd = open(argv[1], O_CREAT | O_EXCL, 0777);
    
    if (fd < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    printf("创建 %s 成功\n", argv[1]);
    
    close(fd);
    
}
