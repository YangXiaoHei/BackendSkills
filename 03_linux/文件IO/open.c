#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
//    char buf[] = "hello world";
    char buf[] = "lijie";
    
    if (argc < 2) {
        printf("./app filename\n");
        exit(1);
    }
    /**
     *  如果文件不存在，那么创建该文件，并设定权限位
     
        如果不指定权限，会发生什么事
     */
//    fd = open(argv[1], O_CREAT | O_RDWR, 0644);
    
    /**
     *  如果文件已存在，那么只需要两个参数
     */
//    fd = open(argv[1], O_RDWR);
    
    // O_WRONLY
    // O_RDONLY
    fd = open(argv[1], O_RDWR | O_APPEND);
    printf("fd = %d\n", fd);
    
    /**
     *  write(int fd, const void *buf, ssize_t len);
     */
    
    write(fd, buf, sizeof(buf));
    
    // file descriptor
    /**
     *  returns zero if success
     */
    close(fd);
    
    return 0;
}
