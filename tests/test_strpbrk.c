#include <check.h>
#include <stdlib.h>

#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_strpbrk_basic) {
  const char *str = "hello world";
  const char *keys = "aeiou";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_no_match) {
  const char *str = "xyz";
  const char *keys = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_empty_str) {
  const char *str = "";
  const char *keys = "abc";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_empty_keys) {
  const char *str = "hello";
  const char *keys = "";
  ck_assert_ptr_eq(s21_strpbrk(str, keys), strpbrk(str, keys));
}

START_TEST(test_strpbrk_null_byte) {
  const char *str = "test\0string";
  const char *keys = "\0";
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