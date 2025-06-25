#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_strchr_multiple_occasions) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  char c = 'a';
  char *result_s21 = s21_strchr(str, c);
  char *result_std = strchr(str, c);
  ck_assert_ptr_eq(result_s21, result_std);  // Compare pointers
  if (result_s21 != NULL && result_std != NULL) {
    ck_assert_str_eq(result_s21, result_std);  // Compare strings if non-NULL
  }
}
END_TEST

START_TEST(test_strchr_zero_occasions) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  char c = 'F';
  ck_assert_ptr_eq(s21_strchr(str, c),
                   strchr(str, c));  // Compare pointers (both NULL)
}
END_TEST

START_TEST(test_strchr_empty_string) {
  const char *str = "";
  char c = 'F';
  ck_assert_ptr_eq(s21_strchr(str, c),
                   strchr(str, c));  // Compare pointers (both NULL)
}
END_TEST

START_TEST(test_strchr_search_null) {
  const char *str = "asdfasd";
  char c = '\0';
  char *result_s21 = s21_strchr(str, c);
  char *result_std = strchr(str, c);
  ck_assert_ptr_eq(result_s21, result_std);  // Compare pointers
  if (result_s21 != NULL && result_std != NULL) {
    ck_assert_str_eq(result_s21, result_std);  // Compare strings (both "\0")
  }
}
END_TEST

START_TEST(test_strchr_search_eof) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  ck_assert_ptr_eq(s21_strchr(str, EOF),
                   strchr(str, EOF));  // Compare pointers (both NULL)
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strchr_multiple_occasions);
  tcase_add_test(tc_core, test_strchr_zero_occasions);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_search_null);
  tcase_add_test(tc_core, test_strchr_search_eof);

  suite_add_tcase(s, tc_core);

  return s;
}
