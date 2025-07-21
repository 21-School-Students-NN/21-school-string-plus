#include <s21_string.h>

#include "../headers/s21_string.h"

static char *olds;

/**
 * @brief get length of a prefix substring
 * @return the `s21_strspn()` function returns the number of bytes in the
 * initial segment of `str` which consist only of bytes from `accept`.
 *
 * @version 1.0
 * @date June 19, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
static s21_size_t s21_strspn(const char *str, const char *accept) {
  const char *p;
  const char *a;
  s21_size_t count = 0;

  for (p = str; *p != '\0'; ++p) {
    for (a = accept; *a != '\0'; ++a)
      if (*p == *a) break;
    if (*a == '\0')
      return count;
    else
      ++count;
  }

  return count;
}

char *s21_strtok(char *str, const char *delim) {
  char *token;

  if (str == S21_NULL) str = olds;

  /* Scan leading delimiters.  */
  str += s21_strspn(str, delim);
  if (*str == '\0') {
    olds = str;
    return S21_NULL;
  }

  /* Find the end of the token. */
  token = str;
  str = s21_strpbrk(token, delim);
  if (str == S21_NULL) /* This token finishes the string.  */
    olds = s21_strchr(token, '\0');
  else {
    /* Terminate the token and make OLDS point past it.  */
    *str = '\0';
    olds = str + 1;
  }
  return token;
}
