#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define EXEC_PATH "./upper.o"

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("至少需要 2 个命令行参数\n");
        exit(1);
    }
    
    int fd = open(argv[1], O_RDONLY);
    
    if (fd < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    dup2(fd, STDIN_FILENO);
    close(fd);
    
    execl(argv[2], "hehe", NULL);
    
    perror(argv[2]);
    exit(1);
    
    return 0;
}
