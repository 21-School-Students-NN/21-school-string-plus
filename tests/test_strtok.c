#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

#define ALICE_TEXT                                                                 \
  "Alice was beginning to get very tired of sitting by her sister on the "         \
  "bank, and of having nothing to do: once or twice she had peeped into the "      \
  "book her sister was reading, but it had no pictures or conversations in "       \
  "it, “and what is the use of a book,” thought Alice “without pictures or " \
  "conversations?”"

#define ALICE_SIZE 384

// Test 1: Basic tokenization with space delimiter
START_TEST(test_strtok_space_delim) {
  char buffer1[ALICE_SIZE] = {0}, buffer2[ALICE_SIZE] = {0};
  strcpy(buffer1, ALICE_TEXT);
  strcpy(buffer2, ALICE_TEXT);

  char *token1 = strtok(buffer1, " ");
  char *token2 = s21_strtok(buffer2, " ");

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    ck_assert_mem_eq(buffer1, buffer2, ALICE_SIZE);

    token1 = strtok(NULL, " ");
    token2 = s21_strtok(S21_NULL, " ");
  }

  // Verify both return NULL at the end
  ck_assert_ptr_null(token1);
  ck_assert_ptr_null(token2);
}
END_TEST

// Test 2: Comma and punctuation delimiters
START_TEST(test_strtok_comma_delim) {
  char buffer1[ALICE_SIZE] = {0}, buffer2[ALICE_SIZE] = {0};
  strcpy(buffer1, ALICE_TEXT);
  strcpy(buffer2, ALICE_TEXT);

  char *token1 = strtok(buffer1, ",:”");
  char *token2 = s21_strtok(buffer2, ",:”");

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    ck_assert_mem_eq(buffer1, buffer2, ALICE_SIZE);

    token1 = strtok(NULL, ",:”");
    token2 = s21_strtok(S21_NULL, ",:”");
  }
}
END_TEST

// Test 3: Mixed delimiters with NULL calls
START_TEST(test_strtok_mixed_delims_with_null) {
  char buffer1[ALICE_SIZE] = {0}, buffer2[ALICE_SIZE] = {0};
  strcpy(buffer1, ALICE_TEXT);
  strcpy(buffer2, ALICE_TEXT);

  const char *delims = " ,.:”";
  char *token1 = strtok(buffer1, delims);
  char *token2 = s21_strtok(buffer2, delims);

  int iteration = 0;
  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    ck_assert_mem_eq(buffer1, buffer2, strlen(ALICE_TEXT) + 1);

    // Every 3rd call, change delimiters
    const char *current_delims = ((iteration++) % 3 == 0) ? "h" : delims;
    token1 = strtok(NULL, current_delims);
    token2 = s21_strtok(S21_NULL, current_delims);
  }
}
END_TEST

// Test 4: Edge case - empty string
START_TEST(test_strtok_empty_string) {
  const char empty_str[] = "";
  char buffer1[ALICE_SIZE] = {0}, buffer2[ALICE_SIZE] = {0};
  strcpy(buffer1, empty_str);
  strcpy(buffer2, empty_str);

  char *token1 = strtok(buffer1, " ");
  char *token2 = s21_strtok(buffer2, " ");

  ck_assert_ptr_null(token1);
  ck_assert_ptr_null(token2);
  ck_assert_mem_eq(buffer1, buffer2, ALICE_SIZE);
}
END_TEST

// Test 5: No delimiters found
START_TEST(test_strtok_no_delims) {
  const char no_delims[] = "ThisStringHasNoDelimiters";
  char buffer1[64] = {0}, buffer2[64] = {0};
  strcpy(buffer1, no_delims);
  strcpy(buffer2, no_delims);

  char *token1 = strtok(buffer1, " ,.");
  char *token2 = s21_strtok(buffer2, " ,.");

  ck_assert_str_eq(token1, token2);
  ck_assert_mem_eq(buffer1, buffer2, strlen(no_delims) + 1);

  token1 = strtok(NULL, " ,.");
  token2 = s21_strtok(S21_NULL, " ,.");
  ck_assert_ptr_null(token1);
  ck_assert_ptr_null(token2);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s = suite_create("strtok");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strtok_space_delim);
  tcase_add_test(tc, test_strtok_comma_delim);
  tcase_add_test(tc, test_strtok_mixed_delims_with_null);
  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_no_delims);

  suite_add_tcase(s, tc);
  return s;
}