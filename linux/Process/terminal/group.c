#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

void do_sig(int signo) {
    
    printf("do sig");
    
    int all_release = -1, try_again = 0;
    pid_t pid;
    int stat;
    while ((pid = waitpid(0, &stat, WNOHANG)) != all_release) {
        if (pid == try_again) {
            printf("暂时没有可回收进程\n");
        } else {
            printf("进程 %d 被回收\n", pid);
            
            if (WIFEXITED(stat)) {
                printf("子进程正常退出，状态码是 %d\n", WEXITSTATUS(stat));
            } else if (WIFSIGNALED(stat)) {
                printf("子进程被信号终止，终止信号是 %d\n", WTERMSIG(stat));
            }
        }
    }
}

void sys_err(const char *format, ...) {
    char buf[128];
    va_list vg;
    va_start(vg, format);
    vsprintf(buf, format, vg);
    va_end(vg);
    perror(buf);
    exit(1);
}

int main() {
    
    pid_t pid;
    
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = do_sig;
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);
    
    /* fork 失败 */
    if ((pid = fork()) < 0) {
        sys_err("fork ");
        
        /* 子进程 */
    } else if (pid == 0) {
    
        printf("子进程 : pid : %d gid : %d\n", getpid(), getpgid(0));
        
        /* 避免父进程为子进程设置 PID 时子进程已经结束退出 */
        while (1);
        
        /* 父进程 */
    } else {
        
        sleep(3);
        
        /* 设置子进程 组ID 是自己的 PID */
        if ( setpgid(pid, pid) < 0 )
            sys_err("setpid ");
        
        printf("子进程 : pid : %d gid : %d\n", pid, getpgid(pid));
        
        sleep(3);
        
        printf("父进程 : pid : %d gid : %d\n", getpid(), getpgid(getpid()));
        
        /* 设置父进程 组ID 是自己父进程的 PID */
        if (setpgid(getpid(), getppid()) < 0)
            sys_err("setpid ");
        
        printf("父进程 : pid : %d gid : %d\n", getpid(), getpgid(getpid()));
        
        /* 让父进程自己重新当选组长 */
        if (setpgid(getpid(), getpid()) < 0)
            sys_err("setpid ");
        
        /* 让子进程再次进入到父进程的组，如果不这样，那么 waitpid(0,..) 就没有效果，因为 0 是等待同组所有子进程 */
        if (setpgid(pid, getpid()) < 0)
            sys_err("setpid ");
        
        printf("子进程 : pid : %d gid : %d\n", pid, getpgid(pid));
        
        /* 父进程杀死子进程 */
        printf("父进程杀死子进程");
        kill(pid, SIGINT);
        
        /* 避免子进程被终止时发出 SIGCHLD 信号，但由于父进程已经死了，所以接收不到该 SIGCHLD 信号 */
        sleep(3);
        
    }
    return 0;
}
/**
 *   YangHan:terminal YangHan$ cc group.c -o group
     YangHan:terminal YangHan$ ./group
     子进程 : pid : 22170 gid : 22169
     子进程 : pid : 22170 gid : 22170
     父进程 : pid : 22169 gid : 22169
     父进程 : pid : 22169 gid : 21031
     子进程 : pid : 22170 gid : 22169
     父进程杀死子进程do sig进程 22170 被回收
     子进程被信号终止，终止信号是 2
 */
