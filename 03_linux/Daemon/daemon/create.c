#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    
    /* 创建父进程，然后父进程退出 */
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork ");
        exit(1);
    }
    
    /* 退出父进程 */
    if (pid > 0)
        exit(0);
    
    /* 脱离当前控制终端 */
    setsid();
    
    /* 切换工作目录 */
    if (chdir("/") < 0) {
        perror("chdir ");
        exit(1);
    }
    
    /* 设置守护进程 umask(0) */
    umask(0);
    
    /* 重定向 0, 1, 2 到 /dev/null 因为已经失去控制终端，再操作 0 1 2 没意义 */
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
    
    /* 守护线程干活 */
    while (1);
}
