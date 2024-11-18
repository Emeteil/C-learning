#include <stdio.h>
#include "../header.h"

void fill_matrix(size_t rows, size_t cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            matrix[i][j] = 0;
        }
    }

    int apple_index = random_int(0, rows * cols - 1);
    matrix[apple_index / cols][apple_index % cols] = -1;

    int snake_index;
    do {
        snake_index = random_int(0, rows * cols - 1);
    } while (snake_index == apple_index);

    matrix[snake_index / cols][snake_index % cols] = 1;
}