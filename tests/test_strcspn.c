#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_strcspn_basic_match) {
  const char *str = "hello_world";
  const char *reject = "w_";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char *str = "abcdef";
  const char *reject = "xyz";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_full_match) {
  const char *str = "123456";
  const char *reject = "321";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_empty_string) {
  const char *str = "";
  const char *reject = "abc";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_empty_reject) {
  const char *str = "hello";
  const char *reject = "";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_both_empty) {
  const char *str = "";
  const char *reject = "";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_null_byte_in_reject) {
  const char *str = "hello\0world";
  const char *reject = "\0";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_unicode_chars) {
  const char *str = "привет мир";
  const char *reject = "мр";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_repeated_chars) {
  const char *str = "aabbccdd";
  const char *reject = "bc";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_strcspn_first_char_match) {
  const char *str = "xylophone";
  const char *reject = "x";
  ck_assert_uint_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("strcspn");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strcspn_basic_match);
  tcase_add_test(tc_core, test_strcspn_no_match);
  tcase_add_test(tc_core, test_strcspn_full_match);
  tcase_add_test(tc_core, test_strcspn_empty_string);
  tcase_add_test(tc_core, test_strcspn_empty_reject);
  tcase_add_test(tc_core, test_strcspn_both_empty);
  tcase_add_test(tc_core, test_strcspn_null_byte_in_reject);
  tcase_add_test(tc_core, test_strcspn_unicode_chars);
  tcase_add_test(tc_core, test_strcspn_repeated_chars);
  tcase_add_test(tc_core, test_strcspn_first_char_match);

  suite_add_tcase(s, tc_core);
  return s;
}