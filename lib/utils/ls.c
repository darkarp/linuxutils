#include "ls.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define RESET_COLOR "\033[0m"
#define DIR_COLOR "\033[1;34m"
#define FILE_COLOR "\033[0;32m"
#define EXEC_COLOR "\033[0;31m"

void print_permissions(mode_t mode) {
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

// Main ls function
void run_ls(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char time_str[20];
    struct tm *time_info;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) < 0) {
            perror("stat");
            continue;
        }

        print_permissions(file_stat.st_mode);

        printf(" %ld", file_stat.st_nlink);

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);

        printf(" %s %s", pw ? pw->pw_name : "", gr ? gr->gr_name : "");

        printf(" %5ld", file_stat.st_size);

        time_info = localtime(&file_stat.st_mtime);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
        printf(" %s ", time_str);

        // Apply color coding based on file type
        if (S_ISDIR(file_stat.st_mode)) {
            printf(DIR_COLOR "%s" RESET_COLOR, entry->d_name);
        } else if (file_stat.st_mode & S_IXUSR) {
            printf(EXEC_COLOR "%s" RESET_COLOR, entry->d_name);
        } else {
            printf(FILE_COLOR "%s" RESET_COLOR, entry->d_name);
        }

        printf("\n");
    }

    closedir(dir);
}
