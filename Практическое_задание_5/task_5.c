#include <stdio.h>

void main() {
    int a, k;

    printf("a k: ");
    scanf("%d %d", &a, &k);

    int r = (a << k) | (a >> ((sizeof(a) << 3) - k));
    // sizeof(var_int) => 4
    // 4 => 0b100
    // 0b100 << 3 => 0b100000 => 32 бита
    // int - 4 байта - 32 бита

    printf("%d\n", r);
}
