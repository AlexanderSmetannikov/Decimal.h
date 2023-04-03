#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_s21_negate_1) {
  s21_decimal num = {{1, 0, 0, 2147483648u}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(verter_negate_1) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "32444 100 343253 1507328";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_negate_2) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "1 1 1 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_negate_3) {
  s21_decimal x = {{0, 0, 0, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_negate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 2148401152";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_negate() {
  Suite *suite = suite_create("s21_negate");
  TCase *tcase = tcase_create("case_s21_negate");

  tcase_add_test(tcase, test_s21_negate_1);
  tcase_add_test(tcase, test_s21_negate_2);
  tcase_add_test(tcase, test_s21_negate_3);
  tcase_add_test(tcase, verter_negate_1);
  tcase_add_test(tcase, verter_negate_2);
  tcase_add_test(tcase, verter_negate_3);

  suite_add_tcase(suite, tcase);

  return suite;
}
