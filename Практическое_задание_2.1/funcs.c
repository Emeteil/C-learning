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

void printStudentInfo(Student student, int only_score) {
    if (only_score) {
        printf("%-*s : %u\n", 10, student.stud_name, student.total_score);
        return;
    }

    printf("Студент %s\n", student.stud_name);
    printf("Балл по математике %u\n", student.math_score);
    printf("Балл по физике %u\n", student.phys_score);
    printf("Балл по информатике %u\n", student.cs_score);
    printf("Всего баллов %u\n", student.total_score);
}

void printProcessorInfo() {
    FILE *file = fopen("/proc/cpuinfo", "r");

    char model_name[100];
    int mn_status = 0;

    float cpu_mhz = 0;
    int cm_status = 0;

    char line[256];
    while (fgets(line, sizeof(line), file) && (!mn_status || !cm_status)) {
        if (sscanf(line, "model name : %[^\n]", model_name) == 1) 
            mn_status = 1;

        if (sscanf(line, "cpu MHz : %f", &cpu_mhz) == 1)
            cm_status = 1;
    }

    printf("Model Name: %s\n", model_name);
    printf("CPU MHz: %f\n", cpu_mhz);
}

void printProcessorInfoViaSystem() {
    system("grep -E 'model name|cpu MHz' /proc/cpuinfo | head -2");
}

int random_int(int a, int b) {
    return a + rand() % (b - a + 1);
}