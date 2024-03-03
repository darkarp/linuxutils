#include "headers/ls.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
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

// Global options
bool show_all = false;
bool human_readable = false;

void display_help() {
    printf("Usage: _ls [OPTION]... [DIRECTORY]\n");
    printf("List information about the DIRECTORY's contents (current directory "
           "by default).\n\n");
    printf("Options:\n");
    printf("  -a, --all              do not ignore entries starting with .\n");
    printf("  -H, --human-readable   print sizes in human-readable format "
           "(e.g., 1K 234M 2G)\n");
    printf("\n");
}

int run_main(int argc, char *argv[]) {
    const char *path = ".";
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            display_help();
            return 0;
        } else if (strcmp(argv[i], "-a") == 0 ||
                   strcmp(argv[i], "--all") == 0) {
            show_all = true;
        } else if (strcmp(argv[i], "-H") == 0 ||
                   strcmp(argv[i], "--human-readable") == 0) {
            human_readable = true;
        } else {
            path = argv[i];
        }
    }

    run_ls(path);
    return 0;
}

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

void print_size(long size) {
    if (human_readable) {
        const char *units[] = {"B", "K", "M", "G", "T", "P", "E"};
        int unit = 0;
        double sized = size;
        while (sized >= 1024 && unit < 6) {
            sized /= 1024;
            unit++;
        }
        printf("%.*f%s", unit ? 1 : 0, sized, units[unit]);
    } else {
        printf("%ld", size);
    }
}

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
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }

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

        print_size(file_stat.st_size);

        time_info = localtime(&file_stat.st_mtime);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
        printf(" %s ", time_str);

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
