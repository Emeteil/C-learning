#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool is_prime(int x) {
    if (x == 0 || x == 1) return false;
    for (int n = 2; n < x; n++)
        if (x % n == 0) return false;
    return true;
}

int max_prime(int M[], int length) {
    int max = 0;
    for (int i = 0; i < length; i++)
        if (is_prime(M[i]) && M[i] > max)
            max = M[i];
    return max;
}

float avg_prime(int M[], int length) {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < length; i++)
        if (is_prime(M[i])) {
            sum += M[i];
            count++;
        }
    return (float)sum / count;
}

int count_odd(int M[], int length) {
    int count = 0;
    for (int i = 0; i < length; i++)
        if (M[i] % 2 != 0)
            count++;
    return count;
}

void print_array(int M[], int length) {
    for (int i = 0; i < length; i++)
        printf("%d ", M[i]);
    puts("");
}

void random_array_filling(int *M, int length, int max_rand) {
    for (int i = 0; i < length; i++){
        *(M + i) = rand() % max_rand;
    }
}

void main() {
    srand(time(NULL));
    const int length_X = 20;
    int X[length_X];
    random_array_filling(X, length_X, 50);

    int new_X_length = length_X + count_odd(X, length_X);
    int new_X[new_X_length];
    int max_prime_X = max_prime(X, length_X);
    for (int i, j = 0; i < length_X; i++) {
        new_X[i + j] = X[i];
        if (X[i] % 2 != 0) {
            j++;
            new_X[i + j] = max_prime_X;
        }
    }

    printf("Массив до вставки: ");
    print_array(X, length_X);

    printf(
        "Cреднее  арифметическое простых элементов массива до вставки: %f\n",
        avg_prime(X, length_X)
    );

    printf("Массив после вставки: ");
    print_array(new_X, new_X_length);

    printf(
        "Cреднее  арифметическое простых элементов массива после вставки: %f\n",
        avg_prime(new_X, new_X_length)
    );
}