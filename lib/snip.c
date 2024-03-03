#include "../headers/snip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SNIPPETS_DB "snippets.db"

void add_snippet(const char *title, const char *content) {
    FILE *file = fopen(SNIPPETS_DB, "a");
    if (!file) {
        perror("Error opening snippet database");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "{\"title\": \"%s\", \"content\": \"%s\"}\n", title, content);

    fclose(file);
    printf("\033[0;32mSnippet '%s' added successfully.\033[0m\n", title);
}

void list_snippets() {
    char line[1024];
    FILE *file = fopen(SNIPPETS_DB, "r");
    if (!file) {
        perror("Error reading snippet database");
        exit(EXIT_FAILURE);
    }

    printf("\033[1;34mAvailable Snippets:\033[0m\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void search_snippets(const char *keyword) {
    char line[1024];
    FILE *file = fopen(SNIPPETS_DB, "r");
    if (!file) {
        perror("Error reading snippet database");
        exit(EXIT_FAILURE);
    }

    printf("\033[1;34mSearch Results for '%s':\033[0m\n", keyword);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, keyword)) {
            printf("%s", line);
        }
    }

    fclose(file);
}
