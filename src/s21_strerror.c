#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"

#include <string.h>

/**
 * @brief get error message string
 * @return a pointer to a string that describes the error code passed in  the
 * argument  errnum
 *
 * @version 1.0
 * @date June 6, 2025
 * @author Demian Domozhirov (DarkDomian/trelawnm)
 */
char *s21_strerror(int errnum) {
  const char *const errlist[] = {
#define _S(n, str) [n] = str,
#include "../headers/s21_errlist.h"
#undef _S
  };

  if (errnum >= 0 && errnum < S21_ERRlIST_LEN && errlist[errnum] != S21_NULL)
    return (char *)errlist[errnum];
  else
    return (char *)"Unknown error ";  // TODO: add to the returned message value
                                      // of errnum
}