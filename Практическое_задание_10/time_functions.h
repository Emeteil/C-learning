typedef struct H_M_time {
    int hours;
    int minutes;
} my_time;

my_time duration_time(my_time start, my_time end);
my_time multiply_time(my_time x_time, int multiplier);
my_time random_time(my_time time_min, my_time time_max);