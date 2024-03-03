#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/headers/cat.h"
#include "../lib/headers/fsearch.h"
#include "../lib/headers/grep.h"
#include "../lib/headers/ln.h"
#include "../lib/headers/ls.h"
#include "../lib/headers/snip.h"
#include "../lib/headers/wc.h"

int main(int argc, char *argv[]) {
    char *progName = argv[0];
    char *baseName = strrchr(progName, '/');
    if (!baseName) {
        baseName = strrchr(progName, '\\'); // Windows
    }
    baseName = baseName ? baseName + 1 : progName;

    if (strcmp(baseName, "ls") == 0) {
        // const char *path = argc > 1 ? argv[1] : ".";
        run_main(argc, argv);
        // run_ls(path);
    } else if (strcmp(baseName, "snip") == 0) {
        if (argc > 1) {
            if (strcmp(argv[1], "add") == 0 && argc == 4) {
                add_snippet(argv[2], argv[3]);
            } else if (strcmp(argv[1], "list") == 0) {
                list_snippets();
            } else if (strcmp(argv[1], "search") == 0 && argc == 3) {
                search_snippets(argv[2]);
            } else {
                printf("\033[1;31mInvalid command or arguments.\033[0m\n");
            }
        } else {
            printf("\033[1;31mUsage:\033[0m\n  %s add <title> <content>\n  %s "
                   "list\n  %s search <keyword>\n",
                   argv[0], argv[0], argv[0]);
        }
    } else if (strcmp(baseName, "fsearch") == 0) {
        if (argc == 3) {
            run_fsearch(argv[1], argv[2]);
        } else {
            printf("Usage of fsearch:\n");
            printf("  fsearch [path] [pattern]\n");
            printf("Search for files in [path] containing [pattern] in their "
                   "names.\n\n");
            printf("Arguments:\n");
            printf("  path     - The directory path where the search should "
                   "begin.\n");
            printf("  pattern  - The pattern to search for in file names.\n\n");
            printf("Example:\n");
            printf("  fsearch /home/user/docs \"report\"\n");
            printf("This command searches for files containing \"report\" in "
                   "their "
                   "names, starting in /home/user/docs.\n");
        }
    } else if (strcmp(baseName, "cat") == 0) {
        run_cat(argv[1]);
    } else if (strcmp(baseName, "ln") == 0) {
        if (argc != 4) {
            printf("Usage: %s ln [-s] <target> <linkname>\n", argv[0]);
            return 1;
        }
        int symbolic = strcmp(argv[1], "-s") == 0 ? 1 : 0;
        const char *target = argv[argc - 2];
        const char *linkname = argv[argc - 1];
        run_ln(target, linkname, symbolic);
    } else if (strcmp(baseName, "grep") == 0) {
        run_grep(argv[1], argv[2]);
    } else if (strcmp(baseName, "wc") == 0 && argc == 2) {
        run_wc(argv[1]);
    } else {
        printf("Executable name or command not recognized");
    }

    return 0;
}
