#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(decimal_is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_2) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_4) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_8) {
  s21_decimal x = {{0, 0, 0, MINUS}};
  s21_decimal y = {{1, 0, 0, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, MINUS}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_is_equal_10) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, MINUS}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_is_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_is_equal() {
  Suite *suite = suite_create("s21_is_equal");
  TCase *tcase = tcase_create("case_s21_is_equal");

  tcase_add_test(tcase, decimal_is_equal_1);
  tcase_add_test(tcase, decimal_is_equal_2);
  tcase_add_test(tcase, decimal_is_equal_3);
  tcase_add_test(tcase, decimal_is_equal_4);
  tcase_add_test(tcase, decimal_is_equal_5);
  tcase_add_test(tcase, decimal_is_equal_6);
  tcase_add_test(tcase, decimal_is_equal_7);
  tcase_add_test(tcase, decimal_is_equal_8);
  tcase_add_test(tcase, decimal_is_equal_9);
  tcase_add_test(tcase, decimal_is_equal_10);

  tcase_add_test(tcase, verter_is_equal_1);
  tcase_add_test(tcase, verter_is_equal_2);
  tcase_add_test(tcase, verter_is_equal_3);
  tcase_add_test(tcase, verter_is_equal_4);
  tcase_add_test(tcase, verter_is_equal_5);

  suite_add_tcase(suite, tcase);
  return suite;
}