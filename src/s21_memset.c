#include "../headers/s21_errno.h"
#include "../headers/s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr =
      (unsigned char *)str;  // Cast void* to unsigned char* for byte access
  unsigned char ch =
      (unsigned char)c;  // Use only the least significant byte of c
  // Loop through the memory block and set each byte
  // Check if n > than str size
  int len = sizeof(str);
  if (len > (int)n) 
        n = len;
  
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = ch;
  }

  return str;
}
