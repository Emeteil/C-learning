#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

Rating game(const size_t game_field_size, unsigned int delay) {
    int matrix[game_field_size][game_field_size];
    unsigned int length = 1;
    char action = 'l';
    
    fill_matrix(game_field_size, game_field_size, matrix);

    while (1) {
        read_action(&action);

        int i, j;
        find_head(game_field_size, matrix, length, &i, &j);
        
        int next_i, next_j;
        find_element_instead_of_head(
            action,
            i, j,
            (int)game_field_size,
            &next_i,
            &next_j
        );
        
        switch (matrix[next_i][next_j]) {
            case -1:
                lengthen_snake(
                    game_field_size,
                    matrix,
                    &length,
                    next_i,
                    next_j
                );
                
                if (length == game_field_size * game_field_size) {
                    print_game_field(game_field_size, game_field_size, matrix);
                    return (Rating){
                        .win = 1,
                        .leaght = length
                    };
                }
                add_apple(game_field_size, matrix);
                break;
            case 0:
            case 1:
                matrix[next_i][next_j] = length + 1;
                break;
            default:
                return (Rating){
                    .win = 0,
                    .leaght = length
                };
        }

        step_game(game_field_size, matrix);

        print_game_field(game_field_size, game_field_size, matrix);
        usleep(delay * 1000);
    }
}