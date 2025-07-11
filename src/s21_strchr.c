#include <s21_string.h>
// TODO: remove string.h and replace strlen when s21_strlen will be implemented
#include "../headers/s21_string.h"

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == (char)c) {
      return (char *)str;  // Cast to remove const
    }
    str++;
  }
  // Check the null terminator itself
  if ((char)c == '\0') {
    return (char *)str;
  }
  return S21_NULL;  // Character not found
}
