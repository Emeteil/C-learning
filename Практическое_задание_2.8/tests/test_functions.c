#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../triangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool fileContains(const char* filename, const char* str) {
    FILE* file = fopen(filename, "rb");
    if (!file) return false;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buf = malloc(size + 1);
    fread(buf, 1, size, file);
    buf[size] = '\0';

    fclose(file);
    bool result = strstr(buf, str) != NULL;
    free(buf);
    return result;
}

void test_triangularNumberRecursive_1(void) {
    CU_ASSERT_EQUAL(triangularNumberRecursive(1), 1);
}

void test_triangularNumberRecursive_n(void) {
    for (int n = 2; n < 100; n++) {
        CU_ASSERT_EQUAL(triangularNumberRecursive(n), (n * (n + 1)) / 2);
    }
}

void test_validateInput_correct(void) {
    char* prog = "prog";
    char* args1[] = {prog, "5"};
    CU_ASSERT_TRUE(validateInput(2, args1));
}

void test_validateInput_no_args(void) {
    char* prog = "prog";
    char* args2[] = {prog};
    CU_ASSERT_FALSE(validateInput(1, args2));
}

void test_validateInput_extra_args(void) {
    char* prog = "prog";
    char* args3[] = {prog, "5", "extra"};
    CU_ASSERT_FALSE(validateInput(3, args3));
}

void test_parseInput_positive(void) {
    CU_ASSERT_EQUAL(parseInput("1"), 1);
    CU_ASSERT_EQUAL(parseInput("22"), 22);
    CU_ASSERT_EQUAL(parseInput("333"), 333);
    CU_ASSERT_EQUAL(parseInput("4444"), 4444);
    CU_ASSERT_EQUAL(parseInput("55555"), 55555);
    CU_ASSERT_EQUAL(parseInput("1890"), 1890);
}

void test_parseInput_edge_cases(void) {
    CU_ASSERT_EQUAL(parseInput("0"), 0);
    CU_ASSERT_EQUAL(parseInput("-5"), -5);
}

void test_parseInput_invalid(void) {
    CU_ASSERT_EQUAL(parseInput("abc"), 0);
    CU_ASSERT_EQUAL(parseInput("123abc"), 123);
}

void test_printTriangleToFile_3(void) {
    printTriangleToFile(3);
    CU_ASSERT_TRUE(fileContains("triangle.txt", "🟩 \n🟩 🟩 \n🟩 🟩 🟩 \n"));
    unlink("triangle.txt");
}

void test_printTriangleToFile_1(void) {
    printTriangleToFile(1);
    CU_ASSERT_TRUE(fileContains("triangle.txt", "🟩 \n"));
    unlink("triangle.txt");
}

void test_printTriangleToFile_0(void) {
    printTriangleToFile(0);
    FILE* f = fopen("triangle.txt", "r");
    fseek(f, 0, SEEK_END);
    CU_ASSERT_EQUAL(ftell(f), 0);
    fclose(f);
    unlink("triangle.txt");
}

void test_printUsage(void) {
    freopen("usage_test.txt", "w", stderr);
    printUsage("prog");
    fclose(stderr);
    CU_ASSERT_TRUE(fileContains("usage_test.txt", "Формат ввода: prog <n>"));
    unlink("usage_test.txt");
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite1 = CU_add_suite("triangularNumberRecursive", NULL, NULL);
    CU_add_test(suite1, "triangularNumberRecursive for 1", test_triangularNumberRecursive_1);
    CU_add_test(suite1, "triangularNumberRecursive for 2->99", test_triangularNumberRecursive_n);

    CU_pSuite suite2 = CU_add_suite("validateInput", NULL, NULL);
    CU_add_test(suite2, "validateInput correct", test_validateInput_correct);
    CU_add_test(suite2, "validateInput no args", test_validateInput_no_args);
    CU_add_test(suite2, "validateInput extra args", test_validateInput_extra_args);
    
    CU_pSuite suite3 = CU_add_suite("parseInput", NULL, NULL);
    CU_add_test(suite3, "parseInput positive numbers", test_parseInput_positive);
    CU_add_test(suite3, "parseInput edge cases", test_parseInput_edge_cases);
    CU_add_test(suite3, "parseInput invalid input", test_parseInput_invalid);

    CU_pSuite suite4 = CU_add_suite("printTriangleToFile", NULL, NULL);
    CU_add_test(suite4, "printTriangleToFile n=0", test_printTriangleToFile_0);
    CU_add_test(suite4, "printTriangleToFile n=1", test_printTriangleToFile_1);
    CU_add_test(suite4, "printTriangleToFile n=3", test_printTriangleToFile_3);

    CU_pSuite suite5 = CU_add_suite("printUsage", NULL, NULL);
    CU_add_test(suite5, "printUsage", test_printUsage);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}