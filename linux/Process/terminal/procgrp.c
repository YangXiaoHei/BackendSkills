#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork ");
        exit(1);
    } else if (pid == 0) {
        
        /* 获取进程 ID */
        printf("child process PID is %d\n", getpid());
        /* 获取当前进程组 ID */
        printf("Group ID is %d\n", getpgrp());
        /* 获取当前进程组的组 ID */
        printf("Group ID is %d\n", getpgid(0));
        /* 获取指定进程 ID 的进程组 */
        printf("Group ID is %d\n", getpgid(getpid()));
        exit(0);
    }
    
    sleep(3);
    
    printf("parent process PID is %d\n", getpid());
    printf("Group ID is %d\n", getpgrp());
    
    return 0;
}
