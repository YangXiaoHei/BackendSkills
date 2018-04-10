#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *thr1(void *arg) {
    
    /* 得到 A 锁 */
    pthread_mutex_lock(&lockA);
    printf("thread 1 抢到 A 锁\n");
    
    printf("thread 1 睡 2 秒\n");
    sleep(2);
    
    printf("thread 1 试图抢占 B 锁\n");
    pthread_mutex_lock(&lockB);
    printf("thread 1 抢到了 B 锁\n");
    
    /* 释放锁 */
    pthread_mutex_unlock(&lockB);
    pthread_mutex_unlock(&lockA);
    
    return (void *)2;
}

/**
 *  先抢 B 锁，倒计时 3 秒后抢 A 锁
 */
void *thr2(void *arg) {
    
    /* 得到 B 锁 */
    pthread_mutex_lock(&lockB);
    printf("thread 2 抢到 B 锁\n");
    
    printf("thread 2 睡 4 秒\n");
    sleep(4);
    
    printf("thread 2 试图抢占 A 锁\n");
    pthread_mutex_lock(&lockA);
    printf("thread 2 抢到了 A 锁\n");
    
    /* 释放锁 */
    pthread_mutex_unlock(&lockA);
    pthread_mutex_unlock(&lockB);
    return (void *)1;
}

int main() {
    
    pthread_t tid1, tid2;
    
    pthread_create(&tid1, NULL, thr1, NULL);
    pthread_create(&tid2, NULL, thr2, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("主线程回收完两个线程的资源\n");
    
    return 0;
}
/**
 *   YangHan:Thread_Sync YangHan$ cc deadlock.c -o deadlock
     YangHan:Thread_Sync YangHan$ ./deadlock
     thread 1 抢到 A 锁
     thread 2 抢到 B 锁
     thread 1 睡 2 秒
     thread 2 睡 4 秒
     thread 1 试图抢占 B 锁
     thread 2 试图抢占 A 锁
     ^C

 */
