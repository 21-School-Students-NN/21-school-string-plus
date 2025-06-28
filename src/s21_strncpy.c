#include "../headers/s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0, j = 0;

  while (i < n) {
    if (src[j] != '\0')
      dest[i++] = src[j++];
    else
      dest[i++] = src[j];
  }

  return dest;
}