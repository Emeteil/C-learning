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
