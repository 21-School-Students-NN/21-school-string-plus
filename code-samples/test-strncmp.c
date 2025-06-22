#include <stdio.h>
#include <string.h>
#include <check.h>
#include "../headers/s21_string.h"

void compare_strncmp(const char *s1, const char *s2, size_t n) {
    int original = strncmp(s1, s2, n);
    int custom = s21_strncmp(s1, s2, n);
    printf("strncmp(\"%s\", \"%s\", %zu) = %d\n", s1, s2, n, original);
    printf("s21_strncmp(\"%s\", \"%s\", %zu) = %d\n", s1, s2, n, custom);
    printf("Results are %s\n\n", (original == custom) ? "EQUAL" : "DIFFERENT");
}

// Check library test cases
START_TEST(test_check_strncmp_basic) {
    const char *s1 = "A";
    const char *s2 = "a";
    int original = strncmp(s1, s2, 1);
    int custom = s21_strncmp(s1, s2, 1);
    printf("CHECK TEST: strncmp(\"%s\", \"%s\", 1) = %d\n", s1, s2, original);
    printf("CHECK TEST: s21_strncmp(\"%s\", \"%s\", 1) = %d\n", s1, s2, custom);
    printf("CHECK TEST: Results are %s\n\n", (original == custom) ? "EQUAL" : "DIFFERENT");
    
    // Check that both have the same sign
    int sign_original = (original > 0) - (original < 0);
    int sign_custom = (custom > 0) - (custom < 0);
    ck_assert_int_eq(sign_original, sign_custom);
}
END_TEST

START_TEST(test_check_strncmp_case_diff) {
    char s1[2] = {0};
    char s2[2] = {0};
    
    // Test uppercase vs lowercase
    s1[0] = 'A';
    s2[0] = 'a';
    
    int original = strncmp(s1, s2, 1);
    int custom = s21_strncmp(s1, s2, 1);
    
    printf("CHECK TEST: strncmp('%c', '%c', 1) = %d\n", s1[0], s2[0], original);
    printf("CHECK TEST: s21_strncmp('%c', '%c', 1) = %d\n", s1[0], s2[0], custom);
    printf("CHECK TEST: Results are %s\n\n", (original == custom) ? "EQUAL" : "DIFFERENT");
    
    // Check that both have the same sign
    int sign_original = (original > 0) - (original < 0);
    int sign_custom = (custom > 0) - (custom < 0);
    ck_assert_int_eq(sign_original, sign_custom);
}
END_TEST

START_TEST(test_check_strncmp_exact_value) {
    const char *s1 = "HELLO";
    const char *s2 = "hello";
    
    int original = strncmp(s1, s2, 5);
    int custom = s21_strncmp(s1, s2, 5);
    
    printf("CHECK TEST: strncmp(\"%s\", \"%s\", 5) = %d\n", s1, s2, original);
    printf("CHECK TEST: s21_strncmp(\"%s\", \"%s\", 5) = %d\n", s1, s2, custom);
    printf("CHECK TEST: Results are %s\n\n", (original == custom) ? "EQUAL" : "DIFFERENT");
    
    // This test will fail if the values don't match exactly
    ck_assert_int_eq(original, custom);
}
END_TEST

Suite *check_strncmp_suite(void) {
    Suite *s = suite_create("check_strncmp");
    TCase *tc = tcase_create("Core");
    
    tcase_add_test(tc, test_check_strncmp_basic);
    tcase_add_test(tc, test_check_strncmp_case_diff);
    tcase_add_test(tc, test_check_strncmp_exact_value);
    
    suite_add_tcase(s, tc);
    return s;
}

int main() {
    printf("=== STANDALONE TESTS ===\n");
    // Test cases from the test file
    compare_strncmp("identical", "identical", 10);
    compare_strncmp("hello", "hello_world", 5);
    compare_strncmp("apple", "application", 3);
    compare_strncmp("привет", "пока", 2);
    compare_strncmp("", "", 1);
    compare_strncmp("any_string", "other_string", 0);
    compare_strncmp("abc\0def", "abc\0xyz", 6);
    compare_strncmp("HELLO", "hello", 5);
    
    // Test case with case differences
    char s1[2] = {0}, s2[2] = {0};
    s1[0] = 'A'; s2[0] = 'a';
    compare_strncmp(s1, s2, 1);
    s1[0] = 'a'; s2[0] = 'A';
    compare_strncmp(s1, s2, 1);
    
    printf("=== CHECK LIBRARY TESTS ===\n");
    // Run Check library tests
    Suite *s = check_strncmp_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? 0 : 1;
}