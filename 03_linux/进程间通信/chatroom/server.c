#include "common_define.h"

#define SERV_FIFO_PATH  "./serv_fifo/serv_fifo"
#define SERV_READ_MAX_LEN (10 << 10)
#define MAX_USER_NUM  (10)

///**
// *  聊天数据包协议
// */
//typedef enum pack_protocol_ {
//    PACK_LOGIN_TYPE,
//    PACK_CHAT_TYPE,
//    PACK_LOGOUT_TYPE
//} chat_pack_protocl;
//
//typedef struct _user {
//    char name[MAX_NAME_LEN + 1];
//    unsigned short len;
//    int fd;
//} chat_user;
//
///**
// *  聊天数据包结构体
// */
//typedef struct _pack {
//    /* 数据包总长度 */
//    unsigned short pac_len
//    /* 数据包协议 */
//    unsigned short pac_pro,
//    /* 数据包来源方 */
//    char src_name[MAX_NAME_LEN + 1],
//    /* 数据包目的方 */
//    char dst_name[MAX_NAME_LEN + 1],
//    /* 聊天内容 */
//    unsigned char *data;
//    /* 聊天内容长度 */
//    unsigned short data_len;
//} chat_pack;

int process_login_pack(chat_pack *pack, chat_user ** login_list) {
    char *name = pack->src_name;
    int noti_fds[MAX_USER_NUM], cnt = 0;
    for (int i = 0; i < MAX_USER_NUM; i++) {
        if (strcmp(login_list[i]->name, name) == 0) {
            noti_fds[cnt++] = login_list[i]->fd;
        }
    }
    for (int i = 0; i < cnt; i++) {
        int fd = noti_fds[i];
        
        
    }
}

int process_data_pack(chat_pack *pack, chat_user ** login_list) {
    
}

int process_logout_pack(chat_pack *pack, chat_user ** login_list) {
    
}

int init_comman_fd() {
    int serv_comman_fd;
    
    if (access(SERV_FIFO_PATH, F_OK) != 0) {
        serv_comman_fd = mkfifo(SERV_FIFO_PATH, 0777);
    } else {
        serv_comman_fd = open(SERV_FIFO_PATH, O_RDWR);
    }
    if (serv_comman_fd < 0) {
        perror("serv open fifo ");
        exit(1);
    }
    int mode = fcntl(serv_comman_fd, F_GETFL);
    mode |= O_NONBLOCK;
    
    if (fcntl(serv_comman_fd, F_SETFD, mode) < 0) {
        perror("serv fcntl");
        eixt(1);
    }
    return serv_comman_fd;
}

int clear_buf(char *buf) {
    bzero(buf, SERV_READ_MAX_LEN);
    return 1;
}

int main() {
    
    // 初始化服务器主 fifo
    int serv_fd = init_comman_fd();
    
    // 用于和用户私自通信
    chat_user **login_list = calloc(MAX_USER_NUM, sizeof(chat_user *));
    
    int cur_user_num = 0;
    
    int len;
    char buf[SERV_READ_MAX_LEN];
    
    while (1) {
        
        len = read(serv_fd, buf, sizeof(buf));
        
        // 读取操作出错
        if (len < 0) {
            if (errno == EAGAIN) {
                continue;
            }
            perror("serv read");
            break;
        }
        
        // 读取包出错
        if (len < 2) {
            printf("服务器读取包错误，将包丢弃\n");
            continue;
        }
        
        // 包长信息出错
        int pack_len;
        memcpy(&pack_len, buf, 2);
        if (pack_len != len) {
            printf("服务器读包长度错误，将包丢弃\n");
            continue;
        }
        
        switch (pack->pac_pro) {
            case : PACK_LOGIN_TYPE {
                process_login_pack((chat_pack *)buf, login_list);
            } break;
            case : PACK_CHAT_TYPE {
                process_data_pack((chat_pack *)buf, login_list);
            } break;
            case : PACK_LOGOUT_TYPE {
                process_logout_pack((chat_pack *)buf, login_list);
            } break;
            default: break;
        }
    }
    
    close(serv_fd);
    
    return 0;
}
