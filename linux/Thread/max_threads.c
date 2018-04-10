#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thr_(void *arg) {
    while (1);
}


int main() {
    
    
    pthread_t tid;
    void *ret;
    int i = 1, success = 0;
    while (1) {
        if (pthread_create(&tid, NULL, thr_, NULL) == success) {
            printf("%d create thread - %zd success\n",i++, tid);
        } else {
            printf("create fail\n");
            break;
        }
    }
    return 0;
}
