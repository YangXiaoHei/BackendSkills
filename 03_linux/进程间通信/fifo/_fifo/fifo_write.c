#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "./fifo"

int main(int argc, char *argv[]) {
    
    int fd;
    
    if (access(FIFO_PATH, F_OK) != 0) {
        fd = mkfifo(FIFO_PATH, 0777);
    } else {
        fd = open(FIFO_PATH, O_RDWR);
    }
    
    if (fd < 0) {
        perror("mkfifo ");
        exit(1);
    }
    
    char buf[] = "yanghan is pig\n";
    if (write(fd, buf, strlen(buf)) < 0) {
        perror("write ");
        exit(1);
    }
    
    printf("向 fifo 写入数据成功!\n");
    
    close(fd);
    return 0;
}
