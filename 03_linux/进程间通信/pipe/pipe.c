#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_ENDIAN 0
#define WRIT_ENDIAN 1

int main() {
    
    int fds[2];
    
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(1);
    }
    
    pid_t pid = fork();
    
    char str[] = "test string\n";
    char buf[1024];
    
    /**
     *  父写子读
     */
    if (pid == 0) { // 子进程
        close(fds[READ_ENDIAN]);
        printf("pid %d : 向子进程写 %s\n", getpid(), str);
        write(fds[WRIT_ENDIAN], str, strlen(str));
        wait(NULL);
    } else if (pid > 0) { // 父进程
        close(fds[WRIT_ENDIAN]);
        int len = read(fds[READ_ENDIAN], buf, sizeof(buf));
        printf("pid %d : 从父进程读 %s\n", getpid(), buf);
        write(STDOUT_FILENO, buf, len);
    } else {
        perror("fork");
        exit(1);
    }
}
