#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define W_END 1
#define R_END 0

int main() {
    
    int fd[2];
    
    // 创建管道
    if (pipe(fd) < 0) {
        perror("pipe ");
        exit(1);
    }
    
    char buf[8]; // 读取缓冲区
    char msg[64]; // 写入管道内容
    for (int i = 0; i < sizeof(msg); i++) {
        msg[i] = 'a';
    }
    
    // 创建子进程
    pid_t pid = fork();
    
    // 父写子读，子进程关闭写端，父进程关闭读端
    if (pid == 0) {
        
        close(fd[W_END]);
        
        // 将可能导致阻塞的读端设置为非阻塞
        int flag = fcntl(fd[R_END], F_GETFL);
        
        flag |= O_NONBLOCK;
        
        fcntl(fd[R_END], F_SETFL, flag);
        
        while (1) {
            
            int len = read(fd[R_END], buf, sizeof(buf));
            
            // 当读端设置为非阻塞，如果此次没有读到内容，就返回 -1
            if (len < 0) {
                
                printf("\ntry again\n");
                
                sleep(1); // 睡一秒钟，然后再去读
                
            } else {
                
                // 读到内容
                printf("子进程 : %d 读到 %d 字节数据\n", getpid(), len);
            }
        }
        
    } else if (pid > 0) {
        
        close(fd[R_END]);
        
        while (1) {
            
            // 父进程每隔 3 秒向管道写 64 字节内容
            if (write(fd[W_END], msg, strlen(msg)) < 0) {
                perror("write ");
                exit(1);
            }
            
            printf("父进程 : %d 写入 %zd 字节数据\n", getpid(), strlen(msg));
            
            sleep(3);
        }
        
    }
    return 0;
}
