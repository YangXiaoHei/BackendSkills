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
    cli_add.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(listenfd, (struct sockaddr *)&cli_add, sizeof(struct sockaddr_in)) < 0) {
        perror("bind ");
        exit(1);
    }
    yh_log("bind success\n");
    if (listen(listenfd, nlisten) < 0) {
        perror("listen ");
        exit(1);
    }
    yh_log("listen success\n");
    return listenfd;
}

void read_cb(evutil_socket_t fd, short events, void *arg) {
    
}

void listen_cb(evutil_socket_t fd, short events, void *arg) {
    
    yh_log("listen callback\n");
    
    struct sockaddr_in cli_add;
    bzero(&cli_add, sizeof(struct sockaddr_in));
    cli_add.sin_family = AF_INET;
    
    
    struct event_base *base = (struct event_base *)arg;
    
    int newfd = accept(fd, (struct sockaddr *)&cli_add, sizeof(cli_add));
    if (newfd < 0) {
        perror("accpet ");
    }
    
    yh_log("accpet a client -----  %d\n",newfd);
    sleep(1);
    
    struct event *ev_accpet = event_new(base, newfd, EV_PERSIST | EV_READ, read_cb, NULL);
    event_add(ev_accpet, NULL);
}

int main(int argc, const char * argv[]) {
    
    int listenfd = tcp_connet_fd(8000, 10);
    if (listenfd < 0) {
        perror("tcp connect fd");
        return -1;
    }
    
    struct event_base *base = event_base_new();
    
    /* 监听 listen 事件 */
    struct event *ev_listen = event_new(base, listenfd, EV_READ | EV_PERSIST, listen_cb, base);
    event_add(ev_listen, NULL);
    
    event_base_dispatch(base);
    
    return 0;
}
