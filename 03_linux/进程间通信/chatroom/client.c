#include "common_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* 获取私有管道路径 */
char *get_fifo_path(const char *uname) {
    ssize_t str_len = strlen(USER_FIFO_PATH) + strlen("/") + strlen(uname) + 1;
    char * user_fifo_path = calloc(1, str_len);
    sprintf(user_fifo_path, "%s/%s", USER_FIFO_PATH, uname);
    user_fifo_path[str_len - 1] = '\0';
    return user_fifo_path;
}

/* 将文件描述符转化为非阻塞 */
int conv_to_nblock(int fd) {
    int mode = fcntl(fd, F_GETFL);
    mode |= O_NONBLOCK;
    if (fcntl(fd, F_SETFD, mode) < 0) {
        return -1;
    }
    return 0;
}

/* 创建登陆包 */
chat_pack *cre_pack(chat_pack_protocl pro, char *src, char *dst, char *data, ssize_t dat_len) {
    chat_pack *pack = calloc(1, sizeof(chat_pack));
    pack->pac_pro = pro;
    memcpy(pack->src_name, src, strlen(src));
    if (dst != NULL) {
        memcpy(pack->dst_name, dst, strlen(dst));
    }
    if (dat_len != 0) {
        memcpy(pack->data, data, dat_len);
    } else {
        pack->data = NULL;
        pack->data_len = 0;
    }
    return pack;
}

/* 处理数据包 */
int process_recv_data(chat_pack *pack) {
    char *msg = NULL;
    switch (pack->pac_pro) {
            
            /* 处理登陆包 */
        case PACK_LOGIN_TYPE: {
            ssize_t len = strlen(pack->src_name) + strlen("登陆成功\n") + 1;
            msg = calloc(1, len);
            if (msg == NULL) {
                return -1;
            }
            sprintf(msg, "%s登陆成功\n", pack->src_name);
            msg[len - 1] = 0;
            printf("%s", msg);
        }  break;
            
            /* 处理聊天包 */
        case PACK_CHAT_TYPE: {
            ssize_t len = strlen(pack->src_name) + strlen(" To ") + strlen(pack->dst_name) + strlen(" : ") + pack->data_len + strlen("\n") + 1;
            msg = calloc(1, len);
            if (msg == NULL) {
                return -1;
            }
            sprintf(msg, "%s To %s : %s\n", pack->src_name, pack->dst_name, pack->data);
            msg[len - 1] = 0;
            printf("%s", msg);
        }  break;
        default: break;
    }
    free(msg);
    return 0;
}


int main(int argc, char *argv[]) {
    
    /* 判断用户是否传入登录名 */
    if (argc < 2)
        usr_err("命令行至少需要 1 个参数\n");
    
    /* 判断总管道是否存在 */
    if (access(SERV_FIFO_PATH, F_OK) != 0)
        usr_err("服务器端总管道不存在!\n");
    printf("服务器总管道已存在！\n");
    
    /* 打开总管道 */
    int fd = open(SERV_FIFO_PATH, O_WRONLY);
    if (fd < 0)
        usr_err("打开服务器总管道失败 %s\n", strerror(errno));
    printf("打开服务器总管道成功！\n");
    
    /* 登陆包 */
    chat_pack *pack = cre_pack(PACK_LOGIN_TYPE, argv[1], NULL, NULL, 0);
    
    /* 发送登陆包 */
    ssize_t w_len = 0;
    if ((w_len = write(fd, pack, sizeof(chat_pack))) < 0)
        usr_err("打开服务器总管道失败 %s\n", strerror(errno));
    printf("登陆包成功发出，总共 %zd 字节\n", sizeof(pack));
    
    /* 释放登陆包 */
    free(pack);
    
    /* 私有 fifo 路径 */
    char *user_fifo_path = get_fifo_path(argv[1]);
    
    /* 如果私有 fifo 存在 */
    if (access(user_fifo_path, F_OK) == 0) {
        
        /* 打开私有 fifo */
        int priv_fd = open(user_fifo_path, O_RDWR);
        if (priv_fd < 0) {
            free(user_fifo_path);
            sys_err("user fifo open", 1);
        }
        free(user_fifo_path);
        
        /* 转换为非阻塞读写 */
        conv_to_nblock(priv_fd);
        
        /* 缓冲区大小 4KB */
        char buf[4 << 10];
        bzero(buf, sizeof(buf));
        ssize_t len;
        
        while (1) {
            len = read(priv_fd, buf, sizeof(buf));
            
            if (len < 0 && errno != EAGAIN)
                usr_err("%s 从私有管道读取数据失败 %s\n",argv[1], strerror(errno));
            
            if (len > 0) {
                process_recv_data((chat_pack *)buf);
            }
        }
    } else {
        printf("%s 不存在\n", user_fifo_path);
    }
}


