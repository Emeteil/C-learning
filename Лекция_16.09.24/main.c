#include <stdio.h>

#define N 2 // синтаксическая замена, не переменная

int cats_cnt; // 0

int test() {
    return 10+9;
}

void main() {
    int cats_counters; // не 0

    int hex = 0x7B;

    int oct = 0173;

    int dec = 179;

    int bin = 0b1101010;

    printf("%x == %d == %o == %d", hex, dec, oct, bin);

    cats_counters = 10;

    printf("%d\n", cats_counters);

    printf("%d\n", cats_cnt);
    printf("%d\n", test());
    printf("Hello, World!\n");

    printf("%d %f\n", 5+10, 5.0f/3.1f);

    int x = 5;
    double y = 12.3;

    y = (double)x;
    x = (int)y;

    double z = (double)x / 2;
}
