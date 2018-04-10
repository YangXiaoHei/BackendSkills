#include <stdio.h>
#include <unistd.h>

int main() {
    
    printf("fd 0 : %s\n", ttyname(STDIN_FILENO)); /* 测终端文件描述符 */
    printf("fd 1 : %s\n", ttyname(STDOUT_FILENO));
    printf("fd 2 : %s\n", ttyname(STDERR_FILENO));
    
    return 0;
}
