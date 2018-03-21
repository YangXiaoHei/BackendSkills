#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define R_END 0
#define W_END 1

int main() {
    
    int fd[2];
    
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    
    char buf[256];
    char msg[1024];
    for (int i = 0; i < sizeof(msg); i++) {
        msg[i] = 'a';
    }
    msg[sizeof(msg) - 1] = '\0';
    
    pid_t pid = fork();
    
    if (pid == 0) {
        
        close(fd[W_END]);
        
        while (1) {
            
            int len = read(fd[R_END], buf, sizeof(buf));
            
            printf("子进程 : %d 读到 %d 字节数据\n", getpid(), len);
            
            if (len == 0) {
                break;
            }
            
            sleep(1);
        }
        
    } else if (pid > 0) {
        
        close(fd[R_END]);
        
        printf("父进程 : %d 写入 %zd 字节数据\n", getpid(), sizeof(msg));
        
        write(fd[W_END], msg, strlen(msg));
        
        close(fd[W_END]);
        
    } else {
        
        perror("fork ");
        
        exit(1);
    }
    return 0;
}
