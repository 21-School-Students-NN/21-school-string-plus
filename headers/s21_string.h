#ifndef S21_STRING_H
#define S21_STRING_H

// Define custom size_t based on platform
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__)
// 64-bit systems
typedef unsigned long long s21_size_t;
#elif defined(_WIN32) || defined(__i386__) || defined(__arm__)
// 32-bit systems
typedef unsigned int s21_size_t;
#else
// Default fallback (can be adjusted based on your target platform)
typedef unsigned long s21_size_t;
#endif

// Define our own NULL macro
#define S21_NULL ((void *)0)

/** @brief Just an example function which prints "Hello, world!"
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date June 4, 2025
 * @version 1.0
 * @return void
 * @note Notice how this comment made - you should also do it for yours func's.
*/
void s21_example_func(void);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
/** @brief Fill memory with a constant byte
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date June 16, 2025
 * @version 1.0
 * @return void *
 * @note Actually, it returns *dest
*/
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif
