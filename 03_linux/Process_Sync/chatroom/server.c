#include "common_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* 创建一个私有 fifo */
int cre_private_fifo(const char *fname) {
    
    int user_fifo_fd = 0;
    
    // 为 fifo 名字分配内存
    ssize_t str_len = strlen(USER_FIFO_PATH) + strlen("/") + strlen(fname) + 1;
    char *fifo_path = calloc(1, str_len);
    sprintf(fifo_path, "%s/%s", USER_FIFO_PATH, fname);
    fifo_path[str_len - 1] = '\0';
    
    // 如果 fifo 存在
    if (access(fifo_path, F_OK) == 0) {
        printf("用户私有管道 %s 已经被创建\n", fifo_path);
    } else { // 如果不存在，创建
        user_fifo_fd = mkfifo(fifo_path, 0777);
        if (user_fifo_fd < 0) { // 创建失败
            printf("用户私有管道 %s 创建失败\n", USER_FIFO_PATH);
            return -1;
        }
    }
    return 0;
}

/* 发送给指定 用户 */
//int send_to_user(const char *src,
//                 const char *dst,
//                 char *data,
//                 short dat_len,
//                 chat_user **login_list) {
//
//
//
//
//}

/* 通知登陆列表中所有人 */
int notify_all(chat_pack *pack, chat_user ** login_list) {
    for (int i = 0; i < MAX_USER_NUM; i++) {
        
        chat_user *login_user = NULL;
        
        if ((login_user = login_list[i]) != NULL) {
            
            // 广播消息
            char msg[300];
            sprintf(msg, "用户 : %s 上线\n", pack->src_name);
            
            // 创建包
            chat_pack *send_pack = calloc(1, sizeof(chat_pack));
            if (send_pack == NULL) {
                printf("创建回复包出错\n");
                return -1;
            }
            memcpy(send_pack->src_name, pack->src_name, strlen(pack->src_name));
            memcpy(send_pack->dst_name, login_user->name, strlen(login_user->name));
            memcpy(send_pack->data, msg, strlen(msg));
            send_pack->data_len = strlen(msg);
            send_pack->pac_pro = PACK_LOGIN_TYPE;
            
            // 向客户端写入数据
            if (write(login_user->fd, send_pack, sizeof(send_pack)) < 0) {
                char *err = strerror(errno);
                printf("服务器向客户端 %s 写入数据出错 : %s\n", login_user->name, err);
                return -1;
            }
        }
    }
    return 0;
}

/* 创建一个用户 */
chat_user *cre_user(char *name, int fd) {
    chat_user *user = calloc(1, sizeof(chat_user));
    if (user == NULL) {
        printf("user 创建失败\n");
        return NULL;
    }
    memcpy(user->name, name, strlen(name));
    user->fd = fd;
    return user;
}

/* 添加一个登陆用户 */
int add_user_to_login_list(chat_user *user, chat_user **login_list) {
    int cur = 0;
    while (login_list[cur] != NULL) {
        cur++;
    }
    login_list[cur] = user;
    return 0;
}

/* 执行登陆流程 */
int process_login_pack(chat_pack *pack, chat_user ** login_list) {
    
    printf("执行登陆流程\n");
    
    /* 创建一个私有 fifo */
    int user_fifo_fd = cre_private_fifo(pack->src_name);
    if (user_fifo_fd < 0) {
        return -1;
    }
    printf("%s 与服务器的 fifo 已经创建成功!\n", pack->src_name);
    
    /* 创建一个登陆用户 */
    chat_user *user = cre_user(pack->src_name, user_fifo_fd);
    if (user == NULL) {
        return -1;
    }
    printf("创建登陆用户 %s 成功!\n", pack->src_name);
    
    /*  向所有人广播  */
    if (notify_all(pack, login_list) < 0) {
        return -1;
    }
    printf("%s 的登陆消息通知了所有人!\n", pack->src_name);
    
    /* 将登陆用户添加到登陆列表 */
    if (add_user_to_login_list(user, login_list) < 0) {
        return -1;
    }
    printf("%s 成功添加到登陆列表中!\n", pack->src_name);
    
    return 0;
}

int process_data_pack(chat_pack *pack, chat_user ** login_list) {
    int found = 0;
    
    // 在登陆列表中找发送目标用户
    for (int i = 0; i < MAX_USER_NUM; i++) {
        if (strcmp(login_list[i]->name, pack->dst_name) == 0) {
            found = 1;
            if (write(login_list[i]->fd, pack->data, pack->data_len) < 0) {
                const char *err = strerror(errno);
                printf("用户 : %s 向用户 : %s 发送信息 %s 出错 : %s\n",
                       pack->src_name,
                       pack->dst_name,
                       pack->data,
                       err);
                return -1;
            }
        }
    }
    if (found != 1) {
        printf("没有找到发送信息的目标用户\n");
    }
    return 0;
}

int init_comman_fd(int *serv_fd) {
    int serv_comman_fd;
    
    /* 创建总管道 fifo */
    if (access(SERV_FIFO_PATH, F_OK) != 0) {
        serv_comman_fd = mkfifo(SERV_FIFO_PATH, 0777);
    } else {
        serv_comman_fd = open(SERV_FIFO_PATH, O_RDWR);
    }
    if (serv_comman_fd < 0) {
        perror("serv open fifo ");
        return -1;
    }
    
    *serv_fd = serv_comman_fd;
    
    /* 设置总管道为非阻塞 */
    int mode = fcntl(serv_comman_fd, F_GETFL);
    mode |= O_NONBLOCK;
    if (fcntl(serv_comman_fd, F_SETFD, mode) < 0) {
        perror("serv fcntl");
        return -1;
    }
    return 0;
}

int clear_buf(char *buf) {
    bzero(buf, SERV_READ_MAX_LEN);
    return 1;
}

int main() {
    
    // 初始化服务器主 fifo
    int serv_fd;
    if (init_comman_fd(&serv_fd) < 0) {
        printf("创建总管道失败\n");
        exit(1);
    }
    printf("创建总管道成功\n");
    
    // 用于和用户私自通信
    chat_user **login_list = NULL;
    if ((login_list = calloc(MAX_USER_NUM, sizeof(chat_user *))) == NULL) {
        printf("创建登陆列表失败\n");
        exit(1);
    }
    printf("创建登陆列表成功\n");
    
    ssize_t len;
    char buf[SERV_READ_MAX_LEN];
    
    while (1) {
        
        len = read(serv_fd, buf, sizeof(buf));
    
        // 读取操作出错
        if (len < 0) {
            if (errno != EAGAIN) {
                perror("服务器 read");
                break;
            } else {
                printf("没有用户向服务器发送数据\n");
            }
        }
        printf("读取到 %zd 字节数据\n", len);
        
        // 根据包协议执行不同操作
        int ret = 0;
        
        switch (((chat_pack *)buf)->pac_pro) {
            case PACK_LOGIN_TYPE : {
                ret = process_login_pack((chat_pack *)buf, login_list);
            } break;
            case PACK_CHAT_TYPE : {
                ret = process_data_pack((chat_pack *)buf, login_list);
            } break;
            default: break;
        }
        
        if (ret != 0) {
            printf("服务器跳出主循环\n");
            break;
        } else {
            clear_buf(buf);
        }
        
        usleep(1000000 * 0.1);
    }
    
    close(serv_fd);
    
    return 0;
}


