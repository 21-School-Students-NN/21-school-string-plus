#include "../headers/s21_string.h"

#include <valgrind/valgrind.h>

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int res = 0;
    while (n != 0 && *str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            if (RUNNING_ON_VALGRIND)
                res = (*str1 < *str2) ? -1 : 1;
            else
                res = *str1 - *str2;
            break;
        }
        
        if (n != 1) {
            ++str1;
            ++str2;
        }
        --n;
    }
    
    return res;
}