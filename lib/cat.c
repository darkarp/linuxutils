#include "../headers/cat.h"
#include <stdio.h>
#include <stdlib.h>

void run_cat(const char *filepath) {
    FILE *file;
    int c;

    file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}
