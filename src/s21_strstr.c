#include "../headers/s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (needle == S21_NULL || haystack == S21_NULL) {
    return S21_NULL;
  }

  // Если needle пустая строка, вернём haystack (по стандарту)
  if (*needle == '\0') {
    return (char *)haystack;
  }

  // Проходим по haystack
  for (; *haystack; haystack++) {
    const char *h = haystack;
    const char *n = needle;

    // Сравниваем символы, пока не кончится needle или не будет несоответствия
    while (*h && *n && (*h == *n)) {
      h++;
      n++;
    }

    // Если дошли до конца needle — значит, нашли подстроку
    if (*n == '\0') {
      return (char *)haystack;
    }
  }

  // Не нашли
  return S21_NULL;
}