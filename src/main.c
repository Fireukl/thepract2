#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "file_utils.h"

#define MAX_OPTIONS 15

int main(int argc, char *argv[]) {
    char *log_path = NULL;
    char *error_path = NULL;
    int opt;
    int flagu, flagp = 0;
    int error_occurred = 0;
    char options[MAX_OPTIONS];
    int option_count = 0;

    if (argc == 1) {
        print_help();
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
                if (option_count < MAX_OPTIONS) {
                    options[option_count++] = 'u';
                }
                break;
            case 'p':
                if (option_count < MAX_OPTIONS) {
                    options[option_count++] = 'p';
                }
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

    if (log_path != NULL) {
        FILE *log_file = freopen(log_path, "a", stdout);
        if (log_file == NULL) {
            log_error("Ошибка открытия файла лога.", error_path);
            error_occurred = 1;
        }
    }

    if (error_path != NULL) {
        FILE *error_file = freopen(error_path, "a", stderr);
        if (error_file == NULL) {
            log_error("Ошибка открытия файла ошибок.", error_path);
            error_occurred = 1;
        }
    }

    
    if (error_occurred) {
        return 1;
    }
    
    for (int i = 0; i < option_count; i++) {
        switch (options[i]) {
            case 'u':
                if (!flagu){
                    print_users();
                    flagu = 1;
                }
                break;
            case 'p':
                if (!flagp){
                    print_processes();
                    flagp = 1;
                }
                break;
            default:
                break;
        }
    }

    return 0;
}
