#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./suites.h"

int main(void) {
  int number_failed;
  Suite *s = s21_strerror_suite();
  SRunner *sr = srunner_create(s);

  srunner_add_suite(sr, s21_strstr_suite());

  // Check for CK_RUN_SUITE and set a custom log file
  const char *suite = getenv("CK_RUN_SUITE");
  if (suite && strlen(suite) > 0) {
    char logname[128];
    snprintf(logname, sizeof(logname), "../%s.log", suite);
    srunner_set_log(sr, logname);
  } else {
    srunner_set_log(sr, "../test.log");
  }

  // srunner_set_log (sr, "../test.log");
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}