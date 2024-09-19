#include <stdio.h>
#include <stdbool.h>

void main() {
    int year;
    bool lean_year;

    printf("Введите год: ");
    scanf("%d", &year);

    if (year % 400 == 0)
        lean_year = true;
    else if ((year % 400) % 100 == 0)
        lean_year = false;
    else if (((year % 400) % 100) % 4 == 0)
        lean_year = true;
    else
        lean_year = false;

    if (lean_year)
        printf("YES\n");
    else
        printf("NO\n");
}
