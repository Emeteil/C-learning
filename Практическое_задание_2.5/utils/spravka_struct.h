#include <stdio.h>

typedef struct {
    char name_start_point_route[50];
    char name_final_point_route[50];
    int route_number;
} spravka;

spravka random_spravka();
long get_file_size(const char *filename);
void print_spravka(spravka my_spravka);
int create_random_file(const char* filename);
void print_all_file(FILE* file);
int finder(FILE* file);