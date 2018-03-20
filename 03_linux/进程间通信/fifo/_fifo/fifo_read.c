#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FIFO_PATH "./fifo"

int main() {
    
    if (access(FIFO_PATH, F_OK) != 0) {
        printf("fifo 不存在\n");
        exit(1);
    }
    
    int fd = open(FIFO_PATH, O_RDONLY);
    
    if (fd < 0) {
        perror("open ");
        exit(1);
    }
    
    char buf[100];
    int len;
    if ((len = read(fd, buf, sizeof(buf))) < 0) {
        perror("read ");
        exit(1);
    }
    
    for (int i = 0; i < len; i++) {
        buf[i] = toupper(buf[i]);
    }
    
    write(STDOUT_FILENO, buf, strlen(buf));
    
    close(fd);
    return 0;
}
