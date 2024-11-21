#include <stdio.h>

void main() {
    int max_int = 2147483647; // от −2 147 483 648 до 2 147 483 647 (при 4 байтах) и выше
    unsigned int unsigned_int_max = 4294967295; // от 0 до 4 294 967 295 (для 4 байт)
    char min_char = -128;


    printf("Max_int: %d\n", max_int);
    printf("Max_int+1(Переполнение): %d\n", max_int + 1);
    // При переполнении переменной её значение "обёртывается" вокруг диапазона типа данных.
    // Вывод: -2147483648

    printf("\n");

    printf("Max_unsigned_int: %u\n", unsigned_int_max);
    printf("Max_unsigned_int+1(Переполнение): %u\n", unsigned_int_max + 1);
    // Вывод: 0

    printf("\n");

    printf("Min_char: %c\n", min_char);
    printf("Min_char-1: %c\n", min_char - 1);
}
