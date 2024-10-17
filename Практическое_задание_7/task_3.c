#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int random_int(int a, int b) {
	return (rand() % (b - a + 1)) + a;
}

void rand_str(char str[], size_t size) {
    for (int i = 0; i < size; i++) {
        if (
                random_int(0, 6) == 0
                &&
                str[i-1] != ' '
                &&
                i != size - 1 && i != 0
            ) {
            str[i] = ' ';
            continue;
        }
        str[i] = random_int(97, 122);
    }
    str[size] = '\0';
}

void main() {
    // char str[] = "Loraem ipsum dolaor ayyaaa sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id esat laborum.";
    
    srand(time(NULL));
    size_t len_s = random_int(100, 1000);
    char str[len_s];
    rand_str(str, len_s);
    printf("Строка: %s\n", str);

    const char find_char = 'a';

    const size_t len_str = strlen(str) + 1; // 452 + 1
    // const size_t len_str = sizeof(str) / sizeof(str[0]); // 453

    char *max_a_in_word_ptr;
    int max_a_in_word_len = 0;
    int max_a = 0;

    char *ptr = str;
    int len = 0;
    int a = 0;
    for (int i = 0; i < len_str; i++) {
        if (str[i] != ' ' && str[i] != '\0') {
            len++;
            if (str[i] == find_char) a++;
        }
        else
        {
            if (a > max_a) {
                max_a = a;
                max_a_in_word_ptr = ptr;
                max_a_in_word_len = len;
            }
            ptr = str + i + 1;
            len = a = 0;
        }
    }

    char r[max_a_in_word_len];

    // for (int i = 0; i < max_a_in_word_len; i++)
    //     r[i] = *(max_a_in_word_ptr + i);
    strncpy(r, max_a_in_word_ptr, max_a_in_word_len);
    r[max_a_in_word_len] = '\0';

    printf(
        "Максимальное количество букв %c в слове: %s\n",
        find_char,
        r
    );
    printf(
        "Слово состоит из %d букв, %d из которых %c\n",
        max_a_in_word_len,
        max_a,
        find_char
    );
}