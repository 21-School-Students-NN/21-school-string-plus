#include <stdlib.h>

#include "../headers/s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *dest = S21_NULL;
  if (src && trim_chars) {
    const char *start = src;
    while (start && s21_strchr(trim_chars, *start)) start++;
    const char *end = src + s21_strlen(src) - 1;
    while (end >= start && s21_strchr(trim_chars, *end)) end--;
    s21_size_t len = end >= start ? (end - start + 1) : 0;
    dest = (char *)malloc(len + 1);
    if (dest) {
      s21_strncpy(dest, start, len);
      dest[len] = '\0';
    }
  }
  return dest;
}