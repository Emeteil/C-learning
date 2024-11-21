#include <stdio.h>
#include <math.h>

double factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double my_cos(double x, int *count, double precision, int n) {
    double member = n ? pow(-1, n) * (pow(x, 2 * n) / factorial(2 * n)) : 1;
    (*count)++;
    
    if (fabs(member) <= precision) return member;
    
    return member + my_cos(x, count, precision, n + 1);
}

void main() {
    double x = M_PI / 6;
    
    int counter = 0;
    
    double my_cos_value  = my_cos(x, &counter, 0.5e-4, 0);
    
    printf("Значение суммы ряда: %.15f\n", my_cos_value);
    printf("Число членов ряда: %d\n", counter);
    
    double math_h_cos_value = cos(x);
    
    printf("Значение cos(pi/6) из функции math.h cos(): %.15f\n", math_h_cos_value);
    printf("Разница между my_cos_value и math_h_cos_value: %.15f\n", fabs(my_cos_value - math_h_cos_value));
}