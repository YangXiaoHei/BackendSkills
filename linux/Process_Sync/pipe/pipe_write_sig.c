#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define R_END 0
#define W_END 1

void callBack() {
    printf("进程 %d 收到 sigpipe 信号\n",getpid());
}

int main() {
    
    int fd[2];
    
    // 监听 sigpipe 信号
    signal(SIGPIPE,callBack);
    
    if (pipe(fd) < 0) {
        perror("pipe ");
        exit(1);
    }
    
    pid_t pid = fork();
    
    char msg[] = "yanghan is pig";
    char buf[3];
    
    if (pid == 0) {
        
        close(fd[W_END]);
        
        int len = read(fd[R_END], buf, sizeof(buf));
        if (len < 0) {
            perror("read ");
            exit(1);
        }
        
        printf("子进程 : %d 读到 %zd 字节数据\n", getpid(), len);
        
        close(fd[R_END]);
        
    } else if (pid > 0) {
        
        close(fd[R_END]);
        
        while (1) {
            
            if (write(fd[W_END], msg, strlen(msg)) < 0) {
                perror("write ");
                exit(1);
            }
            
            printf("父进程 : %d 写入 %zd 字节数据\n", getpid(),
                   strlen(msg));
        }
        
        if (errno != 0) {
            perror("what happen ");
            exit(1);
        }
        
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}
