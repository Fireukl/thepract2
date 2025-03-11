#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void print_processes() {
    DIR *dir = opendir("/proc");
    struct dirent *entry;

    if (!dir) {
        perror("Failed to open /proc directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            int pid = atoi(entry->d_name);
            if (pid > 0) {
                char path[256];
                snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
                FILE *fp = fopen(path, "r");
                if (fp) {
                    char comm[256];
                    fscanf(fp, "%*d %s", comm);
                    printf("PID: %d,  %s\n", pid, comm);
                    fclose(fp);
                }
            }
        }
    }

    closedir(dir);
}