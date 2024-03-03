#ifndef LS_H
#define LS_H

#include <sys/types.h>

void run_ls(const char *path);
void print_permissions(mode_t mode);
void print_size(long size);
void run_ls(const char *path);
void display_help();
int run_main(int argc, char *argv[]);

#endif
