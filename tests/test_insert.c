#include <check.h>
#include <stdlib.h>

#include "../headers/s21_string.h"

START_TEST(test_insert_normal) {
  const char *src = "Hello World";
  const char *str = " Beautiful";
  s21_size_t index = 5;
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(result, "Hello Beautiful World");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_src) {
  const char *src = "";
  const char *str = "Hello";
  s21_size_t index = 0;
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  const char *src = "Hello World";
  const char *str = "";
  s21_size_t index = 5;
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(test_insert_index_out_of_bounds) {
  const char *src = "Hello";
  const char *str = " World";
  s21_size_t index = 10;  // index out of bounds
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_insert_null_src) {
  const char *src = NULL;
  const char *str = "Hello";
  s21_size_t index = 0;
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  const char *src = "Hello";
  const char *str = NULL;
  s21_size_t index = 3;
  char *result = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("insert");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_normal);
  tcase_add_test(tc_core, test_insert_empty_src);
  tcase_add_test(tc_core, test_insert_empty_str);
  tcase_add_test(tc_core, test_insert_index_out_of_bounds);
  tcase_add_test(tc_core, test_insert_null_src);
  tcase_add_test(tc_core, test_insert_null_str);

  suite_add_tcase(s, tc_core);

  return s;
}
