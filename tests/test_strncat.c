#include <check.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

#define STRING_SIZE 16

// Normal case - append part of source
START_TEST(test_strncat_normal) {
  char dest_original[STRING_SIZE] = "Hello";
  char dest_school[STRING_SIZE] = "Hello";

  const char *src = " World";
  size_t n = 3;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

// Edge case: n = 0 (no change to dest)
START_TEST(test_strncat_n_zero) {
  char dest_original[STRING_SIZE] = "Hello";
  char dest_school[STRING_SIZE] = "Hello";

  const char *src = " World";
  size_t n = 0;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

// Edge case: src shorter than n
START_TEST(test_strncat_src_shorter_than_n) {
  char dest_original[STRING_SIZE] = "Hello";
  char dest_school[STRING_SIZE] = "Hello";

  const char *src = "A";
  size_t n = 5;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

// Additional normal case - append full source
START_TEST(test_strncat_full_append) {
  char dest_original[STRING_SIZE] = "Hello";
  char dest_school[STRING_SIZE] = "Hello";

  const char *src = " World";
  size_t n = 6;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

// Edge case: empty source
START_TEST(test_strncat_empty_src) {
  char dest_original[STRING_SIZE] = "Hello";
  char dest_school[STRING_SIZE] = "Hello";

  const char *src = "";
  size_t n = 3;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

// Edge case: empty dest
START_TEST(test_strncat_empty_dest) {
  char dest_original[STRING_SIZE] = "\0 World";
  char dest_school[STRING_SIZE] = "\0 World";

  const char *src = "Hello";
  size_t n = 5;

  ck_assert_str_eq(s21_strncat(dest_school, src, n),
                   strncat(dest_original, src, n));
}
END_TEST

START_TEST(test_strncat_from_int_to_string) {
  int dest_original[STRING_SIZE] = {66, 100, 49, 50, 0,  38, 100, 0,
                                    0,  111, 15, 71, 66, 80, 14,  0};
  int dest_school[STRING_SIZE] = {66, 100, 49, 50, 0,  38, 100, 0,
                                  0,  111, 15, 71, 66, 80, 14,  0};

  const char *src = "Hello";
  size_t n = 5;

  ck_assert_str_eq(s21_strncat((char *)dest_school, src, n),
                   strncat((char *)dest_original, src, n));
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strncat");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncat_normal);
  tcase_add_test(tc_core, test_strncat_n_zero);
  tcase_add_test(tc_core, test_strncat_src_shorter_than_n);
  tcase_add_test(tc_core, test_strncat_full_append);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_empty_dest);
  tcase_add_test(tc_core, test_strncat_from_int_to_string);

  suite_add_tcase(s, tc_core);

  return s;
}