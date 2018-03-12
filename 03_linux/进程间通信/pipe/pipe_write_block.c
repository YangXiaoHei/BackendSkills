#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W_END 1
#define R_END 0

int main() {
    
    int fd[2];
    
    if (pipe(fd) < 0) {
        perror("fd ");
        exit(1);
    }
    
    /**
     *  根据测试，我电脑上 _PC_PIPE_BUF 值为 512 B
     */
    pid_t pid = fork();
    
    int r_len = 1024 * 2;
    char rbuf[r_len];
    
    int w_len = 1024 * 10;
    char buf[w_len];
    
    for (int i = 0; i < w_len; i++) {
        buf[i] = 'a';
    }
    
    /**
     *  父写子读
     */
    if (pid == 0) {
        
        close(fd[W_END]);
        
        while (1) {

            int len = read(fd[R_END], rbuf, r_len - 1);

            rbuf[r_len - 1] = '\0';

            printf("子进程 %d 读到 %d KB\n",
                   getpid(),
                   len / 1024);

            // 每读 2 个字节就睡 1 秒钟
            sleep(1);
        }
        
    } else if (pid > 0) {
        
        close(fd[R_END]);
        
        while (1) {
        
            int i = 0;
        
            if (write(fd[W_END], buf, w_len) < 0) {
                perror("write ");
                exit(1);
            }
            
            printf("父进程 %d 写入 %d KB i = %d\n", getpid(),
                   w_len / 1024, i++);
        }
    } else {
        perror("fork ");
        exit(1);
    }
    return 0;
}
