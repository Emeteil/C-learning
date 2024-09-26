#include <stdio.h>

void main() {
    int a;

    printf("a: ");
    scanf("%d", &a);

    int n = 2, flag = 0;
    while (a%n != 0) {
        n++;
        if (n == a) {
            flag = 1;
            break;
        }
    }
    // здесь для проверки числа на простоту используется цикл while
    // перебор [2; a)
    // если цикл дошёл до конца, то он останавливается при помощи break

    puts(flag ? "1" : "0");
}
