#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h> // Макросы O_RDONLY, O_WRONLY и др.
#include <unistd.h> // Системные вызовы

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Invalid arguments!\n");
        fprintf(stderr, "Using: %s <filename> <arg1> <arg2> ...\n", argv[0]);
        return 1;
    }

    printf("Create %s file\n", argv[1]);
    
    // O_RDONLY  00000 (Только чтение)
    // O_WRONLY  00001 (Только запись)
    // O_CREAT   00100 (Создать файл)
    // O_TRUNC   01000 (Отчистить содержимое)

    // 00400 | 00200 (Права чтения и записи для пользователя)

    // fd - file descriptor [fd == -1 -> open error]
    // https://www.opennet.ru/man.shtml?topic=open&category=2
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200);

    if (fd == -1) {
        perror("Open file error");
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        // https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=write&category=2
        ssize_t bytes_count = write(fd, argv[i], strlen(argv[i]));

        if (bytes_count == -1) {
            perror("Write bytes error");
            close(fd);
            return 1;
        }

        if (i != (argc - 1))
            write(fd, " ", 1);
    }

    close(fd);

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open file error");
        return 1;
    }

    puts("Contents created file: ");
    const int c_buffer_size = 1024;
    char buffer[c_buffer_size];
    ssize_t bytes_read;
    while (1) {
        // https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=read&category=2
        bytes_read = read(fd, buffer, c_buffer_size - 1);
        if (bytes_read <= 0) break;

        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }
    puts("");

    if (bytes_read == -1) {
        perror("Read file error");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}