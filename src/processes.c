#include <stdlib.h>
#include "processes.h"

void print_processes() {
    system("ps -e -o pid,cmd,start --sort=pid");
}

