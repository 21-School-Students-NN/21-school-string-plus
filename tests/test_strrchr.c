#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

// NOTE: Yes, all of this is just replaced strchr().

START_TEST(test_strrchr_multiple_occasions) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  char c = 'a';
  char *result_s21 = s21_strrchr(str, c);
  char *result_std = strrchr(str, c);
  ck_assert_ptr_eq(result_s21, result_std);  // Compare pointers
  if (result_s21 != NULL && result_std != NULL) {
    ck_assert_str_eq(result_s21, result_std);  // Compare strings if non-NULL
  }
}
END_TEST

START_TEST(test_strrchr_zero_occasions) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  char c = 'F';
  ck_assert_ptr_eq(s21_strrchr(str, c),
                   strrchr(str, c));  // Compare pointers (both NULL)
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  const char *str = "";
  char c = 'F';
  ck_assert_ptr_eq(s21_strrchr(str, c),
                   strrchr(str, c));  // Compare pointers (both NULL)
}
END_TEST

START_TEST(test_strrchr_search_null) {
  const char *str = "asdfasd";
  char c = '\0';
  char *result_s21 = s21_strrchr(str, c);
  char *result_std = strrchr(str, c);
  ck_assert_ptr_eq(result_s21, result_std);  // Compare pointers
  if (result_s21 != NULL && result_std != NULL) {
    ck_assert_str_eq(result_s21, result_std);  // Compare strings (both "\0")
  }
}
END_TEST

START_TEST(test_strrchr_search_eof) {
  const char *str = "I'm a little Bee and my name is Vitalya";
  ck_assert_ptr_eq(s21_strrchr(str, EOF),
                   strrchr(str, EOF));  // Compare pointers (both NULL)
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("strrchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr_multiple_occasions);
  tcase_add_test(tc_core, test_strrchr_zero_occasions);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_search_null);
  tcase_add_test(tc_core, test_strrchr_search_eof);

  suite_add_tcase(s, tc_core);

  return s;
}
