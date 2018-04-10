//
//  main.c
//  R_Client
//
//  Created by YangHan on 2018/3/26.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>  // inet_aton
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <event.h>
#include <event2/event.h>
#include <stdlib.h>

#define IP "10.10.3.7"
#define PORT 8000

void yh_log(const char *format, ...) {
    va_list vg;
    va_start(vg, format);
    vprintf(format, vg);
    va_end(vg);
}

int tcp_connect_fd(const char *ip, int port) {
    
    /* 服务器地址 */
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_aton(ip, &serv_addr.sin_addr);
    
    /* 检测 IP 是否有效 */
    if (serv_addr.sin_addr.s_addr == 0) {
        errno = EINVAL;
        return -1;
    }
    yh_log("IP 有效\n");
    
    /* 创建套接字 */
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return -1;
    }
    yh_log("套接字创建成功\n");
    
    /* connect
     *
     * 向服务器发送 SYN 包
     * 阻塞直到收到服务端的 SYN、ACK 包
     * 然后向服务器发送 ACK 包，不理会回应，然后返回
     */
    int con_err;
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        con_err = errno;
        close(sockfd);
        errno = con_err;
        return -1;
    }
    yh_log("TCP 三次握手成功\n");
    evutil_make_socket_nonblocking(sockfd);
    return sockfd;
}

/**
 *  socket 可读事件监听
 */
void socket_rd_cb(evutil_socket_t sockfd, short events, void *arg) {
    char buf[1024];
    
    /* 从 socket 中读取来自服务器的数据 */
    ssize_t len;
    if ((len = read(sockfd, buf, sizeof(buf))) <= 0) {
        perror("从 sockfd 读取失败 ");
        exit(1);
    }
    buf[len] = 0;
    printf("从服务器收到消息 : %s", buf);
}

/**
 *  监听终端输入事件
 */
void cmd_rd_cb(evutil_socket_t fd, short events, void *arg) {
    char buf[1024];
    int sockfd = *(int *)arg;
    
    /* 从终端读取 */
    ssize_t len;
    if ((len = read(fd, buf, sizeof(buf))) <= 0) {
        perror("从终端读取失败 ");
        exit(1);
    }
    buf[len] = 0;
    
    /* 向服务器发送 */
    printf("向服务器发送消息 : %s", buf);
    if (write(sockfd, buf, len) < 0) {
        perror("write ");
    }
}

int main(int argc, const char * argv[]) {
    
    /* 创建 TCP 套接字并向服务器发送 SYN 包 */
    int sockfd;
    if ((sockfd = tcp_connect_fd(IP, PORT)) < 0) {
        perror("tcp connect fd ");
        exit(1);
    }
    
    /* Reactor Center */
    struct event_base *base = event_base_new();
    
    /* 监听 socket 可读事件 */
    struct event *ev_socket = event_new(base,
                                        sockfd,
                                        EV_READ | EV_PERSIST,
                                        socket_rd_cb,
                                        NULL);
    event_add(ev_socket, NULL);
    
    /* 监听终端的输入事件 */
    struct event *ev_input = event_new(base,
                                       STDIN_FILENO,
                                       EV_READ | EV_PERSIST,
                                       cmd_rd_cb,
                                       (void *)&sockfd);
    event_add(ev_input, NULL);
    
    /* 开启事件循环 */
    event_base_dispatch(base);
    return 0;
}

