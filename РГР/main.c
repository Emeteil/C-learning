#include "translate.h"

int main(int argc, char *argv[]) {
    ProgramOptions options = parse_arguments(argc, argv);
    
    if (options.input_path == NULL || options.dict_path == NULL || options.output_path == NULL) {
        print_help();
        return 1;
    }

    HashTable *dictionary = create_hash_table(100);
    FILE *dict_file = fopen(options.dict_path, "r");
    if (dict_file == NULL) {
        printf("Ошибка: Не удалось открыть файл словаря\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), dict_file)) {
        char *key = strtok(line, " -");
        char *value = strtok(NULL, " -\n");
        if (key && value) {
            hash_table_insert(dictionary, key, value);
        }
    }
    fclose(dict_file);

    struct stat path_stat;
    stat(options.input_path, &path_stat);

    if (S_ISDIR(path_stat.st_mode)) {
        process_directory(options.input_path, options.output_path, dictionary, &options);
    } else {
        process_file_translation(options.input_path, options.output_path, dictionary, &options);
    }

    free_hash_table(dictionary);
    return 0;
}