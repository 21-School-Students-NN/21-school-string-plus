#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

// #include "../headers/s21_string.h"

#include "./test_strerror.c"

int main(void) {
    int number_failed;
    Suite *s = strerror_suite();
    SRunner *sr = srunner_create(s);

    srunner_set_log (sr, "test.log");
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}