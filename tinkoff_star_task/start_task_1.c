#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int list_enlargement(int **matrix, int index, int *capacity) {
    if (index >= *capacity) {
        (*capacity)++;
        *matrix = (int*)realloc(*matrix, *capacity * sizeof(int));
        if (*matrix == NULL) return -1;
    }
    return 0;
}

int *converter(size_t str_len, char str[str_len], int* len) {
    int capacity = 1;

    int* matrix = (int*)malloc(capacity * sizeof(int*));
    if (matrix == NULL) return NULL;

    int index = 0;

    char* token = strtok(str, ",");
    while (token != NULL) {
        char* separator = strchr(token, '-');
        if (separator == NULL) {
            list_enlargement(&matrix, index, &capacity);
            matrix[index] = atoi(token);
            index++;
            token = strtok(NULL, ",");
            continue;
        }
        int token_len = strlen(token);
        int ind_sep = separator - token;

        char start_char[ind_sep + 1];
        for (int i = 0; i < ind_sep; i++)
            start_char[i] = token[i];
        start_char[ind_sep] = '\0';
        int end_len = token_len - ind_sep - 1;
        char end_char[end_len + 1];
        for (int i = 0; i < end_len; i++)
            end_char[i] = token[ind_sep + 1 + i];
        end_char[end_len] = '\0';

        int start = atoi(start_char);
        int end = atoi(end_char);
        for (int i = start; i <= end; i++) {
            list_enlargement(&matrix, index, &capacity);
            matrix[index] = i;
            index++;
        }

        token = strtok(NULL, ",");
    }

    *len = capacity;
    return matrix;
}

void main(int argc, char *argv[]) {
    char input_str[] = "1-6,8-9,11";
    if (argc >= 2)
        strncpy(input_str, argv[1], strlen(input_str));

    int len = 0;
    int* ints = converter(strlen(input_str), input_str, &len);

    for (int i = 0; i < len; i++)
        printf("%d ", ints[i]);
    puts("");

    free(ints);
    ints = NULL;
}