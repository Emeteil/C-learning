# This is where my notes on language will be..
at the same time I'll improve my English.

## Data Types in C:
![image](https://github.com/user-attachments/assets/df788732-ad17-46e0-a9c1-d9bb8257bd4c)

## ASCII table:
![image](https://github.com/user-attachments/assets/fcdc2a46-3e96-4b19-b996-7dee4441099c)

## Compilation steps
![image](https://github.com/user-attachments/assets/1bf9399c-f362-4ed8-b5a4-1f95de0eec4c)
*When using libraries - add `-lm` key*

## Constants
![image](https://github.com/user-attachments/assets/a95d439b-3ce6-4b1b-a455-86f99d2b6a55)

## Number systems
![image](https://github.com/user-attachments/assets/3eafbe7c-98c2-4c9b-ab28-1e469e70bd88)

## Arithmetic Operators
![image](https://github.com/user-attachments/assets/e1758a81-0609-461f-b5d5-4d4b81c2f261)

## Ternary Operator
![image](https://github.com/user-attachments/assets/595762f6-dbba-4b10-82ad-a861e6fe6404)

## Type casting
![image](https://github.com/user-attachments/assets/0c35045e-51ce-4270-a355-34ffbd5282ab)

## Logical Operators
![image](https://github.com/user-attachments/assets/c7999f10-7fbd-47f2-99a8-bcf2001ba4f9)

## while loop
![image](https://github.com/user-attachments/assets/aba572a7-c80b-4ce1-b695-771ef6eed3e6)

## do .. while loop
![image](https://github.com/user-attachments/assets/d58e2ba0-d74b-4846-a36f-ea3a17946c53)

## for loop
![image](https://github.com/user-attachments/assets/13b01ea6-f217-485e-9dc7-f555fcaf0f50)

## break, continue example
![image](https://github.com/user-attachments/assets/75fb8bd3-dfa0-497b-baf6-777d208229f5)

## for loop variations
![image](https://github.com/user-attachments/assets/3e8045cf-452a-4f56-be9a-40e3123e3c90)

## Bitwise operations
```c
// Побитовое И (AND) - `&`
int a = 5;  // 0101 в двоичной системе
int b = 3;  // 0011 в двоичной системе
int c = a & b;  // Результат: 0001 (1 в десятичной системе)

// Побитовое ИЛИ (OR) - `|`
int a = 5;  // 0101 в двоичной системе
int b = 3;  // 0011 в двоичной системе
int c = a | b;  // Результат: 0111 (7 в десятичной системе)

// Побитовое ИСКЛЮЧАЮЩЕЕ ИЛИ (XOR) - `^`
int a = 5;  // 0101 в двоичной системе
int b = 3;  // 0011 в двоичной системе
int c = a ^ b;  // Результат: 0110 (6 в десятичной системе)

// Побитовое НЕ (NOT) - `~`
int a = 5;  // 0101 в двоичной системе
int b = ~a;  // Результат: 1010 (в зависимости от размера типа данных)

// Сдвиг влево (Left Shift) - `<<`
int a = 5;  // 0101 в двоичной системе
int b = a << 1;  // Результат: 1010 (10 в десятичной системе)

// Сдвиг вправо (Right Shift) - `>>`
int a = 5;  // 0101 в двоичной системе
int b = a >> 1;  // Результат: 0010 (2 в десятичной системе)
```

## Magic with bitwise operations
```c
// Умножение на 2 в степени n
x = 5;
result = x << 1;  // result = 10 (5 * 2^1)

// Деление на 2 в степени n
x = 10;
result = x >> 1;  // result = 5 (10 / 2^1)

// Проверка на четность
x = 7;
int is_even = (x & 1) == 0;  // is_even = 0 (false), так как 7 нечетное

// Обмен значениями двух переменных без использования временной переменной
int a = 5;
int b = 10;

a = a ^ b;
b = a ^ b;
a = a ^ b;

// Проверка, является ли число степенью двойки
x = 8;
int is_power_of_two = (x & (x - 1)) == 0;  // is_power_of_two = 1 (true), так как 8 = 2^3
```

## Arrays, Addressing, Matrices
![image (1)](https://github.com/user-attachments/assets/3ae32e45-1fb0-430d-a7e7-5d2cdb9e2b94)

## string.h
```c
#include <stdio.h>

// Копирует до 5 символов из src в dest
char dest[10];
char src[] = "Hello, World!";
strncpy(dest, src, 5);  // dest содержит "Hello"

// Присоединяет до 3 символов из src к dest
char dest[20] = "Hello, ";
char src[] = "World!";
strncat(dest, src, 3);  // dest содержит "Hello, Wor"

// Сравнивает первые 3 символа str1 и str2
char str1[] = "apple";
char str2[] = "apricot";
int result = strncmp(str1, str2, 3);  // result = 0

// Ищет последнее вхождение 'o' в строке
char str[] = "Hello, World!";
char* ptr = strrchr(str, 'o');  // ptr указывает на последнюю 'o'

// Возвращает длину начального сегмента из цифр
char str1[] = "123abc";
char str2[] = "1234567890";
size_t length = strspn(str1, str2);  // length = 3

// Возвращает длину начального сегмента без цифр
char str1[] = "abc123";
char str2[] = "1234567890";
size_t length = strcspn(str1, str2);  // length = 3

// Ищет первое вхождение 'o' или 'e' в строке
char str[] = "Hello, World!";
char accept[] = "oe";
char* ptr = strpbrk(str, accept);  // ptr указывает на первую 'o'

// Разбивает строку на слова по пробелам
char str[] = "This is a test";
char* token = strtok(str, " ");  // token указывает на "This"
while (token != NULL) {
    token = strtok(NULL, " ");  // Получение следующего токена
}

// Возвращает длину строки
char str[] = "Hello, World!";
size_t length = strlen(str);  // length = 13
```

## Pointer in C
```c
// Объявление указателя и присваивание ему адреса переменной
int x = 10;
int* ptr = &x;  // Стиль 1: * рядом с типом данных
int *ptr2 = &x; // Стиль 2: * рядом с именем переменной

// Разыменование указателя для доступа к значению
int y = *ptr;  // y теперь равно 10

// Изменение значения через указатель
*ptr = 20;  // x теперь равно 20

// Указатель на указатель
int** ptr_to_ptr = &ptr;  // ptr_to_ptr указывает на ptr

// Разыменование двойного указателя
int z = **ptr_to_ptr;  // z теперь равно 20

// Указатель на массив
int arr[5] = {1, 2, 3, 4, 5};
int* arr_ptr = arr;  // arr_ptr указывает на первый элемент массива

// Доступ к элементам массива через указатель
int first_element = *arr_ptr;  // first_element равно 1
int second_element = *(arr_ptr + 1);  // second_element равно 2

// Перебор элементов массива с помощью указателя
for (int i = 0; i < 5; i++) {
    printf("%d ", *(arr_ptr + i));  // Вывод: 1 2 3 4 5
}

// Указатель на статический массив
int static_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int (*static_arr_ptr)[3] = static_arr;  // static_arr_ptr указывает на первую строку массива

// Доступ к элементам статического массива через указатель
int element = *(*(static_arr_ptr + 1) + 2);  // element равно 6

// Перебор элементов статического массива с помощью указателя
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        printf("%d ", *(*(static_arr_ptr + i) + j));  // Вывод: 1 2 3 4 5 6 7 8 9
    }
}

void increment(int* ptr) {
    (*ptr)++;  // Увеличиваем значение, на которое указывает ptr
}
int a = 5;
increment(&x);
printf("x после инкремента: %d\n", x);  // Вывод: x после инкремента: 6
```

## Memory work. Memory clearing
```c
#include <stdlib.h>
#include <string.h>

// Выделение памяти для одного элемента
int* ptr = (int*)malloc(sizeof(int));

// Выделение памяти для массива
int* arr = (int*)malloc(10 * sizeof(int));

// Выделение памяти и инициализация нулями
// Первый аргумент (1) указывает количество элементов, второй аргумент (sizeof(int)) — размер каждого элемента
int* ptr_zero = (int*)calloc(1, sizeof(int));

// Изменение размера выделенной памяти
int* new_ptr = (int*)realloc(ptr, 20 * sizeof(int));

// Копирование 4 байт из src в dest
char dest[10];
char src[] = "Hello";
memcpy(dest, src, 4);  // dest содержит "Hell"

// Заполнение 5 байт памяти значением 'A'
char str[10];
memset(str, 'A', 5);  // str содержит "AAAAA"

// Копирование 4 байт из src в dest, даже если области перекрываются
char str_overlap[] = "abcdef";
memmove(str_overlap + 1, str_overlap, 4);  // str_overlap содержит "aabcdf"

// Сравнивает первые 3 байта str1 и str2
char str1[] = "abc";
char str2[] = "abd";
int result = memcmp(str1, str2, 3);  // result < 0

// Освобождение выделенной памяти
free(ptr);
ptr = NULL;

free(arr);
arr = NULL;

free(ptr_zero);
ptr_zero = NULL;

free(new_ptr);
new_ptr = NULL;
```

## Functions in C
```c
// Пример функции, которая возвращает факториал числа
int factorial(int N) {
    if (N < 1) return 1; 
    return N * factorial(N - 1);
}

// Пример нерекурсивной функции для вычисления факториала
int factorial_non_recursive(int N) {
    int res = 1;
    for (int i = N; i > 1; i--) {
        res = res * i;
    }
    return res;
}

// Пример вызова функций
int n = factorial(5);  // n будет равно 120
int m = factorial_non_recursive(5);  // m также будет равно 120

// Пример функции с указателями
void swap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int a = 5, b = 10;
swap(&a, &b);  // Теперь a = 10, b = 5

// Пример функции с передачей результата через указатель
void add(int a, int b, int *res) {
    *res = a + b;
}

int result;
add(5, 3, &result);  // result будет равен 8

// Пример функции с возвратом значения
int sum(int a, int b) {
    return a + b;
}

int total = sum(5, 3);  // total будет равен 8

// !!! НЕПРАВИЛЬНЫЙ ПРИМЕР !!!
// Пример функции с висячим указателем
char *f() {
    char s = 'A';
    return &s;  // Возвращает адрес локальной переменной, которая будет уничтожена после выхода из функции
}

// !!! НЕПРАВИЛЬНЫЙ ПРИМЕР !!!
// Использование висячего указателя
char *a = f();  // a будет указывать на невалидный адрес
// Использование a может привести к неопределенному поведению

// Пример использования указателя на функцию
int (*cipher_func)(int, char *);

int cipher1(int key, char *text) {
    // Реализация шифрования
}

cipher_func = cipher1;
cipher_func(420, "sample text");  // Вызов функции через указатель

// Пример массива указателей на функции
float (*dfts_fun[])(float, int) = { dft128, dft256, dft512, dft1024 };
float b = dfts_fun[2](5.5, 4);  // Вызов функции dft512

// Пример функции обратного вызова (callback)
void filter(int size_in, const int in[], int size_out, int out[], int (*condition_func)(int)) {
    for (int i = 0; i < size_in; i++) {
        if (condition_func(in[i])) {
            out[i] = in[i];
        }
    }
}

int is_even(int num) {
    return num % 2 == 0;
}

int A[] = {1, 2, 3, 4, 5};
int B[5];
filter(5, A, 5, B, is_even);  // Фильтрация четных чисел

// Пример вариативной функции (variadic function)
#include <stdarg.h>

int my_log_print(char *format, ...) {
    va_list args;
    va_start(args, format);
    // Использование args для доступа к аргументам
    va_end(args);
    return 0;
}

// Пример использования вариативной функции
my_log_print("Error at LINE=%d, FILE=%s, function=%s", __LINE__, __FILE__, __FUNCTION__);
```

## Preprocessor in C
```c
// Директива #include
#include <stdio.h>  // Подключение стандартной библиотеки ввода-вывода
#include "my_header.h"  // Подключение пользовательского заголовочного файла

// Директива #define для определения констант и макросов
#define PI 3.14159  // Определение константы
#define MIN(a, b) ((a) < (b) ? (a) : (b))  // Определение макроса

// Пример использования макроса
int x = 5, y = 10;
int min_value = MIN(x, y);  // min_value будет равен 5

// Условная компиляция
#define DEBUG 1

#if DEBUG == 1
    printf("Debug mode is on\n");
#else
    printf("Debug mode is off\n");
#endif

// Проверка на наличие/отсутствие макроса
#ifdef DEBUG
    printf("Debug is defined\n");
#endif

#ifndef DEBUG
    printf("Debug is not defined\n");
#endif

// Защита от повторного включения заголовочных файлов
#ifndef _MY_HEADER_H_
#define _MY_HEADER_H_
// Содержимое заголовочного файла
#endif // _MY_HEADER_H_

// Предопределенные константы препроцессора
printf("Line: %d, File: %s, Function: %s\n", __LINE__, __FILE__, __FUNCTION__);
printf("Compilation date: %s, time: %s\n", __DATE__, __TIME__);
```

## Structures, Unions, and Enums in C
```c
// Пример структуры (struct)
struct complex {
    int re;  // Реальная часть
    int im;  // Мнимая часть
};

struct complex my_complex;
my_complex.re = -5;
my_complex.im = 6;

// Пример массива структур
struct animal {
    char *name;
    int age;
};

struct animal dogs[3];
dogs[0].name = "Muhtar";
dogs[0].age = 5;

struct animal cats[] = {{"Tom", 5}, {"Felix", 4}, {"Mango", 3}};

// Пример указателя на структуру
struct test {
    char a;
    int b;
};

struct test a;
struct test *ptr = &a;
ptr->a = 'A';  // Использование оператора ->
(*ptr).b = 555;  // Альтернативный способ доступа через разыменование

// Пример битовых полей в структуре
struct byte {
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
};

char a = 0b00010001;  // 17
struct byte *bits = (struct byte *)&a;
bits->b0 = 0;  // Изменение первого бита числа a

// Битовые поля позволяют экономить память, упаковывая несколько переменных в один байт.
// Например, структура byte использует 8 битовых полей, каждое из которых занимает 1 бит.
// Это позволяет хранить 8 логических значений (0 или 1) в одном байте.

// Пример объединения (union)
union test_union {
    char a;
    int b;
};

union test_union test;
test.a = 'A';
test.b = 12345;  // Теперь test.a будет содержать младший байт числа 12345

// Объединения позволяют хранить разные типы данных в одной и той же области памяти.
// В примере выше, test.a и test.b разделяют одну и ту же область памяти.
// Когда мы присваиваем значение test.b, test.a будет содержать младший байт этого значения.

// Пример перечисления (enum)
enum colors {
    RED,    // 0
    GREEN,  // 1
    BLUE = 5,  // 5
    ORANGE  // 6
};

enum colors my_color = GREEN;
switch (my_color) {
    case RED:
        printf("Color is red\n");
        break;
    case GREEN:
        printf("Color is green\n");
        break;
    default:
        printf("Unknown color\n");
}

// Перечисления позволяют создавать именованные константы, что делает код более читаемым и понятным.
// В примере выше, RED, GREEN, BLUE и ORANGE являются константами, которые можно использовать вместо чисел.

// Пример использования typedef
typedef unsigned int uint;
uint a;  // Теперь uint эквивалентно unsigned int

typedef struct {
    int age;
    char name[64];
} cat_t;

cat_t my_cat = {3, "Mango"};

// typedef позволяет создавать псевдонимы для типов данных, что упрощает их использование.
// В примере выше, cat_t является псевдонимом для структуры, содержащей возраст и имя кота.

// Использование typedef с анонимными членами структуры
typedef struct {
    struct {
        int x;
        int y;
    };
    int radius;
} CircleTypedef;

CircleTypedef circle = {{200, 210}, 10}; // circle=(center=(200, 210), radius=10)
```

## Makefile
```makefile
# Цель по умолчанию, которая будет выполнена, если вы запустите `make` без аргументов.
# Она зависит от цели `main`.
all: main

# Цель для сборки исполняемого файла `main`.
# Зависит от объектных файлов `main_task_4_for_5.o`, `math_for_time.o`, и `rand_time_generate.o`.
main: main_task_4_for_5.o math_for_time.o rand_time_generate.o
	# Компилируем объектные файлы в исполняемый файл `Build/a.out`.
	# После сборки удаляем все объектные файлы (`.o`).
	gcc main_task_4_for_5.o math_for_time.o rand_time_generate.o -o Build/a.out ; rm -rf *.o

# Цель для сборки объектного файла `main_task_4_for_5.o`.
# Зависит от исходного файла `main_task_4_for_5.c` и заголовочного файла `time_functions.h`.
main_task_4_for_5.o: main_task_4_for_5.c time_functions.h
	# Компилируем `main_task_4_for_5.c` в объектный файл `main_task_4_for_5.o`.
	gcc -c main_task_4_for_5.c

# Цель для сборки объектного файла `rand_time_generate.o`.
# Зависит от исходного файла `functions/rand_time_generate.c` и заголовочного файла `time_functions.h`.
rand_time_generate.o: functions/rand_time_generate.c time_functions.h
	# Компилируем `functions/rand_time_generate.c` в объектный файл `rand_time_generate.o`.
	gcc -c functions/rand_time_generate.c

# Цель для сборки объектного файла `math_for_time.o`.
# Зависит от исходного файла `functions/math_for_time.c` и заголовочного файла `time_functions.h`.
math_for_time.o: functions/math_for_time.c time_functions.h
	# Компилируем `functions/math_for_time.c` в объектный файл `math_for_time.o`.
	gcc -c functions/math_for_time.c
```

## CMakeLists.txt
```cmake
# Устанавливаем минимальную требуемую версию CMake.
# В данном случае это версия 3.10.
cmake_minimum_required(VERSION 3.10)

# Создаем проект с именем "Практическое_задание_10".
project(Практическое_задание_10)

# Устанавливаем переменную SOURCE_EXE, которая содержит имя основного исходного файла.
set(SOURCE_EXE main_task_4_for_5.c)

# Используем команду file(GLOB ...) для поиска всех исходных файлов в директории "functions".
# Результат сохраняем в переменной SOURCE_LIB.
file(GLOB SOURCE_LIB "functions/*.c")

# Создаем статическую библиотеку с именем MY_LIB, используя найденные исходные файлы.
add_library(MY_LIB ${SOURCE_LIB})

# Создаем исполняемый файл с именем a.out, используя основной исходный файл.
add_executable(a.out ${SOURCE_EXE})

# Линкуем исполняемый файл a.out с библиотекой MY_LIB.
target_link_libraries(a.out MY_LIB)

# ------------------------------------------
# !!! Примеры со сторонними библиотеками !!!

# Найти библиотеку SDL2
find_package(SDL2 REQUIRED)

# Связать библиотеку MY_LIB с исполняемым файлом
target_link_libraries(a.out MY_LIB)

# Связать библиотеку SDL2 с исполняемым файлом
target_link_libraries(a.out SDL2::SDL2)

# Для других зависимостей
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(a.out SDL2::SDL2 SDL2::SDL2_image SDL2::SDL2_ttf SDL2::SDL2_mixer)
```
### Подробнее про Make и CMake:
 - [Habr.com](https://habr.com/ru/articles/155201)
 - [C-Programming/13_make_cmake](https://github.com/kruffka/C-Programming/tree/master/2023-2024/13_make_cmake)

## Files for works:
- 🖼️[0_introduction](https://eios.sibsutis.ru/mod/resource/view.php?id=161078)
- 🖼️[1_hello_world](https://eios.sibsutis.ru/mod/resource/view.php?id=161567)
- 📄[Практическое задание 1. Типы данных и вывод](https://eios.sibsutis.ru/mod/resource/view.php?id=161572)
- 🖼️[2_types_and_conds](https://eios.sibsutis.ru/mod/resource/view.php?id=162002)
- 🖼️[2.5_conditions](https://eios.sibsutis.ru/mod/resource/view.php?id=162377)
- 📄[Практическое задание 2. Условия](https://eios.sibsutis.ru/mod/resource/view.php?id=162144)
- 🖼️[3_loops](https://eios.sibsutis.ru/mod/resource/view.php?id=162400)
- 🖼️[3.5_functions_part1](https://eios.sibsutis.ru/mod/resource/view.php?id=162722)
- 📄[Практическое задание 3. Циклы](https://eios.sibsutis.ru/mod/resource/view.php?id=162401)
- 📄[Практическое задание 4. Вложенные циклы](https://eios.sibsutis.ru/mod/resource/view.php?id=162402)
- 🖼️[4_bitwise_op](https://eios.sibsutis.ru/mod/resource/view.php?id=162854)
- 📄[Практическое задание 5. Битовые операции](https://eios.sibsutis.ru/mod/resource/view.php?id=162845)
- 🖼️[5_static_arrays](https://eios.sibsutis.ru/mod/resource/view.php?id=163911)
- 📄[Практическое задание 6. Одномерные массивы](https://eios.sibsutis.ru/mod/resource/view.php?id=163160)
- 📄[Практическое задание 7. Строки](https://eios.sibsutis.ru/mod/resource/view.php?id=163912)
- 🖼️[5.1 pointers](https://eios.sibsutis.ru/mod/resource/view.php?id=165242)
- 📄[Практическое задание 8. Матрицы](https://eios.sibsutis.ru/mod/resource/view.php?id=165329)
- 🖼️[5.2_dynamic_arrays](https://eios.sibsutis.ru/mod/resource/view.php?id=165917)
- 📄[Доп. задание под *: Улитка](https://eios.sibsutis.ru/mod/resource/view.php?id=166167)
- 🖼️[6_functions_p2](https://eios.sibsutis.ru/mod/resource/view.php?id=165946)
- 🖼️[6.1_preprocessor](https://eios.sibsutis.ru/mod/resource/view.php?id=166863)
- 📄[Практическое задание 9. Функции](https://eios.sibsutis.ru/mod/resource/view.php?id=165933)
- 📄[Доп. задание под *: Рекурсия](https://eios.sibsutis.ru/mod/resource/view.php?id=166502)
- 🖼️[7_struct_union](https://eios.sibsutis.ru/mod/resource/view.php?id=166867)
- 📄[Практическое задание 10. Структуры данных.](https://eios.sibsutis.ru/mod/resource/view.php?id=166506)

## 📚 List of Literature

### 🌐 **C Programming Language**

#### Basics of C from the creators of the language
- **Book:** *"The C Programming Language"* (1988)  
  Authors: Brian W. Kernighan, Dennis M. Ritchie  
  [Download PDF](https://github.com/auspbro/ebook-c/blob/master/The.C.Programming.Language.2Nd.Ed%20Prentice.Hall.Brian.W.Kernighan.and.Dennis.M.Ritchie..pdf)

#### Online Courses
- **CS50 or CS50x** - Harvard course on YouTube  
  [Watch on YouTube](https://www.youtube.com/watch?v=cwtpLIWylAw&list=PLhQjrBD2T381WAHyx1pq-sBfykqMBI7V4&index=2)

### 💻 **PC Hardware, Processor (Architecture), Memory**

#### Articles and Resources
- **How a CPU works:**  
  [Read on Tproger](https://tproger.ru/explain/how-cpu-works)

- **Processors and Architecture:**  
  [Read on Habr](https://habr.com/ru/companies/selectel/articles/542074/)

- **CPU and Linux:**  
  [Read on CPU.land](https://cpu.land/the-basics)

#### Video Courses
- **Series of videos with animations about PC hardware:**  
  [Watch on YouTube](https://www.youtube.com/watch?v=wtdnatmVdIg&list=PL6rx9p3tbsMsZ9hUvU-kDOXc8Fot04Hhu&ab_channel=BranchEducation)

### 🛠️ **Git Basics**

#### Articles and Resources
- **Git Basics:**  
  [Read on Habr](https://habr.com/ru/articles/541258/)

- **Getting started with Git:**  
  [Read on Javarush](https://javarush.com/groups/posts/2683-nachalo-rabotih-s-git-podrobnihy-gayd-dlja-novichkov)

#### Interactive Lessons
- **Learn Git Branching:**  
  [Try it](https://learngitbranching.js.org/?locale=ru_RU)

### 🐧 **Installing Linux on a Laptop (WSL)**

#### Installation Guide
- **Installing WSL:**  
  [Read on Microsoft Learn](https://learn.microsoft.com/ru-ru/windows/wsl/install)

### 🔍 **GDB Debugger**

#### Articles and Resources
- **Debugging in the console:**  
  [Read on Habr](https://habr.com/ru/articles/535960/)

#### Code Examples
- **Examples on GitHub:**  
  [View on GitHub](https://github.com/kruffka/C-Programming)

### 🛠️ **GCC Compilation Stages**

#### Code Examples
- **Examples on GitHub:**  
  [View on GitHub](https://github.com/kruffka/C-Programming/tree/master/0_hello_world)

### 🧩 **Leisure Time Tasks**

#### Practice Platforms
- **LeetCode:**  
  [Go to LeetCode](https://leetcode.com/)

- **Codeforces:**  
  [Go to Codeforces](https://codeforces.com/)

---
<br>*Если у вас есть идеи по улучшению этого README.md, не стесняйтесь отправлять `Pull requests`!*
