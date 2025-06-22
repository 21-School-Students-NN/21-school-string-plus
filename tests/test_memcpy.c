#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"

// Test function comparing s21_memcpy with memcpy (copy from int to int)
START_TEST(test_memcpy_int_int) {
  int src1 = 256;
  int dest1 = 7;
  int dest2 = 7;

  ck_assert_int_eq(*(int *)s21_memcpy(&dest1, &src1, 3),
                   *(int *)memcpy(&dest2, &src1, 3));
}
END_TEST

// Test function comparing s21_memcpy with memcpy (copy from int to double)
START_TEST(test_memcpy_double_int) {
  int src1 = 256;
  double dest1 = 7;
  double dest2 = 7;
  ck_assert_double_eq(*(double *)s21_memcpy(&dest1, &src1, 3),
                      *(double *)memcpy(&dest2, &src1, 3));
}
END_TEST

// Test function comparing s21_memcpy with memcpy
START_TEST(test_memcpy_string_comparison) {
  char src[] = "Hello, world!";
  char dest1[50];
  char dest2[50];

  size_t n = strlen(src) + 1;  // including the null terminator

  // Use standard memcpy
  memcpy(dest1, src, n);
  // Use our s21_memcpy
  s21_memcpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

// Test copying zero bytes
START_TEST(test_memcpy_zero_length) {
  char src[] = "Test";
  char dest1[10] = {0};
  char dest2[10] = {0};

  size_t n = 0;

  // Copy zero bytes
  memcpy(dest1, src, n);
  s21_memcpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, sizeof(dest1));
}
END_TEST

// Test behavior with null pointers (should be compliant with standard)
START_TEST(test_memcpy_null_pointers) {
  // Calling with NULL pointers and zero length should not cause errors
  ck_assert_ptr_eq(s21_memcpy(NULL, NULL, 0), NULL);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("memcpy");

  tc_core = tcase_create("int_comparison");
  tcase_add_test(tc_core, test_memcpy_int_int);
  suite_add_tcase(s, tc_core);
  tc_core = tcase_create("double_int_comparison");
  tcase_add_test(tc_core, test_memcpy_double_int);
  suite_add_tcase(s, tc_core);
  tc_core = tcase_create("string_comparison");
  tcase_add_test(tc_core, test_memcpy_string_comparison);
  suite_add_tcase(s, tc_core);
  tc_core = tcase_create("zero_length");
  tcase_add_test(tc_core, test_memcpy_zero_length);
  suite_add_tcase(s, tc_core);
  tc_core = tcase_create("null_pointers");
  tcase_add_test(tc_core, test_memcpy_null_pointers);
  suite_add_tcase(s, tc_core);

  return s;
}