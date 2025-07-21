#include "../headers/s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *char_str = (const char *)str;
  char have_find = 0;

  while (*char_str && !have_find && n--) {
    if (c == (unsigned char)*char_str) {
      have_find = 1;
    } else {
      ++char_str;
    }
  }

  return have_find ? (char *)char_str : S21_NULL;
}
