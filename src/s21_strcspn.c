#include "../headers/s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    const char *s; // from `source`
    const char *r; // from reject
    s21_size_t count = 0;
  
    for (s = str1; *s != '\0'; ++s) {
      for (r = str2; *r != '\0'; ++r)
        if (*s == *r) break;
      if (*r == '\0')
        ++count;
      else
        return count;
    }
  
    return count;
}