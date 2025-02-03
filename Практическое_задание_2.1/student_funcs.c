#include "header.h"

Student addStudent(char name[], unsigned int math, unsigned int phy, unsigned int inf) {
    Student new_student;

    strcpy(new_student.stud_name, name);
    new_student.math_score = math;
    new_student.phys_score = phy;
    new_student.cs_score = inf;
    new_student.total_score = math + phy + inf;

    return new_student;
}

void printStudentInfo(Student student) {
    printf("Студент %s\n", student.stud_name);
    printf("Балл по математике %u\n", student.math_score);
    printf("Балл по физике %u\n", student.phys_score);
    printf("Балл по информатике %u\n", student.cs_score);
    printf("Всего баллов %u\n", student.total_score);
}

int random_int(int a, int b) {
    return a + rand() % (b - a + 1);
}