#include "../headers/s21_string.h"
#include "./suites.h"


// Тест 1: Поиск существующей подстроки
START_TEST(test_strstr_found) {
    const char *haystack = "Hello, world!";
    const char *needle = "world";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_nonnull(result);  // Проверяем, что не NULL
    ck_assert_str_eq(result, "world!");  // Проверяем найденную подстроку
}
END_TEST

// Тест 2: Подстрока не найдена
START_TEST(test_strstr_not_found) {
    const char *haystack = "Hello, world!";
    const char *needle = "foo";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_null(result);  // Должен вернуть NULL
}
END_TEST

// Тест 3: Пустая строка needle
START_TEST(test_strstr_empty_needle) {
    const char *haystack = "Hello, world!";
    const char *needle = "";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_eq(result, haystack);  // Должен вернуть haystack
}
END_TEST

// Тест 4: needle равен haystack
START_TEST(test_strstr_needle_eq_haystack) {
    const char *haystack = "Hello";
    const char *needle = "Hello";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_eq(result, haystack);  // Должен вернуть haystack
}
END_TEST

// Тест: Сравнение s21_strstr и strstr
START_TEST(test_strstr_vs_original) {
    // Пары тестовых данных: {haystack, needle}
    const char *test_cases[][2] = {
        {"Hello, world!", "world"},    // Обычный случай
        {"abcabc", "abc"},             // Множественные вхождения
        {"short", "verylongneedle"},   // needle длиннее haystack
        {"", ""},                      // Пустые строки
        {"abc", ""},                   // Пустой needle
        {"abc", "xyz"},                // Нет вхождения
        {"mississippi", "issi"},       // Частичные совпадения
        {"aaaaa", "aa"},               // Повторяющиеся символы
        {NULL, "test"},                // haystack = NULL (UB в стандартной strstr)
        {"test", NULL},                // needle = NULL (UB в стандартной strstr)
    };

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        const char *haystack = test_cases[i][0];
        const char *needle = test_cases[i][1];

        // Пропускаем NULL-тесты, так как strstr не обрабатывает их явно
        if (haystack == NULL || needle == NULL) {
            continue;
        }

        char *original_result = strstr(haystack, needle);
        char *custom_result = s21_strstr(haystack, needle);

        if (original_result == NULL) {
            ck_assert_ptr_null(custom_result);  // Обе должны вернуть NULL
        } else {
            // Обе должны вернуть указатель на одну и ту же позицию
            ck_assert_ptr_nonnull(custom_result);
            ck_assert_int_eq(original_result - haystack, custom_result - haystack);
        }
    }
}
END_TEST

// Создаём тестовый набор
Suite *s21_strstr_suite(void) {
    Suite *s = suite_create("s21_strstr");
    TCase *tc = tcase_create("Core");

    // Добавляем тесты в test-case
    tcase_add_test(tc, test_strstr_found);
    tcase_add_test(tc, test_strstr_not_found);
    tcase_add_test(tc, test_strstr_empty_needle);
    tcase_add_test(tc, test_strstr_needle_eq_haystack);
    tcase_add_test(tc, test_strstr_vs_original);

    suite_add_tcase(s, tc);
    return s;
}