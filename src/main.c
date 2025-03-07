#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "file_utils.h"

int main(int argc, char *argv[]) {
    char *log_path = NULL;
    char *error_path = NULL;
    int opt;
    int flags = 0;
    int error_occurred = 0;

    if (argc == 1) {
        log_error("Ошибка: Не указаны никакие опции.", error_path);
        return 1;
    }

    static struct option long_options[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "uphl:e:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'u':
                flags |= 1;
                break;
            case 'p':
                flags |= 2;
                break;
            case 'h':
                print_help();
                return 0;
            case 'l':
                log_path = optarg;
                break;
            case 'e':
                error_path = optarg;
                break;
            default:
                error_occurred = 1;
                break;
        }

        if (error_occurred && error_path != NULL) {
            log_error("Неизвестная опция.", error_path);
        } else if (error_occurred) {
            fprintf(stderr, "Неизвестная опция.\n");
        }
    }

    if (flags == 0 && !error_occurred) {
        log_error("Ошибка: Не указаны никакие опции.", error_path);
        return 1;
    }

    if (log_path != NULL && freopen(log_path, "a", stdout) == NULL) {
        log_error("Ошибка открытия файла лога.", error_path);
        error_occurred = 1;
    }

    if (error_path != NULL && freopen(error_path, "a", stderr) == NULL) {
        log_error("Ошибка открытия файла ошибок.", error_path);
        error_occurred = 1;
    }

    if (error_occurred) {
        return 1;
    }

    if (error_path != NULL) {
        log_error("Ошибок не было.", error_path);
    }

    if (flags & 1) {
        print_users();
    }

    if (flags & 2) {
        print_processes();
    }

    return 0;
}