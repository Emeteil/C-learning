#include <stdio.h> // предпроцесорная дериктива -> #
// #include <string.h>

// Comment

/*
Long Comment
*/

int main() { // основная функция

    char my_char = '@';
    signed char a = 125; // знаковый
    unsigned char a2 = 125; // безнаковый

    char world_string[] = "World";

    int my_int = 123;
    float my_float = 0.1;
    double my_double = 0.2;
    long double my_long_double = 0.3;

    // long int my_long_int = 1234;
    // long long int my_long_int = 1234;

    printf("Hello, %s!\n", world_string);

    return 0;
}
