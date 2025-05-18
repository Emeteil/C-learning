#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_N_PRINT 50
#define CREATE_GRAPHIC 50
#define GENERATE_GRAPH 0

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