#include <stdio.h>

void main() {
    int n;

    printf("n: ");
    scanf("%d", &n);

    int s = 1;
    for (int i = 1; i <= n; i++)
        s = s * i;
    // данный алгоритм считайет факториал числа
    // [1; n]

    printf("%d\n", s);
}
