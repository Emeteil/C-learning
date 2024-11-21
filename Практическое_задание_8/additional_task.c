#include <stdio.h>

void print_matrix(size_t size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        puts("");
    }
}

void main() {
    size_t N = 0;

    printf("N: ");
    scanf("%zu", &N);

    int matrix[N][N];

    int a = 1;
    int init_x = 0;
    int end_x = N - 1;
    int init_y = 0;
    int end_y = N - 1;

    while (init_x <= end_x && init_y <= end_y) {
        for (int y = init_y; y <= end_y; y++) {
            matrix[init_x][y] = a;
            a++;
        }
        init_x++;

        for (int x = init_x; x <= end_x; x++) {
            matrix[x][end_y] = a;
            a++;
        }
        end_y--;

        if (init_x <= end_x) {
            for (int y = end_y; y >= init_y; y--) {
                matrix[end_x][y] = a;
                a++;
            }
            end_x--;
        }

        if (init_y <= end_y) {
            for (int x = end_x; x >= init_x; x--) {
                matrix[x][init_y] = a;
                a++;
            }
            init_y++;
        }
    }

    print_matrix(N, matrix);
}