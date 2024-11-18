typedef struct
{
    unsigned int leaght;
    int win;
} Rating;

Rating game(size_t game_field_size);
void print_game_field(size_t rows, size_t cols, int matrix[rows][cols]);
void fill_matrix(size_t rows, size_t cols, int matrix[rows][cols]);
int random_int(int a, int b);
int kbhit();