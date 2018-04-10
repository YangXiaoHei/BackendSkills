#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thr1_(void *arg) {
    printf("thread_1 %zd \n", pthread_self());
    return (void *)1;
}

void *thr2_(void *arg) {
    printf("thread_2 %zd\n", pthread_self());
    pthread_exit((void *)2);
}

void *thr3_(void *arg) {
    while (1) {
        printf("thread %zd is running\n", pthread_self());
        sleep(1);
    }
}

int main() {
    
    pthread_t tid;
    void *ret;
    
    pthread_create(&tid, NULL, thr1_, NULL);
    pthread_join(tid, &ret);
    printf("thread %zd exit code %zd\n", tid, (int)ret);
    
    pthread_create(&tid, NULL, thr2_, NULL);
    pthread_join(tid, &ret);
    printf("thread %zd exit code %zd\n",tid, (int)ret);
    
    pthread_create(&tid, NULL, thr3_, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &ret);
    printf("thread %zd exit code %zd\n",tid, (int)ret);
    
    return 0;
}
