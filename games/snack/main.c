#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int main() {
    const size_t game_field_size = 10;
    int matrix[game_field_size][game_field_size];
    unsigned int length = 1;
    char key = 'w'; // bad idea.. rework

    fill_matrix(game_field_size, game_field_size, matrix);

    while (1) {
        print_game_field(game_field_size, game_field_size, matrix);

        while (kbhit())
            key = getchar();

        int i, j;
        for (i = 0; i < game_field_size; i++) {
            for (j = 0; j < game_field_size; j++)
                if (matrix[i][j] == game_field_size)
                    break;
            if (matrix[i][j] == game_field_size)
                break;
        }

        int next_i, next_j;
        switch (key) {
            case 'w':
                next_i = (i - 1) % game_field_size;
                next_j = j;
                break;
            case 's':
                next_i = (i + 1) % game_field_size;
                next_j = j;
                break;
            case 'a':
                next_i = i;
                next_j = (j - 1) % game_field_size;
                break;
            case 'd':
                next_i = i;
                next_j = (j + 1) % game_field_size;
                break;
        }

        switch (matrix[next_i][next_j]) {
            case -1:
                length++;
                matrix[next_i][next_j] = length;
                for (int i = 0; i < game_field_size; i++)
                    for (int j = 0; j < game_field_size; j++)
                        if (matrix[i][j] != 0 & matrix[i][j] != -1)
                            matrix[i][j]++;
                break;
            case 0:
                matrix[next_i][next_j] = length + 1;
                break;
            default:
                break;
        }

        for (int i = 0; i < game_field_size; i++)
            for (int j = 0; j < game_field_size; j++)
                if (matrix[i][j] != 0 & matrix[i][j] != -1)
                    matrix[i][j]--;

        sleep(1);
    }

    return 0;
}