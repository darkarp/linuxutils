#include "../../headers/views/ls.h"
#include <dirent.h>
#include <stdio.h>

void run_ls(void) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("opendir");
    }
}
