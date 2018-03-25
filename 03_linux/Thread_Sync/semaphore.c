#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct Queue {
    int size;
    struct Node *header;
    struct Node *tailer;
};

struct Param {
    struct Queue *q;
    int id;
};

/* 创建队列内部节点 */
static int q_node_create(struct Node **no,
                         int data,
                         struct Node *prev,
                         struct Node *next) {
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        return -1;
    }
    n->data = data;
    n->prev = prev;
    n->next = next;
    prev->next= n;
    next->prev = n;
    *no = n;
    return 0;
}

/* 删除队列内部节点 */
static int q_node_delete(struct Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
    return 0;
}

/* 创建队列 */
int q_create(struct Queue **que) {
    if (que == NULL) {
        return -1;
    }
    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        return -1;
    }
    bzero(q, sizeof(struct Queue));
    q->header = malloc(sizeof(struct Node));
    if (q->header == NULL) {
        return -1;
    }
    q->tailer = malloc(sizeof(struct Node));
    if (q->tailer == NULL) {
        return -1;
    }
    q->header->next = q->tailer;
    q->tailer->prev = q->header;
    *que = q;
    return 0;
}

/* 入队操作 */
int q_enqueue(struct Queue *q, int data) {
    pthread_mutex_lock(&lock);
    struct Node *n = NULL;
    if (q_node_create(&n, data, q->tailer->prev, q->tailer) < 0) {
        return -1;
    }
    q->size++;
    pthread_mutex_unlock(&lock);
    return 0;
}

/* 出队操作 */
int q_dequeue(struct Queue *q, int *d) {
    pthread_mutex_lock(&lock);
    if (q == NULL || d == NULL) {
        return -1;
    }
    if (q->size <= 0) {
        return -1;
    }
    int data = q->header->next->data;
    if (q_node_delete(q->header->next) < 0) {
        return -1;
    }
    *d = data;
    q->size--;
    pthread_mutex_unlock(&lock);
    return 0;
}

/* 队列是否为空 */
int q_is_empty(struct Queue *q) {
    pthread_mutex_lock(&lock);
    int empty = q->size == 0;
    pthread_mutex_unlock(&lock);
    return empty;
}

/* 获取队列容量 */
int q_size(struct Queue *q) {
    pthread_mutex_lock(&lock);
    int size = q->size;
    pthread_mutex_unlock(&lock);
    return size;
}

/* 销毁队列 */
int q_destroy(struct Queue **q) {
    int d;
    while (!q_is_empty(*q)) {
        if (q_dequeue(*q, &d) < 0) {
            return -1;
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
    if (q_create(&q) < 0) {
        printf("队列创建失败\n");
    }
    for (int i = 0; i < 10; i++) {
        if (q_enqueue(q, i) < 0) {
            printf("%d 入队失败\n", i);
        }
    }
    int d;
    while (!q_is_empty(q)) {
        q_dequeue(q, &d);
        printf("%d 出队\n", d);
    }
    if (q_destroy(&q) < 0) {
        printf("队列销毁失败!\n");
    }
}

sem_t *empty;
sem_t *exist;

void *producer(void *arg) {
    struct Param *p = (struct Param *)arg;
    struct Queue *q = p->q;
    int id = p->id;
    while (1) {
        sem_wait(empty);
        printf("生产者 %d 进来\n", id);
        int t = rand() % 100 + 1;
        q_enqueue(q, t);
        printf("生产者 %d 生产蛋糕 %d，并放入队列中，现在队列总共有 %d 个蛋糕\n", id, t, q_size(q));
        sem_post(exist);
        sleep(rand() % 3);
    }
    return (void *)1;
}

void *consumer(void *arg) {
    struct Param *p = (struct Param *)arg;
    struct Queue *q = p->q;
    int id = p->id;
    while (1) {
        sem_wait(exist);
        printf("消费者 %d 进来\n", id);
        int d;
        q_dequeue(q, &d);
        printf("消费者 %d 吃了蛋糕 %d，队列还剩下 %d 个蛋糕\n", id, d, q_size(q));
        sem_post(empty);
        sleep(rand() % 3);
    }
    return (void *)1;
}

/**
 *   int sem_init(sem_t *sem,int pshared,unsigned int value);
 int sem_destroy(sem_t *sem);
 int sem_wait(sem_t *sem);
 int sem_trywait(sem_t *sem);
 int sem_post(sem_t *sem);
 int sem_getvalue(sem_t *sem);
 */
int main() {
    
    int q_capacity = 10;
    
    /* 初始化信号量 */
    if ((empty = sem_open("./empty", O_CREAT, 0644, q_capacity)) == SEM_FAILED) {
        perror("sem_init ");
        exit(1);
    }
    if ((exist = sem_open("./exist", O_CREAT, 0644, 0)) == SEM_FAILED) {
        perror("sem_init ");
        exit(1);
    }
    
    /* 创建生产线 */
    struct Queue *q = NULL;
    q_create(&q);
    
    /* 10 个消费者，3 个生产者 */
    pthread_t cs[10], ps[3];
    for (int i = 0; i < 10; i++) {
        struct Param p;
        p.q = q;
        p.id = i;
        pthread_create(cs + i, NULL, consumer, &p);
    }
    for (int i = 0; i < 3; i++) {
        struct Param p;
        p.q = q;
        p.id = i;
        pthread_create(ps + i, NULL, producer, &p);
    }
    
    while (1);
    
    return 0;
}

