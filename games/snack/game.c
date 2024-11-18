#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

Rating game(size_t game_field_size) {
    int matrix[game_field_size][game_field_size];
    unsigned int length = 1;
    char action = 'r';
    char key = 'w'; // bad idea.. rework

    fill_matrix(game_field_size, game_field_size, matrix);

    while (1) {
        while (kbhit())
            key = getchar();
        
        switch (key) {
            case 'w':
                if (action != 'd')
                    action = 'u';
                break;
            case 's':
                if (action != 'u')
                    action = 'd';
                break;
            case 'a':
                if (action != 'r')
                    action = 'l';
                break;
            case 'd':
                if (action != 'l')
                    action = 'r';
                break;
        }

        int i, j;
        for (i = 0; i < game_field_size; i++)
            for (j = 0; j < game_field_size; j++)
                if (matrix[i][j] == length)
                    goto found;
        found:
        
        int next_i, next_j;
        switch (action) {
            case 'u':
                next_i = (i - 1) % game_field_size;
                next_j = j;
                break;
            case 'd':
                next_i = (i + 1) % game_field_size;
                next_j = j;
                break;
            case 'l':
                next_i = i;
                next_j = (j - 1) % game_field_size;
                break;
            case 'r':
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
                        if (matrix[i][j] != 0 && matrix[i][j] != -1)
                            matrix[i][j]++;
                break;
            case 0:
                matrix[next_i][next_j] = length + 1;
                break;
            default:
                return (Rating){
                    .win = 0,
                    .leaght = length
                };
        }

        if (length == game_field_size * game_field_size)
            return (Rating){
                .win = 0,
                .leaght = length
            };

        print_game_field(game_field_size, game_field_size, matrix);
        sleep(1);
    }

    return (Rating){
        .win = 0,
        .leaght = length
    };
}


// switch (matrix[next_i][next_j]) {
//     case -1: {
//         length++;
//         matrix[next_i][next_j] = length;
//         for (int i = 0; i < game_field_size; i++)
//             for (int j = 0; j < game_field_size; j++)
//                 if (matrix[i][j] != 0 && matrix[i][j] != -1)
//                     matrix[i][j]++;
//         for (int i = 0; i < game_field_size; i++)
//             for (int j = 0; j < game_field_size; j++)
//                 if (matrix[i][j] != 0 & matrix[i][j] != -1)
//                     matrix[i][j]--;
        
//         int count_zero = 0;
//         for (int i = 0; i < game_field_size; i++)
//             for (int j = 0; j < game_field_size; j++)
//                 if (!matrix[i][j]) count_zero++;

//         // Declare the VLA outside the loop
//         int indexs[count_zero][2];
//         int index = 0;
//         for (int i = 0; i < game_field_size; i++)
//             for (int j = 0; j < game_field_size; j++)
//                 if (!matrix[i][j]) {
//                     indexs[index][0] = i;
//                     indexs[index][1] = j;
//                     index++;
//                 }
        
//         index = random_int(0, count_zero - 1);
//         matrix[indexs[index][0]][indexs[index][1]] = -1;
//         break;
//     }
//     case 0:
//         matrix[next_i][next_j] = length + 1;
//         break;
//     default:
//         return (Rating){
//             .win = 0,
//             .leaght = length
//         };
// }