#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void do_sig(int num) {
    printf("num = %d\n", num);
}

int main() {
    
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    
    sa.sa_handler = do_sig;
    
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    
    while (1) {
        printf("***************\n");
        sleep(1);
    }
    
    return 0;
}
