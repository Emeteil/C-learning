#include <stdio.h>

void main() {
    char ch = 63;
    unsigned char uch = 'r';
    short j = 'b', k = 99;

    printf("%c == %d\n", ch, ch); // Переменную типа char в первом случаи мы выводим как симвл, а во втором как целочисленное число
    printf("%c == %d\n", uch, uch); // Аналогично, но изначально мы задали переменную в виде символа. Ему соответствует число 114
    printf("%c, %d\n", j, k);
}
