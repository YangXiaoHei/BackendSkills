/**
 *  打开文件 /practise/yanghan/yanghan.txt 用于写操作，以追加的方式打开
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define PATH "./yanghan/yanghan.txt"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("至少需要传 1 个参数\n");
        exit(1);
    }
    
    int fd = open(PATH, O_WRONLY | O_APPEND);
    
    if (fd < 0) {
        perror(PATH);
        exit(1);
    }
    
    int len = write(fd, argv[1], strlen(argv[1]));
    
    if (len < 0) {
        perror("write fail : ");
        exit(1);
    }
    
    return 0;
}
