#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef unsigned int Q_result_t;
typedef enum Q_status_ {
    Q_success           = 0,
    Q_malloc_fail       = 1 << 0,
    Q_err_arg           = 1 << 1,
    Q_lock_init_fail    = 1 << 2,
    Q_lock_fail         = 1 << 3,
    Q_sem_open_fail     = 1 << 4,
    Q_sem_unlock_fail   = 1 << 5
} Q_status;

struct Queue {
    int size;
    sem_t *exist;
    sem_t *empty;
    pthread_mutex_t lock;
    struct Node *header;
    struct Node *tailer;
};

struct Param {
    struct Queue *q;
    int id;
};

/* 创建队列内部节点 */
static Q_status q_node_create(struct Node **no,
                              int data,
                              struct Node *prev,
                              struct Node *next) {
    Q_status s = Q_success;
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL || no == NULL || prev == NULL || next == NULL) {
        return s |= Q_err_arg;
    }
    n->data = data;
    n->prev = prev;
    n->next = next;
    prev->next= n;
    next->prev = n;
    *no = n;
    return s;
}

/* 删除队列内部节点 */
static Q_status q_node_delete(struct Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
    return Q_success;
}

/* 创建队列 */
Q_status q_create(struct Queue **que, int max, const char *a, const char *b) {
    if (que == NULL || max <= 0) {
        return Q_err_arg;
    }
    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        return Q_malloc_fail;
    }
    bzero(q, sizeof(struct Queue));
    q->header = malloc(sizeof(struct Node));
    if (q->header == NULL) {
        return Q_malloc_fail;
    }
    errno = 0;
    
    umask(0);
    
    if ((q->empty = sem_open(a, O_CREAT , 0777, max)) == NULL) {
        perror("sem_open");
        return Q_sem_open_fail;
    }
    if ((q->exist = sem_open(b, O_CREAT , 0777, 0)) == NULL) {
        perror("sem_open");
        return Q_sem_open_fail;
    }
    if (errno != 0) {
        perror("sem_open");
        exit(1);
    }
    if (pthread_mutex_init(&q->lock, NULL) != 0) {
        perror("mutex_init");
        return Q_lock_init_fail;
    }
    q->tailer = malloc(sizeof(struct Node));
    if (q->tailer == NULL) {
        return Q_malloc_fail;
    }
    q->header->next = q->tailer;
    q->tailer->prev = q->header;
    *que = q;
    return Q_success;
}

/* 入队操作 */
Q_status q_enqueue(struct Queue *q, int data, int tid) {
    printf("producer %d\n", tid);
    sem_wait(q->empty);
    printf("producer %d进入\n", tid);
    pthread_mutex_lock(&q->lock);
    printf("producer %d 抢到了锁\n", tid);
    struct Node *n = NULL;
    Q_status s = q_node_create(&n, data, q->tailer->prev, q->tailer);
    if (s != Q_success) {
        pthread_mutex_unlock(&q->lock);
        return s;
    }
    q->size++;
    sem_post(q->exist);
    printf("producer %d 生产蛋糕 %d，并放入队列中，现在队列总共有 %d 个蛋糕\n",tid, data, q->size);
    pthread_mutex_unlock(&q->lock);
    return Q_success;
}

/* 出队操作 */
Q_status q_dequeue(struct Queue *q, int *d, int tid) {
    if (q == NULL || d == NULL) {
        return Q_err_arg;
    }
    printf("消费者 %d\n", tid);
    sem_wait(q->exist);
    printf("消费者 %d 进入\n", tid);
    pthread_mutex_lock(&q->lock);
    printf("消费者 %d 抢到了锁\n", tid);
    int data = q->header->next->data;
    Q_status s = q_node_delete(q->header->next);
    if (s != Q_success) {
        pthread_mutex_unlock(&q->lock);
        return s;
    }
    *d = data;
    q->size--;
    sem_post(q->empty);
    printf("消费者 %d 吃了蛋糕 %d，队列还剩下 %d 个蛋糕\n",tid, data, q->size);
    pthread_mutex_unlock(&q->lock);
    return Q_success;
}

/* 队列是否为空 */
Q_result_t q_is_empty(struct Queue *q) {
    pthread_mutex_lock(&q->lock);
    int empty = q->size == 0;
    pthread_mutex_unlock(&q->lock);
    return empty;
}

/* 获取队列容量 */
Q_result_t q_size(struct Queue *q) {
    pthread_mutex_lock(&q->lock);
    int size = q->size;
    pthread_mutex_unlock(&q->lock);
    return size;
}

/* 销毁队列 */
Q_status q_destroy(struct Queue **q) {
    if (q == NULL) {
        return -1;
    }
    int d;
    while (!q_is_empty(*q)) {
        Q_status t = q_dequeue(*q, &d, 0);
        if (t != Q_success) {
            return t;
        }
    }
    free((*q)->header);
    free((*q)->tailer);
    free(*q);
    *q = NULL;
    return 0;
}

/* 队列测试 */
void q_test() {
    struct Queue *q = NULL;
    if (q_create(&q, 100, "a", "b") != Q_success) {
        printf("队列创建失败\n");
    }
    for (int i = 0; i < 10; i++) {
        if (q_enqueue(q, i, 0) != Q_success) {
            printf("%d 入队失败\n", i);
        }
    }
    int d;
    while (!q_is_empty(q)) {
        q_dequeue(q, &d, 0);
        printf("%d 出队\n", d);
    }
    if (q_destroy(&q) != Q_success) {
        printf("队列销毁失败!\n");
    }
}

void *producer(void *arg) {
    struct Param *p = (struct Param *)arg;
    struct Queue *q = p->q;
    int id = p->id;
    while (1) {
        int t = rand() % 100 + 1;
        q_enqueue(q, t, id);
        pthread_testcancel();
    }
    return (void *)1;
}

void *consumer(void *arg) {
    struct Param *p = (struct Param *)arg;
    struct Queue *q = p->q;
    int id = p->id;
    while (1) {
        int d;
        q_dequeue(q, &d, id);
        pthread_testcancel();
    }
    return (void *)1;
}

int main(int argc, char *argv[]) {
    
    if (argc < 3) {
        printf("./semaphore name1 name2\n");
        exit(1);
    }
    
    int q_capacity = 10;
    
    /* 创建生产线 */
    struct Queue *q = NULL;
    int t = q_create(&q, q_capacity, argv[1], argv[2]);
    if (t != 0) {
        printf("队列创建失败\n");
    }
    
    /* 10 个消费者，3 个生产者 */
    pthread_t cs[10];
    pthread_t ps[3];
    
    // consumer
    for (int i = 0; i < 10; i++) {
        struct Param *p = malloc(sizeof(struct Param));
        p->q = q;
        p->id = i;
        pthread_create(cs + i, NULL, consumer, p);
    }
    
    // producer
    for (int i = 0; i < 3; i++) {
        struct Param *p = malloc(sizeof(struct Param));
        p->q = q;
        p->id = i;
        pthread_create(ps + i, NULL, producer, p);
    }
    
    sleep(5);
    
    sem_unlink(argv[1]);
    sem_unlink(argv[2]);
    
    for (int i = 0; i < 3; i++) {
        pthread_cancel(cs[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_cancel(cs[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        pthread_join(cs[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(ps[i], NULL);
    }
    
    printf("回收完成\n");
    
    return 0;
}


