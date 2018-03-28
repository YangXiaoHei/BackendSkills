//
//  main.c
//  C
//
//  Created by YangHan on 2018/3/28.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <event.h>
#include <event2/event.h>

int tcp_socket_fd(const char *ip, unsigned short port) {
    
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_aton(ip, &serv.sin_addr);
    
    if (serv.sin_addr.s_addr == 0) {
        printf("IP 地址无效");
        return -1;
    }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    
    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect ");
        exit(1);
    }
    printf("-------- connect success ----------\n");
    return sockfd;
}

void cmd_msg_cb(int fd, short event, void *arg) {
    struct bufferevent *bev = (struct bufferevent *)arg;
    char buf[1024];
    ssize_t rd_len = read(fd, buf, sizeof(buf));
    buf[rd_len] = 0;
    if (bufferevent_write(bev, buf, rd_len) < 0) {
        printf("套接字写失败\n");
    }
    printf("从终端读取到输入 : 【%s】\n", buf);
}

void read_cb(struct bufferevent *bev, void *arg) {
    printf("套接字 -读- 回调\n");
    char buf[1024];
    ssize_t len = bufferevent_read(bev, buf, sizeof(buf));
    if (len < 0) {
        printf("套接字读取失败\n");
    }
    buf[len] = 0;
    printf("从服务器收到消息 : 【%s】\n", buf);
}

void event_cb(struct bufferevent *bev, short events, void *arg) {
    printf("异常 -读- 回调\n");
}

void establish_connection(const char *ip, unsigned short port) {
    int sockfd = tcp_socket_fd(ip, port);
    
    struct event_base *base = event_base_new();
    // 网络
    struct bufferevent *ev_sock = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(ev_sock, read_cb, NULL, event_cb, NULL);
    bufferevent_enable(ev_sock, EV_READ | EV_WRITE);
    
    // 终端
    struct event *ev_cmd = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, ev_sock);
    event_add(ev_cmd, NULL);
    event_base_dispatch(base);
}

int main(int argc, const char * argv[]) {
    establish_connection("10.10.3.7", 8000);
    return 0;
}
