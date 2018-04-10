#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
    int val;
    for (int i = 0; i < 5000; i++) {
        pthread_mutex_lock(&mutex);
        val = counter;
        val++;
        counter = val;
        pthread_mutex_unlock(&mutex);
    }
    return (void *)1;
}

int main() {
    
    pthread_t tid1, tid2;
    
    pthread_create(&tid1, NULL, increment, NULL);
    pthread_create(&tid2, NULL, increment, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("counter = %d\n", counter);
    
    return 0;
}
