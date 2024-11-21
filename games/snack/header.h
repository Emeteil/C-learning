#include <stddef.h>

typedef struct
{
    unsigned int leaght;
    int win;
} Rating;

Rating game(size_t game_field_size, unsigned int delay);

void print_game_field(size_t rows, size_t cols, int matrix[rows][cols]);
void fill_matrix(size_t rows, size_t cols, int matrix[rows][cols]);

void find_head(
    size_t game_field_size,
    int matrix[game_field_size][game_field_size],
    int length,
    int *x,
    int *y
);
void find_element_instead_of_head(
    char action,
    int i,
    int j,
    int game_field_size,
    int *next_i,
    int *next_j
);
void lengthen_snake(
    size_t game_field_size,
    int matrix[game_field_size][game_field_size],
    int *length,
    int next_i,
    int next_j
);
void add_apple(const size_t game_field_size, int matrix[game_field_size][game_field_size]);
void step_game(size_t game_field_size, int matrix[game_field_size][game_field_size]);

void read_action(char *action);

int random_int(int a, int b);
int kbhit();