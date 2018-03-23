

/*
 
 SIGCHLD 产生条件
    子进程终止时
    子进程暂停，继续时
        子进程接收到 SIGSTOP 信号停止时
        子进程处在停止态，接收到 SIGCONT 后唤醒时
 
 pid_t waitpid(pid_t pid, int *status, int options)
 
 options
    WNOHANG
    没有子进程结束，立即返回
    WUNTRACED
    如果子进程由于被停止产生的SIGCHLD， waitpid则立即返回
    WCONTINUED
    如果子进程由于被SIGCONT唤醒而产生的SIGCHLD， waitpid则立即返回
 
    获取status
        WIFEXITED(status)
            子进程正常exit终止，返回真
                WEXITSTATUS(status)返回子进程正常退出值
        WIFSIGNALED(status) 子进程被信号终止，返回真
                WTERMSIG(status)返回终止子进程的信号值
        WIFSTOPPED(status) 进程被停止，返回真
                WSTOPSIG(status)返回停止子进程的信号值
        WIFCONTINUED(status) 子进程由停止态转为就绪态，返回真
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sys_err(char *str) {
    perror(str);
    exit(1);
}

void do_sig_child(int signo) {
    
    pid_t pid_c;
    int all_release = -1, try_again = 0;
    int status;
    while ((pid_c = waitpid(0, &status, WNOHANG)) != all_release) {
        /* 当前有子进程，但没有可以回收的子进程 */
        if (pid_c == try_again) {
            printf("无可供回收子进程，3 秒后重试\n");
            for (int i = 3; i > 0; i--) {
                printf("%d\n", i);
                sleep(1);
            }
            /* 回收子进程成功 */
        } else {
            /* 子进程正常退出 */
            if (WIFEXITED(status)) {
                printf("回收子进程 : %zd 退出码 : %d\n", pid_c, WEXITSTATUS(status));
                /* 子进程被信号终止 */
            } else if (WIFSIGNALED(status)) {
                printf("回收子进程 : %zd 被 %d 信号终止\n",pid_c, WTERMSIG(status));
            }
        }
    }
}

//void do_sig_child(int signo) {
//
//    pid_t pid_c;
//    int all_release = -1, try_again = 0;
//
//    /* 如果 waitpid 返回值为 -1，表示所有子进程都回收完毕，
//     * 如果返回 0， 代表现在还有可以回收的子进程，
//     * 但没有退出或者暂停的子进程可供回收
//     */
//    while ((pid_c = waitpid(0, NULL, WNOHANG)) != all_release) {
//        if (pid_c != try_again) {
//            printf("回收子进程 : Child PID = %d\n", pid_c);
//        } else {
//            printf("3 秒后再试试\n");
//            for (int i = 3; i > 0; i--) {
//                printf("%d\n", i);
//                sleep(1);
//            }
//        }
//    }
//    printf("所有子进程都回收完毕，此时 pid_c = %d\n", pid_c);
//}


int main() {
    
    pid_t pid;
    
    int i;
    
    /* 阻塞 SIGCHLD 信号 */
    
    for (i = 0; i < 10; i++) {
        if ((pid = fork()) == 0) {
            break;
        } else if (pid < 0) {
            sys_err("fork ");
        }
    }
    
    if (pid == 0) {
        int n = 16;
        while (n--) {
            printf("Child ID %zd\n", getpid());
            sleep(1);
        }
        return i;
    } else if (pid > 0) {
        
        /* 先设置捕捉函数，再解除阻塞 */
        struct sigaction act;
        act.sa_handler = do_sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        
        sigaction(SIGCHLD, &act, NULL);
        
        while (1) {
            printf("Parent ID %zd\n", getpid());
            sleep(1);
        }
    }
    return 0;
}
