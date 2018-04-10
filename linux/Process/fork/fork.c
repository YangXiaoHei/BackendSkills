#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    pid_t id = fork();
    
    int n;
    char *msg;
    
    if (id == 0) { // child
        n = 6;
        msg = "I am child";
    } else if (id > 0) { // parent
        n = 3;
        msg = "I am father";
    } else {
        perror("fork fail ");
        exit(1);
    }
    
    while (n-- > 0) {
        printf("pid : %d msg : %s\n", getpid(), msg);
        sleep(1);
    }
    return 0;
}
