#include <math.h>
#include <stdarg.h>

#include "../headers/s21_string.h"

#define BUFFER_SIZE 1024
#define MINUS 1
#define PLUS 2
#define SPACE 4

void config_init(format_config *conf) {
  conf->width = 0;
  conf->precision = -1;
  conf->flags = 0;
  conf->length = ' ';
}

const char *format_parse(format_config *conf, const char *f) {
  while (*f == '-' || *f == '+' || *f == ' ') {
    if (*f == '-') conf->flags |= MINUS;  // flag '-'
    if (*f == '+') conf->flags |= PLUS;   // flag '+'
    if (*f == ' ') conf->flags |= SPACE;  // flag ' '
    f++;
  }

  // processing of width
  if (*f >= '0' && *f <= '9') {
    conf->width = str_to_int(f);
    while (*f >= '0' && *f <= '9') f++;
  }

  // processing of precision
  if (*f == '.') {
    f++;
    conf->precision = str_to_int(f);
    while (*f >= '0' && *f <= '9') f++;
  }

  // processing of length
  if (*f == 'l' || *f == 'h') {
    conf->length = *f;
    f++;
  }
  return f;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[BUFFER_SIZE];
  char *ptr = str;
  const char *f = format;

  while (*f) {
    if (*f == '%') {
      f++;
      if (*f == '%') {
        *ptr++ = '%';
      } else {
        format_config conf;
        config_init(&conf);
        f = format_parse(&conf, f);

        // processing of specifiers
        switch (*f) {
          case 'c': {
            char c = (char)va_arg(args, int);
            buffer[0] = c;
            buffer[1] = '\0';
            ptr += add_substring(ptr, buffer, conf);
            break;
          }
          case 'd': {
            if (conf.length == 'h') {
              short d = (short)va_arg(args, int);
              int_to_str((long)d, buffer, conf.precision, conf.flags);
            } else if (conf.length == 'l') {
              long d = va_arg(args, long);
              int_to_str(d, buffer, conf.precision, conf.flags);
            } else {
              int d = va_arg(args, int);
              int_to_str((long)d, buffer, conf.precision, conf.flags);
            }
            ptr += add_substring(ptr, buffer, conf);
            break;
          }
          case 'u': {
            if (conf.length == 'h') {
              short unsigned u = (short unsigned)va_arg(args, int);
              uint_to_str((long unsigned)u, buffer, conf.precision);
            } else if (conf.length == 'l') {
              long unsigned u = va_arg(args, long unsigned);
              uint_to_str(u, buffer, conf.precision);
            } else {
              unsigned int u = va_arg(args, unsigned int);
              uint_to_str((long unsigned)u, buffer, conf.precision);
            }
            ptr += add_substring(ptr, buffer, conf);
            break;
          }
          case 'f': {
            double fval = va_arg(args, double);
            float_to_str(fval, buffer, conf.precision >= 0 ? conf.precision : 6,
                         conf.flags);
            ptr += add_substring(ptr, buffer, conf);
            break;
          }
          case 's': {
            char *s = va_arg(args, char *);
            if (conf.precision >= 0) s[conf.precision] = '\0';
            ptr += add_substring(ptr, s, conf);
            break;
          }
          default: {
            break;
          }
        }
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

void int_to_str(long n, char *str, int precision, int flags) {
  int i = 0, sign = n;
  if (sign < 0) n = -n;  // processing the negative n
  int len = 0;
  do {
    str[i++] = n % 10 + '0';
    n /= 10;
    len++;
  } while (n > 0);
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

void uint_to_str(unsigned long n, char *str, int precision) {
  int len = 0;
  int i = 0;
  do {
    str[i++] = n % 10 + '0';
    n /= 10;
    len++;
  } while (n > 0);
  while (len++ < precision) str[i++] = '0';
  str[i] = '\0';
  // reversing string (swapping the chars)
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

void float_to_str(long double f, char *str, int precision, int flags) {
  long double int_part;   // = (long)f;
  long double frac_part;  // = f - (long double)int_part;
  frac_part = modfl(f, &int_part);

  // turning int_part into string
  int_to_str((long)int_part, str, -1, flags);
  int len = s21_strlen(str);

  // adding the fractional part
  if (precision > 0) {
    str[len] = '.';
    for (int i = 0; i < precision; i++) {
      frac_part *= 10;
      str[len + 1 + i] = (int)frac_part + '0';
      frac_part -= (int)frac_part;
    }
  }
}

int add_substring(char *str, char *buffer, format_config conf) {
  int len = s21_strlen(buffer);
  int minus_flag = conf.flags & MINUS;
  if (!minus_flag)
    for (int i = len; i < conf.width; i++) *str++ = ' ';
  s21_strncpy(str, buffer, len);
  if (minus_flag)
    for (int i = len; i < conf.width; i++) str[i] = ' ';
  return len < conf.width ? conf.width : len;
}