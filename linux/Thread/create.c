#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void printtids(const char *arg) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid : %zd  tid :%zd  (0x%x)\n",arg, pid, tid, (unsigned int)tid);
    while (1);
}

void *thr_act(void *arg) {
    printtids(arg);
    return NULL;
}

int main() {
    pthread_t tid;
    int err;
    err = pthread_create(&tid, NULL, thr_act, "new thread");
    if (err != 0) {
        fprintf(stderr, "create thread fail : %s\n", strerror(err));
        exit(1);
    }
    printtids("main thread");
    while (1);
    return 0;
}
