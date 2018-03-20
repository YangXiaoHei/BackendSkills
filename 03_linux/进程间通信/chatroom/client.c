#include "common_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("命令行至少需要 1 个参数\n");
        exit(1);
    }
    
    if (access(SERV_FIFO_PATH, F_OK) != 0) {
        printf("服务器端总管道不存在!\n");
        exit(1);
    }
    printf("服务器总管道已存在！\n");
    
    int fd = open(SERV_FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        char *err = strerror(errno);
        printf("打开服务器总管道失败 %s\n", err);
        exit(1);
    }
    printf("打开服务器总管道成功！\n");
    
    /* 登陆包 */
    chat_pack *pack = calloc(1, sizeof(chat_pack));
    pack->pac_pro = PACK_LOGIN_TYPE;
    memcpy(pack->src_name, argv[1], strlen(argv[1]));
    bzero(pack->dst_name, sizeof(pack->dst_name));
    pack->data = NULL;
    pack->data_len = 0;
    
    if (write(fd, pack, sizeof(pack)) < 0) {
        char *err = strerror(errno);
        printf("客户端登陆失败 %s\n", err);
        exit(1);
    }
    printf("登陆包成功发出\n");
    
    free(pack);
    
    ssize_t len;
    
    int str_len = strlen(USER_FIFO_PATH) + strlen(argv[1]) + 1;
    char * user_fifo_path = calloc(1, str_len);
    sprintf(user_fifo_path, "%s/%s", USER_FIFO_PATH, argv[1]);
    user_fifo_path[str_len] = '\0';
    
    char buf[4096];
    bzero(buf, sizeof(buf));
    
    if (access(user_fifo_path, F_OK) == 0) {
        int fd = open(user_fifo_path, O_RDWR);
        if (fd < 0) {
            perror("user fifo open");
            exit(1);
        }
        
        int mode = fcntl(fd, F_GETFL);
        mode |= O_NONBLOCK;
        fcntl(fd, F_SETFD, mode);
        
        while (1) {
            len = read(fd, buf, sizeof(buf));
            
            if (len < 0 && errno != EAGAIN) {
                char *err = strerror(errno);
                printf("客户端读取出错 : %s\n", err);
                exit(1);
            }
            
            if (len > 0) {
                
            }
            
        }
    } else {
        printf("%s 不存在\n", user_fifo_path);
    }
}

