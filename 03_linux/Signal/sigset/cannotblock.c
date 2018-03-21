#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    sigset_t s;
    
    sigemptyset(&s);
    
    if (sigaddset(&s, SIGKILL) < 0) {
        printf("设置阻塞 sigkill 信号失败\n");
    }
    
    if (sigaddset(&s, SIGSTOP) < 0) {
        printf("设置阻塞 sigstop 信号失败\n");
    }
    
    if (sigprocmask(SIG_BLOCK, &s, NULL) < 0) {
        printf("阻塞信号失败\n");
    }
    
    int i = 0;
    while (1) {
        printf("哈哈 i = %d\n", i++);
        sleep(1);
    };
    return 0;
}
