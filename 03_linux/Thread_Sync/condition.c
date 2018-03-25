#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_cond_t empty;
pthread_mutex_t con_mtx = PTHREAD_MUTEX_INITIALIZER;

struct Cake {
    int id;
    struct Cake *next;
};

struct Basket {
    struct Cake *cake;
    int sz;
};

struct Basket basket;

void *producer(void *arg) {
    
    while (1) {
        
        /* 生产一个蛋糕 */
        struct Cake *newcake = malloc(sizeof(struct Cake));
        newcake->id = rand() % 1000 + 1;
        newcake->next = NULL;
        
        printf("生产者抢锁\n");
        pthread_mutex_lock(&con_mtx);
        printf("生产者抢到了锁✅\n");
        
        /* 把蛋糕放入篮子 */
        if (basket.cake == NULL) {
            basket.sz = 1;
            basket.cake = newcake;
        } else {
            newcake->next = basket.cake;
            basket.cake = newcake;
            basket.sz++;
        }
        
        printf("生产者把蛋糕 %d 放入篮子里，现在有 %d 块蛋糕\n", newcake->id, basket.sz);
        
        pthread_mutex_unlock(&con_mtx);
        printf("生产者释放了锁\n");
        
        /* 唤醒等待在条件变量上的所有线程 */
        printf("生产者发送了广播\n");
        pthread_cond_broadcast(&empty);
        
        pthread_testcancel();
        
        sleep(rand() % 3);
    }
    
    return (void *)1;
}

void *consumer(void *arg) {
    
    int id = (int)arg;
    
    while (1) {
        
        printf("消费者 %d 抢锁\n", id);
        pthread_mutex_lock(&con_mtx);
        printf("消费者 %d 抢到了锁✅\n", id);
        
        while (basket.sz == 0) {
            printf("-----篮子空，消费者 %d 抢到了锁，即将释放锁并陷入等待\n", id);
            pthread_cond_wait(&empty, &con_mtx);
            printf("-----消费者 %d 被唤醒并抢到了锁\n", id);
        }
        
        struct Cake *cake = basket.cake;
        basket.cake = basket.cake->next;
        basket.sz--;
        
        printf("消费者 %d 吃到了蛋糕 %d \n", id, cake->id);
        
        free(cake);
        
        printf("消费者 %d 释放了锁\n", id);
        pthread_mutex_unlock(&con_mtx);
        
        pthread_testcancel();
        
        sleep(rand() % 3);
    }
    return (void *)2;
}

int main() {
    
    srand((unsigned int)time(NULL));
    
    /* 创建线程 */
    pthread_t pid, cid[4];
    pthread_create(&pid, NULL, producer, NULL);
    for (int i = 0; i < 4; i++) {
        pthread_create(cid + i, NULL, consumer, (void *)i);
    }
    
    /* 初始化条件变量 */
    pthread_cond_init(&empty, NULL);
    
    bzero(&basket, sizeof(struct Basket));
    basket.cake = NULL;
    basket.sz = 0;
    
    printf("主线程开始睡眠\n");
    sleep(5);
    printf("主线程苏醒\n");
    
    pthread_cancel(pid);
    for (int i = 0; i < 4; i++) {
        pthread_cancel(cid[i]);
    }
    
    pthread_join(pid, NULL);
    printf("生产者被回收\n");
    for (int i = 0; i < 4; i++) {
        pthread_join(cid[i], NULL);
        printf("消费者 %d 被回收\n", i);
    }
    
    printf("结束!\n");
    
    return 0;
}
