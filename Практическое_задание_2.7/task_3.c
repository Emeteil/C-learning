#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    char** strings;
    int count;
} StringsStruct;

void print_strs(StringsStruct* strs);

void cleanup_handler(void* arg) {
    puts("Поток завершился/был отменён");
}

void* thread_func(void* arg) {
    pthread_cleanup_push(cleanup_handler, NULL);
    print_strs((StringsStruct*)arg);
    pthread_cleanup_pop(0);
    return NULL;
}

void print_strs(StringsStruct* strs) {
    for (int i = 0; i < strs->count; i++) {
        pthread_testcancel();
        printf("%s\n", strs->strings[i]);
        sleep(2);
    }
}

int main() {
    pthread_t threads[4];
    StringsStruct params[4];
    
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
    char* strings2[] = {
        "Поток 3: строка 1",
        "Поток 3: строка 2",
        "Поток 3: строка 3"
    };
    char* strings3[] = {
        "Поток 4: строка 1",
        "Поток 4: строка 2",
        "Поток 4: строка 3"
    };
    
    params[0].strings = strings0;
    params[0].count = 3;
    
    params[1].strings = strings1;
    params[1].count = 3;
    
    params[2].strings = strings2;
    params[2].count = 3;
    
    params[3].strings = strings3;
    params[3].count = 3;
    
    for (int i = 0; i < 4; i++)
        if (pthread_create(&threads[i], NULL, thread_func, &params[i]))
            return 1;
    
    sleep(2);
    
    for (int i = 0; i < 4; i++)
        pthread_cancel(threads[i]);
    
    sleep(1); // время для вывода cleanup_handler
    
    return 0;
}