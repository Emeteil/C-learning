#include "../time_functions.h"

my_time duration_time(my_time start, my_time end) {
    my_time result_time;

    int start_minutes = start.hours * 60 + start.minutes;
    int end_minutes = end.hours * 60 + end.minutes;

    if (end_minutes < start_minutes)
        return (my_time){0, 0};

    int result_minutes = end_minutes - start_minutes;
    result_time.hours = result_minutes / 60;
    result_time.minutes = result_minutes % 60;

    return result_time;
}

my_time multiply_time(my_time x_time, int multiplier) {
    my_time result_time;

    int minutes = x_time.hours * 60 + x_time.minutes;

    int result_minutes = minutes * multiplier;
    result_time.hours = result_minutes / 60;
    result_time.minutes = result_minutes % 60;

    return result_time;
}