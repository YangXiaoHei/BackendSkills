#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void do_sig(int num) {
    /* do nothing */
}

/**
 *  有 Bug 的 mysleep
 */
void mysleep(unsigned int secs) {
    
    signal(SIGALRM, do_sig);
    
    alarm(secs);
    
    pause();
}

unsigned int mysleep_cor(unsigned int nsecs) {
    
    /* catch SIGALRM signal  and save old action */
    struct sigaction newact, oldact;
    newact.sa_flags = 0;
    newact.sa_handler = do_sig;
    sigemptyset(&newact.sa_mask);
    sigaction(SIGALRM, &newact, &oldact);
    
    
    /* block SIGALRM signal */
    sigset_t newmask, oldmask, suspmask;
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    
    /* 收到 SIGALRM 信号默认动作是终止进程，而且 SIG_DEL 也是默认终止，
       SIG_IGN 是忽略，所以需要用户自定义捕获函数
     */
    alarm(nsecs);
    
    /* unblock and suspend */
    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);
    sigsuspend(&suspmask);
    
    unsigned int unslept = alarm(0);
    
    /* reset previous action */
    sigaction(SIGALRM, &oldact, NULL);
    
    /* reset previous signal mask */
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    
    return unslept;
}

int main() {
    
    printf("开始睡觉\n");
    
    for (int i = 0; i < 3; i++) {
        printf("%d\n", i);
        mysleep_cor(1);
    }
    
    printf("睡眠结束\n");
    
    return 0;
}
