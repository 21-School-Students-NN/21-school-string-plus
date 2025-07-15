#include "../headers/s21_sscanf.h"

#include "../headers/s21_string.h"

/**
 * there is a comment about table work
 */
static int parse_int(const char **, const fmt_token_t *, va_list *);
static int parse_string(const char **, const fmt_token_t *, va_list *);
static int parse_char(const char **, const fmt_token_t *, va_list *);
static int parse_uint(const char **, const fmt_token_t *, va_list *);
static int parse_float(const char **, const fmt_token_t *, va_list *);
static int parse_octal(const char **, const fmt_token_t *, va_list *);
static int parse_pointer(const char **, const fmt_token_t *, va_list *);
static int parse_count(const char **, const fmt_token_t *, va_list *);

/**
 * different functions worked outside from table
 */
static void init_fmt_token(fmt_token_t *tok);
static int format_parsing(const char **format, fmt_token_t *tok);
static int char_to_digit(char c, int base);

int s21_sscanf(const char *str, const char *format, ...) {
  if (str == S21_NULL || format == S21_NULL || *str == '\0') {
    return S21_EOF;
  }
  dispatch_entry_t dispatch_table[] = {
      {'c', parse_char},   {'d', parse_int},     {'i', parse_int},
      {'e', parse_float},  {'E', parse_float},   {'f', parse_float},
      {'g', parse_float},  {'G', parse_float},   {'o', parse_octal},
      {'s', parse_string}, {'u', parse_uint},    {'x', parse_uint},
      {'X', parse_uint},   {'p', parse_pointer}, {'n', parse_count}};
  const int dispatch_table_size =
      sizeof(dispatch_table) / sizeof(dispatch_table[0]);
  va_list args;
  va_start(args, format);
  const char **str_ptr = &str;
  const char **format_ptr = &format;
  fmt_token_t tok;
  init_fmt_token(&tok);
  tok.start_ptr = str;
  int counter = 0, flag = 1;
  while (flag && format_parsing(format_ptr, &tok)) {
    while (isspace((unsigned char)**str_ptr)) (*str_ptr)++;
    if (tok.specifier && tok.specifier != '%') {
      for (int i = 0; i < dispatch_table_size; i++) {
        if (dispatch_table[i].specifier == tok.specifier) {
          int res = dispatch_table[i].func(str_ptr, &tok, &args);
          if (res == 0 && !tok.suppress) {
            flag = 0;
          } else {
            counter += res;
          }
        }
      }
    } else if (tok.literal || tok.specifier == '%') {
      if (**str_ptr == tok.literal) {
        (*str_ptr)++;
      } else {
        flag = 0;
      }
    }
  }
  va_end(args);
  return counter;
}

static int format_parsing(const char **format, fmt_token_t *tok) {
  init_fmt_token(tok);
  const char *p = *format;
  int success = 1;
  while (*p == ' ' || *p == '\t' || *p == '\n') p++;
  if (*p == '\0') {
    success = 0;
  } else if (*p == '%') {
    p++;
    if (*p == '%') {
      tok->literal = '%';
      p++;
    } else {
      if (*p == '*') {
        tok->suppress = 1;
        p++;
      }
      while (isdigit((unsigned char)*p)) {
        tok->width = tok->width * 10 + (*p - '0');
        p++;
      }
      if (p[0] == 'h' && p[1] == 'h') {
        tok->length_modifier = LEN_HH;
        p += 2;
      } else if (p[0] == 'h') {
        tok->length_modifier = LEN_H;
        p++;
      } else if (p[0] == 'l' && p[1] == 'l') {
        tok->length_modifier = LEN_LL;
        p += 2;
      } else if (p[0] == 'l') {
        tok->length_modifier = LEN_L;
        p++;
      } else if (p[0] == 'L') {
        tok->length_modifier = LEN_LD;
        p++;
      }
      if (*p != '\0' && s21_strchr("diouxXfFeEgGaAcspn", *p)) {
        tok->specifier = *p;
        p++;
      } else {
        success = 0;
      }
    }
  } else {
    tok->literal = *p;
    p++;
  }
  *format = p;
  return success;
}

static void init_fmt_token(fmt_token_t *tok) {
  if (tok) {
    tok->suppress = 0;
    tok->width = 0;
    tok->length_modifier = LEN_NONE;
    tok->specifier = '\0';
    tok->literal = '\0';
  }
}

static int parse_int(const char **str, const fmt_token_t *tok, va_list *args) {
  long long value = 0;
  int sign = 1, base = 10, chars_read = 0, res = 1,
      max_width = tok->width ? tok->width : INT_MAX;
  while (isspace((unsigned char)**str)) (*str)++;
  if (**str == '-') {
    sign = -1;
    (*str)++;
    chars_read++;
  } else if (**str == '+') {
    (*str)++;
    chars_read++;
  }
  if (tok->specifier == 'i' || tok->specifier == 'x' || tok->specifier == 'X' ||
      tok->specifier == 'o') {
    if (**str == '0') {
      (*str)++;
      chars_read++;
      if ((**str == 'x' || **str == 'X') && tok->specifier != 'o') {
        base = 16;
        (*str)++;
        chars_read++;
      } else {
        base = 8;
      }
    }
  }
  int digit_count = 0;
  int flag = 1;
  while (flag && chars_read < max_width) {
    char c = **str;
    int digit = char_to_digit(c, base);
    if (digit < 0) {
      flag = 0;
    } else {
      value = value * base + digit;
      (*str)++;
      chars_read++;
      digit_count++;
    }
  }
  if (digit_count == 0) {
    res = 0;
  } else {
    value *= sign;
    if (!tok->suppress) {
      if (tok->length_modifier == LEN_HH) {
        *va_arg(*args, char *) = (char)value;
      } else if (tok->length_modifier == LEN_H) {
        *va_arg(*args, short *) = (short)value;
      } else if (tok->length_modifier == LEN_L) {
        *va_arg(*args, long *) = (long)value;
      } else if (tok->length_modifier == LEN_LL) {
        *va_arg(*args, long long *) = value;
      } else {
        *va_arg(*args, int *) = (int)value;
      }
    } else {
      res = 0;
    }
  }
  return res;
}

static int parse_string(const char **str, const fmt_token_t *tok,
                        va_list *args) {
  int res = 0, len = 0, max_width = tok->width ? tok->width : INT_MAX;
  while (isspace((unsigned char)**str)) (*str)++;
  if (tok->suppress) {
    while (**str && !isspace((unsigned char)**str) && len < max_width) {
      (*str)++;
      len++;
    }
  } else {
    char *dest = va_arg(*args, char *);
    while (**str && !isspace((unsigned char)**str) && len < max_width) {
      *dest++ = **str;
      (*str)++;
      len++;
    }
    *dest = '\0';
    res = len > 0 ? 1 : 0;
  }
  return res;
}

static int parse_char(const char **str, const fmt_token_t *tok, va_list *args) {
  int width = tok->width ? tok->width : 1;
  int count = 0, res = 0;
  if (!tok->suppress) {
    char *dest = va_arg(*args, char *);
    while (count < width && **str) {
      *dest++ = **str;
      (*str)++;
      count++;
    }
    res = 1;
  } else {
    while (count < width && **str) {
      (*str)++;
      count++;
    }
  }
  return res;
}

static int parse_uint(const char **str, const fmt_token_t *tok, va_list *args) {
  unsigned long long value = 0;
  int base = 10, chars_read = 0, res = 0,
      max_width = tok->width ? tok->width : INT_MAX;
  if (tok->specifier == 'o') {
    base = 8;
  } else if (tok->specifier == 'x' || tok->specifier == 'X') {
    base = 16;
    if (max_width > 2 && **str == '0' &&
        (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
      *str += 2;
      chars_read += 2;
      max_width -= 2;
    }
  }
  int digit = 0;
  while (chars_read < max_width && digit >= 0) {
    char c = **str;
    digit = -1;
    if (c >= '0' && c <= '9' && (c - '0') < base) {
      digit = c - '0';
    } else if (base == 16) {
      if (c >= 'a' && c <= 'f')
        digit = c - 'a' + 10;
      else if (c >= 'A' && c <= 'F')
        digit = c - 'A' + 10;
    }
    if (digit >= 0) {
      value = value * base + digit;
      (*str)++;
      chars_read++;
    }
  }
  if (chars_read != 0 && !tok->suppress) {
    if (tok->length_modifier == LEN_H) {
      *va_arg(*args, unsigned short *) = (unsigned short)value;
    } else if (tok->length_modifier == LEN_L) {
      *va_arg(*args, unsigned long *) = (unsigned long)value;
    } else if (tok->length_modifier == LEN_LL) {
      *va_arg(*args, unsigned long long *) = value;
    } else {
      *va_arg(*args, unsigned int *) = (unsigned int)value;
    }
    res = 1;
  }
  return res;
}

static int parse_float(const char **str, const fmt_token_t *tok,
                       va_list *args) {
  while (isspace((unsigned char)**str)) (*str)++;
  double value = 0.0;
  int sign = 1, chars_read = 0, res = 0,
      max_width = tok->width ? tok->width : INT_MAX;
  if (max_width > 0 && (**str == '-' || **str == '+')) {
    sign = (**str == '-') ? -1 : 1;
    (*str)++;
    chars_read++;
    max_width--;
  }
  while (chars_read < max_width && isdigit(**str)) {
    value = value * 10.0 + (**str - '0');
    (*str)++;
    chars_read++;
  }
  if (chars_read < max_width && **str == '.') {
    (*str)++;
    chars_read++;
    double fraction = 0.1;
    int fraction_digits = 0;
    while (chars_read < max_width && isdigit(**str)) {
      value += (**str - '0') * fraction;
      fraction *= 0.1;
      (*str)++;
      chars_read++;
      fraction_digits++;
    }
  }
  if (chars_read < max_width && (**str == 'e' || **str == 'E')) {
    (*str)++;
    chars_read++;
    int exp_sign = 1;
    if (chars_read < max_width && (**str == '-' || **str == '+')) {
      exp_sign = (**str == '-') ? -1 : 1;
      (*str)++;
      chars_read++;
    }
    int exponent = 0;
    while (chars_read < max_width && isdigit(**str)) {
      exponent = exponent * 10 + (**str - '0');
      (*str)++;
      chars_read++;
    }
    value *= pow(10.0, exp_sign * exponent);
  }
  value *= sign;
  if (chars_read != 0 && !tok->suppress) {
    if (tok->length_modifier == LEN_LD) {
      *va_arg(*args, long double *) = (long double)value;
    } else if (tok->length_modifier == LEN_L) {
      *va_arg(*args, double *) = (double)value;
    } else {
      *va_arg(*args, float *) = (float)value;
    }
    res = 1;
  }
  return res;
}

static int parse_octal(const char **str, const fmt_token_t *tok,
                       va_list *args) {
  while (isspace((unsigned char)**str)) (*str)++;
  int res = 0;
  if (**str >= '0' && **str <= '7') {
    unsigned long long value = 0;
    while (**str >= '0' && **str <= '7') {
      value = value * 8 + (**str - '0');
      (*str)++;
    }
    if (!tok->suppress) {
      if (tok->length_modifier == LEN_H) {
        *va_arg(*args, unsigned short *) = (unsigned short)value;
      } else if (tok->length_modifier == LEN_L) {
        *va_arg(*args, unsigned long *) = (unsigned long)value;
      } else {
        *va_arg(*args, unsigned int *) = (unsigned int)value;
      }
      res = 1;
    }
  }
  return res;
}

static int parse_pointer(const char **str, const fmt_token_t *tok,
                         va_list *args) {
  while (isspace((unsigned char)**str)) (*str)++;
  if (s21_strncmp(*str, "0x", 2) == 0 || s21_strncmp(*str, "0X", 2) == 0) {
    *str += 2;
  }
  unsigned long long value = 0;
  int chars_read = 0, res = 0, parsing = 1,
      max_width = tok->width ? tok->width : INT_MAX;
  while (chars_read < max_width && parsing) {
    char c = **str;
    int digit = char_to_digit(c, 16);
    if (digit == -1) {
      parsing = 0;
    } else {
      value = value * 16 + digit;
      (*str)++;
      chars_read++;
    }
  }
  if (chars_read > 0 && !tok->suppress) {
    void **arg_ptr = va_arg(*args, void **);
    *arg_ptr = (void *)(uintptr_t)value;
    res = 1;
  }
  return res;
}

static int char_to_digit(char c, int base) {
  int digit = -1;
  if (c >= '0' && c <= '9') {
    digit = c - '0';
  } else if (c >= 'a' && c <= 'f') {
    digit = c - 'a' + 10;
  } else if (c >= 'A' && c <= 'F') {
    digit = c - 'A' + 10;
  }
  if (digit >= base) {
    digit = -1;
  }
  return digit;
}

static int parse_count(const char **str, const fmt_token_t *tok,
                       va_list *args) {
  if (!tok->suppress) {
    *va_arg(*args, int *) = (int)(*str - tok->start_ptr);
  }
  return 0;
}