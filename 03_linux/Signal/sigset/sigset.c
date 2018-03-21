#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void printsigset(sigset_t s) {
    for (int i = (sizeof(s) << 3) - 1; i >= 0; i--) {
        printf("%-3d", (s >> i) & 1);
    }
    printf("\n");
}

int main() {
    
    sigset_t s, p;
    sigemptyset(&s);
    
    // 阻塞信号 SIGINT
    sigaddset(&s, SIGINT);
    
    // 阻塞信号 SIGTSTP
    sigaddset(&s, SIGTSTP);
    
    sigprocmask(SIG_BLOCK, &s, NULL);
    
    for (int i = 0; i < 8; i++) {
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
