#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void do_sig(int num) {
    
    printf("do_sig num = %d\n", num);
}

int main() {
    
    sigset_t s;
    
    sigemptyset(&s);
    
    sigaddset(&s, SIGTSTP);
    
    sigprocmask(SIG_BLOCK, &s, NULL);
    
    struct sigaction act;
    
    act.sa_handler = do_sig;
    
    sigemptyset(&act.sa_mask);
    
    act.sa_flags = 0;
    
    sigaction(SIGUSR1, &act, NULL);
    
    pause();
    
    printf("hello world\n");
    
    return 0;
}
