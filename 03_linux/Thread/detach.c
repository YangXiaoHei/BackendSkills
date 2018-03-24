#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr_(void *arg) {
    int n = 3;
    while (n--) {
        printf("thread %zd is running\n", pthread_self());
        sleep(1);
    }
    return (void *)1;
}

int main() {
    
    pthread_t tid;
    void *ret;
    int err;
    
    pthread_create(&tid, NULL, thr_, NULL);
    
    /* 是否设置线程为分离态，如果设置，那么在线程执行完成后，不需要join,
     * 线程由操作系统负责回收，并且设置为 detachable 的线程，不能再调用
        pthread_join(该线程 ID)，调用了会返回 errno = EINVAL 的错误
     */
    pthread_detach(tid);
    while (1) {
        err = pthread_join(tid, &ret);
        if (err != 0) {
            fprintf(stderr, "thread %zd : %s\n", tid, strerror(err));
        } else {
            fprintf(stderr, "thread %zd exit code %d\n", tid, (int)ret);
        }
        printf("主线程睡 1 秒再回来\n");
        sleep(1);
    }
    return 0;
}

// 没有打开注视

/**
 *   YangHan:Thread YangHan$ cc detach.c -o detach
     YangHan:Thread YangHan$ ./detach
     thread 123145416110080 is running
     thread 123145416110080 is running
     thread 123145416110080 is running
     thread 123145416110080 exit code 1
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
     thread 123145416110080 : No such process
     主线程睡 1 秒再回来
 ^C
 */


// 打开注视

/**
 *   YangHan:Thread YangHan$ cc detach.c -o detach
     YangHan:Thread YangHan$ ./detach
     thread 123145417293824 : Invalid argument
     thread 123145417293824 is running
     主线程睡 1 秒再回来
     thread 123145417293824 : Invalid argument
     thread 123145417293824 is running
     主线程睡 1 秒再回来
     thread 123145417293824 : Invalid argument
     thread 123145417293824 is running
     主线程睡 1 秒再回来
     thread 123145417293824 : Invalid argument
     主线程睡 1 秒再回来
     thread 123145417293824 : No such process
     主线程睡 1 秒再回来
     thread 123145417293824 : No such process
     主线程睡 1 秒再回来
     thread 123145417293824 : No such process
     主线程睡 1 秒再回来
     thread 123145417293824 : No such process
     主线程睡 1 秒再回来
 ^C

 */
