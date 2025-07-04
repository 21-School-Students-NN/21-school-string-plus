#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "suites.h"

START_TEST(test_s21_sprintf_c) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%c", 'A');
  sprintf(expected, "%c", 'A');
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%d", 123);
  sprintf(expected, "%d", 123);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%f", 123.);
  sprintf(expected, "%f", 123.);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%f", 123.45);
  sprintf(expected, "%f", 123.45);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%s", "Hello");
  sprintf(expected, "%s", "Hello");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%u", (unsigned)123);
  sprintf(expected, "%u", (unsigned)123);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%%");
  sprintf(expected, "%%");
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_flags) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%-10d", 123);
  sprintf(expected, "%-10d", 123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%+d", 123);
  sprintf(expected, "%+d", 123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "% d", 123);
  sprintf(expected, "% d", 123);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_width_and_precision) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%10d", 123);
  sprintf(expected, "%10d", 123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%.2f", 123.456);
  sprintf(expected, "%.2f", 123.456);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%10.2f", 123.456);
  sprintf(expected, "%10.2f", 123.456);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_length_modifiers) {
  char buffer[100];
  char expected[100];

  s21_sprintf(buffer, "%hd", (short)123);
  sprintf(expected, "%hd", (short)123);
  ck_assert_str_eq(buffer, expected);

  s21_sprintf(buffer, "%ld", (long)123456789);
  sprintf(expected, "%ld", (long)123456789);
  ck_assert_str_eq(buffer, expected);
}
END_TEST

START_TEST(test_s21_sprintf_multiple) {
  char buffer1[100];
  char buffer2[100];

  // multiple args with different types
  const char *format = "Name: %s, Age: %d";
  const char *name = "Alice";
  int age = 30;

  int ret1 = s21_sprintf(buffer1, format, name, age);
  int ret2 = sprintf(buffer2, format, name, age);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sprintf_multiple_2) {
  char buffer1[100];
  char buffer2[100];

  // multiple args with different types
  const char *format = "Name:%10s, Age:%5.3hd, Weight: %-10.3lf";
  const char *name = "Alice";
  short age = 30;
  double weight = 53.3;

  int ret1 = s21_sprintf(buffer1, format, name, age, weight);
  int ret2 = sprintf(buffer2, format, name, age, weight);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf_c);
  tcase_add_test(tc_core, test_s21_sprintf_d);
  tcase_add_test(tc_core, test_s21_sprintf_f);
  tcase_add_test(tc_core, test_s21_sprintf_s);
  tcase_add_test(tc_core, test_s21_sprintf_u);
  tcase_add_test(tc_core, test_s21_sprintf_percent);
  tcase_add_test(tc_core, test_s21_sprintf_flags);
  tcase_add_test(tc_core, test_s21_sprintf_width_and_precision);
  tcase_add_test(tc_core, test_s21_sprintf_length_modifiers);
  tcase_add_test(tc_core, test_s21_sprintf_multiple);
  tcase_add_test(tc_core, test_s21_sprintf_multiple_2);

  suite_add_tcase(s, tc_core);

  return s;
}