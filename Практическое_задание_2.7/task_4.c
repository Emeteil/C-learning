#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int key = 0;

typedef struct {
    char** strings;
    int count;
    int thread_id;
} StringsStruct;

void print_strings(StringsStruct* strs) {
    for (int i = 0; i < strs->count; i++) {
        pthread_mutex_lock(&mutex);
        while (key != strs->thread_id) {
            pthread_mutex_unlock(&mutex);
            usleep(100);
            pthread_mutex_lock(&mutex);
        }
        
        printf("%s\n", strs->strings[i]);
        key = (key + 1) % 2;
        
        pthread_mutex_unlock(&mutex);
    }
}

void* thread_func(void* arg) {
    print_strings((StringsStruct*)arg);
    return NULL;
}

int main() {
    pthread_t thread;
    StringsStruct params[2];
    
    char* strings0[] = {
        "Поток 1: строка 1",
        "Поток 1: строка 2",
        "Поток 1: строка 3"
    };
    char* strings1[] = {
        "Поток 2: строка 1",
        "Поток 2: строка 2",
        "Поток 2: строка 3"
    };
    
    params[0].strings = strings0;
    params[0].count = 3;
    params[0].thread_id = 0;
    
    params[1].strings = strings1;
    params[1].count = 3;
    params[1].thread_id = 1;

    if (pthread_create(&thread, NULL, thread_func, &params[1])) {
        return 1;
    }
    
    print_strings(&params[0]);
    
    pthread_join(thread, NULL);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}