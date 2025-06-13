#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/s21_string.h"
#include "../headers/s21_errno.h"
#include "./suites.h"


START_TEST(test_strerror_known_errors) {
    ck_assert_str_eq(s21_strerror(0), strerror(0));
    ck_assert_str_eq(s21_strerror(1), strerror(1));
    ck_assert_str_eq(s21_strerror(2), strerror(2));
    ck_assert_str_eq(s21_strerror(ENOENT), strerror(ENOENT));
    ck_assert_str_eq(s21_strerror(EACCES), strerror(EACCES));
}
END_TEST

START_TEST(test_strerror_unknown_errors) {
    ck_assert_str_eq(s21_strerror(-1), strerror(-1));
    ck_assert_str_eq(s21_strerror(9999), strerror(9999));
    ck_assert_str_eq(s21_strerror(S21_ERRLIST_LEN + 1), strerror(S21_ERRLIST_LEN + 1));
}
END_TEST

START_TEST(test_strerror_integration) {
    for (int err = -200; err < 200; err++) {
        const char *sys_str = strerror(err);
        const char *our_str = s21_strerror(err);
        ck_assert_msg(strcmp(sys_str, our_str) == 0,
                     "Error %d: system='%s', our='%s'", err, sys_str, our_str);
    }
}
END_TEST

Suite *s21_strerror_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("strerror");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_strerror_known_errors);
    tcase_add_test(tc_core, test_strerror_unknown_errors);
    tcase_add_test(tc_core, test_strerror_integration);
    suite_add_tcase(s, tc_core);

    return s;
}