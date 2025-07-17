#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"

// TODO: remove stdio.h
#include <stdio.h>

char *s21_strerror(int errnum) {
  const char *const errlist[] = {
#define _S(n, str) [n] = str,
#include "../headers/s21_errlist.h"
#undef _S
  };

  static char errmes[64] = {0};

  if (errnum >= 0 && errnum <= S21_ERRLIST_LEN && errlist[errnum] != S21_NULL)
    return (char *)errlist[errnum];
  else {
    // TODO: change to s21_sprintf
    sprintf(errmes, "Unknown error %d", errnum);
  }
  return errmes;
}
