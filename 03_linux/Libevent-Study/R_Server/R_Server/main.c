//
//  main.c
//  R_Server
//
//  Created by YangHan on 2018/3/26.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <event2/event.h>
#include "event.h"
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void yh_log(const char *format, ...) {
    va_list vg;
    va_start(vg, format);
    vprintf(format, vg);
    va_end(vg);
}

/**
 *  socket -> bind -> listen -> return fd
 */
int tcp_connet_fd(int port, int nlisten) {
    evutil_socket_t listenfd;
    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket ");
        return -1;
    }
    
    struct sockaddr_in cli_add;
    bzero(&cli_add, sizeof(struct sockaddr_in));
    cli_add.sin_family = AF_INET;
    cli_add.sin_port = htons(port);
    cli_add.sin_addr.s_addr = 0;
    
    // bind
    if (bind(listenfd, (struct sockaddr *)&cli_add, sizeof(struct sockaddr_in)) < 0) {
        perror("bind ");
        exit(1);
    }
    yh_log("bind success\n");
    
    // listen
    if (listen(listenfd, nlisten) < 0) {
        perror("listen ");
        exit(1);
    }
    yh_log("listen success\n");
    return listenfd;
}

/**
 *  read call back
 */
void buffer_read_cb(struct bufferevent *bev, void *ctx) {
    
    // 获取缓冲区数据长度
    struct evbuffer *input = bufferevent_get_input(bev);
    size_t len = evbuffer_get_length(input);
    
    // 获取 fd
    int sockfd = bufferevent_getfd(bev);
    
    printf("\n------------ 【%d】 --------------\n", sockfd);
    printf("缓冲区中的数据长度 %zd\n", len);
    char buf[1024];
    size_t rdlen = bufferevent_read(bev, buf, sizeof(buf));
    printf("服务器读到的数据长度 %zd\n", len);
    buf[rdlen] = 0;
    printf("服务器收到消息 : %s", buf);
    printf("---------------------------------\n");
}

/**
 *  write call back
 */
void buffer_write_cb(struct bufferevent *bev, void *ctx) {
    printf("bufferevent read cb\n");
}

/**
 *  event call back
 */
void buffer_event_cb(struct bufferevent *bev, short what, void *ctx) {
    printf("bufferevent read cb\n");
}

/**
 *  listen call back
 */
void onAccept(evutil_socket_t fd, short events, void *arg) {
    struct sockaddr_in cli_add;
    bzero(&cli_add, sizeof(struct sockaddr_in));
    
    struct event_base *base = (struct event_base *)arg;
    
    socklen_t len = sizeof(cli_add);
    int newfd = accept(fd, (struct sockaddr *)&cli_add, &len);
    if (newfd < 0) {
        perror("accpet ");
        exit(1);
    }
    yh_log("accpet a client -----  %d\n",newfd);
    struct bufferevent *buffevn = bufferevent_new(newfd,
                                              buffer_read_cb,
                                              buffer_write_cb,
                                              buffer_event_cb,
                                              NULL);
    bufferevent_base_set(base, buffevn);
    bufferevent_enable(buffevn, EV_READ | EV_WRITE | EV_PERSIST);
}

int main(int argc, const char * argv[]) {
    int listenfd = tcp_connet_fd(8000, 10);
    if (listenfd < 0) {
        perror("tcp connect fd");
        return -1;
    }
    struct event_base *base = event_base_new();
    
    /* 监听 listen 事件 */
    struct event *ev_listen = event_new(base, listenfd, EV_READ | EV_PERSIST, onAccept, base);
    event_add(ev_listen, NULL);
    event_base_dispatch(base);
    return 0;
}
