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

void run_fsearch(const char *path, const char *pattern) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, pattern) != NULL) {
            printf(MATCH_COLOR "%s/%s" RESET_COLOR "\n", path, entry->d_name);
        }

        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0) {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            run_fsearch(new_path, pattern);
        }
    }

    closedir(dir);
}
