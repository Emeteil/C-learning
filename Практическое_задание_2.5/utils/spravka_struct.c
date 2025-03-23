#include <spravka_struct.h>
#include <console_utils.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static int random_int(int a, int b) {
    return a + rand() % (b - a + 1);
}

long getFileSize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0)
        return -1;

    return st.st_size;
}

spravka random_spravka() {
    spravka rnd_spravka;

    for (int i = 0; i < 50; i++)
        rnd_spravka.name_start_point_route[i] = (char)random_int('a', 'z');
    rnd_spravka.name_start_point_route[49] = '\0';

    for (int i = 0; i < 50; i++)
        rnd_spravka.name_final_point_route[i] = (char)random_int('a', 'z');
    rnd_spravka.name_final_point_route[49] = '\0';

    rnd_spravka.route_number = random_int(0, 1000);

    return rnd_spravka;
}

void print_spravka(spravka my_spravka) {
    printf(
        "Название начального пункта маршрута: %s\n",
        my_spravka.name_start_point_route
    );
    printf(
        "Название конечного пункта маршрута: %s\n",
        my_spravka.name_final_point_route
    );
    printf(
        "Номер маршрута: %d\n",
        my_spravka.route_number
    );
}

int create_random_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
        return 1;

    size_t N = size_t_window("Количество записей");

    for (int i = 0; i < N; i++) {
        spravka spravka_tmp = random_spravka();
        fwrite(&spravka_tmp, 1, sizeof(spravka), file);
    }

    fclose(file);
    return 0;
}

void print_all_file(FILE* file) {
    fseek(file, 0, SEEK_SET);

    spravka current_spravka;
    while (fread(&current_spravka, sizeof(spravka), 1, file) > 0) {
        print_spravka(current_spravka);
        puts("-------------------------------------------");
    }

    fseek(file, 0, SEEK_SET);
}

int finder(FILE* file) {
    puts("\nИскать в файле по:");
    puts("0) название начального пункта маршрута");
    puts("1) название конечного пункта маршрута");
    puts("2) номер маршрута");
    puts("3) выход");

    size_t ind;
    while (true) {
        ind = size_t_window("Выберите пункт");
        if (ind <= 3) break;
    }

    spravka current_spravka;
    char* buffer = NULL;
    int k = 0;
    switch (ind)
    {
        case 0:
            buffer = string_window("Введите подстроку");
            if (buffer == NULL)
                return 0; // break

            puts("");
            while (fread(&current_spravka, sizeof(spravka), 1, file) > 0) {
                if (strstr(current_spravka.name_start_point_route, buffer) == NULL)
                    continue;
                print_spravka(current_spravka);
                puts("-------------------------------------------");
                k++;
            }
            printf("Количество совпадений: %d\n", k);

            free(buffer);
            break;
        case 1:
            buffer = string_window("Введите подстроку");
            if (buffer == NULL)
                return 0; // break
            
            puts("");
            while (fread(&current_spravka, sizeof(spravka), 1, file) > 0) {
                if (strstr(current_spravka.name_final_point_route, buffer) == NULL)
                    continue;
                print_spravka(current_spravka);
                puts("-------------------------------------------");
                k++;
            }
            printf("Количество совпадений: %d\n", k);

            free(buffer);
            break;
        case 2:
            int route_number = int_window("Введите номер маршрута");

            puts("");
            while (fread(&current_spravka, sizeof(spravka), 1, file) > 0) {
                if (current_spravka.route_number != route_number)
                    continue;
                print_spravka(current_spravka);
                puts("-------------------------------------------");
                k++;
            }
            printf("Количество совпадений: %d\n", k);

            break;
        case 3:
            return 0; // break
    }
    
    fseek(file, 0, SEEK_SET);
    return 1; // continue
}