#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork fail ");
        exit(1);
    }
    
    if (pid == 0) {
        while (1) {
            printf("I am child %d、my parent is %d\n",
                   getpid(), getppid());
            sleep(1);
        }
    } else if (pid > 0) {
        printf("I am parent %d\n", getpid());
        sleep(4);
        exit(0);
    }
    return 0;
}
