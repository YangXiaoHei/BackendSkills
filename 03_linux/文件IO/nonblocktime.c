#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MSG_TRY "\ntry again\n"
#define MSG_TIMEOUT "\ntime out\n"

int main() {
    
    int fd, i, len;
    char buf[1024];
    
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    
    if (fd < 0) {
        perror("/dev/tty ");
        exit(1);
    }
    
    for (i = 0; i < 5; i++) {
        
        len = read(fd, buf, sizeof(buf));
        
        if (len > 0) break;
        
        if (errno != EAGAIN) {
            perror("read dev/tty ");
            exit(1);
        }
        
        sleep(1);
        write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
    }
    if (i == 5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    } else {
        write(STDOUT_FILENO, buf, len);
    }
    close(fd);
    
    return 0;
}
