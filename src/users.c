#include <stdio.h>
#include <pwd.h>

void print_users() {
    struct passwd *pw;
    while ((pw = getpwent()) != NULL) {
        if (pw->pw_uid >= 1000) {
            printf("%s\t%s\n", pw->pw_name, pw->pw_dir);
        }
    }
    endpwent();
}

