#include <stdio.h>

#include "../s21_string.h"

/**
 * copies byte by byte from src to dest
 */

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;
  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}