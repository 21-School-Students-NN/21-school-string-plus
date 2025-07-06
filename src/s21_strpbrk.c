#include "../headers/s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *a;  // from `accept`

  for (; *str1 != '\0'; ++str1)
    for (a = str2; *a != '\0'; ++a)
      if (*str1 == *a) return (char *)str1;

  return S21_NULL;
}