#include "args_processing.h"
#include <getopt.h>

void print_help() {
    printf("Использование: translate [ОПЦИИ] ВХОДНОЙ_ФАЙЛ СЛОВАРЬ ВЫХОДНОЙ_ФАЙЛ\n");
    printf("Опции:\n");
    printf("  -y              Автоматически подтверждать все запросы\n");
    printf("  -n              Не подтверждать запросы автоматически\n");
    printf("  --no-internet   Отключить поиск в интернете\n");
    printf("  -e EXT          Указать расширение файлов для обработки (по умолчанию: txt)\n");
    printf("  -t THREADS      Указать количество потоков (по умолчанию: 1)\n");
    printf("  -h, --help      Показать эту справку\n");
}

ProgramOptions parse_arguments(int argc, char *argv[]) {
    ProgramOptions options = {
        .input_path = NULL,
        .dict_path = NULL,
        .output_path = NULL,
        .overwrite = false,
        .no_overwrite = false,
        .auto_approve = false,
        .no_internet = false,
        .file_extension = "txt",
        .thread_count = 1
    };

    static struct option long_options[] = {
        {"no-internet", no_argument, 0, 0},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "yne:t:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'y':
                options.auto_approve = true;
                break;
            case 'n':
                options.no_overwrite = true;
                break;
            case 'e':
                options.file_extension = optarg;
                break;
            case 't':
                options.thread_count = atoi(optarg);
                if (options.thread_count < 1) {
                    printf("Ошибка: Количество потоков должно быть положительным числом\n");
                    exit(1);
                }
                break;
            case 'h':
                print_help();
                exit(0);
            case 0:
                options.no_internet = true;
                break;
            default:
                print_help();
                exit(1);
        }
    }

    if (optind + 2 >= argc) {
        printf("Ошибка: Недостаточно аргументов\n");
        print_help();
        exit(1);
    }

    options.input_path = argv[optind];
    options.dict_path = argv[optind + 1];
    options.output_path = argv[optind + 2];

    if (options.auto_approve && options.no_overwrite) {
        printf("Ошибка: Нельзя использовать одновременно -y и -n\n");
        exit(1);
    }

    return options;
}