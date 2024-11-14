#include <stdio.h>
#include "time_functions.h"

void main() {
    my_time start_work = random_time((my_time){1, 0}, (my_time){3, 0});
    my_time end_work = random_time((my_time){4, 0}, (my_time){7, 0});

    printf(
        "Время запуска прибора %02d:%02d\n",
        start_work.hours,
        start_work.minutes
    );
    printf(
        "Время остановки прибора %02d:%02d\n",
        end_work.hours,
        end_work.minutes
    );

    my_time time_work = duration_time(start_work, end_work);
    my_time time_work_per_week = multiply_time(time_work, 7);

    printf(
        "Время работы прибора в день %02d:%02d\n",
        time_work.hours,
        time_work.minutes
    );

    printf(
        "Время работы прибора за неделю: %d часов и %d минут\n",
        time_work_per_week.hours,
        time_work_per_week.minutes
    );
}