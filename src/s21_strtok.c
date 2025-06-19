#include <string.h>

#include "../headers/s21_string.h"

static char *olds;

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
static s21_size_t s21_strspn(const char *s, const char *accept) {
  const char *p;
  const char *a;
  s21_size_t count = 0;

  for (p = s; *p != '\0'; ++p) {
    for (a = accept; *a != '\0'; ++a)
      if (*p == *a) break;
    if (*a == '\0')
      return count;
    else
      ++count;
  }

  return count;
}

/* Find the first occurrence in S of any character in ACCEPT.  */
#if 0
static char *s21_strpbrk(const char *s, const char *accept) {
  while (*s != '\0') {
    const char *a = accept;
    while (*a != '\0')
      if (*a++ == *s) return (char *)s;
    ++s;
  }

  return S21_NULL;
}
#endif

#if 0
static char *s21_strpbrk(const char *s1, const char *s2) {
  const char *c = s2;
  if (!*s1) return (char *)S21_NULL;

  while (*s1) {
    for (c = s2; *c; c++) {
      if (*s1 == *c) break;
    }
    if (*c) break;
    s1++;
  }

  if (*c == '\0') s1 = S21_NULL;

  return (char *)s1;
}
#endif

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the last string strtok() was called with is
   used.  For example:
        char s[] = "-abc-=-def";
        x = strtok(s, "-");		// x = "abc"
        x = strtok(NULL, "-=");		// x = "def"
        x = strtok(NULL, "=");		// x = NULL
                // s = "abc\0=-def\0"
*/
char *s21_strtok(char *str, const char *delim) {
  char *token;

  if (str == S21_NULL) str = olds;

  /* Scan leading delimiters.  */
  str += s21_strspn(str, delim);
  if (*str == '\0') {
    olds = str;
    return S21_NULL;
  }

  /* Find the end of the token.  */
  token = str;
  str = strpbrk(token, delim);
  if (str == S21_NULL) /* This token finishes the string.  */
    olds = strchr(token, '\0');
  else {
    /* Terminate the token and make OLDS point past it.  */
    *str = '\0';
    olds = str + 1;
  }
  return token;
}