#include <stdio.h>
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

    return n;
}
