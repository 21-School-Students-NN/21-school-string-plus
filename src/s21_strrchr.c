#include <string.h>
// TODO: remove string.h and replace strlen when s21_strlen will be implemented
#include "../headers/s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char *)str;  // Cast to remove const
    }
    str++;
  }
  // Check the null terminator itself
  if ((char)c == '\0') {
    result = (char *)str;
  }
  return result;  // Character not found
}
