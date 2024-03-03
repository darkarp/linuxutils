#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/views/ls.h"

void run_ls(const char *path);

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

    if (strcmp(baseName, "_ls") == 0) {
        const char *path = argc > 1 ? argv[1] : ".";
        run_ls(path);
    } else if (strcmp(baseName, "_cat") == 0) {
        // run_cat();
    } else {
        // TODO: others
    }

    return 0;
}
