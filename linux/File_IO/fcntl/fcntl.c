#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MSG_TRY_AGAIN "\ntry again\n"

int main() {
    
    int flag = fcntl(STDIN_FILENO, F_GETFL);
    
    flag |= O_NONBLOCK;
    
    fcntl(STDIN_FILENO, F_SETFL, flag);
    
    int len; char buf[1024];
    
tryagain:
    
    len = read(STDIN_FILENO, buf, sizeof(buf));
    
    if (len <= 0) {
        
        if (errno == EAGAIN) {
            write(STDOUT_FILENO, MSG_TRY_AGAIN, strlen(MSG_TRY_AGAIN));
            
            sleep(1);
            
            goto tryagain;
        }
        
        perror("error : ");
        exit(1);
    }
    
    write(STDOUT_FILENO, buf, len);
    
    return 0;
}
