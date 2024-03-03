#include "headers/grep.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCH_COLOR "\033[1;32m"
#define RESET_COLOR "\033[0m"

void run_grep(const char *pattern, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    regex_t regex;
    int reti;
    char msgbuf[100];
    reti = regcomp(&regex, pattern, 0);
    if (reti) {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) {
            printf(MATCH_COLOR "%s" RESET_COLOR, line);
        } else if (reti != REG_NOMATCH) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex execution failed: %s\n", msgbuf);
            break;
        }
    }

    fclose(file);
    if (line) {
        free(line);
    }

    regfree(&regex);
}
