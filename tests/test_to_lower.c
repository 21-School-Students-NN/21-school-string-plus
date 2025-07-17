#include <check.h>
#include <stdlib.h>

#include "../headers/s21_string.h"
#include "suites.h"

// tests for s21_to_lower function
START_TEST(test_to_lower_normal) {
  const char *input = "HeLlO, wOrLd!";
  char *result = (char *)s21_to_lower(input);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
}
END_TEST

START_TEST(test_to_lower_empty) {
  const char *input = "";
  char *result = (char *)s21_to_lower(input);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_null) {
  char *result = (char *)s21_to_lower(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_to_lower_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("to_lower");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_lower_normal);
  tcase_add_test(tc_core, test_to_lower_empty);
  tcase_add_test(tc_core, test_to_lower_null);

  suite_add_tcase(s, tc_core);

  return s;
}