//
//  main.c
//  S
//
//  Created by YangHan on 2018/3/28.
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
    if (listen(sockfd, nlisten) < 0) {
        perror("listen ");
        exit(1);
    }
    evutil_make_socket_nonblocking(sockfd);
    return sockfd;
}

void net_read_cb(int fd, short event, void *arg) {
    
    struct event *ev = (struct event *)arg;
    
    char buf[1024];
    bzero(buf, sizeof(buf));
    
    ssize_t rd_len = read(fd, buf, sizeof(buf));
    if (rd_len < 0) {
        perror("read");
        event_free(ev);
        close(fd);
//        exit(1);
    }
    buf[rd_len] = 0;
    printf("收到客户端 : 【%s】\n", buf);
    
    char reply[1024] = "我已经收到 :";
    strcat(reply + strlen(reply), buf);
    write(fd, buf, rd_len + strlen(reply));
}

void on_accpet(int fd, short event, void *arg) {
    printf("----------------- accpet -----------\n");
    struct event_base *base = (struct event_base *)arg;
    
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t l = sizeof(cli);
    int newfd = accept(fd, (struct sockaddr *)&cli, &l);
    printf("--------- accpet new fd %d ----------\n", newfd);
    
    struct event *ev_sock = event_new(base, -1, 0, NULL, NULL);
    event_assign(ev_sock, base, newfd, EV_WRITE | EV_READ | EV_PERSIST, net_read_cb, ev_sock);
    event_add(ev_sock, NULL);
}

void establish_connection(unsigned int port, int nlisten) {
    int listener = tcp_listen_socket_fd(port, nlisten);
    struct event_base *base = event_base_new();
    struct event *ev_listen = event_new(base, listener, EV_READ | EV_PERSIST, on_accpet, base);
    event_add(ev_listen, NULL);
    event_base_dispatch(base);
}


int main(int argc, const char * argv[]) {
    establish_connection(8000, 10);
    return 0;
}
