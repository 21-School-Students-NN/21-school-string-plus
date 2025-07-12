#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/s21_string.h"
#include "./suites.h"

START_TEST(test_sscanf_basic) {
  const char *str = "42 Hello";
  int d1, d2;
  char s1[20], s2[20];

  int res1 = s21_sscanf(str, "%d %19s", &d1, s1);
  int res2 = sscanf(str, "%d %19s", &d2, s2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_float) {
  const char *str = "3.14 -0.5";
  float f1, f2, f3, f4;

  int res1 = s21_sscanf(str, "%f %f", &f1, &f2);
  int res2 = sscanf(str, "%f %f", &f3, &f4);

  ck_assert_int_eq(res1, res2);
  ck_assert(fabs(f1 - f3) < 1e-6);
  ck_assert(fabs(f2 - f4) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_int_formats) {
  const char *str = "42 -42 052 0x2A";
  int a1, b1, c1, d1;
  int a2, b2, c2, d2;

  int res1 = s21_sscanf(str, "%d %i %i %i", &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, "%d %i %i %i", &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  const char *str = "42 052 0x2A 4294967295";
  unsigned u1, o1, x1, max1;
  unsigned u2, o2, x2, max2;

  int res1 = s21_sscanf(str, "%u %o %x %u", &u1, &o1, &x1, &max1);
  int res2 = sscanf(str, "%u %o %x %u", &u2, &o2, &x2, &max2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_uint_eq(o1, o2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(max1, max2);
}
END_TEST

START_TEST(test_sscanf_width) {
  const char *str = "1234567890";
  int a1, b1, c1;
  int a2, b2, c2;

  int res1 = s21_sscanf(str, "%3d%2d%5d", &a1, &b1, &c1);
  int res2 = sscanf(str, "%3d%2d%5d", &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_n_specifier) {
  const char *str = "12345";
  int d1, d2, n1 = 0, n2 = 0;

  int res1 = s21_sscanf(str, "%d%n", &d1, &n1);
  int res2 = sscanf(str, "%d%n", &d2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_partial_match) {
  const char *str = "abc 123 def";
  int d1, d2;
  char s1[20], s2[20];

  int res1 = s21_sscanf(str, "%d %19s", &d1, s1);
  int res2 = sscanf(str, "%d %19s", &d2, s2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_empty_input) {
  const char *str = "";
  int d1, d2;

  int res1 = s21_sscanf(str, "%d", &d1);
  int res2 = sscanf(str, "%d", &d2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_hex) {
  const char *str = "0x1a 1A deadBEEF";
  int i1, i2;
  unsigned u1, u2;
  unsigned long ul1, ul2;

  int res1 = s21_sscanf(str, "%i %x %lX", &i1, &u1, &ul1);
  int res2 = sscanf(str, "%i %x %lX", &i2, &u2, &ul2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(i1, i2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(test_sscanf_pointer) {
  void *p1, *p2;
  const char *str = "0x7ffd1234";

  int res1 = s21_sscanf(str, "%p", &p1);
  int res2 = sscanf(str, "%p", &p2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(test_sscanf_percent) {
  const char *str = "42%";
  int res1 = s21_sscanf(str, "42%%");
  int res2 = sscanf(str, "42%%");

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_char) {
  const char *str = "abc";
  char c1, c2, c3;
  char d1, d2, d3;

  int res1 = s21_sscanf(str, "%c%c%c", &c1, &c2, &c3);
  int res2 = sscanf(str, "%c%c%c", &d1, &d2, &d3);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, d1);
  ck_assert_int_eq(c2, d2);
  ck_assert_int_eq(c3, d3);
}
END_TEST

START_TEST(test_sscanf_char_width) {
  const char *str = "abc";
  char s1[3], s2[3];

  int res1 = s21_sscanf(str, "%2c", s1);
  int res2 = sscanf(str, "%2c", s2);

  ck_assert_int_eq(res1, res2);
  s1[2] = s2[2] = '\0';
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_long) {
  const char *str = "123456789 987654321";
  long l1, l2;
  long m1, m2;

  int res1 = s21_sscanf(str, "%ld %ld", &l1, &l2);
  int res2 = sscanf(str, "%ld %ld", &m1, &m2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(l1, m1);
  ck_assert_int_eq(l2, m2);
}
END_TEST

START_TEST(test_sscanf_short) {
  const char *str = "123 456";
  short s1, s2;
  short t1, t2;

  int res1 = s21_sscanf(str, "%hd %hd", &s1, &s2);
  int res2 = sscanf(str, "%hd %hd", &t1, &t2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(s1, t1);
  ck_assert_int_eq(s2, t2);
}
END_TEST

START_TEST(test_sscanf_scientific) {
  const char *str = "1.23e4 -5.67E-8";
  float f1, f2, f3, f4;

  int res1 = s21_sscanf(str, "%e %e", &f1, &f2);
  int res2 = sscanf(str, "%e %e", &f3, &f4);

  ck_assert_int_eq(res1, res2);
  ck_assert(fabs(f1 - f3) < 1e-6);
  ck_assert(fabs(f2 - f4) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_ignore) {
  const char *str = "42 hello 3.14";
  float f1, f2;

  int res1 = s21_sscanf(str, "%*d %*s %f", &f1);
  int res2 = sscanf(str, "%*d %*s %f", &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert(fabs(f1 - f2) < 1e-6);
}
END_TEST

START_TEST(test_sscanf_boundary) {
  const char *str = "2147483647 -2147483648 4294967295";
  int max1, min1;
  unsigned umax1;
  int max2, min2;
  unsigned umax2;

  int res1 = s21_sscanf(str, "%d %d %u", &max1, &min1, &umax1);
  int res2 = sscanf(str, "%d %d %u", &max2, &min2, &umax2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(max1, max2);
  ck_assert_int_eq(min1, min2);
  ck_assert_uint_eq(umax1, umax2);
}
END_TEST

START_TEST(test_sscanf_binary) {
  unsigned char data[] = {0x01, 0x02, 0x03, 0x04, '\0'};
  const char *str = (const char *)data;
  char buf1[4], buf2[4];

  int res1 = s21_sscanf(str, "%4c", buf1);
  int res2 = sscanf(str, "%4c", buf2);

  ck_assert_int_eq(res1, res2);
  ck_assert_mem_eq(buf1, buf2, 4);
}
END_TEST

START_TEST(test_sscanf_mismatch) {
  const char *str = "abc 123";
  int d1, d2;

  int res1 = s21_sscanf(str, "xyz %d", &d1);
  int res2 = sscanf(str, "xyz %d", &d2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_return_value) {
  const char *str = "10 20 30";
  int a1, b1, c1;
  int a2, b2, c2;

  int res1 = s21_sscanf(str, "%d %d %d", &a1, &b1, &c1);
  int res2 = sscanf(str, "%d %d %d", &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_sscanf_octal) {
  const char *str = "52 755";
  unsigned o1, o2;
  unsigned o3, o4;

  int res1 = s21_sscanf(str, "%o %o", &o1, &o2);
  int res2 = sscanf(str, "%o %o", &o3, &o4);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(o1, o3);
  ck_assert_uint_eq(o2, o4);
}
END_TEST

START_TEST(test_sscanf_unsigned_long) {
  const char *str = "4294967295 18446744073709551615";
  unsigned long ul1, ul2;
  unsigned long ul3, ul4;

  int res1 = s21_sscanf(str, "%lu %lu", &ul1, &ul2);
  int res2 = sscanf(str, "%lu %lu", &ul3, &ul4);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(ul1, ul3);
}
END_TEST

START_TEST(test_sscanf_double) {
  const char *str = "3.1415926535 -2.71828";
  double d1, d2;
  double d3, d4;

  int res1 = s21_sscanf(str, "%lf %lf", &d1, &d2);
  int res2 = sscanf(str, "%lf %lf", &d3, &d4);

  ck_assert_int_eq(res1, res2);
  ck_assert(fabs(d1 - d3) < 1e-9);
  ck_assert(fabs(d2 - d4) < 1e-9);
}
END_TEST

START_TEST(test_sscanf_string_width) {
  const char *str = "HelloWorld";
  char s1[10], s2[10];
  char s3[10], s4[10];

  int res1 = s21_sscanf(str, "%5s%5s", s1, s2);
  int res2 = sscanf(str, "%5s%5s", s3, s4);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s3);
  ck_assert_str_eq(s2, s4);
}
END_TEST

START_TEST(test_sscanf_mixed_types) {
  const char *str = "Int:42 Float:3.14 String:Test";
  int i1, i2;
  float f1, f2;
  char s1[10], s2[10];

  int res1 = s21_sscanf(str, "Int:%d Float:%f String:%9s", &i1, &f1, s1);
  int res2 = sscanf(str, "Int:%d Float:%f String:%9s", &i2, &f2, s2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(i1, i2);
  ck_assert(fabs(f1 - f2) < 1e-6);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_i_specifier) {
  const char *str = "42 052 0x2A";
  int i1, i2, i3;
  int j1, j2, j3;

  int res1 = s21_sscanf(str, "%i %i %i", &i1, &i2, &i3);
  int res2 = sscanf(str, "%i %i %i", &j1, &j2, &j3);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(i1, j1);
  ck_assert_int_eq(i2, j2);
  ck_assert_int_eq(i3, j3);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("sscanf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_basic);
  tcase_add_test(tc, test_sscanf_float);
  tcase_add_test(tc, test_sscanf_int_formats);
  tcase_add_test(tc, test_sscanf_unsigned);
  tcase_add_test(tc, test_sscanf_width);
  tcase_add_test(tc, test_sscanf_n_specifier);
  tcase_add_test(tc, test_sscanf_partial_match);
  tcase_add_test(tc, test_sscanf_empty_input);
  tcase_add_test(tc, test_sscanf_hex);
  tcase_add_test(tc, test_sscanf_pointer);
  tcase_add_test(tc, test_sscanf_percent);
  tcase_add_test(tc, test_sscanf_char);
  tcase_add_test(tc, test_sscanf_char_width);
  tcase_add_test(tc, test_sscanf_long);
  tcase_add_test(tc, test_sscanf_short);
  tcase_add_test(tc, test_sscanf_scientific);
  tcase_add_test(tc, test_sscanf_ignore);
  tcase_add_test(tc, test_sscanf_boundary);
  tcase_add_test(tc, test_sscanf_binary);
  tcase_add_test(tc, test_sscanf_mismatch);
  tcase_add_test(tc, test_sscanf_return_value);
  tcase_add_test(tc, test_sscanf_octal);
  tcase_add_test(tc, test_sscanf_unsigned_long);
  tcase_add_test(tc, test_sscanf_double);
  tcase_add_test(tc, test_sscanf_string_width);
  tcase_add_test(tc, test_sscanf_mixed_types);
  tcase_add_test(tc, test_sscanf_i_specifier);

  suite_add_tcase(s, tc);
  return s;
}