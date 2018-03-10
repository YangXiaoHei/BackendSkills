#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define PATH "./yanghan/yanghan.txt"

int main(int argc, char *argv[]) {
    
    umask(0);
    
    int fd = open(PATH, O_CREAT | O_WRONLY | O_EXCL, 0777);
    
    if (fd < 0) {
        perror(PATH);
        exit(1);
    }
    
    if (argc >= 2) {
       int len = write(fd, argv[1], strlen(argv[1]));
        if (len < 0) {
            perror("write fail : ");
            close(fd);
            exit(1);
        }
    }
    close(fd);
    return 0;
}
