#include <stdarg.h>

#include "../headers/s21_string.h"

#define BUFFER_SIZE 1024
#define MINUS 1
#define PLUS 2
#define SPACE 4

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[BUFFER_SIZE];
  char *ptr = str;
  const char *f = format;

  while (*f) {
    if (*f == '%') {
      f++;
      int width = 0;
      int precision = -1;
      int flags = 0;

      // processing of flags
      while (*f == '-' || *f == '+' || *f == ' ') {
        if (*f == '-') flags |= MINUS;  // flag '-'
        if (*f == '+') flags |= PLUS;   // flag '+'
        if (*f == ' ') flags |= SPACE;  // flag ' '
        f++;
      }

      // processing of width
      if (*f >= '0' && *f <= '9') {
        width = str_to_int(f);
        while (*f >= '0' && *f <= '9') f++;
      }

      // processing of precision
      if (*f == '.') {
        f++;
        precision = str_to_int(f);
        while (*f >= '0' && *f <= '9') f++;
      }

      // processing of specifiers
      switch (*f) {
        case 'c': {
          char c = (char)va_arg(args, int);
          *ptr++ = c;
          break;
        }
        case 'd': {
          int d = va_arg(args, int);
          int_to_str(d, buffer, precision, flags);
          ptr += add_substring(ptr, buffer, width, flags & MINUS);
          break;
        }
        case 'f': {
          double fval = va_arg(args, double);
          float_to_str(fval, buffer, precision >= 0 ? precision : 6, flags);
          ptr += add_substring(ptr, buffer, width, flags & MINUS);
          break;
        }
        case 's': {
          char *s = va_arg(args, char *);
          if (precision >= 0) s[precision] = '\0';
          ptr += add_substring(ptr, buffer, width, flags & MINUS);
          break;
        }
        case 'u': {
          unsigned int u = va_arg(args, unsigned int);
          int_to_str(u, buffer, precision, flags);
          ptr += add_substring(ptr, buffer, width, flags & MINUS);
          break;
        }
        case '%': {
          *ptr++ = '%';
          break;
        }
        default:
          break;
      }
    } else {
      *ptr++ = *f;
    }
    f++;
  }

  *ptr = '\0';  // ending the string
  va_end(args);
  return ptr - str;  // return the length of the string
}

int str_to_int(const char *str) {
  int result = 0;  // resulting number
  int sign = 1;    // sign of the number

  // missing the space chars in the begginning of *str
  while (*str == ' ') {
    str++;
  }

  // processing of sign
  if (*str == '-') {
    sign = -1;  // negative number
    str++;
  } else if (*str == '+') {
    str++;  // positive number
  }

  // turning chars in digits
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');  // rewright the result
    str++;
  }

  return sign * result;  // returning the result
}

void int_to_str(int n, char *str, int precision, int flags) {
  int i = 0, sign = n;
  if (sign < 0) n = -n;  // processing the negative n
  int len = 0;
  while (n > 0) {
    str[i++] = n % 10 + '0';
    n /= 10;
    len++;
  }
  while (len++ < precision) str[i++] = '0';
  if (sign < 0)
    str[i++] = '-';
  else if (flags & PLUS)
    str[i++] = '+';
  else if (flags & SPACE)
    str[i++] = ' ';
  str[i] = '\0';

  // reversing string (swapping the chars)
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

void float_to_str(double f, char *str, int precision, int flags) {
  int int_part = (int)f;
  double frac_part = f - (double)int_part;

  // turning int_part into string
  int_to_str(int_part, str, -1, flags);
  int len = s21_strlen(str);

  // adding the fractional part
  if (precision > 0) {
    str[len] = '.';
    len++;
    while ((precision--) > 0) frac_part *= 10;  // multiply to 10^precision
    int_to_str((int)frac_part, str + len, -1, 0);
  }
}

int add_substring(char *str, char *buffer, int width, int minus_flag) {
  int len = s21_strlen(buffer);
  if (!minus_flag)
    for (int i = len; i < width; i++) *str++ = ' ';
  s21_strncpy(str, buffer, len);
  if (minus_flag)
    for (int i = len; i < width; i++) *str++ = ' ';
  return len < width ? width : len;
}