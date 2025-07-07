#include "../headers/s21_string.h"
#include "./suites.h"

// custom solution test for substring search
START_TEST(test_strstr_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "world";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_nonnull(result);  
  ck_assert_str_eq(result, "world!"); 
}
END_TEST

// custom solution test for missing substring
START_TEST(test_strstr_not_found) {
  const char *haystack = "Hello, world!";
  const char *needle = "foo";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_null(result); 
}
END_TEST

// custom solution test for empty needle
START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Hello, world!";
  const char *needle = "";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(result, haystack); 
}
END_TEST

// custom solution test for needle = haystack
START_TEST(test_strstr_needle_eq_haystack) {
  const char *haystack = "Hello";
  const char *needle = "Hello";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(result, haystack);  
}
END_TEST

/* comparative tests */

// finding an existing substring
START_TEST(test_strstr_basic_match) {
    const char *haystack = "Hello, world!";
    const char *needle = "world";
    // cppcheck-suppress unreadVariable
    const char *original_result = strstr(haystack, needle);  
    const char *custom_result = s21_strstr(haystack, needle);
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_int_eq(original_result - haystack, custom_result - haystack);
}
END_TEST

// finding the first existing substring
START_TEST(test_strstr_multiple_matches) {
    const char *haystack = "abcabc";
    const char *needle = "abc";
    
    const char *original_result = strstr(haystack, needle);
    const char *custom_result = s21_strstr(haystack, needle);
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_int_eq(original_result - haystack, custom_result - haystack);
}
END_TEST

// needle is longer than haystack
START_TEST(test_strstr_needle_longer) {
    const char *haystack = "short";
    const char *needle = "verylongneedle";
    // cppcheck-suppress unreadVariable
    const char *original_result = strstr(haystack, needle);
    const char *custom_result = s21_strstr(haystack, needle);
    
    ck_assert_ptr_null(custom_result);
}
END_TEST

// empty lines
START_TEST(test_strstr_empty_strings) {
    const char *original_result = strstr("", "");
    const char *custom_result = s21_strstr("", "");
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_ptr_eq(original_result, custom_result);
}
END_TEST

// empty needle
START_TEST(test_strstr_empty_needle) {
    const char *haystack = "abc";
    
    const char *original_result = strstr(haystack, "");
    const char *custom_result = s21_strstr(haystack, "");
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_ptr_eq(original_result, custom_result);
}
END_TEST

// lack of entry
START_TEST(test_strstr_no_match) {
    const char *haystack = "abc";
    const char *needle = "xyz";
    // cppcheck-suppress unreadVariable
    const char *original_result = strstr(haystack, needle); 
    const char *custom_result = s21_strstr(haystack, needle); 
    
    ck_assert_ptr_null(custom_result);
}
END_TEST

// partial match
START_TEST(test_strstr_partial_match) {
    const char *haystack = "mississippi";
    const char *needle = "issi";
    
    const char *original_result = strstr(haystack, needle);
    const char *custom_result = s21_strstr(haystack, needle);
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_int_eq(original_result - haystack, custom_result - haystack);
}
END_TEST

// duplicate characters
START_TEST(test_strstr_repeated_chars) {
    const char *haystack = "aaaaa";
    const char *needle = "aa";
    
    const char *original_result = strstr(haystack, needle);
    const char *custom_result = s21_strstr(haystack, needle);
    
    ck_assert_ptr_nonnull(custom_result);
    ck_assert_int_eq(original_result - haystack, custom_result - haystack);
}
END_TEST

// test set
Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc = tcase_create("Core");

  // add tests to test-case
  tcase_add_test(tc, test_strstr_found);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_needle_eq_haystack);
  tcase_add_test(tc, test_strstr_basic_match);
  tcase_add_test(tc, test_strstr_multiple_matches);
  tcase_add_test(tc, test_strstr_needle_longer);
  tcase_add_test(tc, test_strstr_empty_strings);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_no_match);
  tcase_add_test(tc, test_strstr_partial_match);
  tcase_add_test(tc, test_strstr_repeated_chars);

  suite_add_tcase(s, tc);
  return s;
}