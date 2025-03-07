#include <stdio.h>
#include "file_utils.h"

int check_path(const char *path) {
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    fclose(file);
    return 0;
}

void log_error(const char *message, const char *error_path) {
    if (error_path != NULL) {
        FILE *error_file = fopen(error_path, "a");
        if (error_file != NULL) {
            fprintf(error_file, "%s\n", message);
            fclose(error_file);
        } else {
            perror("Ошибка открытия файла ошибок");
        }
    } else {
        fprintf(stderr, "%s\n", message); // Если путь к файлу ошибок не задан, выводим в stderr
    }
}
