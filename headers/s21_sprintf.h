#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

// configuration for formatting string in sscanf and sprintf
typedef struct {
  int width;
  int precision;
  int flags;
  char length;
} format_config;

#endif // S21_SPRINTF_H