#include <check.h>
#include <string.h>
#include "../headers/s21_string.h"

// Test case 1: Basic string
START_TEST(test_strlen_basic) {
    const char *str = "Hello, world!";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 2: Empty string
START_TEST(test_strlen_empty) {
    const char *str = "";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 3: String with spaces
START_TEST(test_strlen_spaces) {
    const char *str = "    ";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 4: String with special characters
START_TEST(test_strlen_special_chars) {
    const char *str = "!@#$%^&*()";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 5: Long string
START_TEST(test_strlen_long_string) {
    const char *str = "This is a very long string to test if s21_strlen handles long inputs correctly.";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 6: String with null terminator in the middle (undefined behavior, but should not crash)
START_TEST(test_strlen_null_middle) {
    const char *str = "Hello\0 World";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// Test case 7: NULL input (undefined behavior, but should not crash)
START_TEST(test_strlen_null_input) {
    const char *str = NULL;
    if (str) {
        ck_assert_int_eq(s21_strlen(str), strlen(str));
    }
}
END_TEST

// Create test suite
Suite *s21_strlen_suite(void) {
    Suite *suite = suite_create("strlen");
    TCase *tc = tcase_create("Core");

    // Add test cases
    tcase_add_test(tc, test_strlen_basic);
    tcase_add_test(tc, test_strlen_empty);
    tcase_add_test(tc, test_strlen_spaces);
    tcase_add_test(tc, test_strlen_special_chars);
    tcase_add_test(tc, test_strlen_long_string);
    tcase_add_test(tc, test_strlen_null_middle);
    tcase_add_test(tc, test_strlen_null_input);

    suite_add_tcase(suite, tc);
    return suite;
}