#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LINES 40
#define MAX_LEN 150

int random_int(int a, int b) {
    return a + rand() % (b - a + 1);
}

void rand_str(char *str, int N) {
    for (int i = 0; i < N - 1; i++)
        str[i] = (char)random_int('a', 'z');
    str[N] = '\0';
}

void reverse_str(char *str, long len) {
    for (int i = 0; i < len / 2; i++) {
        char t = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = t;
    }
}

void generate_rand_file(const char *__restrict__ __filename) {
    FILE *file = fopen(__filename, "w");

    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    size_t count_lines = (size_t)random_int(1, MAX_LINES);
    
    for (int i = 0; i < count_lines; i++) {
        size_t len = (size_t)random_int(1, MAX_LEN - 1);
        char str[MAX_LEN];
        rand_str(str, len);
        fprintf(file, "%s\n", str);
    }

    fclose(file);
}

bool is_file(const char *__restrict__ __filename) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "[ -f %s ]", __filename);
    return (bool)(system(cmd) == 0);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc < 2) {
        fprintf(stderr, "Invalid arguments!\n");
        return 1;
    }
    
    if (!is_file(argv[1])) {
        printf("File %s does not exist!\n", argv[1]);
        generate_rand_file(argv[1]);
        printf("%s file created!\n", argv[1]);
    }

    FILE *file = fopen(argv[1], "r+");

    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    long max_line_len = 0;
    long max_line_point = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        if (read > max_line_len) {
            max_line_len = read;
            max_line_point = ftell(file) - read;
        }
    }

    if (max_line_len == 0) {
        fprintf(stderr, "Lenght max string = 0");
        return 1;
    }

    fseek(file, max_line_point, SEEK_SET);
    char *max_line = malloc(max_line_len + 1);
    if (max_line == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    fgets(max_line, max_line_len + 1, file);

    printf("String: %s", max_line);
    reverse_str(max_line, max_line_len - 1);
    printf("Reversed string: %s", max_line);

    fseek(file, max_line_point, SEEK_SET);
    fputs(max_line, file);

    free(max_line);
    fclose(file);

    return 0;
}