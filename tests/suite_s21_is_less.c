#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(decimal_is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_4) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};

  int ourRes = s21_is_less(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_6) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};

  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_less_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_less() {
  Suite *suite = suite_create("s21_is_less");
  TCase *tcase = tcase_create("case_s21_is_less");

  tcase_add_test(tcase, decimal_is_less_1);
  tcase_add_test(tcase, decimal_is_less_2);
  tcase_add_test(tcase, decimal_is_less_3);
  tcase_add_test(tcase, decimal_is_less_4);
  tcase_add_test(tcase, decimal_is_less_5);
  tcase_add_test(tcase, decimal_is_less_6);
  tcase_add_test(tcase, decimal_is_less_7);
  tcase_add_test(tcase, decimal_is_less_8);
  tcase_add_test(tcase, verter_is_less_1);
  tcase_add_test(tcase, verter_is_less_2);
  tcase_add_test(tcase, verter_is_less_3);
  tcase_add_test(tcase, verter_is_less_4);
  tcase_add_test(tcase, verter_is_less_5);

  suite_add_tcase(suite, tcase);
  return suite;
}