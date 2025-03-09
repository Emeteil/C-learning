#include <stdio.h>

void _swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertionSort(int list[], size_t N) {
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (list[j] > list[j - 1]) break;

            _swap(&list[j], &list[j - 1]);
        }
    }
}

void main() {
    int a[] = {4, 2, 0, 10};

    insertionSort(a, 4);

    for (int i = 0; i < 4; i++)
        printf("%d ", a[i]);
    puts("");
}