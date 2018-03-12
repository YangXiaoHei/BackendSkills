#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define R_END 0
#define W_END 1

/**
 *  当
 */
int main() {
    
    int fds[2];
    
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(1);
    }
    
    pid_t pid = fork();
    
    char str[] = "helloworld";
    char buf[3];
    
    if (pid == 0) {
        
        // 不断的从读端读取数据
        while (1) {
            
            // 读到 len 个字节
            int len = read(fds[R_END], buf, sizeof(buf) - 1);
            
            buf[2] = '\0';
            
            // 打印读取到的信息
            printf("子进程 : %d 从管道读到 %zd 字节，内容 %s\n",
                   getpid(), len, buf);
            
            // 睡眠 1 s
            sleep(1);
        }
        
    } else if (pid > 0) {
        
        printf("父进程 : %d, 向管道写入 %zd 字节，内容 %s\n",
               getpid(), strlen(str), str);
        
        write(fds[W_END], str, strlen(str));
        
        sleep(8);
        
        printf("父进程 : %d, 向管道写入 %zd 字节，内容 %s\n",
               getpid(), strlen(str), str);
        printf("子进程 %d 被唤醒\n", pid);
        
        write(fds[W_END], str, strlen(str));
        
        pid_t pid_c = wait(NULL);
        
        if (pid_c < 0) {
            perror("wait fail ");
            exit(1);
        }
        
        printf("wait for child : %d\n", pid_c);
        
        exit(1);
        
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}
