#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <console_utils.h>
#include <spravka_struct.h>

int main() {
    srand(time(NULL));
    const char* filename = "Spravka.dat";
    int s_c = create_random_file(filename);
    if (s_c != 0) {
        perror("Failed to open file");
        return 1;
    }

    FILE* r_file = fopen(filename, "rb");
    if (r_file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // long file_size = get_file_size(filename);
    // spravka spravks[file_size / sizeof(spravka)];
    // fread(&spravks, file_size, 1, r_file);

    print_all_file(r_file);
    fseek(r_file, 0, SEEK_SET);

    while (finder(r_file));

    fclose(r_file);
    return 0;
}