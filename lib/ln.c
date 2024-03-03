#include "headers/ln.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RESET_COLOR "\033[0m"
#define SUCCESS_COLOR "\033[1;32m"
#define ERROR_COLOR "\033[1;31m"

void run_ln(const char *target, const char *linkname, int symbolic) {
    int result;
    if (symbolic) {
        result = symlink(target, linkname);
    } else {
        result = link(target, linkname);
    }

    if (result == 0) {
        printf(SUCCESS_COLOR "Link created successfully: %s -> %s" RESET_COLOR
                             "\n",
               linkname, target);
    } else {
        perror(ERROR_COLOR "Error creating link" RESET_COLOR);
    }
}