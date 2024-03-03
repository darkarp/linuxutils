#define _POSIX_C_SOURCE 200809L

#include "unity/unity.h"
// https://github.com/ThrowTheSwitch/Unity

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

void setUp() {}

void tearDown() {}

void test_stuff() { TEST_ASSERT_EQUAL_STRING("a", "a"); }

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_stuff);
    return UNITY_END();
}