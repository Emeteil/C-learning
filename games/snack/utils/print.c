#include <stdio.h>

void print_game_field(size_t rows, size_t cols, char matrix[rows][cols]) {
    system("clear");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (matrix[i][j])
            {
                case -1:
                    printf("-1 ");
                    break;
                case 0:
                    printf("0 ");
                    break;
                default:
                    printf("%d ", matrix[i][j]);
                    break;
            }
        }
        printf("\n");
    }
}