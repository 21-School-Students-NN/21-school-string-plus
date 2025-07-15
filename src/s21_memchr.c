#include <string.h>
// TODO: remove string.h and replace strlen when s21_strlen will be implemented
#include "../headers/s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == S21_NULL) return S21_NULL;
  const char *char_str = (const char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    if (char_str[i] == '\0') return S21_NULL;
    if (c == (unsigned char)char_str[i]) return (char *)&char_str[i];
  }
  return S21_NULL;
}
