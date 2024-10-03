#include <stdio.h>

void main() {
    int a, k;

    printf("a k: ");
    scanf("%d %d", &a, &k);

    int r = (a << k) | (a >> ((sizeof(a) << 3) - k)); // 8 бит

    printf("%d\n", r);
}
