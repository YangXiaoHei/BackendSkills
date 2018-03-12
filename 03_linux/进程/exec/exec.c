#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    
    printf("程序开始执行\n");
    
    
//     execl(const char *path, const char *arg0, ... /*, (char *)0 */);
//
//    int
//    execle(const char *path, const char *arg0, ... /*, (char *)0, char *const envp[] */);
//
//    int
//    execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
//
//    int
//    execv(const char *path, char *const argv[]);
//
//    int
//    execvp(const char *file, char *const argv[]);
    
    // 路径不能省略
//    execl("/bin/ls","ls" "-l", NULL);
    
    // 路径可以省略，只传文件名，然后该函数会从 PATH 目录开始搜索
    execlp("ls", "ls", "-l","/", NULL);
    
    
    printf("hello world");
    
    return 0;
}
