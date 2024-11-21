#include <stdlib.h>
#include <time.h>

int random_int(int a, int b) {
    srand(time(NULL));
    return a + rand() % (b - a + 1);
}