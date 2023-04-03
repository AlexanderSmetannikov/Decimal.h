#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(decimal_div_1) {
  s21_decimal x = {{310000000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "310000000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_div_2) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(decimal_div_3) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_4) {
  s21_decimal x = {{52525252, 0, 0, 2147483648}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_5) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_6) {
  s21_decimal x = {{52525252, 0, 0, 8845}};
  s21_decimal y = {{0, 0, 0, 10}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_7) {
  s21_decimal x = {{52525252, 0, 0, 65465}};
  s21_decimal y = {{0, 0, 0, 9598595}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_8) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, MINUS}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 2);
}
END_TEST

START_TEST(decimal_div_9) {
  s21_decimal x = {{5, 0, 50, MINUS}};
  s21_decimal y = {{5, 0, 0, MINUS}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_10) {
  s21_decimal x = {{0, 0, 0, MINUS}};
  s21_decimal y = {{5, 0, 0, MINUS}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&y.bits[SCALE], 20);
  int err = 0;
  err = s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_div_11) {
  s21_decimal x = {{5, 0, 0, MINUS}};
  s21_decimal y = {{0, 0, 0, MINUS}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&y.bits[SCALE], 28);
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_div_12) {
  s21_decimal x = {{5, 0, 0, MINUS}};
  s21_decimal y = {{5, 0, 0, MINUS}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&x.bits[SCALE], 28);
  set_exp(&y.bits[SCALE], 28);
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_div_1) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_div_2) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 983040}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "100000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_div_3) {
  s21_decimal x = {{1, 1, 1, 10 << 16}};
  s21_decimal y = {{1, 10, 1, MINUS + (15 << 16)}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1019311944 458670364 542101085 2148990976";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_div_4) {
  s21_decimal x = {{1, 1, 1, 983040}};
  s21_decimal y = {{1, 1, 1, -2146500608}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_div() {
  Suite *suite = suite_create("s21_div");
  TCase *tcase = tcase_create("case_s21_div");

  tcase_add_test(tcase, decimal_div_1);
  tcase_add_test(tcase, decimal_div_2);
  tcase_add_test(tcase, decimal_div_3);
  tcase_add_test(tcase, decimal_div_4);
  tcase_add_test(tcase, decimal_div_5);
  tcase_add_test(tcase, decimal_div_6);
  tcase_add_test(tcase, decimal_div_7);
  tcase_add_test(tcase, decimal_div_8);
  tcase_add_test(tcase, decimal_div_9);
  tcase_add_test(tcase, decimal_div_10);
  tcase_add_test(tcase, decimal_div_11);
  tcase_add_test(tcase, decimal_div_12);
  tcase_add_test(tcase, verter_div_1);
  tcase_add_test(tcase, verter_div_2);
  tcase_add_test(tcase, verter_div_3);
  tcase_add_test(tcase, verter_div_4);

  suite_add_tcase(suite, tcase);

  return suite;
}
