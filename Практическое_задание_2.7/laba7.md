# task 3

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
### Output:
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
### Output:
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
### Output:
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
### Output:
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
### Output:
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
### Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc sleepsort.c ; ./a.out
3 5 3 12 27 42 50 64 64 99 111 123 133 156 175 187 188 199 210 220 240 245 249 321 404 450 512 512 777 777 789 888 888 911 911 1001 1234 1333 1450 1666 1776 1888 1950 2100 2200 2250 2300 2400 2500 
```

# task 4

## упр. 7
```c
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
```
### Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc task_4.c ; ./a.out
Поток 1: строка 1
Поток 2: строка 1
Поток 1: строка 2
Поток 2: строка 2
Поток 1: строка 3
Поток 2: строка 3
```

## упр. 8,9
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_N_PRINT 50
#define CREATE_GRAPHIC 50
#define GENERATE_GRAPH 1

typedef struct {
    int N;
    int** A;
    int** B;
    int** C;
    int s_row;
    int e_row;
} ThreadArgs;

void matrix_multiply(int N, int** A, int** B, int** C, int s_row, int e_row) {
    for (int i = s_row; i < e_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void* thread_multiply(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    matrix_multiply(
        targs->N,
        targs->A,
        targs->B,
        targs->C,
        targs->s_row,
        targs->e_row
    );
    return NULL;
}

double multithreaded_matrix_multiply(int N, int** A, int** B, int** C, int len_threads) {
    if (len_threads > N)
        len_threads = N;
    
    pthread_t threads[len_threads];
    ThreadArgs args[len_threads];
    
    int rows_per_thread = N / len_threads;
    int rem_rows = N % len_threads;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < len_threads; i++) {
        args[i].N = N;
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].s_row = i * rows_per_thread;
        args[i].e_row = (i + 1) * rows_per_thread;
        
        pthread_create(&threads[i], NULL, thread_multiply, &args[i]);
    }

    if (rem_rows > 0) {
        matrix_multiply(
            N,
            A,
            B,
            C,
            rows_per_thread * len_threads,
            rows_per_thread * len_threads + rem_rows
        );
    }

    for (int i = 0; i < len_threads; i++)
        pthread_join(threads[i], NULL);

    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + 
           (end.tv_usec - start.tv_usec) / 1e6;
}

void print_matrix(int N, int** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void generate_graph() {
    int sizes[] = {100, 300, 500, 700, 900};
    int len_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int len_threads = sizeof(thread_counts) / sizeof(thread_counts[0]);
    
    double results[len_sizes][len_threads];
    
    puts("Начало вычислений...");
    printf("Всего размеров матриц: %d\n", len_sizes);
    printf("Всего вариантов потоков: %d\n\n", len_threads);
    
    for (int i = 0; i < len_sizes; i++) {
        int N = sizes[i];
        printf("Обработка матрицы %dx%d (%d/%d)\n", N, N, i+1, len_sizes);
        
        int** A = (int**)malloc(N * sizeof(int*));
        int** B = (int**)malloc(N * sizeof(int*));
        int** C = (int**)malloc(N * sizeof(int*));
        for (int k = 0; k < N; k++) {
            A[k] = (int*)malloc(N * sizeof(int));
            B[k] = (int*)malloc(N * sizeof(int));
            C[k] = (int*)malloc(N * sizeof(int));
            
            for (int l = 0; l < N; l++) {
                A[k][l] = rand() % 100;
                B[k][l] = rand() % 100;
            }
        }
        
        for (int j = 0; j < len_threads; j++) {
            int threads = thread_counts[j];
            printf("  Тестирование с %d потоками... ", threads);
            fflush(stdout);
            
            double time = multithreaded_matrix_multiply(N, A, B, C, threads);
            results[i][j] = time;
            
            printf("готово (%.4f сек)\n", time);
        }
        
        for (int k = 0; k < N; k++) {
            free(A[k]);
            free(B[k]);
            free(C[k]);
        }
        free(A);
        free(B);
        free(C);
        
        puts("");
    }
    
    puts("Все вычисления завершены. Генерация графика...");
    
    FILE* py_file = fopen("tmp.py", "w");
    if (py_file == NULL) return;
    
    fprintf(py_file, "import matplotlib.pyplot as plt\n");
    fprintf(py_file, "import numpy as np\n\n");
    
    fprintf(py_file, "sizes = [");
    for (int i = 0; i < len_sizes; i++) {
        fprintf(py_file, "%d", sizes[i]);
        if (i < len_sizes - 1)
            fprintf(py_file, ", ");
    }
    fprintf(py_file, "]\n\n");
    
    fprintf(py_file, "thread_counts = [");
    for (int j = 0; j < len_threads; j++) {
        fprintf(py_file, "%d", thread_counts[j]);
        if (j < len_threads - 1)
            fprintf(py_file, ", ");
    }
    fprintf(py_file, "]\n\n");
    
    fprintf(py_file, "results = [\n");
    for (int i = 0; i < len_sizes; i++) {
        fprintf(py_file, "    [");
        for (int j = 0; j < len_threads; j++) {
            fprintf(py_file, "%.4f", results[i][j]);
            if (j < len_threads - 1)
                fprintf(py_file, ", ");
        }
        fprintf(py_file, "]");
        if (i < len_sizes - 1)
            fprintf(py_file, ",");
        fprintf(py_file, "\n");
    }
    fprintf(py_file, "]\n\n");
    fprintf(py_file, "plt.figure(figsize=(12, 8))\n");
    fprintf(py_file, "for j in range(len(thread_counts)):\n");
    fprintf(py_file, "    plt.plot(sizes, [results[i][j] for i in range(len(sizes))], \n");
    fprintf(py_file, "             marker='o', label=f'{thread_counts[j]} потоков')\n\n");
    fprintf(py_file, "plt.xlabel('Размер матрицы (N x N)')\n");
    fprintf(py_file, "plt.ylabel('Время выполнения (секунды)')\n");
    fprintf(py_file, "plt.legend()\n");
    fprintf(py_file, "plt.grid(True)\n");
    fprintf(py_file, "plt.savefig('graph.png')\n");
    // fprintf(py_file, "plt.show()\n");
    
    fclose(py_file);
    
    system("python3 tmp.py");
    puts("График сохранён!");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 3) {
        printf("Использование: %s <размер матрицы> <количество потоков>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int len_threads = atoi(argv[2]);

    if (N <= 0 || len_threads <= 0) {
        printf("Размер матрицы и количество потоков должны быть положительными числами.\n");
        return 1;
    }

    int** A = (int**)malloc(N * sizeof(int*));
    int** B = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    double time_sec = multithreaded_matrix_multiply(N, A, B, C, len_threads);

    if (N < MAX_N_PRINT) {
        printf("Матрица A:\n");
        print_matrix(N, A);

        printf("Матрица B:\n");
        print_matrix(N, B);

        printf("Матрица C (результат умножения A * B):\n");
        print_matrix(N, C);
    }
    printf("Время выполнения %f\n", time_sec);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    if (GENERATE_GRAPH)
        generate_graph();
    return 0;
}
```
### Output
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc matrix_multiplication.c ; ./a.out
Матрица A:
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
Матрица B:
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 1 
Матрица C (результат умножения A * B):
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
11 11 11 11 11 11 11 11 11 11 11 
Время выполнения 0.000670
Начало вычислений...
Всего размеров матриц: 5
Всего вариантов потоков: 8

Обработка матрицы 100x100 (1/5)
  Тестирование с 1 потоками... готово (0.0084 сек)
  Тестирование с 2 потоками... готово (0.0069 сек)
  Тестирование с 4 потоками... готово (0.0045 сек)
  Тестирование с 8 потоками... готово (0.0033 сек)
  Тестирование с 16 потоками... готово (0.0038 сек)
  Тестирование с 32 потоками... готово (0.0058 сек)
  Тестирование с 64 потоками... готово (0.0112 сек)
  Тестирование с 128 потоками... готово (0.0114 сек)

Обработка матрицы 300x300 (2/5)
  Тестирование с 1 потоками... готово (0.2693 сек)
  Тестирование с 2 потоками... готово (0.1293 сек)
  Тестирование с 4 потоками... готово (0.1015 сек)
  Тестирование с 8 потоками... готово (0.0866 сек)
  Тестирование с 16 потоками... готово (0.0915 сек)
  Тестирование с 32 потоками... готово (0.0834 сек)
  Тестирование с 64 потоками... готово (0.1034 сек)
  Тестирование с 128 потоками... готово (0.1001 сек)

Обработка матрицы 500x500 (3/5)
  Тестирование с 1 потоками... готово (1.3277 сек)
  Тестирование с 2 потоками... готово (0.7970 сек)
  Тестирование с 4 потоками... готово (0.4366 сек)
  Тестирование с 8 потоками... готово (0.3396 сек)
  Тестирование с 16 потоками... готово (0.3467 сек)
  Тестирование с 32 потоками... готово (0.3367 сек)
  Тестирование с 64 потоками... готово (0.4257 сек)
  Тестирование с 128 потоками... готово (0.7105 сек)

Обработка матрицы 700x700 (4/5)
  Тестирование с 1 потоками... готово (3.9283 сек)
  Тестирование с 2 потоками... готово (2.1012 сек)
  Тестирование с 4 потоками... готово (1.3894 сек)
  Тестирование с 8 потоками... готово (1.1705 сек)
  Тестирование с 16 потоками... готово (1.1117 сек)
  Тестирование с 32 потоками... готово (1.1799 сек)
  Тестирование с 64 потоками... готово (1.3045 сек)
  Тестирование с 128 потоками... готово (1.8100 сек)

Обработка матрицы 900x900 (5/5)
  Тестирование с 1 потоками... готово (9.9049 сек)
  Тестирование с 2 потоками... готово (5.5175 сек)
  Тестирование с 4 потоками... готово (3.6889 сек)
  Тестирование с 8 потоками... готово (3.7509 сек)
  Тестирование с 16 потоками... готово (3.7577 сек)
  Тестирование с 32 потоками... готово (3.7469 сек)
  Тестирование с 64 потоками... готово (3.7161 сек)
  Тестирование с 128 потоками... готово (3.7414 сек)

Все вычисления завершены. Генерация графика...
График сохранён!
```
### graph.png
[![graph.png](https://i.postimg.cc/x8FNQgKV/graph.png)](https://postimg.cc/5QL2qB7s)

## упр. 10
```c
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
```
### Output
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc simple_chat.c ; ./a.out
Client2: отправил сообщение (1)
Client3: отправил сообщение (2)
Client1: отправил сообщение (0)
[Server1] Привет от Client1, уникальный id 0
[Server2] Привет от Client2, уникальный id 1
Client2: отправил сообщение (4)
Client1: отправил сообщение (5)
Client3: отправил сообщение (3)
[Server1] Привет от Client3, уникальный id 2
[Server2] Привет от Client2, уникальный id 4
[Server2] Привет от Client3, уникальный id 3
[Server1] Привет от Client1, уникальный id 5
Client1: отправил сообщение (6)
Client3: отправил сообщение (7)
[Server2] Привет от Client1, уникальный id 6
Client1: отправил сообщение (8)
Client2: отправил сообщение (9)
[Server2] Привет от Client3, уникальный id 7
[Server1] Привет от Client1, уникальный id 8
Client3: отправил сообщение (10)
[Server2] Привет от Client2, уникальный id 9
Client2: отправил сообщение (11)
Client1: отправил сообщение (12)
[Server2] Привет от Client3, уникальный id 10
Client2: отправил сообщение (13)
[Server1] Привет от Client2, уникальный id 11
Client3: отправил сообщение (14)
[Server2] Привет от Client1, уникальный id 12
[Server1] Привет от Client2, уникальный id 13
Client3: завершение...
Client2: завершение...
Client1: завершение...
[Server2] Привет от Client3, уникальный id 14
Server1: завершение...
Server2: завершение...
```

## Под Звездочкой
```c
/*
 * Классическая задача с обедающими философами и дедлоком
 * Без стыда украл исходник из НГУ POSIX практикума
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILO 5
#define DELAY 30000
#define FOOD 50

pthread_mutex_t forks[PHILO];
pthread_t phils[PHILO];
void *philosopher(void *id);
int food_on_table();
void get_fork(int, int, char *);
void down_forks(int, int);
pthread_mutex_t foodlock;

int sleep_seconds = 0;

int main(int argn, char **argv) {
    int i;
  
    if (argn == 2)
        sleep_seconds = atoi(argv[1]);
  
    pthread_mutex_init(&foodlock, NULL);
    for (i = 0; i < PHILO; i++)
        pthread_mutex_init(&forks[i], NULL);
    for (i = 0; i < PHILO; i++)
        pthread_create(&phils[i], NULL, philosopher, (void *)i);
    for (i = 0; i < PHILO; i++)
        pthread_join(phils[i], NULL);
    return 0;
}

void *philosopher(void *num) {
    int id;
    int left_fork, right_fork, f;
  
    id = (int)num;
    printf("Philosopher %d sitting down to dinner.\n", id);
    right_fork = id;
    left_fork = id + 1;
  
    /* Wrap around the forks. */
    if (left_fork == PHILO)
        left_fork = 0;

    // ------------------------------------------------------------
    /* Меняем порядок взятия вилок у последнего философа.
    Все философы юерут вилку С НАИМЕНЬШИМ НОМЕРОМ, что
    помогает избежать deadlock */
    // https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85#%D0%98%D0%B5%D1%80%D0%B0%D1%80%D1%85%D0%B8%D1%8F_%D1%80%D0%B5%D1%81%D1%83%D1%80%D1%81%D0%BE%D0%B2:~:text=%D0%B2%D1%81%D0%B5%D0%B3%D0%B4%D0%B0%20%D0%B1%D0%B5%D1%80%D1%91%D1%82%20%D1%81%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D0%B0%20%D0%B2%D0%B8%D0%BB%D0%BA%D1%83%20%D1%81%20%D0%BD%D0%B0%D0%B8%D0%BC%D0%B5%D0%BD%D1%8C%D1%88%D0%B8%D0%BC%20%D0%BD%D0%BE%D0%BC%D0%B5%D1%80%D0%BE%D0%BC
    if (id == PHILO - 1) {
        int tmp = left_fork;
        left_fork = right_fork;
        right_fork = tmp;
    }
    /* Также есть вариант добавления "официанта" в задачу, который
    будет разрешать брать вилку философу, на ru wiki советуют взять
    в качесте "официанта" семафор */
    // ------------------------------------------------------------
  
    while (f = food_on_table()) {
        /* Thanks to philosophers #1 who would like to
         * take a nap before picking up the forks, the other
         * philosophers may be able to eat their dishes and
         * not deadlock.
         */
    
        if (id == 1)
            sleep(sleep_seconds);
    
        printf("Philosopher %d: get dish %d.\n", id, f);
        get_fork(id, right_fork, "right");
        get_fork(id, left_fork, "left ");
    
        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));
        down_forks(left_fork, right_fork);
    }
    printf("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table() {
    static int food = FOOD;
    int myfood;
  
    pthread_mutex_lock(&foodlock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock(&foodlock);
    return myfood;
}

void get_fork(int phil, int fork, char *hand) {
    pthread_mutex_lock(&forks[fork]);
    printf("Philosopher %d: got %s fork %d\n", phil, hand, fork);
}

void down_forks(int f1, int f2) {
    pthread_mutex_unlock(&forks[f1]);
    pthread_mutex_unlock(&forks[f2]);
}
```
### Output:
```
emeteil@LAPTOP-0U5RS7LC:~$ gcc din_phil.c ; ./a.out
din_phil.c: In function ‘main’:
din_phil.c:36:54: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
   36 |         pthread_create(&phils[i], NULL, philosopher, (void *)i);
      |                                                      ^
din_phil.c: In function ‘philosopher’:
din_phil.c:46:10: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]
   46 |     id = (int)num;
      |          ^
Philosopher 0 sitting down to dinner.
Philosopher 0: get dish 49.
Philosopher 0: got right fork 0
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 1 sitting down to dinner.
Philosopher 2 sitting down to dinner.
Philosopher 2: get dish 47.
Philosopher 2: got right fork 2
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 3 sitting down to dinner.
Philosopher 3: get dish 46.
Philosopher 4 sitting down to dinner.
Philosopher 4: get dish 45.
Philosopher 1: get dish 48.
Philosopher 0: get dish 44.
Philosopher 1: got right fork 1
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 2: get dish 43.
Philosopher 3: got right fork 3
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 2: got right fork 2
Philosopher 1: get dish 42.
Philosopher 1: got right fork 1
Philosopher 4: get dish 41.
Philosopher 4: got right fork 0
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 40.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 3: got right fork 3
Philosopher 2: get dish 39.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 0: got right fork 0
Philosopher 4: get dish 38.
Philosopher 2: got right fork 2
Philosopher 1: get dish 37.
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 3: get dish 36.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 0: get dish 35.
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 1: got right fork 1
Philosopher 2: get dish 34.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 3: got right fork 3
Philosopher 4: get dish 33.
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 2: got right fork 2
Philosopher 1: get dish 32.
Philosopher 1: got right fork 1
Philosopher 4: get dish 31.
Philosopher 0: got right fork 0
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 30.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 29.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 28.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 27.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 3: get dish 26.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 2: get dish 25.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 0: got left  fork 1
Philosopher 1: get dish 24.
Philosopher 0: eating.
Philosopher 2: got right fork 2
Philosopher 3: get dish 23.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 0: get dish 22.
Philosopher 0: got right fork 0
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 3: get dish 21.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 0: get dish 20.
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 1: got right fork 1
Philosopher 2: get dish 19.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 3: got right fork 3
Philosopher 4: get dish 18.
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 2: got right fork 2
Philosopher 1: get dish 17.
Philosopher 1: got right fork 1
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 0: got right fork 0
Philosopher 4: get dish 16.
Philosopher 3: get dish 15.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 2: get dish 14.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 1: get dish 13.
Philosopher 2: got right fork 2
Philosopher 3: get dish 12.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 0: get dish 11.
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 1: got right fork 1
Philosopher 2: get dish 10.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 3: got right fork 3
Philosopher 4: get dish 9.
Philosopher 0: got right fork 0
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 2: got right fork 2
Philosopher 1: get dish 8.
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 3: get dish 7.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 0: get dish 6.
Philosopher 1: got right fork 1
Philosopher 4: got right fork 0
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 3: got right fork 3
Philosopher 2: get dish 5.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 4: get dish 4.
Philosopher 0: got right fork 0
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 2: got right fork 2
Philosopher 1: get dish 3.
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 3: get dish 2.
Philosopher 3: got right fork 3
Philosopher 3: got left  fork 4
Philosopher 3: eating.
Philosopher 0: get dish 1.
Philosopher 1: got right fork 1
Philosopher 4: got right fork 0
Philosopher 3 is done eating.
Philosopher 4: got left  fork 4
Philosopher 4: eating.
Philosopher 2: got left  fork 3
Philosopher 2: eating.
Philosopher 2 is done eating.
Philosopher 1: got left  fork 2
Philosopher 1: eating.
Philosopher 4 is done eating.
Philosopher 0: got right fork 0
Philosopher 1 is done eating.
Philosopher 0: got left  fork 1
Philosopher 0: eating.
Philosopher 0 is done eating.
```
*Философы доели свои пельмени и не подрались за вилки* 
<!-- [![Chat-GPT-Image-21-2025-03-17-33.png](https://i.postimg.cc/4xryC9bK/Chat-GPT-Image-21-2025-03-17-33.png)](https://postimg.cc/FYVN316m) -->
![nxjhpyeafmrdbzf-cey-0mmnhuy.png](https://habrastorage.org/webt/nx/jh/py/nxjhpyeafmrdbzf-cey-0mmnhuy.png)