#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/headers/ls.h"
#include "../lib/headers/snip.h"

int main(int argc, char *argv[]) {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif
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
        } else if (strcmp(argv[1], "fsearch") == 0 && argc == 4) {
            run_fsearch(argv[2], argv[3]);
        } else if (strcmp(argv[1], "cat") == 0 && argc == 3) {
            run_cat(argv[2]);
        } else if (strcmp(argv[1], "ln") == 0) {
            if (argc != 5) {
                printf("Usage: %s ln [-s] <target> <linkname>\n", argv[0]);
                return 1;
            }
            int symbolic = strcmp(argv[2], "-s") == 0 ? 1 : 0;
            const char *target = argv[argc - 2];
            const char *linkname = argv[argc - 1];
            run_ln(target, linkname, symbolic);
        } else if (strcmp(argv[1], "grep") == 0 && argc >= 4) {
            run_grep(argv[2], argv[3]);
        } else if (strcmp(argv[1], "wc") == 0 && argc == 3) {
            run_wc(argv[2]);
        } else {
            printf("\033[1;31mUsage:\033[0m\n  %s add <title> <content>\n  %s "
                   "list\n  %s search <keyword>\n",
                   argv[0], argv[0], argv[0]);
        }
    } else {
        // TODO: others
    }

    return 0;
}
