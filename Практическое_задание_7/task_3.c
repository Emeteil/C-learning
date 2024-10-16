#include <stdio.h>
#include <string.h>

void main() {
    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

    char find_char = 'a';

    const size_t len_str = strlen(str);

    char *max_a_in_word_ptr;
    int max_a_in_word_len = 0;
    int max_a = 0;

    char *ptr = str;
    int len = 0;
    int a = 0;
    for (int i = 0; i < len_str; i++) {
        if (str[i] != ' ') {
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
    strncpy(r, max_a_in_word_ptr, max_a_in_word_len);
    printf("%s %d\n", r, max_a);
}