#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./suites.h"

int main(void) {
    int number_failed;
    Suite *s_error = s21_strerror_suite();  // Существующий Suite для strerror
    Suite *s_strstr = s21_strstr_suite();   // Новый Suite для strstr

    SRunner *sr = srunner_create(s_error);  // Инициализация с первым Suite
    srunner_add_suite(sr, s_strstr);        // Добавляем Suite для strstr

    // Настройка лог-файла (как у вас было)
    const char *suite = getenv("CK_RUN_SUITE");
    if (suite && strlen(suite) > 0) {
        char logname[128];
        snprintf(logname, sizeof(logname), "../%s.log", suite);
        srunner_set_log(sr, logname);
    } else {
        srunner_set_log(sr, "../test.log");
    }

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}