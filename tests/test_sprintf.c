#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "suites.h"

START_TEST(test_s21_sprintf_basic) {
  char buffer1[100];
  char buffer2[100];

  // just string
  const char *format = "Hello, %s!";
  const char *name = "World";

  int ret1 = s21_sprintf(buffer1, format, name);
  int ret2 = sprintf(buffer2, format, name);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sprintf_integers) {
  char buffer1[100];
  char buffer2[100];

  // integer arg
  const char *format = "Number: %d";
  int number = 42;

  int ret1 = s21_sprintf(buffer1, format, number);
  int ret2 = sprintf(buffer2, format, number);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sprintf_integers_width) {
  char buffer1[100];
  char buffer2[100];

  // integer with width and flag '+'
  const char *format = "Number: %+5d";
  int number = 42;

  int ret1 = s21_sprintf(buffer1, format, number);
  int ret2 = sprintf(buffer2, format, number);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(test_s21_sprintf_floats) {
  char buffer1[128];
  char buffer2[128];

  // float number arg
  const char *format = "Float %+10.3f\n";
  double fnumber = 53.3;

  int ret1 = s21_sprintf(buffer1, format, fnumber);
  int ret2 = sprintf(buffer2, format, fnumber);

  ck_assert_str_eq(buffer1, buffer2);
  ck_assert_int_eq(ret1, ret2);
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

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf_basic);
  tcase_add_test(tc_core, test_s21_sprintf_integers);
  tcase_add_test(tc_core, test_s21_sprintf_integers_width);
  tcase_add_test(tc_core, test_s21_sprintf_floats);
  tcase_add_test(tc_core, test_s21_sprintf_multiple);
  suite_add_tcase(s, tc_core);

  return s;
}