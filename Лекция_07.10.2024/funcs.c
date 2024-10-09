#include <stdio.h>

void func_meow() {
    puts("meow");
}

int no_return() {
    printf("Returned: ");
}

void woof_n_times(int n) {
    for (int i = 0; i < n; i++) {
        puts("woof");
    }
}

void change_int_value(int *ptr, int new_value) {
    *ptr = new_value;
}

int max(int a, int b); // Прототип функции, объявление функции

int max(int a, int b) { // определение функции
    if (a >= b) return a;
    return b;
}

int sum(int a, int b) { // объявление и определение функции
    return a + b;
}

int main() {
    func_meow();
    printf("%d\n", no_return());
    woof_n_times(3);
    printf("%d\n", sum(5, 7));
    
    int x = 10;
    printf("%d\n", x);
    
    change_int_value(&x, 36);
    printf("%d\n", x);
    
    return 0;
}