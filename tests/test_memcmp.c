#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_memcmp_basic) {
  const char *str_1 = "hello world";
  const char *str_2 = "hello world";
  size_t n = 10;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  const char *str_1 = "1234";
  const char *str_2 = "1233";
  size_t n = 0;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_diff_at_start) {
  const char *str_1 = "00000000";
  const char *str_2 = "10000000";
  size_t n = 8;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_diff_at_midle) {
  const char *str_1 = "00000000";
  const char *str_2 = "00011000";
  size_t n = 8;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_diff_at_end) {
  const char *str_1 = "00000001";
  const char *str_2 = "00000000";
  size_t n = 8;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_partial_same) {
  const char *str_1 = "abcdefgh";
  const char *str_2 = "abcdeeee";
  size_t n = 4;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(test_memcmp_binary_data) {
  const unsigned char str_1[4] = {0xFF, 0x00, 0x80, 0x7F};
  const unsigned char str_2[4] = {0xFF, 0x00, 0x81, 0x7F};
  size_t n = 4;

  ck_assert_int_eq(s21_memcmp(str_1, str_2, n), memcmp(str_1, str_2, n));
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *s = suite_create("memcmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcmp_basic);
  tcase_add_test(tc_core, test_memcmp_zero_length);
  tcase_add_test(tc_core, test_memcmp_diff_at_start);
  tcase_add_test(tc_core, test_memcmp_diff_at_midle);
  tcase_add_test(tc_core, test_memcmp_diff_at_end);
  tcase_add_test(tc_core, test_memcmp_partial_same);
  tcase_add_test(tc_core, test_memcmp_binary_data);

  suite_add_tcase(s, tc_core);
  return s;
}