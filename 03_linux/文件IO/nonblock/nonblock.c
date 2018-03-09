#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MSG_TRY_AGAIN "\ntry again\n"

int main() {
    
    int fd = open("/dev/tty", O_RDWR | O_NONBLOCK);
    
    if (fd < 0) {
        perror("/dev/tty ");
        exit(1);
    }
    
    int len; char buf[1024];

tryagain:
    
    len = read(fd, buf, sizeof(buf));
    
    if (len <= 0) {
        
        write(STDOUT_FILENO, MSG_TRY_AGAIN, strlen(MSG_TRY_AGAIN));
        
        sleep(1);
        
        goto tryagain;
    }
    
    write(STDOUT_FILENO, buf, len);
    
    close(fd);
    
    return 0;
    
}
