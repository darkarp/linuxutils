#include "../headers/wc.h"
#include <stdio.h>
#include <stdlib.h>

void run_wc(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int chars = 0, words = 0, lines = 0;
    int in_word = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        chars++;
        if (c == '\n') {
            lines++;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    printf("Lines: %d\nWords: %d\nCharacters: %d\n", lines, words, chars);

    fclose(file);
}
