#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    
    pid_t pid; int n = 3;
    while (n-- > 0) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        printf("I am child : %d\n", getpid());
        sleep(3);
    } else if (pid > 0) {
        while (1) {
            sleep(1);
            printf("I am parent : %d\n", getpid());
            pid_t pid_c = waitpid(0, NULL, WNOHANG);
            if (pid_c > 0) {
                printf("wait for child : %d\n", pid_c);
            } else if (pid_c == 0) {
                continue;
            } else {
                perror("waitpid fail ");
                break;
            }
        }
    }
    
    return 0;
}
