#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_s21_truncate_1) {
  s21_decimal num = {{15, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal num = {{2818572289u, 2606532082u, 1355252715, 2149318656u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal num = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_4) {
  s21_decimal num = {{0, 0, 0, MINUS}};
  s21_decimal res = {{0, 0, 0, MINUS}};
  int error = 0;
  error = s21_truncate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_truncate_5) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_truncate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(verter_truncate_1) {
  s21_decimal x = {{32444, 100, 343253, -2145976320}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "63 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_truncate_2) {
  s21_decimal x = {{1, 1, 1, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "184467 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_truncate_3) {
  s21_decimal x = {{0, 0, 0, 851968}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_truncate(x, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_truncate() {
  Suite *suite = suite_create("s21_truncate");
  TCase *tcase = tcase_create("case_s21_truncate");

  tcase_add_test(tcase, test_s21_truncate_1);
  tcase_add_test(tcase, test_s21_truncate_2);
  tcase_add_test(tcase, test_s21_truncate_3);
  tcase_add_test(tcase, test_s21_truncate_4);
  tcase_add_test(tcase, test_s21_truncate_5);
  tcase_add_test(tcase, verter_truncate_1);
  tcase_add_test(tcase, verter_truncate_2);
  tcase_add_test(tcase, verter_truncate_3);

  suite_add_tcase(suite, tcase);

  return suite;
}
