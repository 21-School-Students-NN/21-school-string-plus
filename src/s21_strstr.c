#include "../headers/s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  // validation
  if (needle == S21_NULL) {
    return S21_NULL;
  }
  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (1) {
    const char *h = haystack;
    const char *n = needle;

    // comment about what it does :)
    for (; *h && *n && (*h == *n); h++, n++);

    if (*n == '\0' || !(*haystack)) break;
    haystack++;
  }

  return *haystack ? (char *)haystack : S21_NULL;
}