#include <stdio.h>
#include "header.h"

int main() {
    const size_t game_field_size = 10;
    Rating result;

    result = game(game_field_size);

    return 0;
}