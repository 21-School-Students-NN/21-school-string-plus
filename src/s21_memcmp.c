#include "../headers/s21_string.h"

/**
 * @brief compares the first n bytes of str1 and str2.
 * @return an integer less than, equal to, or greater than zero if the first n
 bytes of s1 is found, respectively, to be less than, to match, or be greater
 than the first n bytes of s2.
 *
 * @version 1.0
 * @date June 12, 2025
 * @author Amfir (s21: tyananai)
 */

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *string_1 = (unsigned char *)str1;
  const unsigned char *string_2 = (unsigned char *)str2;

  for (s21_size_t i = 0; i < n; i++) {
    if (string_1[i] != string_2[i]) {
      return string_1[i] - string_2[i];
    }
  }

  return 0;
}