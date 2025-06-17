#include <check.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#include "./suites.h"

// Helper function to check if a buffer is filled with a specific value
static int is_buffer_filled(const void *buf, int value, size_t n) {
  const unsigned char *ptr = (const unsigned char *)buf;
  for (size_t i = 0; i < n; i++) {
    if (ptr[i] != (unsigned char)value) {
      return 0;
    }
  }
  return 1;
}

// Helper function to compare two buffers
static int buffers_equal(const void *buf1, const void *buf2, size_t n) {
  return memcmp(buf1, buf2, n) == 0;
}

// Test cases comparing s21_memset and memset
START_TEST(set_non_zero) {
  unsigned char buf_s21[10], buf_std[10];
  s21_memset(buf_s21, 0xAA, 10);
  memset(buf_std, 0xAA, 10);
  ck_assert_int_eq(is_buffer_filled(buf_s21, 0xAA, 10), 1);
  ck_assert_int_eq(is_buffer_filled(buf_std, 0xAA, 10), 1);
  ck_assert_int_eq(buffers_equal(buf_s21, buf_std, 10), 1);
}
END_TEST

START_TEST(set_zero) {
  unsigned char buf_s21[5] = {1, 2, 3, 4, 5}, buf_std[5] = {1, 2, 3, 4, 5};
  s21_memset(buf_s21, 0, 5);
  memset(buf_std, 0, 5);
  ck_assert_int_eq(is_buffer_filled(buf_s21, 0, 5), 1);
  ck_assert_int_eq(is_buffer_filled(buf_std, 0, 5), 1);
  ck_assert_int_eq(buffers_equal(buf_s21, buf_std, 5), 1);
}
END_TEST

START_TEST(set_partial) {
  unsigned char buf_s21[10] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5};
  unsigned char buf_std[10] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 5};
  s21_memset(buf_s21, 0xFF, 5);
  memset(buf_std, 0xFF, 5);
  ck_assert_int_eq(is_buffer_filled(buf_s21, 0xFF, 5), 1);
  ck_assert_int_eq(is_buffer_filled(buf_std, 0xFF, 5), 1);
  ck_assert_int_eq(is_buffer_filled(buf_s21 + 5, 0, 5), 0);
  ck_assert_int_eq(is_buffer_filled(buf_std + 5, 0, 5), 0);
  ck_assert_int_eq(buffers_equal(buf_s21, buf_std, 10), 1);
}
END_TEST

START_TEST(large_buffer) {
  size_t size = 1024;
  unsigned char *buf_s21 = (unsigned char *)malloc(size);
  unsigned char *buf_std = (unsigned char *)malloc(size);
  ck_assert_ptr_nonnull(buf_s21);
  ck_assert_ptr_nonnull(buf_std);
  s21_memset(buf_s21, 0x55, size);
  memset(buf_std, 0x55, size);
  ck_assert_int_eq(is_buffer_filled(buf_s21, 0x55, size), 1);
  ck_assert_int_eq(is_buffer_filled(buf_std, 0x55, size), 1);
  ck_assert_int_eq(buffers_equal(buf_s21, buf_std, size), 1);
  free(buf_s21);
  free(buf_std);
}
END_TEST

START_TEST(negative_value) {
  unsigned char buf_s21[5], buf_std[5];
  s21_memset(buf_s21, -1, 5);
  memset(buf_std, -1, 5);
  ck_assert_int_eq(is_buffer_filled(buf_s21, 0xFF, 5), 1);
  ck_assert_int_eq(is_buffer_filled(buf_std, 0xFF, 5), 1);
  ck_assert_int_eq(buffers_equal(buf_s21, buf_std, 5), 1);
}
END_TEST

// Suite definition
Suite *s21_memset_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("memset");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, set_non_zero);
  tcase_add_test(tc_core, set_zero);
  tcase_add_test(tc_core, set_partial);
  tcase_add_test(tc_core, large_buffer);
  tcase_add_test(tc_core, negative_value);

  suite_add_tcase(s, tc_core);

  return s;
}
