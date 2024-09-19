#include <stdio.h>
#include <math.h>

void main() {
    float x, y;

    float r_big = 2;
    float r_small = 1;

    printf("Введите x, y: ");
    scanf("%f, %f", &x, &y);

    float calc = pow(x, 2) + pow(y, 2);

    if (
           (calc <= pow(r_big, 2))
           &&
           (calc >= pow(r_small, 2))
           &&
           x >= 0
       )
        printf("YES\n");
    else
        printf("NO\n");
}
