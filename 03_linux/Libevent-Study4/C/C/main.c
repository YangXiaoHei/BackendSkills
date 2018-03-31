//
//  main.c
//  C
//
//  Created by YangHan on 2018/3/30.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#include <stdio.h>
#include <event.h>
#include <event2/event.h>
#include <signal.h>

void timer_callback(int fd, short event, void *arg) {
    printf("timer callback\n");
}

int main(int argc, const char * argv[]) {
    struct timeval tv;
    tv.tv_sec = 3;
    struct event_base *base = event_base_new();
    struct event *ev_sig = evtimer_new(base, timer_callback, NULL);
    evsignal_add(ev_sig, NULL);
    event_base_dispatch(base);
    
    return 0;
}
