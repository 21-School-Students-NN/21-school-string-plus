// TODO: remove <string.h> call from file
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

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the last string strtok() was called with is
   used.  For example:
        char s[] = "-abc-=-def";
        x = strtok(s, "-");		// x = "abc"
        x = strtok(NULL, "-=");		// x = "def"
        x = strtok(NULL, "=");		// x = NULL
                // s = "abc\0=-def\0"
*/

// TODO: add `s21_` prefix to `strpbrk` when it will be done

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