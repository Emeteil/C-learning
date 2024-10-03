#include <stdio.h>
#include <math.h>

void main() {
    int a, k;

    printf("a k: ");
    scanf("%d %d", &a, &k);

    int r = (a << k) | ((2 << (k - 1)) - 1);

    printf("%d\n", r);
}
