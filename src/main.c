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
        const char *path = argc > 1 ? argv[1] : ".";
        run_ls(path);
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
    } else {
        // TODO: others
    }

    return 0;
}
