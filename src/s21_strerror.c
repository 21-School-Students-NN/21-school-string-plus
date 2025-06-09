#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"

const char *const errlist[] =
  {
#define _S(n, str)         [n] = str,
#include "../headers/s21_errlist.h"
#undef _S
  };
const s21_size_t errlist_len = sizeof (errlist) / sizeof ((errlist)[0]);


/**
 * @brief get error message string
 * @return a pointer to a string that describes the error code passed in  the  argument  errnum
 * 
 * @version 1.0
 * @date June 6, 2025
 * @author Demian Domozhirov (DarkDomian/trelawnm)
 */
char *s21_strerror(int errnum) {
    if (errnum >= 0 && errnum < errlist_len)
        return errlist[errnum];
    else 
        return (char *)"Unknown error";
}