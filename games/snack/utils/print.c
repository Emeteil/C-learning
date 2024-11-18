#include <stdio.h>
#include <stdlib.h>

void print_game_field(size_t rows, size_t cols, int matrix[rows][cols]) {
    system("clear");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (matrix[i][j])
            {
                case -1:
                    printf("🍎 ");
                    break;
                case 0:
                    printf(". ");
                    break;
                default:
                    printf("# ");
                    break;
            }
        }
        printf("\n");
    }
}