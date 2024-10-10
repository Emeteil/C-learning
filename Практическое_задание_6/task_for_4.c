#include <stdio.h>

void main() {
    const int length_A = 16;
    int A[length_A] = {
        9, -8, 7, 6, -5, 4, 3, -2, 1, -2, 3, 4, 5, -6, 7, 8
    };
    int B[length_A] = {
        1, 2, -3, 4, -5, 6, 7, -8, 9, 8, 7, 6, 5, -4, -3, 2
    };

    int C[length_A];
    for (int i = 0; i < length_A; i++)
        C[i] = A[i] + B[i];
    
    printf("Массив С:");
    for (int i = 0; i < length_A; i++)
        printf(" %d", C[i]);
    puts("");

    int max_real_A = 0;
    for (int i = 0; i < length_A; i+=2)
        if (A[i] > max_real_A)
            max_real_A = A[i];

    printf("Максимальная реальная часть комплексных чисел массива A: %d\n", max_real_A);

    int count_imag_B = 0;
    for (int i = 1; i < length_A; i+=2)
        if (B[i] < 0)
            count_imag_B++;

    printf("Количество мнимых частей, которые меньше 0 в массиве B: %d\n", count_imag_B);

    int sum_C = 0;
    float avg_C = 0;
    for (int i = 0; i < length_A; i++)
        sum_C += C[i];
    avg_C = sum_C / length_A;

    printf("Cреднее арифметическое среди всех элементов массива C: %f\n", avg_C);
}