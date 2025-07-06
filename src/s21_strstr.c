#include "../headers/s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
    // if any of the strings points to null, then we return null
    if (needle == S21_NULL || haystack == S21_NULL) {
        return S21_NULL;
    }

    // if the needle is empty, we return the entire haystack.
    if (*needle == '\0') {
        return (char *)haystack;
    }

    // walking through a haystack
    for (; *haystack; haystack++) {
        // initialization of constant pointers to the first elements of the needle and haystack
        const char *h = haystack;
        const char *n = needle;

        // the characters are compared until the needle runs out or there is no discrepancy
        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }

        // if the end of the needle has been reached, then the first occurrence of the substring has been found
        if (*n == '\0') {
            return (char *)haystack;
        }
    }

    // the needle wasn't in the haystack
    return S21_NULL;
}