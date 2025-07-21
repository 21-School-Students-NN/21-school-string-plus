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
 * @brief Constant indicating end-of-file or input failure.
 * @details `S21_EOF` is returned by functions like `s21_sscanf()` when no input
 * items are successfully matched. It is equivalent to the standard `EOF`,
 * defined as -1.
 *
 * @version 1.0
 * @date July 11, 2025
 * @author Amfir (s21: tyananai)
 */
#define S21_EOF -1

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
 * @author Evgeniy Parfenyuk (Parthen/rhydonte) x Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 * @date Jule 17, 2025
 * @version 1.0
 * @return return a pointer to the matching byte or S21_NULL
 * 	 if the character does not occur in the given memory area.
 */
void *s21_memchr(const void *str, int c, s21_size_t n);

/**
 * @brief compares the first n bytes of str1 and str2.
 * @return an integer less than, equal to, or greater than zero if the first n
 bytes of s1 is found, respectively, to be less than, to match, or be greater
 than the first n bytes of s2.
 *
 * @version 1.0
 * @date June 12, 2025
 * @author Amfir (s21: tyananai)
 */
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
 * @return the `s21_strncmp()` function return an integer less than, equal to,
 * or greater than zero if first n bytes `str1` is found, respectively, to be
 * less than, to match, or be greater than `str2`
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
 * @return The `s21_strcspn()` function returns the number of bytes in the
 * initial segment of  `str1`  which  are  not  in  the string `str2`.
 *
 * @version 0.8
 * @date June 21, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 Scool)
 */
s21_size_t s21_strcspn(const char *str1, const char *str2);

/**
 * @brief calculate the length of a string
 * @return the `s21_strlen()` function returns the number of bytes in the string
 * pointed to by `str`.
 *
 * @version 0.8
 * @date June 19, 2025
 * @author Demian Domozhirov (DarkDomian | trelawnm at 21 School)
 */
s21_size_t s21_strlen(const char *str);

/**
 * @brief search a string for any of a set of bytes
 * @return The `s21_strpbrk()` function returns a pointer to the byte in `str1`
 * that matches one of the bytes in `str2`, or `S21_NULL` if no such byte is
 * found.
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

/**
 * @brief locate a substring
 * @return These functions return a pointer to the beginning of the located substring, or `S21_NULL` if the substring is not found.
 *
 * @version 1.0
 * @date June 20, 2025
 * @author Mark Mindrin (@GOOD3113)
 */
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
 * @brief sends formatted output to a string pointed to, by str
 * @param str pointer to string
 * @param format pointer to format source string
 * @param ... multiple arguments according to format string
 * @date July 01, 2025
 * @author Anton Gashturi (bernieer)
 */
int s21_sprintf(char *str, const char *format, ...);

/**
 * @brief Returns
 * @brief Parses formatted input from a string.
 * @return The `s21_sscanf()` function returns the number of input items
 * successfully matched and assigned, or `-1` (EOF) if an input failure occurs
 * before any assignment.
 *
 * @version 1.0
 * @date July 11, 2025
 * @author Amfir (s21: tyananai)
 */
int s21_sscanf(const char *str, const char *format, ...);

 /** @brief Returns
 * @return a pointer to new string in which all leading and trailing
 * occurrences of
 * @param trim_chars a set of specified characters from
 * @param src the given string are removed.
 * In case of any error, return NULL.
 * @date July 11, 2025
 * @author Anton Gashturi (bernieer)
 */
void *s21_trim(const char *src, const char *trim_chars);

/** @brief Returns a new string in which a specified
 * @param str string is inserted at
 * @param start_index a specified index position in
 * @param src the given string
 * @author Anton Gashturi (Parthen/rhydonte)
 * @return a pointer to `dest`
 * @date July 8, 2025
 * @version 1.0
 */
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

/**
 * @brief returns a copy of string (str) converted to lowercase
 * @return void* pointer to a copy of string (str) converted to lowercase. In
 * case of any error, return NULL
 * @param str source string
 * @version 1.0
 * @date July 8, 2025
 * @author Anton Gashturi (bernieer)
 */
void *s21_to_lower(const char *str);

/**
 * @brief Returns a copy of string (str) converted to uppercase
 * @param str pointer to source string
 * @return pointer to destination string
 * @date July 07, 2025
 * @author Anton Gashturi (bernieer)
 */
void *s21_to_upper(const char *str);

#endif
