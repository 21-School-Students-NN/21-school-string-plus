#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  // Cast void* to unsigned char* for byte access
  unsigned char *ptr = (unsigned char *)str;
  // Use only the least significant byte of c
  unsigned char ch = (unsigned char)c;
  // Loop through the memory block and set each byte
  // NOTE: memset function should trust the caller to provide
  //    a valid n that doesn’t exceed the buffer’s size,
  //    as per the C standard (7.24.6.1).
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = ch;
  }

  return str;
}
