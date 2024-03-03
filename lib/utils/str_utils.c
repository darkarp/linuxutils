#include <string.h>

#include "ctype.h"
#include "str_utils.h"

char *strip(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

void replace_char(char *str, char char_to_replace, char replacement) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == char_to_replace) {
            str[i] = replacement;
        }
    }
}
