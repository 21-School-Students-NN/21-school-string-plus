#include <s21_string.h>

#include "../headers/s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_end = dest + s21_strlen(dest);
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest_end[i] = src[i];
  }

  dest_end[i] = '\0';

  return dest;
}
