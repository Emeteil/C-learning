#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../time_functions.h"

my_time random_time(
        my_time time_min,
        my_time time_max
    ) {
    srand(time(NULL));
    my_time result_time;

    int minutes_min = time_min.hours * 60 + time_min.minutes;
    int minutes_max = time_max.hours * 60 + time_max.minutes;

    int result_minutes = minutes_min + rand() % (minutes_max - minutes_min + 1);
    result_time.hours = result_minutes / 60;
    result_time.minutes = result_minutes % 60;

    return result_time;
}