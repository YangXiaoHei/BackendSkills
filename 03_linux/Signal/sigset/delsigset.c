#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    
    sigset_t s;
    sigemptyset(&s);
    
    sigaddset(&s, SIGINT); // SIGINT 被阻塞
    sigaddset(&s, SIGQUIT); // SIGQUIT 被阻塞
    
    sigprocmask(SIG_BLOCK, &s, NULL);
    
    for (int i = 0; i < 10; i++) {
        printf("哈哈 %d\n", i);
        sleep(1);
    }
    
    sigdelset(&s, SIGINT); // 删除 SIGINT 的阻塞，此时只有 SIGQUIT 阻塞
    
    /* 此时信号屏蔽字里 SIGQUIT SIGINT 都被阻塞 */
    
    /* 此时设置字里只有 SIGQUIT 被置为 1 */
    
    sigprocmask(SIG_UNBLOCK, &s, NULL);
    
    /* mask = mask & ~set 因此 SIGQUIT 被解除了阻塞，而 SIGINT 仍然在阻塞中*/
    
    return 0;    
}
