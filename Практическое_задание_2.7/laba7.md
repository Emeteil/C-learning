### task 3

## упр. 1
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void print_strs();

void* thread_func(void* arg) {
    print_strs();
    return NULL;
}

void print_strs() {
    for (int i = 0; i < 5; i++)
        printf("%d строка\n", i);
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_func, NULL))
        return 1;
    print_strs();
    return 0;
}
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
0 строка
1 строка
2 строка
3 строка
4 строка
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
0 строка
1 строка
2 строка
3 строка
4 строка
0 строка
0 строка
1 строка
2 строка
3 строка
3 строка
```
Проблемы:
- Конкуренция потоков (race condition)
- Завершение программы до завершения второго потока
- Буферизация вывода printf (из за этого некотырые строки выводятся больше 2 раз)

## упр. 2
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void print_strs();

void* thread_func(void* arg) {
    print_strs();
    return NULL;
}

void print_strs() {
    for (int i = 0; i < 5; i++)
        printf("%d строка\n", i);
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_func, NULL))
        return 1;
    pthread_join(thread, NULL);
    print_strs();
    return 0;
}
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
0 строка
1 строка
2 строка
3 строка
4 строка
0 строка
1 строка
2 строка
3 строка
4 строка
```

## упр. 3
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char** strings;
    int count;
} StringsStruct;

void print_strs(StringsStruct* strs);

void* thread_func(void* arg) {
    print_strs((StringsStruct*)arg);
    return NULL;
}

void print_strs(StringsStruct* strs) {
    for (int i = 0; i < strs->count; i++)
        printf("%s\n", strs->strings[i]);
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
    
    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);
    
    return 0;
}
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
Поток 1: строка 1
Поток 1: строка 2
Поток 1: строка 3
Поток 2: строка 1
Поток 2: строка 2
Поток 2: строка 3
Поток 3: строка 1
Поток 3: строка 2
Поток 3: строка 3
Поток 4: строка 1
Поток 4: строка 2
Поток 4: строка 3
```

## упр. 4
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    char** strings;
    int count;
} StringsStruct;

void print_strs(StringsStruct* strs);

void* thread_func(void* arg) {
    print_strs((StringsStruct*)arg);
    return NULL;
}

void print_strs(StringsStruct* strs) {
    for (int i = 0; i < strs->count; i++) {
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
    
    return 0;
}
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
Поток 1: строка 1
Поток 3: строка 1
Поток 4: строка 1
Поток 2: строка 1
Поток 3: строка 2
Поток 4: строка 2
Поток 2: строка 2
Поток 1: строка 2
```

## упр. 5
```c
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
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_3.c ; ./a.out
Поток 1: строка 1
Поток 3: строка 1
Поток 2: строка 1
Поток 4: строка 1
Поток 2: строка 2
Поток 1: строка 2
Поток 3: строка 2
Поток 4: строка 2
Поток завершился/был отменён
Поток завершился/был отменён
Поток завершился/был отменён
Поток завершился/был отменён
```

## упр. 6
```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* sleep_print(void* arg) {
    int a = *(int*)arg;
    usleep(a * 1000); // num микросекунд (* 1000 для точности)
    printf("%d ", a);
    return NULL;
}

int main() {
    int array[] = {
        42, 187, 5, 249, 123, 156, 789,  99, 175,  
        321, 245, 12, 199, 450, 220, 777, 188, 64, 133,  
        911, 240, 3, 210, 512,2200, 777, 1888, 64, 1333,  
        911, 2400, 3, 2100, 512, 1666, 888, 2300, 27, 1450,  
        1001, 2500, 404, 1950, 111, 2250, 888, 1776, 50, 1234
    };
    int n = sizeof(array) / sizeof(array[0]);
    pthread_t threads[n];

    for (int i = 0; i < n; i++) 
        pthread_create(&threads[i], NULL, sleep_print, &array[i]);

    for (int i = 0; i < n; i++) 
        pthread_join(threads[i], NULL);
    
    puts("");
    
    return 0;
}
```
#Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc sleepsort.c ; ./a.out
3 5 3 12 27 42 50 64 64 99 111 123 133 156 175 187 188 199 210 220 240 245 249 321 404 450 512 512 777 777 789 888 888 911 911 1001 1234 1333 1450 1666 1776 1888 1950 2100 2200 2250 2300 2400 2500 
```