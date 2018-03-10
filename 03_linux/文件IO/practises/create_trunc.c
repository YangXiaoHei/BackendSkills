#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define PATH "./yanghan/yanghan.txt"

int main() {
    
    umask(0);
    
    int fd = open(PATH, O_CREAT | O_TRUNC, 0777);
    
    if (fd < 0) {
        perror(PATH);
        exit(1);
    }
    
    close(fd);
    
    return 0;
}
