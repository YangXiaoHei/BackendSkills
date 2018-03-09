#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buf[1024];
    
    int len;
    
    /**
     *  read 阻塞读
     */
    len = read(STDIN_FILENO, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);
    
    return 0;
}
