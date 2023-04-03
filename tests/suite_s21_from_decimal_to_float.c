#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_from_dec_to_float_1) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exp(&(x.bits[3]), 3);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = 15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_dec_to_float_2) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exp(&(x.bits[3]), 3);
  x.bits[3] = set_bit(x.bits[3], 31);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -15.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_dec_to_float_3) {
  s21_decimal x = {{15008, 0, 0, 0}};
  set_exp(&(x.bits[3]), 3);
  x.bits[3] = set_bit(x.bits[3], 31);
  float res1 = 0;
  int n1 = s21_from_decimal_to_float(x, NULL);
  float res2 = 0;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_dec_to_float_4) {
  s21_decimal x = {{1505345008, 0, 0, 0}};
  set_exp(&(x.bits[3]), 3);
  x.bits[3] = set_bit(x.bits[3], 31);
  float res1;
  int n1 = s21_from_decimal_to_float(x, &res1);
  float res2 = -1505345.008;
  ck_assert_float_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *suite_s21_from_decimal_to_float() {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *tcase = tcase_create("case_s21_from_decimal_to_float");

  tcase_add_test(tcase, test_from_dec_to_float_1);
  tcase_add_test(tcase, test_from_dec_to_float_2);
  tcase_add_test(tcase, test_from_dec_to_float_3);
  tcase_add_test(tcase, test_from_dec_to_float_4);

  suite_add_tcase(suite, tcase);

  return suite;
}
