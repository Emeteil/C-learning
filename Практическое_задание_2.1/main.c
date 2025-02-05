#include "header.h"

#define N 5
#define SORT_FUNC quickSort

// insertionSort (USE_COMPARE_FUNC 1)
// сountingSort (USE_COMPARE_FUNC 0)
// quickSort (USE_COMPARE_FUNC 1)
// bogoSort (USE_COMPARE_FUNC 1)

#define USE_COMPARE_FUNC 1
#define COMPARE_FUNC compareElementsTotalScore

#define PRINT_PROCESSOR_INFO 1
#define PRINT_INPUT 0
#define PRINT_ONLY_SCORE 1
#define PRINT_RESULT 1

// insertionSort N=100 - 0.000076 секунд
// insertionSort N=10000 - 0.565924 секунд
// insertionSort N=100000 - 61.487288 секунд

// сountingSort N=100 - 0.000080 секунд
// сountingSort N=10000 - Segmentation fault [max 346]
// сountingSort N=100000 - Segmentation fault

// quickSort N=100 - 0.000021 секунд
// quickSort N=10000 - 0.009189 секунд
// quickSort N=100000 - 0.566445 секунд

// bogoSort N=100 - много секунд
// bogoSort N=10000 - очень много секунд
// bogoSort N=100000 - нереально много секунд

int compareElementsTotalScore(Student a, Student b) {
    return (a.total_score < b.total_score);
}

int compareElementsPhysScore(Student a, Student b) {
    return (a.phys_score < b.phys_score);
}

void main() {
    srand(time(NULL));
    Student students[N];

    if (PRINT_PROCESSOR_INFO) {
        puts("Processor:");
        printProcessorInfo();
        // printProcessorInfoViaSystem();
        puts("");
    }

    for (int i = 0; i < N; i++) {
        size_t name_len = random_int(3, 10);
        char name[name_len];
        for (int j = 0; j < name_len; j++)
            name[j] = (char)random_int('a', 'z');
        
        name[name_len] = '\0';
        
        students[i] = addStudent(
            name,
            random_int(0, 100),
            random_int(0, 100),
            random_int(0, 100)
        );
    }

    if (PRINT_INPUT) {
        puts("До сортировки:");
        for (int i = 0; i < N; i++)
        {
            puts("--------------------");
            printStudentInfo(students[i], PRINT_ONLY_SCORE);
        }
    }


    if (PRINT_INPUT) for (int i = 0; i < 2; i++) puts("");
    puts("Сортировка...");
    struct timeval start, end;

    gettimeofday(&start, NULL);

    #if USE_COMPARE_FUNC
        SORT_FUNC(students, N, COMPARE_FUNC);
    #else
        SORT_FUNC(students, N);
    #endif

    gettimeofday(&end, NULL);

    double seconds = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Время выполнения: %lf секунд\n", seconds);
    if (PRINT_RESULT) for (int i = 0; i < 2; i++) puts("");


    if (PRINT_RESULT) {
        puts("После сортировки:");
        for (int i = 0; i < N; i++)
        {
            puts("--------------------");
            printStudentInfo(students[i], PRINT_ONLY_SCORE);
        }
    }
}