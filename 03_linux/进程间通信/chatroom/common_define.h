
#pragma push
#pragma pack(1)

#define MAX_NAME_LEN 255
#define SERV_FIFO_PATH  "./serv_fifo/serv_fifo"
#define USER_FIFO_PATH "./user_fifo"
#define SERV_READ_MAX_LEN (10 << 10)
#define MAX_USER_NUM  (10)

/**
 *  聊天数据包协议
 */
typedef enum pack_protocol_ {
    PACK_LOGIN_TYPE,
    PACK_CHAT_TYPE,
} chat_pack_protocl;

typedef struct _user {
    char name[MAX_NAME_LEN + 1];
    int fd;
} chat_user;

/**
 *  聊天数据包结构体
 */
typedef struct _pack {
    /* 数据包协议 */
    unsigned short pac_pro;
    /* 数据包来源方 */
    char src_name[MAX_NAME_LEN + 1];
    /* 数据包目的方 */
    char dst_name[MAX_NAME_LEN + 1];
    /* 聊天内容 */
    unsigned char *data;
    /* 聊天内容长度 */
    unsigned short data_len;
} chat_pack;

#pragma pop
