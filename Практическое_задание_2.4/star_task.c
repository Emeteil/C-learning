#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
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