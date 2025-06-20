#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"
#inclu
char *strstr(const char *haystack, const char *needle)
{
    if(needle == "\0")
    {
        return (char*) haystack;
    }
    
}