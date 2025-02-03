#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

typedef struct {
    char stud_name[64];

    unsigned int math_score;
    unsigned int phys_score;
    unsigned int cs_score;

    unsigned int total_score;
} Student;

Student addStudent(char name[], unsigned int math, unsigned int phy, unsigned int inf);
void printStudentInfo(Student student, int only_score);
void printProcessorInfo();
void printProcessorInfoViaSystem();
int random_int(int a, int b);

void insertionSort(Student list[], size_t N, int (*func)(Student, Student));
void сountingSort(Student list[], size_t N);
void quickSort(Student list[], size_t N, int (*func)(Student, Student));

int compareElementsTotalScore(Student a, Student b);
int compareElementsPhysScore(Student a, Student b);