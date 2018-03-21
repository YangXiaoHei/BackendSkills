#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("至少需要 2 个命令行参数\n");
        exit(1);
    }
    
    int fd, save_fd;
    
    // 3 -> file
    if ((fd = open(argv[1],
                   O_RDWR | O_CREAT,
                   S_IRUSR | S_IWUSR)) < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    // 4 -> stdout
    if ((save_fd = dup(STDOUT_FILENO)) < 0) {
        perror("标准输出 ");
        exit(1);
    }
    
    // 1 -> file
    dup2(fd, STDOUT_FILENO);
    
    // 3 -> ❌
    close(fd);
    
    // 向 file 写数据
    write(STDOUT_FILENO, argv[2], strlen(argv[2]));
    
    // 1 -> stdout
    dup2(save_fd, STDOUT_FILENO);
    
    // 4 -> ❌
    close(save_fd);
    
    return 0;
}
