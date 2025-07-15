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

/**
 * @brief Just an example function which prints "Hello, world!"
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date June 4, 2025
 * @version 1.0
 * @return void
 * @note Notice how this comment made - you should also do it for yours func's.
*/
void s21_example_func(void);
/**
 * @brief Finds the first occurrence of c in first n bytes of str
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date Jule 3, 2025
 * @version 1.0
 * @return return a pointer to the matching byte or S21_NULL
 * 	 if the character does not occur in the given memory area.
 */
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

/** @brief copies n bytes from memory area src to memory area dest
 * @author Anton Gashturi (Parthen/rhydonte)
 * @date June 22, 2025
 * @param dest pointer to destination area
 * @param src pointer to source area
 * @param n number of bytes to copy
 * @version 1.0
 * @return a pointer to `dest`
 * @note Notice how this comment made - you should also do it for yours func's.
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
/** @brief Fill memory with a constant byte
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date June 16, 2025
 * @version 1.0
 * @return void *
 * @note Actually, it returns *dest
*/
void *s21_memset(void *str, int c, s21_size_t n);

/**
 * @brief append non-null bytes from a source array to a string, and
 * null-terminate the result
 * @return s21_strncat() return dest
 *
 * @version 0.8
 * @date June 18, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n);
/**
 * @brief Finds the first occurrence of c in str
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date June 19, 2025
 * @version 1.0
 * @return the `s21_strchr()` function return a pointer to the matched character
 *   or S21_NULL if the character is not found.
 */
char *s21_strchr(const char *str, int c);

/**
 * @brief compare only the first (at most) `n` bytes of `str1` and `str2`
 * @return the `s21_strncmp()` function return an integer less than, equal to, or greater than zero if
 * first n bytes `str1` is found, respectively, to be less than, to match, or be greater than `str2`
 *
 * @version 1.0
 * @date June 21, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/**
 * @brief fill a fixed-size buffer with non-null bytes from a string, padding
 * with null bytes as needed
 * @param dest pointer to destination buffer
 * @param src pointer to source buffer
 * @param n the number of bytes to copy
 * @return returns pointer to `dest`
 *
 * @version 0.8
 * @date June 22, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

/**
 * @brief get error message string
 * @return a pointer to a string that describes the error code passed in  the
 * argument  errnum
 *
 * @version 1.0
 * @date June 6, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
char *s21_strerror(int errnum);

/**
 * @brief get length of a prefix substring
 * @return The `s21_strcspn()` function returns the number of bytes in the initial segment of  `str1`  which  are  not  in  the string `str2`.
 *
 * @version 0.8
 * @date June 21, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 Scool)
 */
s21_size_t s21_strcspn(const char *str1, const char *str2);

/**
 * @brief calculate the length of a string
 * @return the `s21_strlen()` function returns the number of bytes in the string pointed to by `str`.
 * 
 * @version 0.8
 * @date June 19, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
s21_size_t s21_strlen(const char *str);

/**
 * @brief search a string for any of a set of bytes
 * @return The `s21_strpbrk()` function returns a pointer to the byte in `str1` that matches one of the bytes in `str2`, or
 * `S21_NULL` if no such byte is found.
 *
 * @version 0.8
 * @date June 21, 2025
 * @author Demian Domozhirov (DarkDomian/trelawnm)
 */
char *s21_strpbrk(const char *str1, const char *str2);
/**
 * @brief Finds the last occurrence of c in str
 * @author Evgeniy Parfenyuk (Parthen/rhydonte)
 * @date Jul 2, 2025
 * @version 1.0
 * @return the `s21_strrchr()` function return a pointer to the matched character
 *   or S21_NULL if the character is not found.
 */
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);

/**
 * @brief extract tokens from strings
 * @return The `s21_strtok()` function return a pointer to the next token, or
 * `S21_NULL` if there are no more tokens.
 *
 * @version 8.0
 * @date June 19, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
char *s21_strtok(char *str, const char *delim);

/**
 * @brief Returns a copy of string (str) converted to uppercase
 * @param str pointer to source string
 * @return pointer to destination string
 * @date July 07, 2025
 * @author Anton Gashturi (bernieer)
 */
void *s21_to_upper(const char *str);

#endif