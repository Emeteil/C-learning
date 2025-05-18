#include "file_processing.h"
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>

void *translate_file_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    process_file_translation(data->input_file, data->output_file, data->dictionary, data->options);
    free(data->input_file);
    free(data->output_file);
    free(data);
    return NULL;
}

void process_file_translation(const char *input_file, const char *output_file, HashTable *dictionary, ProgramOptions *options) {
    struct stat st;
    if (stat(output_file, &st) == 0) {
        if (options->no_overwrite) {
            printf("Файл %s уже существует, пропускаем (опция -n)\n", output_file);
            return;
        }
        if (!options->auto_approve) {
            printf("Файл %s уже существует. Перезаписать? (y/n): ", output_file);
            char response;
            scanf(" %c", &response);
            if (response != 'y' && response != 'Y') {
                return;
            }
        }
    }

    FILE *in = fopen(input_file, "r");
    if (!in) {
        printf("Ошибка: Не удалось открыть входной файл %s\n", input_file);
        return;
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        printf("Ошибка: Не удалось создать выходной файл %s\n", output_file);
        fclose(in);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, in) != -1) {
        char *translated = translate_text(line, dictionary, options, options->dict_path);
        fprintf(out, "%s", translated);
        free(translated);
    }

    free(line);
    fclose(in);
    fclose(out);
}

void process_directory(const char *input_dir, const char *output_dir, HashTable *dictionary, ProgramOptions *options) {
    DIR *dir = opendir(input_dir);
    if (!dir) {
        printf("Ошибка: Не удалось открыть директорию %s\n", input_dir);
        return;
    }

    struct stat st = {0};
    if (stat(output_dir, &st) == -1) {
        mkdir(output_dir, 0700);
    }

    pthread_t *threads = malloc(options->thread_count * sizeof(pthread_t));
    ThreadData **thread_data = malloc(options->thread_count * sizeof(ThreadData*));
    int current_thread = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) { // проходимся по файлам директории
        if (entry->d_type != DT_REG) continue;

        char *ext = strrchr(entry->d_name, '.');
        if (!ext || strcmp(ext + 1, options->file_extension) != 0) continue;

        char input_path[PATH_MAX]; // PATH_MAX = 4096
        char output_path[PATH_MAX];
        snprintf(input_path, PATH_MAX, "%s/%s", input_dir, entry->d_name);
        snprintf(output_path, PATH_MAX, "%s/%s", output_dir, entry->d_name);

        ThreadData *data = malloc(sizeof(ThreadData));
        data->input_file = strdup(input_path);
        data->output_file = strdup(output_path);
        data->dictionary = dictionary;
        data->options = options;

        thread_data[current_thread] = data;

        if (pthread_create(&threads[current_thread], NULL, translate_file_thread, data) != 0) {
            printf("Ошибка: Не удалось создать поток для файла %s\n", input_path);
            free(data->input_file);
            free(data->output_file);
            free(data);
            continue;
        }

        current_thread++;
        if (current_thread >= options->thread_count) { // ждёмс если >=
            for (int i = 0; i < current_thread; i++) {
                pthread_join(threads[i], NULL);
            }
            current_thread = 0;
        }
    }

    for (int i = 0; i < current_thread; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(thread_data);
    closedir(dir);
}