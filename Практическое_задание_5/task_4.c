#include <stdio.h>
#include <math.h>

void main() {
    int a, k;

    printf("a k: ");
    scanf("%d %d", &a, &k);

    int r = (a << k) | ((2 << (k - 1)) - 1);
    // 17
    // 00010001
    // 17 << 2 = 01000100
    // (2 << (2 - 1)) - 1 = 00000011
    // 01000100 | 00000011 = 01000111


    printf("%d\n", r);
}
