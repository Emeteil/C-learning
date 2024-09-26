#include <stdio.h>

#define star "*"
#define dash "-"

int main() {
    int x = 5, y = 5;

    printf("x, y: ");
    scanf("%d, %d", &x, &y);

    if (x < 3 || y < 3) {
        puts("Недопустимые значения");
        return 1;
    }

    for (int i = 0; i < x; i++)
        printf(star);

    printf("\n");

    for (int j = 0; j < (y-2); j++) {
        printf(star);
        for (int i = 0; i < (x-2); i++)
            printf(dash);
        printf(star);

        printf("\n");
    }

    for (int i = 0; i < x; i++)
        printf(star);

    printf("\n");

    return 0;
}
