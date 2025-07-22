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
static int parse_format(const char **format, const char **str, va_list *args);
static int function_for_specifier(const char **str,
                                  const dispatch_entry_t *dispatch_table,
                                  const int d_t_size, fmt_token_t *tok,
                                  va_list *args);
static void space_skip(const char **format, const char **str);
static int processing_specifiers(const char **format, fmt_token_t *tok,
                                 const int length_modifier_t_size,
                                 const dispatch_length_modifier *lmt);
static int skip_before_fspec(const char **format, const char **str,
                             const fmt_token_t *tok);
static int char_to_digit(char c, int base);

int s21_sscanf(const char *str, const char *format, ...) {
  if (str == S21_NULL || format == S21_NULL || *str == '\0') {
    return S21_EOF;
  }
  va_list args;
  va_start(args, format);
  int res = parse_format(&format, &str, &args);
  va_end(args);
  return res;
}
static int parse_format(const char **format, const char **str, va_list *args) {
  fmt_token_t tok;
  init_fmt_token(&tok);
  dispatch_entry_t dispatch_table[] = {
      {'c', parse_char},   {'d', parse_int},     {'i', parse_int},
      {'e', parse_float},  {'E', parse_float},   {'f', parse_float},
      {'g', parse_float},  {'G', parse_float},   {'o', parse_octal},
      {'s', parse_string}, {'u', parse_uint},    {'x', parse_uint},
      {'X', parse_uint},   {'p', parse_pointer}, {'n', parse_count}};

  dispatch_length_modifier lmt[] = {{"h", LEN_H},  {"hh", LEN_HH},
                                    {"l", LEN_L},  {"ll", LEN_LL},
                                    {"L", LEN_LD}, {"", LEN_NONE}};
  int flag = 1;
  int status_proc_spec = 0;
  int counter = 0;
  const char *fp = *format;
  const char *strp = *str;
  tok.start_ptr = strp;
  const int dispatch_table_size =
      sizeof(dispatch_table) / sizeof(dispatch_table[0]);
  const int length_modifier_t_size = sizeof(lmt) / sizeof(lmt[0]);
  while (flag) {
    space_skip(&fp, &strp);
    int whats_next = skip_before_fspec(&fp, &strp, &tok);
    if (whats_next == 2) {
      status_proc_spec =
          processing_specifiers(&fp, &tok, length_modifier_t_size, lmt);
    } else {
      flag = 0;
    }
    if (flag && status_proc_spec) {
      int res = function_for_specifier(&strp, dispatch_table,
                                       dispatch_table_size, &tok, args);
      if (res == 0 && !tok.suppress) {
        flag = 0;
      } else {
        counter += res;
      }
    }
  }
  return counter;
}
static int function_for_specifier(const char **str,
                                  const dispatch_entry_t *dispatch_table,
                                  const int d_t_size, fmt_token_t *tok,
                                  va_list *args) {
  int res = 0;
  for (int i = 0; i < d_t_size; i++) {
    if (dispatch_table[i].specifier == tok->specifier) {
      res = dispatch_table[i].func(str, tok, args);
    }
  }
  return res;
}
static void space_skip(const char **format, const char **str) {
  const char *fp = *format;
  const char *strp = *str;
  if (isspace((unsigned char)*fp)) {
    while (isspace((unsigned char)*fp)) fp++;
    while (isspace((unsigned char)*strp)) strp++;
  }
  *format = fp;
  *str = strp;
}

static int processing_specifiers(const char **format, fmt_token_t *tok,
                                 const int lmts,
                                 const dispatch_length_modifier *lmt) {
  init_fmt_token(tok);
  const char *fp = *format;
  int success = 1;
  if (*fp == '*') {
    tok->suppress = 1;
    fp++;
  }
  while (isdigit((unsigned char)*fp)) {
    tok->width = tok->width * 10 + (*fp - '0');
    fp++;
  }
  for (int i = 0; i < lmts; i++) {
    if (s21_strncmp(fp, lmt[i].clm, s21_strlen(lmt[i].clm)) == 0) {
      tok->length_modifier = lmt[i].length_modifier;
      fp += s21_strlen(lmt[i].clm);
      break;
    }
  }
  if (*fp != '\0' && s21_strchr("diouxXfFeEgGaAcspn", *fp)) {
    tok->specifier = *fp;
    fp++;
  } else {
    success = 0;
  }
  *format = fp;
  return success;
}
static int skip_before_fspec(const char **format, const char **str,
                             const fmt_token_t *tok) {
  int fl = 0;  // discrepancy=1, start_fspec=2, the end=0.
  const char *fp = *format;
  const char *strp = *str;
  while (*fp && tok->specifier != 'n') {
    if (*fp == '%' && *(fp + 1) != '%') {
      fp++;
      fl = 2;
      break;
    } else if (*fp == '%' && *(fp + 1) == '%') {
      if (*strp == '%') {
        fp += 2;
        strp++;
      } else {
        fl = 1;
        break;
      }
    } else if (*fp == *strp) {
      fp++;
      strp++;
    } else {
      fl = 1;
      break;
    }
  }
  *format = fp;
  *str = strp;
  return fl;
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