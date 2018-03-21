#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int fd = open(argv[1], O_WRONLY | O_TRUNC);
    
    if (fd < 0) {
        perror(argv[1]);
        exit(1);
    }
    
    printf("以 O_TRUNC 方式打开文件 %s\n", argv[1]);
    
    return 0;
}
