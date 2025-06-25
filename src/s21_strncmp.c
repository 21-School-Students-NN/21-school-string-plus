#include "../headers/s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (n--) {
    unsigned char u1 = (unsigned char)*str1++;
    unsigned char u2 = (unsigned char)*str2++;
    if (u1 != u2) return u1 - u2;
    if (u1 == '\0') return 0;
  }
  return 0;
}