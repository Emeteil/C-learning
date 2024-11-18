#include <stdio.h>
#include "header.h"

int main() {
    const size_t game_field_size = 10;
    Rating result;

    result = game(game_field_size, 350);
    
    if (!result.win) {
        printf("Ты проиграл!\nДлина: %d\n", result.leaght);
        return 1;
    }

    printf("Ты выйграл!\nДлина: %d\n", result.leaght);
    return 0;
}