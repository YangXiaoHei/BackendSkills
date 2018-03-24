#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork ");
        exit(1);
    } else if (pid > 0) {
        exit(0);
    }
    
    printf("pid = %d gid = %d sid = %d\n", getpid(), getpgid(getpid()), getsid(getpid()));
    
    setsid();
    
    printf("pid = %d gid = %d sid = %d\n", getpid(), getpgid(getpid()), getsid(getpid()));
    
    
    return 0;
}
