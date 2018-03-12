#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    
    umask(0);
    
    int fd = open("abc", O_CREAT, 0777);
    
    if (fd < 0) {
        perror("abc fail ");
        exit(1);
    }
    
    /**
     *  使 uid 和 euid 不同的办法
     
        1、在当前目录下编译出.o 目标文件
        2、将目标文件 cp 到根目录下，使用 sudo
        3、在根目录下 ls -l 发现 getuid 是 -rwxr-xr-x 权限
        4、cd 到根目录下，./getuid 发现无法执行
        5、使用 sudo chmod 4755 getuid 将其设置为执行时为用户权限
        6、./getuid 此时可以执行，并打印出 getuid() 和 geteuid()
        7、此时 getuid() 代表实际用户 ID YangHan，geteuid（）代表有效用户 ID root
     */
    
    char buf[255];
    printf("工作目录 : %s\n", getcwd(buf, sizeof(buf)));
    printf("实际用户 ID : %d\n", getuid());
    printf("有效用户 ID : %d\n", geteuid());
    
    return 0;
}
