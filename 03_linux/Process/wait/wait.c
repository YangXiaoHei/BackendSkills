#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    int n = 3; pid_t pid;
    while (n-- > 0) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        printf("I am child : %zd\n", getpid());
        sleep(3);
    } else if (pid > 0) {
        while (1) {
            pid_t pid_c = wait(NULL);
            if (pid_c == -1) {
                perror("wait fail");
                break;
            } else {
                printf("wait for child : %zd\n", pid_c);
                sleep(1);
            }
        }
    } else {
        
    }
    return 0;
}
