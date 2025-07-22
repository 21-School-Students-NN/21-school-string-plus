#ifndef SSCANF_H
#define SSCANF_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>

typedef enum {
  LEN_NONE,
  LEN_HH,
  LEN_H,
  LEN_L,
  LEN_LL,
  LEN_LD,
} length_modifier_t;

typedef struct {
  int suppress;
  int width;
  length_modifier_t length_modifier;
  char specifier;
  char literal;
  const char *start_ptr;
} fmt_token_t;

typedef int (*handler_fn)(const char **src_ptr, const fmt_token_t *tok,
                          va_list *args);

typedef struct {
  char specifier;
  handler_fn func;
} dispatch_entry_t;

typedef struct {
  const char *clm;
  length_modifier_t length_modifier;
} dispatch_length_modifier;
#endif