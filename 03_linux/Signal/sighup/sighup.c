#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

void do_sig(int signo) {
    
    int fd = open("./rec_sighup.txt", O_CREAT | O_RDWR, 0777);
    if (fd > 0) {
        char buf[] = "接收到了 SIGHUP 信号\n";
        write(fd, buf, sizeof(buf));
    }
}

/*
 *  SIGHUP 当用户退出 shell 时，向所有由 shell 启动的进程发送  SIGHUP 信号
    默认行为是终止进程
 */

int main() {
    
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = do_sig;
    
    sigaction(SIGHUP, &act, NULL);
    
    while (1) {};
 
    return 0;
}
