#include <check.h>
#include <stdlib.h>

#include "../headers/s21_string.h"

START_TEST(test_trim_basic) {
  const char *str = "  Hello World!  ";
  const char *chars = " ";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "Hello World!");
  free(res);
}
END_TEST

START_TEST(test_trim_no_trim_needed) {
  const char *str = "NoTrimNeeded";
  const char *chars = " ";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "NoTrimNeeded");
  free(res);
}
END_TEST

START_TEST(test_trim_all_chars) {
  const char *str = "aaaaaa";
  const char *chars = "a";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_empty_string) {
  const char *str = "";
  const char *chars = " ";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_null_input) {
  // Передача NULL должна возвращать NULL
  ck_assert_ptr_eq(s21_trim(S21_NULL, " "), NULL);
  ck_assert_ptr_eq(s21_trim("test", S21_NULL), NULL);
}
END_TEST

START_TEST(test_trim_only_trimmable_chars) {
  const char *str = "   \t\n";
  const char *chars = " \t\n";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_partial_trimming) {
  const char *str = "--Hello--";
  const char *chars = "-";
  char *res = s21_trim(str, chars);
  ck_assert_str_eq(res, "Hello");
  free(res);
}
END_TEST

// Создаем тестовый набор
Suite *s21_trim_suite(void) {
  Suite *s = suite_create("trim");

  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_basic);
  tcase_add_test(tc_core, test_trim_no_trim_needed);
  tcase_add_test(tc_core, test_trim_all_chars);
  tcase_add_test(tc_core, test_trim_empty_string);
  tcase_add_test(tc_core, test_trim_null_input);
  tcase_add_test(tc_core, test_trim_only_trimmable_chars);
  tcase_add_test(tc_core, test_trim_partial_trimming);

  suite_add_tcase(s, tc_core);

  return s;
}