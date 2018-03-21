#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PATH "./yanghan/expend.txt"

int main() {
    
    umask(0);
    
    int fd = open(PATH, O_CREAT | O_RDWR, 0777);
    
    if (fd < 0) {
        perror(PATH);
        exit(1);
    }
    // 10M = 10 * 1024 * 1024 B
    if (lseek(fd, 10 * 1024 * 1024, SEEK_SET) < 0) {
        perror("lseek fail : ");
        close(fd);
        exit(1);
    }
    
    if (write(fd, "a", 1) < 0) {
        perror("write fail : ");
        close(fd);
        exit(1);
    }
    
    close(fd);
    
    return 0;
}
