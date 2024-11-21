#include <stdio.h>

void main(){
    char c;
    float a;
    float b;

    printf("Действие: ");
    scanf("%c", &c);

    printf("a = ");
    scanf("%f", &a);

    printf("b = ");
    scanf("%f", &b);

    if (c == '+')
        printf("Ответ: %f\n", a+b);
    else if (c == '-')
        printf("Ответ: %f\n", a-b);
    else if (c == '/')
        printf("Ответ: %f\n", a/b);
    else if (c == '*')
        printf("Ответ: %f\n", a*b);
    else
        printf("Так нельзя!\n");
}
