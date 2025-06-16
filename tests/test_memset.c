#include <errno.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_memset_integration) {
  char str[] = "HELLO BORING WORLD!!!";
  // int n = 999;
  ck_assert_str_eq(s21_memset(str, 'c', 5), memset(str, 'c', 5));
  // ck_assert_str_eq(s21_memset(str, 'c', n), memset(str, 'c', n));
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("memset");
  tc_core = tcase_create("Core");  // Test case

  tcase_add_test(tc_core, test_memset_integration);
  suite_add_tcase(s, tc_core);

  return s;
}
