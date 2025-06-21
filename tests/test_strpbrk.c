#include <check.h>
#include <stdlib.h>

#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_strpbrk_basic) {
  char *str = "hello world";
  char *keys = "aeiou";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_no_match) {
  char *str = "xyz";
  char *keys = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_empty_str) {
  char *str = "";
  char *keys = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_empty_keys) {
  char *str = "hello";
  char *keys = "";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_null_byte) {
  char *str = "test\0string";
  char *keys = "\0";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

Suite *s21_strpbrk_suite(void) {
  Suite *s = suite_create("strpbrk");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strpbrk_basic);
  tcase_add_test(tc_core, test_strpbrk_no_match);
  tcase_add_test(tc_core, test_strpbrk_empty_str);
  tcase_add_test(tc_core, test_strpbrk_empty_keys);
  tcase_add_test(tc_core, test_strpbrk_null_byte);

  suite_add_tcase(s, tc_core);
  return s;
}