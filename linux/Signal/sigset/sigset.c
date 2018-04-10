#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* 左边高字节右边低字节打印每个 bit 位 */
void printsigset(sigset_t s) {
    for (int i = (sizeof(s) << 3) - 1; i >= 0; i--) {
        printf("%-3d", (s >> i) & 1);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("./sigset 3\n");
        exit(1);
    }
    
    int t = atoi(argv[1]);
    if (t < 0) {
        printf("invalid time\n");
        exit(1);
    }
    
    sigset_t s, p;
    sigemptyset(&s);
    
    // 阻塞信号 SIGINT
    sigaddset(&s, SIGINT);
    
    // 阻塞信号 SIGTSTP
    sigaddset(&s, SIGTSTP);
    
    // 阻塞信号 SIGQUIT
    sigaddset(&s, SIGQUIT);
    
    // 设置信号屏蔽字
    sigprocmask(SIG_BLOCK, &s, NULL);
    
    for (int i = 0; i < t; i++) {
        sigpending(&p);
        printsigset(p);
        sleep(1);
    }
    
    sigemptyset(&s);
    
    sigprocmask(SIG_SETMASK, &s, NULL);
    
    for (int i = 0; i < 3; i++) {
        sigpending(&p);
        printsigset(p);
        sleep(1);
    }
    
    return 0;
}
