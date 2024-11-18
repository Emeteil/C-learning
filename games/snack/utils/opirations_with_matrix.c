#include "../header.h"

void find_head(
        size_t game_field_size,
        int matrix[game_field_size][game_field_size],
        int length,
        int *x,
        int *y
    ) {
    int i, j;
    for (i = 0; i < game_field_size; i++)
        for (j = 0; j < game_field_size; j++)
            if (matrix[i][j] == length) {
                *x = i;
                *y = j;
                return;
            }
}

void find_element_instead_of_head(
        char action,
        int i,
        int j,
        int game_field_size,
        int *next_i,
        int *next_j
    ) {
    switch (action) {
        case 'u':
            *next_i = (i - 1) % game_field_size;
            if (*next_i < 0) *next_i += game_field_size;
            *next_j = j;
            break;
        case 'd':
            *next_i = (i + 1) % game_field_size;
            *next_j = j;
            break;
        case 'l':
            *next_i = i;
            *next_j = (j - 1) % game_field_size;
            if (*next_j < 0) *next_j += game_field_size;
            break;
        case 'r':
            *next_i = i;
            *next_j = (j + 1) % game_field_size;
            break;
    }
}

void lengthen_snake(
        size_t game_field_size,
        int matrix[game_field_size][game_field_size],
        int *length,
        int next_i,
        int next_j
    ) {
    (*length)++;
    matrix[next_i][next_j] = *length;

    for (int i = 0; i < game_field_size; i++)
        for (int j = 0; j < game_field_size; j++)
            if (matrix[i][j] != 0 && matrix[i][j] != -1) 
                matrix[i][j]++;
}

void add_apple(size_t game_field_size, int matrix[game_field_size][game_field_size]) {
    int count_zero = 0;
    
    for (int i = 0; i < game_field_size; i++)
        for (int j = 0; j < game_field_size; j++)
            if (matrix[i][j] == 0)
                count_zero++;

    int indexs[count_zero][2];
    int index = 0;

    for (int i = 0; i < game_field_size; i++)
        for (int j = 0; j < game_field_size; j++)
            if (matrix[i][j] == 0) {
                indexs[index][0] = i;
                indexs[index][1] = j;
                index++;
            }

    index = random_int(0, count_zero - 1);
    matrix[indexs[index][0]][indexs[index][1]] = -1;
}

void step_game(size_t game_field_size, int matrix[game_field_size][game_field_size]) {
    for (int i = 0; i < game_field_size; i++)
        for (int j = 0; j < game_field_size; j++)
            if (matrix[i][j] != 0 && matrix[i][j] != -1)
                matrix[i][j]--;
}