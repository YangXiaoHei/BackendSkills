#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAP_LEN 0x1000

void sys_err(char *str, int exitno) {
    perror(str);
    exit(exitno);
}

int main(int argc, char *argv[]) {
    
    char *mm;
    int fd, i = 0;
    if (argc < 2) {
        printf("至少需要一个命令行参数");
        exit(1);
    }
    
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        sys_err("open", 1);
    }
    
    mm = mmap(NULL, MAP_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (mm == MAP_FAILED) {
        sys_err("mmap", 5);
    }
    
    close(fd);
    
    while (1) {
        printf("%s\n", mm);
        sleep(1);
    }
    
    munmap(mm, MAP_LEN);
    return 0;
}
