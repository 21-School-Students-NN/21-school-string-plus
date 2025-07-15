#include <check.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

// Helper function to compare results
static int pointers_equal(const void *ptr1, const void *ptr2) {
  return ptr1 == ptr2;
}

START_TEST(test_memchr_basic) {
  unsigned char buf[5] = {1, 2, 3, 4, 5};
  int c = 3;
  size_t n = 5;

  const void *result_s21 = s21_memchr(buf, c, n);
  const void *result_std = memchr(buf, c, n);

  ck_assert_msg(pointers_equal(result_s21, result_std),
                "s21_memchr and memchr returned different pointers");
}
END_TEST

START_TEST(test_memchr_not_found) {
  unsigned char buf[5] = {1, 2, 3, 4, 5};
  int c = 6;  // Value not in buffer
  size_t n = 5;

  void *result_s21 = s21_memchr(buf, c, n);
  void *result_std = memchr(buf, c, n);

  ck_assert_msg(
      pointers_equal(result_s21, result_std),
      "s21_memchr and memchr returned different pointers for value not found");
  ck_assert_ptr_null(result_s21);
  ck_assert_ptr_null(result_std);
}
END_TEST

START_TEST(test_memchr_zero_length) {
  unsigned char buf[5] = {1, 2, 3, 4, 5};
  int c = 3;
  size_t n = 0;

  void *result_s21 = s21_memchr(buf, c, n);
  void *result_std = memchr(buf, c, n);

  ck_assert_msg(
      pointers_equal(result_s21, result_std),
      "s21_memchr and memchr returned different pointers for zero length");
  ck_assert_ptr_null(result_s21);
  ck_assert_ptr_null(result_std);
}
END_TEST

START_TEST(test_memchr_first_byte) {
  unsigned char buf[5] = {1, 2, 3, 4, 5};
  int c = 1;
  size_t n = 5;

  void *result_s21 = s21_memchr(buf, c, n);
  void *result_std = memchr(buf, c, n);

  ck_assert_msg(
      pointers_equal(result_s21, result_std),
      "s21_memchr and memchr returned different pointers for first byte");
  ck_assert_ptr_eq(result_s21, buf);
  ck_assert_ptr_eq(result_std, buf);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("memchr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memchr_basic);
  tcase_add_test(tc_core, test_memchr_not_found);
  tcase_add_test(tc_core, test_memchr_zero_length);
  tcase_add_test(tc_core, test_memchr_first_byte);

  suite_add_tcase(s, tc_core);

  return s;
}
