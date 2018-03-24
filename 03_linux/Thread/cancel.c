#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thr_(void *arg) {
    int i;
    printf("thread %zd is running\n", pthread_self());
    while (1) {
        i++;
        /* 调用 pthread_cancel 不会立即把线程终止，而是将线程标记为
         等下次系统调用时才终止，所以假如该线程一直都没有被系统调用，即便
         使用了 pthread_cancel 也不会被终止*/
        // 手动测试该线程是否需要终止
        pthread_testcancel();
    }
    return (void *)1;
}

int main() {
    
    pthread_t tid;
    void *ret;
    
    pthread_create(&tid, NULL, thr_, NULL);
    
    int i = 3;
    while (i--) {
        printf("main thread : %zd i = %d\n", tid, i);
        sleep(1);
    }
    
    pthread_cancel(tid);
    
    while (1);
    return 0;
}
