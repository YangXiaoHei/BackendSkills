#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void do_sigint(int num) {
    for (int i = 0; i < 5; i++) {
        printf("SIG_INT\n");
        sleep(1);
    }
}

int main() {
    
    // 捕获 SIGINT 信号
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    
    // 在 do_sigint 执行完前都屏蔽 SIGQUIT 信号
    // 但是在执行完捕获函数后，SIGQUIT 未决位是 1，并且临时临时信号阻塞集被还原，因此执行 SIGQUIT 默认行为，终止该进程
    sigaddset(&sa.sa_mask, SIGQUIT);
    
    sa.sa_flags = 0;
    sa.sa_handler = do_sigint;
    sigaction(SIGINT, &sa, NULL);
    
    while (1) {
        printf("************\n");
        sleep(1);
    }
    return 0;
}
