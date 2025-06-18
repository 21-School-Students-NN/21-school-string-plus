#include <string.h>

#include "../headers/s21_string.h"

// TODO: after creating memcpy & strlen add `s21_` prefix

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
#define strnul(s) (s + strlen(s))

  memcpy(strnul(dest), src, (strlen(src) < n) ? strlen(src) : n);
  return dest;
}