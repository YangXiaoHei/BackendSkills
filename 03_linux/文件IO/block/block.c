#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main() {
    
    char buf[BUF_SIZE];
    
    int len = read(STDIN_FILENO, buf, sizeof(buf));
    
    if (len < 0) {
        perror ("read from stdin : ");
        exit(1);
    }
    
    write(STDOUT_FILENO, buf, len);
    
    return 0;
    
}
