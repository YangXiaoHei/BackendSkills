#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    
    alarm(1);
    
    for (int i = 0; 1; i++) {
        printf("i = %d\n", i);
    }
    
    return 0;
}
