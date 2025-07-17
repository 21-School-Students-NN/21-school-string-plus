#include <stdlib.h>

#include "../headers/s21_string.h"
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *dest = S21_NULL;
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;
  s21_size_t lenstr = s21_strlen(str);
  s21_size_t lensrc = s21_strlen(src);
  if (lensrc >= start_index) {
    dest = (char *)malloc(lenstr + lensrc + 1);
    if (dest) {
      s21_strncpy(dest, src, start_index);
      s21_strncpy(dest + start_index, str, lenstr);
      s21_strncpy(dest + start_index + lenstr, src + start_index,
                  lensrc - start_index);
      dest[lenstr + lensrc] = '\0';
    }
  }
  return dest;
}