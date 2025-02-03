#include "header.h"

#define N 10

void main() {
    srand(time(NULL));
    Student students[N];

    for (int i = 0; i < N; i++) {
        char name[64];
        for (int j = 0; j < random_int(1, 64); j++)
            name[j] = (char)random_int(97, 122);
        
        students[i] = addStudent(
            name,
            random_int(0, 100),
            random_int(0, 100),
            random_int(0, 100)
        );
    }

    puts("До сортировки");
    for (int i = 0; i < N; i++)
    {
        printStudentInfo(students[i]);
        puts("--------------------");
    }

    puts("");
    puts("");

    insertionSort(students, N);

    puts("После сортировки");
    for (int i = 0; i < N; i++)
    {
        printStudentInfo(students[i]);
        puts("--------------------");
    }
}