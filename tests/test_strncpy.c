#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

#define BUF_SIZE 32

START_TEST(test_strncpy_basic) {
  char dest1[BUF_SIZE];
  char dest2[BUF_SIZE];
  const char *src = "test string";
  ck_assert_str_eq(s21_strncpy(dest1, src, BUF_SIZE),
                   strncpy(dest2, src, BUF_SIZE));
  ck_assert_mem_eq(s21_strncpy(dest1, src, BUF_SIZE),
                   strncpy(dest2, src, BUF_SIZE), BUF_SIZE);
}
END_TEST

START_TEST(test_strncpy_partial) {
  char dest1[BUF_SIZE] = {0};
  char dest2[BUF_SIZE] = {0};
  const char *src = "longer than five";
  ck_assert_mem_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5),
                   BUF_SIZE);
}
END_TEST

START_TEST(test_strncpy_exact_fit) {
  char dest1[6] = {0};
  char dest2[6] = {0};
  const char *src = "exact";
  ck_assert_str_eq(s21_strncpy(dest1, src, 6), strncpy(dest2, src, 6));
  ck_assert_mem_eq(s21_strncpy(dest1, src, 6), strncpy(dest2, src, 6), 6);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  char dest1[BUF_SIZE] = "initial";
  char dest2[BUF_SIZE] = "initial";
  const char *src = "";
  ck_assert_mem_eq(s21_strncpy(dest1, src, BUF_SIZE),
                   s21_strncpy(dest2, src, BUF_SIZE), BUF_SIZE);
}
END_TEST

START_TEST(test_strncpy_overlap) {
  char buffer1[] = "abcdefghij";
  char buffer2[] = "abcdefghij";

  s21_strncpy(buffer1 + 3, buffer1, 4);
  strncpy(buffer2 + 3, buffer2, 4);

  ck_assert_mem_eq(buffer1, buffer2, 11);
}
END_TEST

START_TEST(test_strncpy_unicode) {
  char dest1[BUF_SIZE];
  char dest2[BUF_SIZE];
  const char *src = "привет";
  ck_assert_mem_eq(s21_strncpy(dest1, src, BUF_SIZE),
                   strncpy(dest2, src, BUF_SIZE), BUF_SIZE);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s = suite_create("strncpy");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strncpy_basic);
  tcase_add_test(tc_core, test_strncpy_partial);
  tcase_add_test(tc_core, test_strncpy_exact_fit);
  tcase_add_test(tc_core, test_strncpy_empty_src);
  tcase_add_test(tc_core, test_strncpy_overlap);
  tcase_add_test(tc_core, test_strncpy_unicode);

  suite_add_tcase(s, tc_core);
  return s;
}