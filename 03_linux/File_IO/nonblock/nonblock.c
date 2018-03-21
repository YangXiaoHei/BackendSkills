#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MSG_TRY_AGAIN "\ntry again\n"
#define PATH "/dev/tty"

int main() {
    
    int fd = open(PATH, O_RDWR | O_NONBLOCK);
    
    if (fd < 0) {
        perror(PATH);
        exit(1);
    }
    
    int len; char buf[1024];

tryagain:
    
    len = read(fd, buf, sizeof(buf));
    
    if (len <= 0) {
        
        if (errno == EAGAIN) {
            write(STDOUT_FILENO, MSG_TRY_AGAIN, strlen(MSG_TRY_AGAIN));
            
            sleep(1);
            
            goto tryagain;
        }
        
        perror(PATH);
        exit(1);
    }
    
    write(STDOUT_FILENO, buf, len);
    
    close(fd);
    
    return 0;
    
}
