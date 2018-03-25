#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;

int counter;

void *read_thr(void *arg) {
    
    int id = (int)arg;
    
    while (1) {
        
        pthread_rwlock_rdlock(&rwlock);
        printf("==========================  线程 %d read : %d\n", id, counter);
        pthread_rwlock_unlock(&rwlock);
        
        pthread_testcancel();
    }
    return (void *)1;
}

void *write_thr(void *arg) {
    int id = (int)arg;
    
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        printf("========= write ==========  线程 %d write : %d\n", id, ++counter);
        pthread_rwlock_unlock(&rwlock);
        
        pthread_testcancel();
    }
    
    return (void *)2;
}

int main() {
    
    pthread_rwlock_init(&rwlock, NULL);
    
    /* 8 个子线程 */
    pthread_t tid[8];
    
    /* 3 个写线程 */
    for (int i = 0; i < 3; i++) {
        pthread_create(tid + i, NULL, write_thr, (void *)i);
    }
    
    /* 5 个读线程 */
    for (int i = 3; i < 8; i++) {
        pthread_create(tid + i, NULL, read_thr, (void *)i);
    }
    
    sleep(3);
    
    /* 结束全部线程 */
    for (int i = 0; i < 8; i++) {
        pthread_cancel(tid[i]);
    }
    
    /* 回收所有子线程 */
    for (int i = 0; i < 8; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("回收完所有子线程的资源\n");
    
    return 0;
}
