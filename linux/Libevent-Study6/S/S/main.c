//
//  main.c
//  S
//
//  Created by YangHan on 2018/4/2.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <event.h>
#include <event2/event.h>

int tcp_listen_socket_fd(unsigned short port, int nlisten) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket ");
        exit(1);
    }
    /**
     *  on Unix : don't hang on to this address after the listener is closed
     *  on Windows : don't keep other process from binding to this address while we're using it
     */
    evutil_make_listen_socket_reuseable(sockfd);
    struct sockaddr_in listener;
    bzero(&listener, sizeof(listener));
    listener.sin_family = AF_INET;
    listener.sin_port = htons(port);
    listener.sin_addr.s_addr = htons(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&listener, sizeof(listener)) < 0) {
        perror("bind ");
        exit(1);
    }
    printf("bind success!\n");
    if (listen(sockfd, nlisten) < 0) {
        perror("listen ");
        exit(1);
    }
    printf("listen success!\n");
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t l = sizeof(cli);
    int newfd;
    if ((newfd = accept(sockfd, (struct sockaddr *)&cli, &l)) < 0) {
        perror("accpet ");
        exit(1);
    }
    printf("accpet success!\n");
    return newfd;
}

void net_read_cb(int fd, short event, void *arg) {
    
    printf("套接字 -读- 回调\n");
    
    struct event *ev = (struct event *)arg;
    if (ev->ev_res & EV_ET) {
        printf("ev_res 边缘触发\n");
    } else {
        printf("ev_res 水平触发\n");
    }
    
    if (event & EV_ET) {
        printf("event 边缘触发\n");
    } else {
        printf("event 水平触发\n");
    }
    
    
    char buf[1024];
    bzero(buf, sizeof(buf));
    
    ssize_t rd_len = read(fd, buf, sizeof(buf));
    if (rd_len < 0) {
        perror("read");
//        exit(1);
    }
    buf[rd_len] = 0;
    printf("收到客户端 : 【%s】\n", buf);
    
//    char reply[1024] = "我已经收到 :";
//    strcat(reply + strlen(reply), buf);
//    write(fd, buf, rd_len + strlen(reply));
}

int main(int argc, const char * argv[]) {
    int fd = tcp_listen_socket_fd(8000, 100);
    struct event_base *base = event_base_new();
    
    printf("%s\n", *(char *)base);
    
    struct event *ev_read = event_new(base, -1, 0, NULL, NULL);
    struct timeval tv;
    tv.tv_sec = 5;
    event_assign(ev_read, base, fd, EV_WRITE | EV_READ | EV_PERSIST | EV_ET, net_read_cb, ev_read);
    event_add(ev_read, &tv);
    event_base_dispatch(base);
    return 0;
}
