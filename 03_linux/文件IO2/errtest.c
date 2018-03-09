#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int fd = open("abc", O_WRONLY);
    
    if (fd < 0) {
        printf("errno = %d\n", errno);
        perror("yanghan");
    }
    
    printf("fd = %d\n", fd);
    
    return 0;
    
}
