//
//  main.c
//  S
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
    printf("from client : 【%s】\n", buf);
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
        printf("向客户端回复数据失败\n");
    }
    printf("回复 : 【%s】\n", buf);
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


int tcp_listen_socket(int port) {
    
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_addr.s_addr = htons(INADDR_ANY);
    cli.sin_port = htons(port);
    
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket ");
        exit(1);
    }
    
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0) {
        perror("setsockopt ");
        exit(1);
    }
    
    if (bind(listenfd, (struct sockaddr *)&cli, sizeof(cli)) < 0) {
        perror("bind ");
        exit(1);
    }
    
    if (listen(listenfd, 10) < 0) {
        perror("listen ");
        exit(1);
    }
    
    return listenfd;
}

void on_accpet(int listener, short event, void *arg) {
    printf("---- on accept -------\n");
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    struct event_base *base = (struct event_base *)arg;
    unsigned int len = sizeof(struct sockaddr_in);
    int newfd = accept(listener,
                       (struct sockaddr *)&cli,
                       &len);
    printf("accept success : newfd = %d\n", newfd);
    
    // net
    struct bufferevent *net = bufferevent_new(newfd,
                                              net_read_callback,
                                              net_write_callback,
                                              net_event_callback,
                                              NULL);
    bufferevent_base_set(base, net);
    bufferevent_settimeout(net, 0, 5);
    bufferevent_enable(net, EV_READ | EV_WRITE);
    
    // terminal
    struct bufferevent *loc = bufferevent_new(STDIN_FILENO,
                                              local_read_callback,
                                              local_write_callback,
                                              local_event_callback,
                                              net);
    bufferevent_base_set(base, loc);
    bufferevent_enable(loc, EV_READ);
}

void establish_connection(int port) {
    int listener = tcp_listen_socket(port);
    struct event_base *base = event_base_new();
    event_add(event_new(base, listener, EV_READ | EV_PERSIST, on_accpet, base), NULL);
    event_base_dispatch(base);
}

int main(int argc, const char * argv[]) {
    establish_connection(8000);
    return 0;
}
