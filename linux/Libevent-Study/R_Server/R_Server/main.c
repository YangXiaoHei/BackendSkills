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
    
    // 设置端口可重用
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0) {
        perror("setsockopt ");
        exit(1);
    }
    
    // bind
    if (bind(listenfd, (struct sockaddr *)&cli_add, sizeof(struct sockaddr_in)) < 0) {
        perror("bind ");
        exit(1);
    }
    yh_log("bind 成功!\n");
    
    // listen
    if (listen(listenfd, nlisten) < 0) {
        perror("listen ");
        exit(1);
    }
    yh_log("listen 成功!\n");
    return listenfd;
}

/**
 *  终端 读回调
 */
void local_buffer_read_cb(struct bufferevent *bev, void *ctx) {
    
    printf("终端 -读- 回调\n");
    
//#ifdef FD_SETSIZE
//#define    __DARWIN_FD_SETSIZE    FD_SETSIZE
//#else /* !FD_SETSIZE */
//#define    __DARWIN_FD_SETSIZE    1024
//#endif /* FD_SETSIZE */
//#define    __DARWIN_NBBY        8                /* bits in a byte */
//#define __DARWIN_NFDBITS    (sizeof(__int32_t) * __DARWIN_NBBY) /* bits per mask */
//#define    __DARWIN_howmany(x, y)    ((((x) % (y)) == 0) ? ((x) / (y)) : (((x) / (y)) + 1)) /* # y's == x bits? */
//
//    __BEGIN_DECLS
//    typedef    struct fd_set {
//        __int32_t    fds_bits[__DARWIN_howmany(1024, 32)];
//    } fd_set;
//    __END_DECLS
    
    // 从终端读取输入
    char buf[1024];
    size_t rd_len = bufferevent_read(bev, buf, sizeof(buf) - 1);
    printf("从终端读取到 %zd 字节数据\n", rd_len);
    buf[rd_len] = '\n';
    buf[rd_len] = '\0';
    
    // 套接字 bufferevent
    struct bufferevent *net = (struct bufferevent *)ctx;
    
    // 向套接字缓冲区写数据
    if (bufferevent_write(net, buf, rd_len) < 0) {
        perror("向套接字缓冲区中写数据失败");
    } else {
        printf("向套接字缓冲区中写入 %zd 字节数据，内容是 :%s",rd_len, buf);
    }
    struct evbuffer *evbuf = bufferevent_get_output(net);
    size_t evbuflen = evbuffer_get_length(evbuf);
    printf("套接字发送缓冲区中有 %zd 个字节\n", evbuflen);
}

/**
 *  套接字 读回调
 */
void net_buffer_read_cb(struct bufferevent *bev, void *ctx) {
    
    printf("套接字 -读- 回调\n");
    
    if (bev->ev_read.ev_events & EV_ET) {
        printf("ev_events 边缘触发\n");
    }
    if (bev->ev_read.ev_res & EV_ET) {
        printf("ev_res 边缘触发\n");
    }
    if (bev->ev_read.ev_flags & EV_ET) {
        printf("ev_flags 边缘触发\n");
    }
    // 获取缓冲区数据长度
    struct evbuffer *input = bufferevent_get_input(bev);
    size_t len = evbuffer_get_length(input);
    
    printf("%lx\n", bev);
    printf("%lx\n", *bev);
    
    // 获取 fd
    int sockfd = bufferevent_getfd(bev);
    
    printf("\n------------ 【%d】 --------------\n", sockfd);
    printf("套接字缓冲区中的数据长度 %zd\n", len);
    char buf[1024];
    size_t rdlen = bufferevent_read(bev, buf, sizeof(buf) - 1);
    printf("服务器读到的数据长度 %zd\n", len);
    buf[rdlen] = 0;
    printf("服务器收到消息 : %s", buf);
    printf("---------------------------------\n");
}

/**
 *  套接字 写回调
 */
void net_buffer_write_cb(struct bufferevent *bev, void *ctx) {

    printf("套接字 -写- 回调\n");
    
    // 获取缓冲区数据长度
    struct evbuffer *input = bufferevent_get_input(bev);
    size_t len = evbuffer_get_length(input);
    printf("套接字缓冲区中的数据长度 %zd\n", len);
}

/**
 *  套接字 异常回调
 */
void net_buffer_event_cb(struct bufferevent *bev, short event, void *ctx) {
    
    printf("套接字 -异常- 回调\n");
    
    /* 连接完成 */
    if (event & BEV_EVENT_CONNECTED) {
        yh_log("连接完成\n");
        
        /* 未知错误 */
    } else if (event & BEV_EVENT_ERROR) {
        int err = EVUTIL_SOCKET_ERROR();
        const char *errstr = evutil_socket_error_to_string(err);
        yh_log("buffer_event_callback 其他错误 -------- %s\n", errstr);
        
        /* 写错误 */
    } else if (event & BEV_EVENT_WRITING) {
        if (event & BEV_EVENT_TIMEOUT) {
            yh_log("buffer_event_callback 写异常 | 超时 \n");
        } else if (event & BEV_EVENT_EOF) {
            yh_log("buffer_event_callback 写异常 | EOF \n");
        }
        
        /* 读错误 */
    } else if (event & BEV_EVENT_READING) {
        if (event & BEV_EVENT_TIMEOUT) {
            yh_log("buffer_event_callback 读异常 | 超时\n");
        } else if (event & BEV_EVENT_EOF) {
            yh_log("buffer_event_callback 读异常 | EOF \n");
        }
    }
}

/**
 *  listen 回调
 */
void onAccept(evutil_socket_t fd, short events, void *arg) {
    
    struct event_base *base = (struct event_base *)arg;
    
    struct sockaddr_in cli_add;
    bzero(&cli_add, sizeof(struct sockaddr_in));
    socklen_t len = sizeof(cli_add);
    int newfd = accept(fd, (struct sockaddr *)&cli_add, &len);
    if (newfd < 0) {
        perror("accpet ");
        exit(1);
    }
    yh_log("TCP 三次握手成功 ----- 新套接字 %d\n",newfd);
    
    // 网络数据流
    struct bufferevent *net = bufferevent_new(newfd,
                                              net_buffer_read_cb,
                                              net_buffer_write_cb,
                                              net_buffer_event_cb,
                                              NULL);

//    struct timeval t = {5, 0};
    bufferevent_base_set(base, net);
    bufferevent_setwatermark(net, EV_READ, 0, 2);
    bufferevent_enable(net, EV_READ | EV_WRITE);
   
    
    // 标准输入流
    struct bufferevent *loc = bufferevent_new(STDIN_FILENO,
                                              local_buffer_read_cb,
                                              NULL,
                                              NULL,
                                              net);
    bufferevent_base_set(base, loc);
    bufferevent_enable(loc, EV_READ);
}

int main(int argc, const char * argv[]) {
    
    // listen fd
    int listenfd = tcp_connet_fd(5555, 10);
    if (listenfd < 0) {
        perror("tcp connect fd");
        return -1;
    }
    
    
    
    // listen
    struct event_base *base = event_base_new();
    printf("%s\n", event_base_get_method(base));
    event_add(event_new(base, listenfd, EV_READ | EV_PERSIST, onAccept, base), NULL);
    event_base_dispatch(base);
    return 0;
}
