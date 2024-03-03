#define _POSIX_C_SOURCE 200809L

#include "unity/unity.h"
// https://github.com/ThrowTheSwitch/Unity

#include "../../c-dictionary/dict/headers/dict.h"
#include "../lib/utils/sort.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20

char **input_files;
char **output_files;

void print_char_arr(char **arr, int size) {

    for (int i = 0; i < size; i++) {
        char *element = arr[i];
        if (!element)
            break;
        printf("%s\n", element);
    }
    printf("\n");
}

void setUp() {
    DIR *dir;
    dir = opendir("test/iotests");
    // FILE* fp;
    input_files = calloc(MAX_SIZE, sizeof(char *));
    output_files = calloc(MAX_SIZE, sizeof(char *));
    struct dirent *p_dir;
    if (dir) {
        int i = 0;
        int j = 0;
        int k = 0;
        while ((p_dir = readdir(dir)) && i <= MAX_SIZE) {
            char *filename = p_dir->d_name;
            // char* input_flag = "in";
            int i_len = 2;
            int o_len = 3;
            int i_start = strlen(filename) - i_len;
            int o_start = strlen(filename) - o_len;

            if (!strcmp(&filename[i_start], "in")) {
                input_files[j] = p_dir->d_name;
                j++;
            } else if (!strcmp(&filename[o_start], "out")) {
                output_files[k] = p_dir->d_name;
                k++;
            }
            i++;
        }
        printf("Size: %d\n", j);
        closedir(dir);
    }
}

void tearDown() {}

void test_stuff() {
    printf("Input filename: %s\n", input_files[0]);
    FILE *infile;
    FILE *outfile;
    char *in_line = NULL;
    for (int i = 0; i < 3; i++) {
        infile = fopen(input_files[i], "r");
        outfile = fopen(output_files[i], "r");
        // char* off_line = NULL;
        size_t line_buf_size = 0;
        // size_t line_size;
        if (!infile)
            break;
        getline(&in_line, &line_buf_size, infile);
        printf("Line: %s\n", in_line);
    }
    /* Close the file now that we are done with it */
    fclose(infile);
    fclose(outfile);
    // print_char_arr(input_files, 1);
    TEST_ASSERT_EQUAL_STRING("a", "a");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_stuff);
    return UNITY_END();
}

// gcc -g test_dict.c unity/unity.c quicksort_generic.c ../src/utils/dict.c
// ../src/utils/prime.c -lm