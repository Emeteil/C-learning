#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_MSG_LEN 128
#define MAX_QUEUE_SIZE 10

int id = -1;
pthread_mutex_t id_mutex = PTHREAD_MUTEX_INITIALIZER;

int get_new_id() {
    pthread_mutex_lock(&id_mutex);
    id++;
    pthread_mutex_unlock(&id_mutex);

    return id;
}

typedef struct {
    char messages[MAX_QUEUE_SIZE][MAX_MSG_LEN + 1];
    int front; // индекс начала
    int rear; // индекс конца
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    int drop;
} queue;

void queue_init(queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    q->drop = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

int msgSend(queue *q, const char *msg) {
    pthread_mutex_lock(&q->mutex);
    
    while (q->count == MAX_QUEUE_SIZE && !q->drop) {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    
    if (q->drop) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    
    int len = strlen(msg);
    if (len > MAX_MSG_LEN) {
        len = MAX_MSG_LEN;
    }
    
    strncpy(q->messages[q->rear], msg, len);
    q->messages[q->rear][len] = '\0';
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->count++;
    
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    
    return len;
}

int msgRecv(queue *q, char *buf, size_t bufsize) {
    pthread_mutex_lock(&q->mutex);
    
    while (q->count == 0 && !q->drop) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    
    if (q->drop && q->count == 0) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    
    int len = strlen(q->messages[q->front]);
    if (len > bufsize - 1) {
        len = bufsize - 1;
    }
    
    strncpy(buf, q->messages[q->front], len);
    buf[len] = '\0';
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->count--;
    
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    
    return len;
}

void msgDrop(queue *q) {
    pthread_mutex_lock(&q->mutex);
    q->drop = 1;
    pthread_cond_broadcast(&q->not_empty);
    pthread_cond_broadcast(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
}

typedef struct {
    queue *q;
    const char *name;
} client_args;

typedef struct {
    queue *q;
    const char *name;
} server_args;

void *client_thread(void *arg) {
    client_args *args = (client_args *)arg;
    queue *q = args->q;
    const char *name = args->name;
    
    srand(time(NULL));
    
    while (1) {
        char msg[MAX_MSG_LEN + 1];
        int m_id = get_new_id();
        snprintf(msg, sizeof(msg), "Привет от %s, уникальный id %d", name, m_id);
        
        int sent = msgSend(q, msg);
        if (sent == -1) {
            printf("%s: завершение...\n", name);
            break;
        }
        
        printf("%s: отправил сообщение (%d)\n", name, m_id);
        
        int sleep_time = rand() % 3 + 1;
        sleep(sleep_time);
    }
    
    return NULL;
}

void *server_thread(void *arg) {
    server_args *args = (server_args *)arg;
    queue *q = args->q;
    const char *name = args->name;
    
    srand(time(NULL));
    
    while (1) {
        char buf[MAX_MSG_LEN + 1];
        int received = msgRecv(q, buf, sizeof(buf));
        if (received == -1) {
            printf("%s: завершение...\n", name);
            break;
        }
        
        printf("[%s] %s\n", name, buf);
        
        int sleep_time = rand() % 3 + 1;
        sleep(sleep_time);
    }
    
    return NULL;
}

int main() {
    queue q;
    queue_init(&q);
    
    const char *client_names[] = {"Client1", "Client2", "Client3"};
    const char *server_names[] = {"Server1", "Server2"};
    
    pthread_t clients[3];
    pthread_t servers[2];
    
    client_args cargs[3];
    for (int i = 0; i < 3; i++) {
        cargs[i].q = &q;
        cargs[i].name = client_names[i];
        pthread_create(&clients[i], NULL, client_thread, &cargs[i]);
    }
    
    server_args sargs[2];
    for (int i = 0; i < 2; i++) {
        sargs[i].q = &q;
        sargs[i].name = server_names[i];
        pthread_create(&servers[i], NULL, server_thread, &sargs[i]);
    }
    
    sleep(10);
    
    msgDrop(&q);
    
    for (int i = 0; i < 3; i++) {
        pthread_join(clients[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(servers[i], NULL);
    }

    return 0;
}