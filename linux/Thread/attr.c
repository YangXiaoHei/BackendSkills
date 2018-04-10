#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg) {
    int n = 20;
    while (n--) {
        printf("n = %d 子线程 %zd 正在运行\n",n, pthread_self());
        sleep(1);
    }
    return (void *)1;
}

int main() {
    
    pthread_attr_t attr;
    
    /* 初始化线程属性 */
    pthread_attr_init(&attr);
    
    /* 设置线程为分离态 */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    /* 创建线程 */
    pthread_t tid;
    pthread_create(&tid, &attr, thr, NULL);
    
    /* join 会失败 */
    int err = pthread_join(tid, NULL);
    if (err != 0) {
        int n = 10;
        while (n--) {
            printf("n = %d 主线程正在运行\n", n);
            sleep(1);
        }
        /* 销毁线程属性 */
        pthread_attr_destroy(&attr);
        pthread_exit((void *)1);
    }
    
    return 0;
}
