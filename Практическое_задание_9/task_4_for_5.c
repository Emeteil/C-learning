#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(size_t N, size_t M, int** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        puts("");
    }
}

size_t get_size_from_user(char var_name[]) {
    size_t size = 0;
    while (1) {
        printf("Введите размер %s: ", var_name);
        scanf("%zu", &size);
        if (size) break; 
    }
    return size;
}

int dialog_box(char question[]) {
    char answer = 0;
    while (1) {
        printf("%s (Y/N): ", question);
        scanf(" %c", &answer);
        if (
            answer == 'Y' ||
            answer == 'N' ||
            answer == 'y' ||
            answer == 'n'
        ) break;
    }
    return (answer == 'Y' || answer == 'y');
} 

int random_num(int a, int b) {
    return a + rand() % (b - a + 1);
}

int** auto_fill_matrix(size_t N, size_t M, int a, int b) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(M * sizeof(int));
        if (matrix[i] == NULL) return NULL;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = random_num(a, b);

    return matrix;
}

int** fill_matrix(size_t N, size_t M) {
    int** matrix = (int**)malloc(N * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(M * sizeof(int));
        if (matrix[i] == NULL) return NULL;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            printf("Элемент %d %d: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    
    return matrix;
}

int** multiply_matrix(size_t M, size_t N, size_t K, int** A, int** B) {
    int** matrix = (int**)malloc(M * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < M; i++) {
        matrix[i] = (int*)calloc(K, sizeof(int));
        if (matrix[i] == NULL) return NULL;
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            for (int k = 0; k < N; k++)
                matrix[i][j] += A[i][k] * B[k][j];

    return matrix;
}

int find_line_with_max_n_nums(size_t N, size_t M, int** matrix) {
    int index = 0;
    int max_count = 0;
    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 0; j < M; j++)
            if (matrix[i][j] < 0)
                count++;
        
        if (count > max_count) {
            index = i;
            max_count = count;
        }
    }

    return index;
}

int count_n_nums(size_t N, size_t M, int** matrix) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (matrix[i][j] < 0)
                count++;

    return count;
}

void replace_n_nums_by_count(size_t N, size_t M, int** matrix) {
    int count = count_n_nums(N, M, matrix);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (matrix[i][j] < 0)
                matrix[i][j] = count;
}

void swap_line_by_reverse(size_t M, int** matrix, int line) {
    for (int j = 0; j < (M / 2); j++) {
        int save = matrix[line][j];
        matrix[line][j] = matrix[line][M - 1 - j];
        matrix[line][M - 1 - j] = save;
    }
}

void clear_memory_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
}

int main() {
    srand(time(NULL));
    puts("Нужно создать 2 матрицы A[m,n] и B[n,k]");
    size_t m = get_size_from_user("m");
    size_t n = get_size_from_user("n");
    size_t k = get_size_from_user("k");

    int** A = dialog_box("Заполнить матрицы A рандомно?") ?
        auto_fill_matrix(m, n, -9, 9) : fill_matrix(m, n);
    
    int** B = dialog_box("Заполнить матрицы B рандомно?") ?
        auto_fill_matrix(n, k, -9, 9) : fill_matrix(n, k);

    if (A == NULL || B == NULL) {
        puts("Не удалось выделить память для работы программы!");
        return 1;
    }
    
    puts("Матрица A: ");
    print_matrix(m, n, A);

    puts("Матрица B: ");
    print_matrix(n, k, B);

    int** C = multiply_matrix(m, n, k, A, B);

    if (C == NULL) {
        puts("Не удалось выделить память для работы программы!");
        return 1;
    }

    clear_memory_matrix(A, m);
    A = NULL;
    clear_memory_matrix(B, n);
    B = NULL;

    puts("Матрица C(A x B): ");
    print_matrix(m, k, C);

    printf(
        "В строке %d наибольшее количество отрицательных чисел!\n",
        find_line_with_max_n_nums(m, k, C)
    );

    replace_n_nums_by_count(m, k, C);

    puts("Замена отрицательных чисел на их количество в C: ");
    print_matrix(m, k, C);

    int line = random_num(0, m - 1);
    printf("Записываем строку %d в обратном порядке:\n", line);
    swap_line_by_reverse(k, C, line);
    print_matrix(m, k, C);

    clear_memory_matrix(C, m);
    C = NULL;

    return 0;
}