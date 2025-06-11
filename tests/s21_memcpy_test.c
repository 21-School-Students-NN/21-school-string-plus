#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memcpy_int_int) {
  int a = 256, b = 7;

  ck_assert_int_eq(*(int *)s21_memcpy(&a, &b, 3), *(int *)memcpy(&a, &b, 3));
  ck_assert_int_eq(*(int *)s21_memcpy(&b, &a, 2), *(int *)memcpy(&b, &a, 2));
}
END_TEST

START_TEST(test_memcpy_double_int) {
  int a = 256;
  double b = 7;

  ck_assert_int_eq(*(int *)s21_memcpy(&a, &b, 2), *(int *)memcpy(&a, &b, 2));
  ck_assert_int_eq(*(double *)s21_memcpy(&b, &a, 3),
                   *(double *)memcpy(&b, &a, 3));
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create(" memcpy ");

  /* Core test case */
  tc_core = tcase_create(" int_int ");
  tcase_add_test(tc_core, test_memcpy_int_int);
  suite_add_tcase(s, tc_core);
  tc_core = tcase_create(" double_int ");
  tcase_add_test(tc_core, test_memcpy_double_int);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_memcpy_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}