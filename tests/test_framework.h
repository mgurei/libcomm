#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

typedef void (*test_func_t)(void);

typedef struct {
    const char *name;
    const char *description;
    test_func_t func;
} test_case_t;

#define MAX_TESTS 100

static test_case_t test_cases[MAX_TESTS];
static int test_count = 0;
static const char *test_file_name = NULL;
static const char *test_file_description = NULL;

#define REGISTER_TEST_FILE(name, desc) \
    do { \
        test_file_name = name; \
        test_file_description = desc; \
    } while (0)

#define REGISTER_TEST(test, desc) \
    do { \
        if (test_count < MAX_TESTS) { \
            test_cases[test_count++] = (test_case_t){#test, desc, test}; \
        } else { \
            fprintf(stderr, "Max test limit reached\n"); \
        } \
    } while (0)

#define RUN_TESTS() \
    do { \
        int pass_count = 0; \
        int fail_count = 0; \
        printf("========================================\n"); \
        printf("\nRunning tests for %s\n", test_file_name); \
        printf("Description: %s\n", test_file_description); \
        printf("========================================\n"); \
        printf("Running %d tests...\n", test_count); \
        printf("========================================\n"); \
        for (int i = 0; i < test_count; ++i) { \
            printf("Test %d: %s\n", i + 1, test_cases[i].name); \
            printf("Description: %s\n", test_cases[i].description); \
            printf("----------------------------------------\n"); \
            test_cases[i].func(); \
            printf("Test %s: \033[0;32mPASS\033[0m\n", test_cases[i].name); \
            pass_count++; \
            printf("========================================\n"); \
        } \
        printf("Summary:\n"); \
        printf("Passed: %d\n", pass_count); \
        printf("Failed: %d\n", fail_count); \
        printf("========================================\n"); \
    } while (0)

#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #cond, __FILE__, __LINE__); \
            printf("Test %s: \033[0;31mFAIL\033[0m\n", __func__); \
            return; \
        } \
    } while (0)

#endif // TEST_FRAMEWORK_H