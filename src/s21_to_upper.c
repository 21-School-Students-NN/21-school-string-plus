#include <stdlib.h>

#include "../headers/s21_string.h"

void *s21_to_upper(const char *str) {
  char *dest = S21_NULL;
  int len = 0;
  if (str) {
    len = s21_strlen(str);
    dest = (char *)malloc(len + 1);
  }
  if (dest) {
    for (int i = 0; i < len; ++i) {
      if (str[i] >= 'a' && str[i] <= 'z')
        dest[i] = str[i] - 32;
      else
        dest[i] = str[i];
    }
    dest[len] = '\0';
  }
  return (void *)dest;
}