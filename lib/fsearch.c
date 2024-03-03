#define _GNU_SOURCE
#include "headers/fsearch.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define RESET_COLOR "\033[0m"
#define MATCH_COLOR "\033[1;32m"
#define PATH_MAX 4096

void run_fsearch(const char *path, const char *pattern) {
    if (!pattern) {
        fprintf(stderr, "Error: Search pattern is null.\n");
        return;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char *full_path;
        if (asprintf(&full_path, "%s/%s", path, entry->d_name) == -1) {
            fprintf(stderr, "Error allocating memory for full path\n");
            continue;
        }
        if (strstr(entry->d_name, pattern) != NULL) {
            printf(MATCH_COLOR "%s" RESET_COLOR "\n", full_path);
        }
        if (entry->d_type == DT_DIR) {
            run_fsearch(full_path, pattern);
        }

        free(full_path);
    }

    closedir(dir);
}