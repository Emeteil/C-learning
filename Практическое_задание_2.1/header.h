#include <stdio.h>
#include <stdlib.h>
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
void printStudentInfo(Student student);
int random_int(int a, int b);

void insertionSort(Student list[], int N);