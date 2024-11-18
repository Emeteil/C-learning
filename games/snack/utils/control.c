#include "../header.h"
#include <stdio.h>

void read_action(char *action) {
    char key = '\0';
    
    while (kbhit())
        key = getchar();

    switch (key) {
        case 'w':
            if (*action != 'd')
                *action = 'u';
            break;
        case 's':
            if (*action != 'u')
                *action = 'd';
            break;
        case 'a':
            if (*action != 'r')
                *action = 'l';
            break;
        case 'd':
            if (*action != 'l')
                *action = 'r';
            break;
    }
}