#include <stdlib.h>
#include <string.h>

#include "./suites.h"
#include "../headers/s21_string.h"


START_TEST(test_strncmp_equal) {
    const char *s1 = "identical";
    const char *s2 = "identical";
    ck_assert_int_eq(s21_strncmp(s1, s2, 10), strncmp(s1, s2, 10));
}
END_TEST

START_TEST(test_strncmp_diff_length) {
    const char *s1 = "hello";
    const char *s2 = "hello_world";
    ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));
}
END_TEST

START_TEST(test_strncmp_partial) {
    const char *s1 = "apple";
    const char *s2 = "application";
    ck_assert_int_eq(s21_strncmp(s1, s2, 3), strncmp(s1, s2, 3));
}
END_TEST

START_TEST(test_strncmp_unicode) {
    const char *s1 = "привет";
    const char *s2 = "пока";
    ck_assert_int_eq(s21_strncmp(s1, s2, 2), strncmp(s1, s2, 2));
}
END_TEST

START_TEST(test_strncmp_empty) {
    const char *s1 = "";
    const char *s2 = "";
    ck_assert_int_eq(s21_strncmp(s1, s2, 1), strncmp(s1, s2, 1));
}
END_TEST

START_TEST(test_strncmp_zero_n) {
    const char *s1 = "any_string";
    const char *s2 = "other_string";
    ck_assert_int_eq(s21_strncmp(s1, s2, 0), strncmp(s1, s2, 0));
}
END_TEST

START_TEST(test_strncmp_null_early) {
    const char *s1 = "abc\0def";
    const char *s2 = "abc\0xyz";
    ck_assert_int_eq(s21_strncmp(s1, s2, 6), strncmp(s1, s2, 6));
}
END_TEST

#if 1
START_TEST(test_strncmp_case_diff_v1) {
    const char *s1 = "hELLO";
    const char *s2 = "hello";
    ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));
}
END_TEST
#endif

START_TEST(test_strncmp_case_diff) {
    char s1[2] = {0};
    char s2[2] = {0};
    
    // Test uppercase in s1 vs lowercase in s2
    for (int i = 'A'; i <= 'Z'; ++i) {
        s1[0] = i;
        s2[0] = i + 32; // ASCII lowercase equivalent
        ck_assert_int_eq(s21_strncmp(s1, s2, 1), strncmp(s1, s2, 1));
    }
    
    // Test lowercase in s1 vs uppercase in s2
    for (int i = 'a'; i <= 'z'; ++i) {
        s1[0] = i;
        s2[0] = i - 32; // ASCII uppercase equivalent
        ck_assert_int_eq(s21_strncmp(s1, s2, 1), strncmp(s1, s2, 1));
    }
}
END_TEST

Suite *s21_strncmp_suite(void) {
    Suite *s = suite_create("strncmp");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_strncmp_equal);
    tcase_add_test(tc_core, test_strncmp_diff_length);
    tcase_add_test(tc_core, test_strncmp_partial);
    tcase_add_test(tc_core, test_strncmp_unicode);
    tcase_add_test(tc_core, test_strncmp_empty);
    tcase_add_test(tc_core, test_strncmp_zero_n);
    tcase_add_test(tc_core, test_strncmp_null_early);
    tcase_add_test(tc_core, test_strncmp_case_diff_v1);
    tcase_add_test(tc_core, test_strncmp_case_diff);

    suite_add_tcase(s, tc_core);
    return s;
}