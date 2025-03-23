#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

bool bool_window(const char* format, ...) {
    char string[256];
    va_list args;
    va_start(args, format);
    vsnprintf(string, sizeof(string), format, args);
    va_end(args);

    char input;
    while (true) {
        printf("%s (Y/N): ", string);
        scanf(" %c", &input);
        input = toupper(input);
        
        while (getchar() != '\n');

        if (input == 'Y' || input == 'N') break;
    }
    return (bool)(input == 'Y');
}

size_t size_t_window(const char* format, ...) {
    char string[256];
    va_list args;
    va_start(args, format);
    vsnprintf(string, sizeof(string), format, args);
    va_end(args);

    size_t n = 1;
    printf("%s: ", string);
    scanf("%zu", &n);

    while (getchar() != '\n');

    return n;
}

int int_window(const char* format, ...) {
    char string[256];
    va_list args;
    va_start(args, format);
    vsnprintf(string, sizeof(string), format, args);
    va_end(args);
    
    int n = 0;
    printf("%s: ", string);
    scanf("%d", &n);

    while (getchar() != '\n');

    return n;
}

char* string_window(const char* format, ...) {
    char string[256];
    va_list args;
    va_start(args, format);
    vsnprintf(string, sizeof(string), format, args);
    va_end(args);
    
    printf("%s: ", string);
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;

    if (strchr(buffer, '\n') == NULL)
        while (getchar() != '\n');

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL)
        return NULL;
    
    strcpy(result, buffer);

    return result;
}