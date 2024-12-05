#include <stdio.h>

typedef struct {
    char name[100];
    unsigned int id_train;
    unsigned int hours;
    unsigned int minutes;
    unsigned int global_minutes;
} Flight;

int main() {
    FILE *file = fopen("Train.dat", "r");

    if (file == NULL) return 1;

    size_t n = 8;
    Flight flight_list[n];

    for (int i = 0; i < n; i++) {
        fscanf(
            file,
            "%99[^;];%u;%u:%u\n",
            flight_list[i].name,
            &flight_list[i].id_train,
            &flight_list[i].hours,
            &flight_list[i].minutes
        );
        flight_list[i].global_minutes = flight_list[i].hours * 60 + flight_list[i].minutes;
    }

    fclose(file);

    unsigned int hours = 0;
    unsigned int minutes = 0;
    printf("Введите время: ");
    scanf("%u:%u", &hours, &minutes);

    int count = 0;
    for (int i = 0; i < n; i++)
        if (flight_list[i].global_minutes > (hours * 60 + minutes)) {
            printf(
                "%s;%u;%u:%u\n",
                flight_list[i].name,
                flight_list[i].id_train,
                flight_list[i].hours,
                flight_list[i].minutes
            );
            count++;
        }

    if (!count) puts("Рейсов позже этого времени нет!");

    return 0;
}
