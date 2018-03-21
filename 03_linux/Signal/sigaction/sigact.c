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
    sa.sa_flags = 0;
    sa.sa_handler = do_sigint;
    sigaction(SIGINT, &sa, NULL);
    
    while (1) {
        printf("************\n");
        sleep(1);
    }
    return 0;
}
