#include <stdio.h>

void main() {
    int five_three_time = 555;
    int words_count = 59;
    int letters_count = 1004;
    int digits_count = 8;

    float a = 0.1;
    float b = 0.2;

    printf("|%d|\n", five_three_time);
    printf("|%10d|\n", five_three_time);
    printf("|%-10d|\n", five_three_time);

    printf("\n");

    printf("Words: %11d\n", words_count);
    printf("Letters: %9d\n", letters_count);
    printf("Digits: %10d\n", digits_count);

    printf("\n");

    printf("a = %f; b = %f\n", a, b);
    printf("a + b = %0.10f\n", a + b);
}
