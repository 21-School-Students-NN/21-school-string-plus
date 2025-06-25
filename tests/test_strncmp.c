#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

static inline int normalize_strncmp_result(int res) {
  if (res == 0) return 0;
  return (res < 0) ? -1 : 1;
}

START_TEST(test_strncmp_equal) {
  const char *str1 = "identical";
  const char *str2 = "identical";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 10)),
                   normalize_strncmp_result(strncmp(str1, str2, 10)));
}
END_TEST

START_TEST(test_strncmp_diff_length) {
  const char *str1 = "hello";
  const char *str2 = "hello_world";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 6)),
                   normalize_strncmp_result(strncmp(str1, str2, 6)));
}
END_TEST

START_TEST(test_strncmp_partial) {
  const char *str1 = "apple";
  const char *str2 = "application";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 3)),
                   normalize_strncmp_result(strncmp(str1, str2, 3)));
}
END_TEST

START_TEST(test_strncmp_unicode) {
  const char *str1 = "привет";
  const char *str2 = "пока";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 2)),
                   normalize_strncmp_result(strncmp(str1, str2, 2)));
}
END_TEST

START_TEST(test_strncmp_empty) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 1)),
                   normalize_strncmp_result(strncmp(str1, str2, 1)));
}
END_TEST

START_TEST(test_strncmp_zero_n) {
  const char *str1 = "any_string";
  const char *str2 = "other_string";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 0)),
                   normalize_strncmp_result(strncmp(str1, str2, 0)));
}
END_TEST

START_TEST(test_strncmp_null_early) {
  const char *str1 = "abc\0def";
  const char *str2 = "abc\0xyz";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 6)),
                   normalize_strncmp_result(strncmp(str1, str2, 6)));
}
END_TEST

START_TEST(test_strncmp_case_diff_v1) {
  const char *str1 = "hELLO";
  const char *str2 = "hello";
  ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 5)),
                   normalize_strncmp_result(strncmp(str1, str2, 5)));
}
END_TEST

START_TEST(test_strncmp_case_diff) {
  char str1[2] = {0};
  char str2[2] = {0};

  // Test uppercase in str1 vs lowercase in str2
  for (int i = 'A'; i <= 'Z'; ++i) {
    str1[0] = i;
    str2[0] = i + 32;  // ASCII lowercase equivalent
    ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 1)),
                     normalize_strncmp_result(strncmp(str1, str2, 1)));
  }

  // Test lowercase in str1 vs uppercase in str2
  for (int i = 'a'; i <= 'z'; ++i) {
    str1[0] = i;
    str2[0] = i - 32;  // ASCII uppercase equivalent
    ck_assert_int_eq(normalize_strncmp_result(s21_strncmp(str1, str2, 1)),
                     normalize_strncmp_result(strncmp(str1, str2, 1)));
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