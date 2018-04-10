//
//  main.c
//  C1
//
//  Created by YangHan on 2018/3/27.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <event.h>
#include <event2/event.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int flag = 1;

/*************************** Network ************************************/
void net_read_callback(struct bufferevent *bev, void *ctx) {
    printf("套接字 - 读 - 回调\n");
    char buf[1024];
    bzero(buf, sizeof(buf));
    ssize_t len = bufferevent_read(bev, buf, sizeof(buf));
    if (len < 0) {
        printf("buffevent_read 读取失败\n");
        return;
    }
    printf("from server : 【%s】\n", buf);
}

void net_write_callback(struct bufferevent *bev, void *ctx) {
    printf("套接字 - 写 - 回调\n");
}

void net_event_callback(struct bufferevent *bev, short event, void *ctx) {
    printf("套接字 - 异常 - 回调\n");
    /* 连接完成 */
    if (event & BEV_EVENT_CONNECTED) {
        printf("连接完成\n");
        
        /* 未知错误 */
    } else if (event & BEV_EVENT_ERROR) {
        int err = EVUTIL_SOCKET_ERROR();
        const char *errstr = evutil_socket_error_to_string(err);
        printf("buffer_event_callback 其他错误 -------- %s\n", errstr);
        
        /* 写错误 */
    } else if (event & BEV_EVENT_WRITING) {
        if (event & BEV_EVENT_TIMEOUT) {
            printf("buffer_event_callback 写异常 | 超时 \n");
        } else if (event & BEV_EVENT_EOF) {
            printf("buffer_event_callback 写异常 | EOF \n");
        }
        
        /* 读错误 */
    } else if (event & BEV_EVENT_READING) {
        if (event & BEV_EVENT_TIMEOUT) {
            printf("buffer_event_callback 读异常 | 超时\n");
        } else if (event & BEV_EVENT_EOF) {
            printf("buffer_event_callback 读异常 | EOF \n");
        }
    }
}
/******************************************************************/

/*************************** Terminal ************************************/
void local_read_callback(struct bufferevent *bev, void *ctx) {
    printf("终端 - 读 - 回调\n");
    char buf[1024];
    bzero(buf, sizeof(buf));
    struct bufferevent *net = (struct bufferevent *)ctx;
    ssize_t len = bufferevent_read(bev, buf, sizeof(buf));
    if (len < 0) {
        printf("从终端读取失败\n");
        return;
    }
    if (bufferevent_write(net, buf, len) < 0) {
        printf("向服务器发数据失败\n");
    }
    printf("send : 【%s】\n", buf);
}

void local_write_callback(struct bufferevent *bev, void *ctx) {
    printf("终端 - 写 - 回调\n");
}

void local_event_callback(struct bufferevent *bev, short event, void *ctx) {
    printf("终端 - 异常 - 回调\n");
    /* 连接完成 */
    if (event & BEV_EVENT_CONNECTED) {
        printf("连接完成\n");
        
        /* 未知错误 */
    } else if (event & BEV_EVENT_ERROR) {
        int err = EVUTIL_SOCKET_ERROR();
        const char *errstr = evutil_socket_error_to_string(err);
        printf("buffer_event_callback 其他错误 -------- %s\n", errstr);
        
        /* 写错误 */
    } else if (event & BEV_EVENT_WRITING) {
        if (event & BEV_EVENT_TIMEOUT) {
            printf("buffer_event_callback 写异常 | 超时 \n");
        } else if (event & BEV_EVENT_EOF) {
            printf("buffer_event_callback 写异常 | EOF \n");
        }
        
        /* 读错误 */
    } else if (event & BEV_EVENT_READING) {
        if (event & BEV_EVENT_TIMEOUT) {
            printf("buffer_event_callback 读异常 | 超时\n");
        } else if (event & BEV_EVENT_EOF) {
            printf("buffer_event_callback 读异常 | EOF \n");
        }
    }
}
/******************************************************************/

int  tcp_socket(struct sockaddr_in serv_add) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    return sockfd;
}

void establish_connection(const char *ip, short port) {
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(struct sockaddr_in));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_aton(ip, &serv.sin_addr);
    
    // socket fd
    int sockfd = tcp_socket(serv);
    
    // loop
    struct event_base *base = event_base_new();
    
    // net
    struct bufferevent *net = bufferevent_new(sockfd,
                                                net_read_callback,
                                                net_write_callback,
                                                net_event_callback,
                                                NULL);
    bufferevent_base_set(base, net);
    bufferevent_socket_connect(net,
                               (struct sockaddr *)&serv,
                               sizeof(struct sockaddr_in));
    bufferevent_settimeout(net, 0, 3);
    bufferevent_enable(net, EV_READ | EV_WRITE);
    
    // terminal
    struct bufferevent *loc = bufferevent_new(STDIN_FILENO,
                                              local_read_callback,
                                              local_write_callback,
                                              local_event_callback,
                                              net);
    bufferevent_base_set(base, loc);
    bufferevent_enable(loc, EV_READ);
    
    // max rd wr capacity
    ssize_t max_rd_len = bufferevent_get_max_to_read(net);
    ssize_t max_wr_len = bufferevent_get_max_to_write(net);
    printf("\n-------------------------------------\n");
    printf("最大读容量 : %ld B, 最大写容量 : %ld B", max_rd_len, max_wr_len);
    printf("\n-------------------------------------\n");
    event_base_dispatch(base);
}

int main(int argc, const char * argv[]) {
    establish_connection("10.10.3.7", 8000);
    return 0;
}
