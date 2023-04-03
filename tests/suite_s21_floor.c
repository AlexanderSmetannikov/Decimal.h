#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_s21_floor_1) {
  s21_decimal num = {{15, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal num = {{19, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal num = {{155, 0, 0, 131072}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal num = {{15, 0, 0, 2147549184u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal num = {{268435457, 1042612833, 542101086, 2149318656u}};
  s21_decimal res = {{2, 0, 0, 2147483648u}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal num = {{0, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal num = {{21, 0, 0, MINUS}};
  s21_decimal res = {{3, 0, 0, MINUS}};
  set_exp(&num.bits[SCALE], 1);
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(verter_floor_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "553402 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_floor_2) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "553403 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_floor_3) {
  s21_decimal x = {{33, 2, 3000, -2146107392}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_floor(x, &z);
  char ourRes[1000], expect[1000] = "56 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_floor() {
  Suite *suite = suite_create("s21_floor");
  TCase *tcase = tcase_create("case_s21_floor");

  tcase_add_test(tcase, test_s21_floor_1);
  tcase_add_test(tcase, test_s21_floor_2);
  tcase_add_test(tcase, test_s21_floor_3);
  tcase_add_test(tcase, test_s21_floor_4);
  tcase_add_test(tcase, test_s21_floor_5);
  tcase_add_test(tcase, test_s21_floor_6);
  tcase_add_test(tcase, test_s21_floor_7);
  tcase_add_test(tcase, verter_floor_1);
  tcase_add_test(tcase, verter_floor_2);
  tcase_add_test(tcase, verter_floor_3);

  suite_add_tcase(suite, tcase);

  return suite;
}
