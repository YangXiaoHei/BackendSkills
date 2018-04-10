
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FILE_PATH "/dev/tty"
#define MSG_TIMEOUT "\ntime out\n"
#define MSG_TRY_AGAIN "\ntry again\n"

int main() {
    
    int fd = open(FILE_PATH, O_RDWR | O_NONBLOCK);
    
    if (fd < 0) {
        perror(FILE_PATH);
        exit(1);
    }
    
    int i, len; char buf[1024];
    
    for (i = 0; i < 5; i++) {
        
        len = read(fd, buf, sizeof(buf));
        
        if (len > 0) break;
        
        if (errno != EAGAIN) {
            perror(FILE_PATH);
            exit(1);
        }
        
        write(STDOUT_FILENO, MSG_TRY_AGAIN, strlen(MSG_TRY_AGAIN));
        
        sleep(1);
    }
    
    if (i == 5)
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    else
        write(STDOUT_FILENO, buf, len);
    
    close(fd);
    
    return 0;
}
