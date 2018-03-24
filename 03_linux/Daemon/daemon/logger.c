#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#define LOG_PATH "/Users/bot/Desktop/C++_Backend_Learning/Cpp_Backend_Learning/03_linux/Daemon/daemon/log.txt"
const unsigned int time_interval = 1;

void sys_err(const char *fm, ...) {
    char buf[128];
    va_list vl;
    va_start(vl, fm);
    vsprintf(buf, fm, vl);
    va_end(vl);
    perror(buf);
    exit(1);
}

int init_daemon() {
    
    /* 创建父进程然后退出 */
    pid_t pid;
    if ((pid = fork()) < 0)
        sys_err("fork ");
    
    /* 退出父进程 */
    if (pid > 0)
        exit(0);
    
    /* 开启新会话，脱离控制终端 */
    setsid();
    
    /* 切换当前工作目录 */
    if (chdir("/") < 0)
        sys_err("chdir ");
    
    /* 设置当前进程 umask */
    umask(0);
    
    /* 打开文件 */
    int fd;
    if ((fd = open(LOG_PATH, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0)
        sys_err("open");
    
    /* 关闭 0 1 2 文件描述符 */
    if (close(STDIN_FILENO) < 0) {
        char *str = strerror(errno);
        write(fd, str, strlen(str));
        exit(1);
    }

    /* 将 0 分配给 /dev/null */
    int nullfd = open("/dev/null", O_RDWR);
    if (nullfd < 0) {
        char *str = strerror(errno);
        write(fd, str, strlen(str));
        exit(1);
    }

    /* 重定向 */
    if (dup2(nullfd, STDOUT_FILENO) < 0) {
        char *str = strerror(errno);
        write(fd, str, strlen(str));
        exit(1);
    }
    
    if (dup2(nullfd, STDERR_FILENO) < 0) {
        char *str = strerror(errno);
        write(fd, str, strlen(str));
        exit(1);
    }
    
    return fd;
}

int main() {
    
    /* 创建守护进程 */
    int fd = init_daemon();
    
    /* 守护进程的工作内容 */
    while (1) {
        
        /* 获取当前时间 */
        time_t t;
        time(&t);
        char buf[64];
        bzero(buf, sizeof(buf));
        ctime_r(&t, buf);
        
        if (write(fd, buf, strlen(buf)) < 0)
            sys_err("write ");
        sleep(time_interval);
    }
    return 0;
}
